/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SSD1963.h"
#include "xpt2046.h"
#include "stdio.h"
#include "image.h"
#include "math.h"
#include "Font_3_Tiny.h"
#include "Font_3_PicoPixel.h"
#include "Font_3_TomThumb_Extended.h"
#include "Font_5_Org.h"
#include "Font_8_Sinclair.h"
#include "Font_8_Sinclair_Inverted.h"
#include "Font_8_Tiny.h"
#include "Font_8_Myke.h"
#include "Font_8_Default.h"
#include "Font_8_Retro.h"
#include "Font_9_Mono.h"
#include "Font_9_Mono_Bold.h"
#include "Font_9_Mono_Bold_Oblique.h"
#include "Font_9_Mono_Oblique.h"
#include "Font_9_Sans.h"
#include "Font_9_Sans_Bold.h"
#include "Font_9_Sans_Bold_Oblique.h"
#include "Font_9_Sans_Oblique.h"
#include "Font_9_Serif.h"
#include "Font_9_Serif_Bold.h"
#include "Font_9_Serif_Bold_Italic.h"
#include "Font_9_Serif_Italic.h"
#include "Font_12_Mono.h"
#include "Font_12_Mono_Bold.h"
#include "Font_12_Mono_Bold_Oblique.h"
#include "Font_12_Mono_Oblique.h"
#include "Font_12_Sans.h"
#include "Font_12_Sans_Bold.h"
#include "Font_12_Sans_Bold_Oblique.h"
#include "Font_12_Sans_Oblique.h"
#include "Font_12_Serif.h"
#include "Font_12_Serif_Bold.h"
#include "Font_12_Serif_Bold_Italic.h"
#include "Font_12_Serif_Italic.h"
#include "Font_16_Arial.h"
#include "Font_16_Arial_Bold.h"
#include "Font_16_Arial_Italic.h"
#include "Font_16_Default.h"
#include "Font_16_FranklinGothic.h"
#include "Font_16_Hallfetica.h"
#include "Font_16_Nadianne.h"
#include "Font_16_Sinclair.h"
#include "Font_16_Sinclair_Inverted.h"
#include "Font_16_Swiss_Outline.h"
#include "Font_16_Matrix_Full.h"
#include "Font_16_Matrix_Full_Slash.h"
#include "Font_16_Matrix_Num.h"
#include "Font_16_Arial_Round.h"
#include "Font_16_OCR.h"
#include "Font_16_Segment_16_Full.h"
#include "Font_16_Grotesk.h"
#include "Font_16_Grotesk_Bold.h"
#include "Font_16_Retro.h"
#include "Font_18_Mono.h"
#include "Font_18_Mono_Bold.h"
#include "Font_18_Mono_Bold_Oblique.h"
#include "Font_18_Mono_Oblique.h"
#include "Font_18_Sans.h"
#include "Font_18_Sans_Bold.h"
#include "Font_18_Sans_Bold_Oblique.h"
#include "Font_18_Sans_Oblique.h"
#include "Font_18_Serif.h"
#include "Font_18_Serif_Bold.h"
#include "Font_18_Serif_Bold_Italic.h"
#include "Font_18_Serif_Italic.h"
#include "Font_24_Matrix_Num.h"
#include "Font_24_Inconsola.h"
#include "Font_24_Ubuntu.h"
#include "Font_24_Ubuntu_Bold.h"
#include "Font_24_Segment_16_Full.h"
#include "Font_24_Mono.h"
#include "Font_24_Mono_Bold.h"
#include "Font_24_Mono_Bold_Oblique.h"
#include "Font_24_Mono_Oblique.h"
#include "Font_24_Grotesk.h"
#include "Font_24_Grotesk_Bold.h"
#include "Font_24_Sans.h"
#include "Font_24_Sans_Bold.h"
#include "Font_24_Sans_Bold_Oblique.h"
#include "Font_24_Sans_Oblique.h"
#include "Font_24_Serif.h"
#include "Font_24_Serif_Bold.h"
#include "Font_24_Serif_Bold_Italic.h"
#include "Font_24_SerifItalic.h"
#include "Font_32_Dingbats.h"
#include "Font_32_Special.h"
#include "Font_32_Calibri_Bold.h"
#include "Font_32_Arial_Num_Plus.h"
#include "Font_32_Matrix_Num.h"
#include "Font_32_Segment_7_Full.h"
#include "Font_32_Segment_7_Num_Plus.h"
#include "Font_32_Segment_16_Full.h"
#include "Font_32_Segment_18_Full.h"
#include "Font_32_Grotesk.h"
#include "Font_32_Grotesk_Bold.h"

#include "008_Open_Sans_Bold.h"
#include "009_Open_Sans_Bold.h"
#include "010_Open_Sans_Bold.h"
#include "012_Open_Sans_Bold.h"
#include "014_Open_Sans_Bold.h"
#include "016_Open_Sans_Bold.h"
#include "018_Open_Sans_Bold.h"
#include "020_Open_Sans_Bold.h"
#include "022_Open_Sans_Bold.h"
#include "024_Open_Sans_Bold.h"
#include "026_Open_Sans_Bold.h"
#include "028_Open_Sans_Bold.h"
#include "036_Open_Sans_Bold.h"
#include "048_Open_Sans_Bold.h"
#include "072_Open_Sans_Bold.h"
#include "096_Open_Sans_Bold.h"
#include "112_Open_Sans_Bold.h"
#include "128_Open_Sans_Bold.h"
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

/* USER CODE BEGIN PV */
uint32_t time = 0;
uint32_t time_1 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  SSD1963_Init();
  time_1 = HAL_GetTick();
  SSD1963_FillScreen(SSD1963_BLUE);
  time = HAL_GetTick() - time_1;
//  LCD_Font(5, 40, "This is\n just a Test\n TomThumb Ext\n", Font_3_TomThumb_Extended, 1, BLACK);
//  LCD_Font(165, 25, "Slider 1", _Open_Sans_Bold_24, 1, BLACK);
  LCD_Font(200, 230, "LED ON", &Open_Sans_Bold_20, 1, BLUE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA5 PA7 PA8 PA9
                           PA10 PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
