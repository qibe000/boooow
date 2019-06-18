## pwm控制舵机

##### 1）开启 TIM1 时钟，配置 PA8 为复用输出。

 要使用 TIM1，我们必须先开启 TIM1 的时钟，这点相信大家看了这么多代码，应该明白了。
 这里我们还要配置 PA8 为复用输出（当然还要时能 PORTA 的时钟），这是因为 TIM1_CH1 通
 道将使用 PA8 的复用功能作为输出。库函数使能 TIM3 时钟的方法是：

```
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能定时器 3 时钟
```

设置 PA8 为复用功能输出的方法在前面的几个实验都有类似的讲解，相信大家很明白,这里简单 列出 GPIO 初始化的一行代码即可：

```
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
```



##### 2）设置 TIM1 的 ARR 和 PSC。

在开启了 TIM1 的时钟之后，我们要设置 ARR 和 PSC 两个寄存器的值来控制输出 PWM 的
周期。当 PWM 周期太慢（低于 50Hz）的时候，我们就会明显感觉到闪烁了。因此，PWM 周
期在这里不宜设置的太小。这在库函数是通过 TIM_TimeBaseInit 函数实现的，在上一节定时器
中断章节我们已经有讲解，这里就不详细讲解，调用的格式为：

```
TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载值
TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值
TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据指定的参数初始化 TIMx 的
```



##### 3）设置 TIM1_CH1 的 PWM 模式及通道方向, 使能 TIM1 的 CH1 输出。

接下来，我们要设置 TIM1_CH1 为 PWM 模式（默认是冻结的），因为我们的 DS0 是低电
平亮，而我们希望当 CCR1 的值小的时候，DS0 就暗，CCR1 值大的时候，DS0 就亮，所以我
们要通过配置 TIM1_CCMR1 的相关位来控制 TIM1_CH1 的模式。在库函数中，PWM 通道设
置是通过函数 TIM_OC1Init()~TIM_OC4Init()来设置的，不同的通道的设置函数不一样，这里我
们使用的是通道 1，所以使用的函数是 TIM_OC1Init()。

```
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)；
```

这种初始化格式大家学到这里应该也熟悉了，所以我们直接来看看结构体 TIM_OCInitTypeDef
的定义：

```
typedef struct
{
 uint16_t TIM_OCMode; 
 uint16_t TIM_OutputState; 
 uint16_t TIM_OutputNState;
 uint16_t TIM_Pulse; 
 uint16_t TIM_OCPolarity; 
 uint16_t TIM_OCNPolarity; 
 uint16_t TIM_OCIdleState; 
 uint16_t TIM_OCNIdleState; 
} TIM_OCInitTypeDef;

```

这里我们讲解一下与我们要求相关的几个成员变量：
参数 TIM_OCMode 设置模式是 PWM 还是输出比较，这里我们是 PWM 模式。
参数 TIM_OutputState 用来设置比较输出使能，也就是使能 PWM 输出到端口。
参数 TIM_OCPolarity 用来设置极性是高还是低。
其他的参数 TIM_OutputNState，TIM_OCNPolarity，TIM_OCIdleState 和 TIM_OCNIdleState 是
高级定时器 TIM1 和 TIM8 才用到的。
要实现我们上面提到的场景，方法是：

```
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择 PWM 模式 2
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
TIM_OC1Init(TIM1, &TIM_OCInitStructure); //初始化 TIM1 OC1
```

##### 4）使能 TIM1。

在完成以上设置了之后，我们需要使能 TIM1。使能 TIM1 的方法前面已经讲解过：

```
TIM_Cmd(TIM1, ENABLE); //使能 TIM1
```

##### 5）设置 MOE 输出，使能 PWM 输出。

普通定时器在完成以上设置了之后，就可以输出 PWM 了，但是高级定时器，我们还需要
使能刹车和死区寄存器（TIM1_BDTR）的 MOE 位，以使能整个 OCx（即 PWM）输出。库函数的设置函数为：

```
TIM_CtrlPWMOutputs(TIM1,ENABLE);// MOE 主输出使能
```

##### 6）修改 TIM1_CCR1 来控制占空比。

最后，在经过以上设置之后，PWM 其实已经开始输出了，只是其占空比和频率都是固定
的，而我们通过修改 TIM1_CCR1 则可以控制 CH1 的输出占空比。继而控制 DS0 的亮度。
在库函数中，修改 TIM1_CCR1 占空比的函数是：

```
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1)；
```

理所当然，对于其他通道，分别有一个函数名字，函数格式为 TIM_SetComparex(x=1,2,3,4)。
通过以上 6 个步骤，我们就可以控制 TIM1 的 CH1 输出 PWM 波了。

##### 7)  杂项。

```
void TIM1_PWM_Init(u16 arr,u16 psc)；
TIM_SetCompare1(TIM1, CCR)；
```

本函数中 arr 和 psc  需满足 PWM频率= 72000000 /（arr + 1）*（ psc + 1） = 50hz。

50hz=20ms，转动0°-180°所对应的占空比为2.5%-12.5%，则旋转x度的CCR = 18000 - （ 2.5 +（12.5 - 2.5 ）/ 180）*  x 。

或者可以使用CCR = ( 18000 - ( 18000 * ( 0.5+2.0 / 180 * x ) ) / 20 ) ，因为舵机控制所需的PWM宽度为0.5ms—2.5ms，宽度2ms。，也就2ms转动180°（其实准确的说舵机可以转185°）。

舵机红线连接电源正极，棕线连接开发板GND和电源负极，黄线（信号线）连接开发板PA8。