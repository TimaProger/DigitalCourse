/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

  uint16_t StrCounter = 0;
  uint8_t buf = 0;
  char string[1024] = { 0 };
  char text[1025] = { 0 };
  char briefly[3] = {8, 32, 8};
  int pulse = 0;
  int dir = 10;
  _Bool flag = 0;
  char FixText[256][8] = { 0 };

  //???????????????????? ??????????????
  void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
//	  char *test = "callback\r\n";
//	  HAL_UART_Transmit(&huart1, test, strlen(test), -1);

	  if(htim == &htim2){
		  pulse += dir;
		  if(pulse == 150){
			  dir = -1;
		  } else if(pulse == 0){
			  dir = 1;
		  }
		  TIM2->CCR2 = pulse;
	  }
//	  else if(htim == &htim1){
//		  if(flag == 1){
//			  htim1.Instance->CCR1 = 750;
//			  HAL_Delay(1000);
//			  htim1.Instance->CCR1 = 250;
//			  HAL_Delay(1000);
//			  htim1.Instance->CCR1 = 250;
//			  HAL_Delay(1000);
//
//			  HAL_GPIO_WritePin(LEDTR_GPIO_Port, LEDTR_Pin, GPIO_PIN_SET);
//
//			  for(int a = 0; a < 256; a++){
//				  for(int b = 0; b < 8; b++){
//					  if(FixText[a][b] == 0){
//						  TIM1->CCR1 = 250;
//					  }else if(FixText[a][b] == 1){
//						  TIM1->CCR1 = 750;
//					  } else TIM1->CCR1 = 1000;
////					  HAL_Delay(1000);
//				  }
//			  }
//	  		  HAL_GPIO_WritePin(LEDTR_GPIO_Port, LEDTR_Pin, GPIO_PIN_RESET);
//			  char *test = "callback end\r\n";
//			  HAL_UART_Transmit(&huart1, test, strlen(test), -1);
//			  flag = 0;
//		  }
//	  }
  }

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);

	TIM2->CCR2 = 500;
	TIM2->ARR = 1000;
	  //????????????????????
	  char *hello = "\r\nAsk me:  ";
	  HAL_UART_Transmit(&huart1, hello, strlen(hello), -1);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  // ???????????????? ????????????, ???????? ???????????? ????????????????
	  if(HAL_UART_Receive(&huart1, &buf, 1, 0)== HAL_OK) {
//		  HAL_GPIO_WritePin(LEDTR_GPIO_Port, LEDTR_Pin, GPIO_PIN_SET);

		  if(buf == 127){
			  if(StrCounter != 0){
				  HAL_UART_Transmit(&huart1, &briefly, 3, -1);
				  string[--StrCounter] = 0;
			  }
		  } else {
			  HAL_UART_Transmit(&huart1, &buf, 1, -1);
			  string[StrCounter] = buf;
			  StrCounter++;
		  }



	  // ???????????????? ???????????? ???? ??????????????????
	  	  if(buf == 13){
	  		  StrCounter--;
	  		  sprintf(text, "\r\nText is: %s\r\n", string);
	  		  HAL_UART_Transmit(&huart1, text, strlen(text), -1);

	  		  char FixText[StrCounter][8];
	  		  for(uint16_t i = 0; i < StrCounter; i++){
	  			  for(uint16_t j = 0; j < 8; j++){
	  				  FixText[i][j] = 0;
	  			  }
	  		  }
			  //???????????????? ???????????? ?? PWM
//	  		  char *TR = "Transmitting...\r\n";
//	  		  HAL_UART_Transmit(&huart1, TR, strlen(TR), -1);

	  		  for(uint16_t i = 0; i < StrCounter; i++){


	  			  //???????????? ?????????????? ?? 10 ??????????????
	  			  char symbol = string[i]; // 62, 2 ,3, 4
	  			  int cell = 7;

	  			  // ?????????????? ?????????????? ?? ???????????????? ??????????????
	  			  while(symbol != 0){
	  				  if(symbol % 2 == 0){
	  					  FixText[i][cell] = 0;
	  					  symbol /= 2;
	  					  cell--;
	  				  } else {
	  					  FixText[i][cell] = 1;
	  					  symbol /= 2;
	  					  cell--;
	  				  }
	  			  }

	  		  }
  			  //???????????? ?? ???????????????? PWM
//	  		  flag = 1;

			htim1.Instance->CCR1 = 750;
			HAL_Delay(1000);
			htim1.Instance->CCR1 = 250;
			HAL_Delay(1000);
			htim1.Instance->CCR1 = 750;
			HAL_Delay(1000);

	  		  for(int a = 0; a < StrCounter; a++){
	  			  for(int b = 0; b < 8; b++){
	  				  if(FixText[a][b] == 0){
	  					  htim1.Instance->CCR1 = 250;
	  				  } else if(FixText[a][b] == 1){
	  					  htim1.Instance->CCR1 = 750;
	  				  } else htim1.Instance->CCR1 = 1000;
	  				  HAL_Delay(1000);
	  			  }
	  		  }

  			  //?????????? ???????????? ?? PWM
	  		char *EndTR = "End transmittin...\r\n";
	  		HAL_UART_Transmit(&huart1, EndTR, strlen(EndTR), -1);
	  		htim1.Instance->CCR1 = 0;

  			  // ?????????????? ??????????????
	  		  for(uint16_t k = 0; k < 1024; k++){
	  			  string[k] = 0;
	  		  }
	  		  HAL_UART_Transmit(&huart1, hello, strlen(hello), -1);
	  		  StrCounter = 0;
	  	  }

	  	  buf = 0;
//  		  HAL_GPIO_WritePin(LEDTR_GPIO_Port, LEDTR_Pin, GPIO_PIN_RESET);

	  }

//	  //?????????????? ???????????????????? ???? ??????????????
//	  uint16_t tick = __HAL_TIM_GET_COUNTER(&htim14);
//	  if(0 < tick && tick < 100){
//		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  } else {
//		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	  }




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 48000-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 480-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LEDTR_GPIO_Port, LEDTR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LEDTR_Pin */
  GPIO_InitStruct.Pin = LEDTR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LEDTR_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
