/*
 * adc.c
 *
 *  Created on: 20 apr 2017
 *      Author: Andrea
 */
#include "adc.h"

void ADC1ch6_init()
{
	AdcHandle.Instance 					=ADC1;
	AdcHandle.Init.ClockPrescaler 		=ADC_CLOCKPRESCALER_PCLK_DIV2;
	AdcHandle.Init.Resolution			=ADC_RESOLUTION_12B;
	AdcHandle.Init.ScanConvMode			=DISABLE;
	AdcHandle.Init.ContinuousConvMode	=ENABLE;
	AdcHandle.Init.DiscontinuousConvMode=DISABLE;
	AdcHandle.Init.NbrOfDiscConversion	=0;
	AdcHandle.Init.ExternalTrigConvEdge	=ADC_EXTERNALTRIGCONVEDGE_NONE;
	AdcHandle.Init.ExternalTrigConv		=ADC_SOFTWARE_START;
	AdcHandle.Init.DataAlign			=ADC_DATAALIGN_RIGHT;
	AdcHandle.Init.NbrOfConversion		=1;
	AdcHandle.Init.EOCSelection			=DISABLE;

	if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
	{
		//ADC initialization error //
		//Error_Handler();
	}
	ADC_ChannelConfTypeDef sConfig;
	/*##-2- Configure ADC regular channel #######################*/
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	sConfig.Offset = 0;

	if(HAL_ADC_ConfigChannel(&AdcHandle,&sConfig)!= HAL_OK)
	{
		assert_param(0);
		//Error_Handler();
	}
}
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin=	GPIO_PIN_6;
	GPIO_InitStruct.Mode=	GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull=	GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
}
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
	/* Reset peripherals */
	__HAL_RCC_ADC_FORCE_RESET();
	__HAL_RCC_ADC_RELEASE_RESET();
	/* Disable peripherals and GPIO Clocks */
	/*De-initialize the ADC Channel GPIO pin*/
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6);
}