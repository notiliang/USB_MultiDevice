/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* UART4 init function */
void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  LL_USART_InitTypeDef UART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetUSARTClockSource(LL_RCC_USART234578_CLKSOURCE_PCLK1);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);

  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD);
  /**UART4 GPIO Configuration
  PD0   ------> UART4_RX
  PD1   ------> UART4_TX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_8;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  UART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  UART_InitStruct.BaudRate = 115200;
  UART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  UART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  UART_InitStruct.Parity = LL_USART_PARITY_NONE;
  UART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  UART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  UART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(UART4, &UART_InitStruct);
  LL_USART_DisableFIFO(UART4);
  LL_USART_SetTXFIFOThreshold(UART4, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(UART4, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_ConfigAsyncMode(UART4);

  /* USER CODE BEGIN WKUPType UART4 */

  /* USER CODE END WKUPType UART4 */

  LL_USART_Enable(UART4);

  /* Polling UART4 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(UART4))) || (!(LL_USART_IsActiveFlag_REACK(UART4))))
  {
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}
/* UART5 init function */
void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  LL_USART_InitTypeDef UART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetUSARTClockSource(LL_RCC_USART234578_CLKSOURCE_PCLK1);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);

  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
  /**UART5 GPIO Configuration
  PB12   ------> UART5_RX
  PB13   ------> UART5_TX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_12|LL_GPIO_PIN_13;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_14;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  UART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  UART_InitStruct.BaudRate = 115200;
  UART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  UART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  UART_InitStruct.Parity = LL_USART_PARITY_NONE;
  UART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  UART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  UART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(UART5, &UART_InitStruct);
  LL_USART_DisableFIFO(UART5);
  LL_USART_SetTXFIFOThreshold(UART5, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(UART5, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_ConfigAsyncMode(UART5);

  /* USER CODE BEGIN WKUPType UART5 */

  /* USER CODE END WKUPType UART5 */

  LL_USART_Enable(UART5);

  /* Polling UART5 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(UART5))) || (!(LL_USART_IsActiveFlag_REACK(UART5))))
  {
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
