/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "lcd.h"
#include <stdlib.h>
#include "data.h"
#include "draw.h"
#include "run.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef stimestructure;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
void all_init(void);
void init_interface_info(void);
void init_interface_info_second_time(void);
void init_interface_info_new_level(void);
void draw_all_through_struct(int);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  LCD_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  int TIME = 60;
  int INTERVAL = 10;
  int current_timestamp;
  all_init();
  draw_all_through_struct(TIME);
  HAL_Delay(500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(interface.level == 0){
		  HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN);
		  interface.start_timestamp = stimestructure.Hours * 3600 + stimestructure.Minutes * 60 + stimestructure.Seconds;
	  }
	  while(1){
		  HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN);
		  current_timestamp = stimestructure.Hours * 3600 + stimestructure.Minutes * 60 + stimestructure.Seconds;
		  if(interface.life == 0 || current_timestamp - interface.start_timestamp >= TIME){break;}
		  if(interface.score !=0 && interface.score % INTERVAL == 0 && interface.level < 3 && interface.level != interface.score/INTERVAL){
			  interface.level = interface.score/INTERVAL;
			  //clear_all_enemy_plane(interface.my_plane,interface.enemy_planes);
			  //interface.boss[0] = 1;
			  break;
		  }

		  switch_my_act(interface.my_plane,interface.my_buttles);
		  update_my_buttles(interface.my_buttles);

		  if(interface.boss[0] == 0){
			  update_enemy_planes(interface.level, interface.enemy_planes);
			  generate_enemy_planes(interface.level,interface.enemy_planes);
			  check_my_plane_to_enemy_plane_collide(&(interface.score),&(interface.life),	interface.my_plane,interface.enemy_planes);
			  check_my_buttles_to_enemy_plane_collide(&(interface.score),	interface.my_buttles, interface.enemy_planes);
		  }

		  draw_all_through_struct(current_timestamp - interface.start_timestamp);
		  HAL_Delay(15);
	  }

	  if(interface.life && current_timestamp - interface.start_timestamp < TIME){
		  draw_new_level(interface.level);
		  KEY0_or_POWER_to_skip();
		  LCD_Clear(GRAY);
		  init_interface_info_new_level();
		  init_play_interface();

		  draw_all_through_struct(current_timestamp - interface.start_timestamp);
	  } else {
		  draw_end(&(interface.score),&(interface.score_2),&(interface.score_3));
		  KEY0_or_POWER_to_skip();

		  //初始界面初始�?????
		  draw_start_page();
		  KEY0_or_POWER_to_skip();
		  LCD_Clear(GRAY);

		  //游玩界面数据初始�?????
		  init_interface_info_second_time();
		  init_play_interface();

		  draw_all_through_struct(TIME);
	  }
	  //游玩界面初始�?????

	  HAL_Delay(500);
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
  /* USER CODE END RTC_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : KEY_WK_Pin */
  GPIO_InitStruct.Pin = KEY_WK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(KEY_WK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : KEY0_Pin */
  GPIO_InitStruct.Pin = KEY0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED0_Pin */
  GPIO_InitStruct.Pin = LED0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : KEY1_Pin */
  GPIO_InitStruct.Pin = KEY1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED1_Pin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void draw_all_through_struct(int limit){
	draw_play_all(interface.score,interface.life,	interface.my_plane,interface.my_buttles,	interface.boss,	interface.enemy_planes,interface.enemy_buttles, limit);
}


void all_init(void){
 	LCD_Init();
	BACK_COLOR=GRAY;

	POINT_COLOR=BLACK;//设置字体为黑�????
	LCD_Clear(GRAY);

	//初始界面初始�????
	draw_start_page();
	KEY0_or_POWER_to_skip();
	LCD_Clear(GRAY);

	//游玩界面数据初始�????
	init_interface_info();

	init_play_interface();
}



void init_interface_info(void){
	int i=0;

	interface.score = 0;
	interface.score_2 = 0;
	interface.score_3 = 0;

	interface.life = 3;

	interface.my_plane[0] = 120;	interface.my_plane[1] = 290;

	for(i=0; i<my_buttle_max; i++){
		interface.my_buttles[i][0] = 0;
		interface.my_buttles[i][1] = 0;
	}

	interface.level = 0;
	interface.boss[0] = 0;	 interface.boss[1] = 0;
	interface.boss_life = 0;

	for(i=0; i<enemy_plane_max; i++){
		interface.enemy_planes[i][0] = 0;
		interface.enemy_planes[i][1] = 0;
	}

	for(i=0; i<enemy_buttle_max; i++){
		interface.enemy_buttles[i][0] = 0;
		interface.enemy_buttles[i][1] = 0;
	}
}

void init_interface_info_second_time(void){
	int i=0;

	interface.life = 3;

	interface.my_plane[0] = 120;	interface.my_plane[1] = 290;

	for(i=0; i<my_buttle_max; i++){
		interface.my_buttles[i][0] = 0;
		interface.my_buttles[i][1] = 0;
	}

	interface.level = 0;
	interface.boss[0] = 0;	 interface.boss[1] = 0;
	interface.boss_life = 0;

	for(i=0; i<enemy_plane_max; i++){
		interface.enemy_planes[i][0] = 0;
		interface.enemy_planes[i][1] = 0;
	}

	for(i=0; i<enemy_buttle_max; i++){
		interface.enemy_buttles[i][0] = 0;
		interface.enemy_buttles[i][1] = 0;
	}
}

void init_interface_info_new_level(void){
	int i = 0;
	for(i=0; i<my_buttle_max; i++){
			interface.my_buttles[i][0] = 0;
			interface.my_buttles[i][1] = 0;
	}

	interface.boss[0] = 0;	 interface.boss[1] = 0;
	interface.boss_life = 0;

	for(i=0; i<enemy_plane_max; i++){
		interface.enemy_planes[i][0] = 0;
		interface.enemy_planes[i][1] = 0;
	}

	for(i=0; i<enemy_buttle_max; i++){
		interface.enemy_buttles[i][0] = 0;
		interface.enemy_buttles[i][1] = 0;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
