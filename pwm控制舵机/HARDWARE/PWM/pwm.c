#include "pwm.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK Mini STM32¿ª·¢°å
//PWM  Çı¶¯´úÂë			   
//ÕıµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ĞŞ¸ÄÈÕÆÚ:2010/12/03
//°æ±¾£ºV1.0
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ÕıµãÔ­×Ó 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//PWMÊä³ö³õÊ¼»¯
//arr£º×Ô¶¯ÖØ×°Öµ
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //Ê¹ÄÜGPIOÍâÉèÊ±ÖÓÊ¹ÄÜ
	                                                                     	

   //ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ,Êä³öTIM1 CH1µÄPWMÂö³å²¨ĞÎ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  ²»·ÖÆµ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»


 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_Pulse = 0; //ÉèÖÃ´ı×°Èë²¶»ñ±È½Ï¼Ä´æÆÂö³åÖµ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //¸ù¾İTIM_OCInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE Ö÷Êä³öÊ¹ÄÜ	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ô¤×°ÔØÊ¹ÄÜ	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //Ê¹ÄÜTIMxÔÚARRÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	
	TIM_Cmd(TIM1, ENABLE);  //Ê¹ÄÜTIM1
  

}
void Angle(int aaa)	
	{
		int bbb=(18000-(18000*(0.5+2.0/180*aaa))/20);
		TIM_SetCompare1(TIM1, bbb);
	}

