/*
 * usart.c
 *
 *  Created on: 06 apr 2017
 *      Author: Andrea
 */
#include "usart.h"

void USART2_Init()
{
	UARTHandle2.Instance			=USART2;
	UARTHandle2.Init.BaudRate		=115200;
	UARTHandle2.Init.WordLength		=UART_WORDLENGTH_8B;
	UARTHandle2.Init.StopBits		=UART_STOPBITS_1;
	UARTHandle2.Init.Parity			=UART_PARITY_NONE;
	UARTHandle2.Init.HwFlowCtl		=UART_HWCONTROL_NONE;
	UARTHandle2.Init.Mode			=UART_MODE_TX_RX;
	UARTHandle2.Init.OverSampling	=UART_OVERSAMPLING_16;

	HAL_UART_Init(&UARTHandle2);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct. Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct. Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	__HAL_RCC_USART2_FORCE_RESET();
	__HAL_RCC_USART2_RELEASE_RESET();
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);
};

