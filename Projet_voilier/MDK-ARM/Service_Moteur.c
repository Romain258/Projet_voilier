#include "Service_Moteur.h"


void Init_Moteur (TIM_TypeDef * Timer,GPIO_TypeDef *GPIOx){
	
	//Allumage clock
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	//Initialisation Timer
	LL_TIM_InitTypeDef TimerIn;
	TimerIn.Prescaler=20;
	TimerIn.Autoreload=1714;
	TimerIn.CounterMode=LL_TIM_COUNTERMODE_UP;
	TimerIn.RepetitionCounter=0;
	TimerIn.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	LL_TIM_Init(Timer,&TimerIn);
	
	//Initialisation GPIO(PWM)
	
	LL_GPIO_InitTypeDef GPIOIn;
	GPIOIn.Pin=LL_GPIO_PIN_1;
	GPIOIn.Mode=LL_GPIO_MODE_ALTERNATE;
	GPIOIn.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	GPIOIn.Speed=LL_GPIO_SPEED_FREQ_MEDIUM;
	LL_GPIO_Init(GPIOx,&GPIOIn);
	
	//Initialisation GPIO (Sens)
	GPIOIn.Pin=LL_GPIO_PIN_2;
	GPIOIn.Mode=LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(GPIOx,&GPIOIn);
}


void Set_Param (int angle){
	//envoi du bon sens dans le plateau
	int dutycycle;
	if (angle<50){
		LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_2);
	  dutycycle=-2*angle+100;
	}
	else if (angle>=50){
		LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_2);
	  dutycycle=2*angle-100;
	}
	//envoi de la vitesse (timer PWM)
	LL_TIM_OC_InitTypeDef Vitesse;
	Vitesse.CompareValue = -(dutycycle*2000-1714);
	Vitesse.OCMode = LL_TIM_OCMODE_PWM1;
	Vitesse.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
	Vitesse.OCState=LL_TIM_OCSTATE_ENABLE;
	Vitesse.OCNIdleState=LL_TIM_OCIDLESTATE_LOW;
	Vitesse.OCIdleState=LL_TIM_OCIDLESTATE_LOW;
	Vitesse.OCNPolarity=LL_TIM_OCPOLARITY_HIGH;
	Vitesse.OCNState=LL_TIM_OCSTATE_DISABLE;
	LL_TIM_OC_Init(TIM2,LL_TIM_CHANNEL_CH2,&Vitesse);
	LL_TIM_OC_EnablePreload(TIM2,LL_TIM_CHANNEL_CH2);
	/*LL_GPIO_AF_EnableRemap_TIM2();	
	LL_GPIO_AF_EnableEventout();
	LL_GPIO_AF_ConfigEventout(LL_GPIO_AF_EVENTOUT_PORT_A,LL_GPIO_AF_EVENTOUT_PIN_1);*/
	
}










