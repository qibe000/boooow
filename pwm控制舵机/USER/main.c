#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
//ALIENTEK Mini STM32�����巶������8
//PWM���ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

 int main(void)
 {	
	u16 led0pwmval=0;    
	u8 dir=1;	
	 
	delay_init();	    	 //��ʱ������ʼ��	  
  LED_Init();
	TIM1_PWM_Init(17999,79);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
 while(1)
	{
		int op=0;
		for(op=0;op<180;op=op+5)
		{
		Angle(op);
		delay_ms(500);
		}
		/*TIM_SetCompare1(TIM1, 195);//-90
		delay_ms(1000);
		Angle(90);
		delay_ms(1000);
		//TIM_SetCompare1(TIM1, 190);//-45
		Angle(180);
		//TIM_SetCompare1(TIM1, 185);//0
		delay_ms(1000);
		Angle(45);
		delay_ms(1000);
		Angle(0);
		delay_ms(1000);
		TIM_SetCompare1(TIM1, 180);//45
		delay_ms(1000);
		Angle(60);
		delay_ms(1000);
		TIM_SetCompare1(TIM1, 175);//90
		delay_ms(1000);
    TIM_SetCompare1(TIM1, 180);//45
		delay_ms(1000);
		TIM_SetCompare1(TIM1, 185);//0
		delay_ms(1000);
		TIM_SetCompare1(TIM1, 190);//-45
		delay_ms(1000);*/

}
}
