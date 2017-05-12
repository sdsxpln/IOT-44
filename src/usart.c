/*
 * usart.c
 *
 *  Created on: 06 apr 2017
 *      Author: Andrea
 */
#include "usart.h"

void USART1_Init()
{
		UARTHandle1.Instance			=USART1;
		UARTHandle1.Init.BaudRate		=115200;
		UARTHandle1.Init.WordLength		=UART_WORDLENGTH_8B;
		UARTHandle1.Init.StopBits		=UART_STOPBITS_1;
		UARTHandle1.Init.Parity			=UART_PARITY_NONE;
		UARTHandle1.Init.HwFlowCtl		=UART_HWCONTROL_NONE;
		UARTHandle1.Init.Mode			=UART_MODE_TX_RX;
		UARTHandle1.Init.OverSampling	=UART_OVERSAMPLING_16;

		HAL_UART_Init(&UARTHandle1);
}

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
if(huart->Instance==USART2)
{
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

	HAL_NVIC_SetPriority(USART2_IRQn,0,1);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}
else if(huart->Instance==USART1)
{
		__GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();

		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct. Alternate = GPIO_AF7_USART1;

		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct. Alternate = GPIO_AF7_USART1;

		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		HAL_NVIC_SetPriority(USART1_IRQn,0,1);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART2)
	{
	__HAL_RCC_USART2_FORCE_RESET();
	__HAL_RCC_USART2_RELEASE_RESET();
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);

	HAL_NVIC_DisableIRQ(USART2_IRQn);
	}
	else if(huart->Instance==USART1)
	{
	__HAL_RCC_USART1_FORCE_RESET();
		__HAL_RCC_USART1_RELEASE_RESET();
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

		HAL_NVIC_DisableIRQ(USART1_IRQn);
	}
};


/*
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__GPIOA_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct. Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct. Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(USART1_IRQn,0,1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	__HAL_RCC_USART1_FORCE_RESET();
	__HAL_RCC_USART1_RELEASE_RESET();
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

	HAL_NVIC_DisableIRQ(USART1_IRQn);
};
*/

UART_HandleTypeDef HandleSelect(int portNum)
{
	switch(portNum)
	{
	case 1:
		printfPort = UARTHandle1;
		break;
	case 2:
		printfPort = UARTHandle2;
		break;
	default:
	break;
	}
	return printfPort;
};
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance==USART2)
	{
		HAL_UART_Transmit(huart,(uint8_t *)aRxBuffer2,1,1);
		HAL_UART_Receive_IT(huart, (uint8_t *)aRxBuffer2,1);
	}
	else if(huart->Instance==USART1)
	{
		//BSP_LED_Toggle(LED2);
		HAL_UART_Transmit(&UARTHandle2, (uint8_t *)aRxBuffer2, 1,1);
		HAL_UART_Receive_IT(huart, (uint8_t *)aRxBuffer2,1);
	}
}
