/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
	
SystemClock_Config(); 
	
RCC->AHBENR |= (1 << 19);
RCC->AHBENR |= (1 << 17);
RCC->APB2ENR |= (1 << 0);
/*
GPIOC->MODER |= (1 << 12);
GPIOC->MODER |= (1 << 14);
GPIOC->MODER |= (1 << 16);
GPIOC->MODER |= (1 << 18);
	

GPIOC->OTYPER |= (0 << 6);
GPIOC->OTYPER |= (0 << 7);
GPIOC->OTYPER |= (0 << 8);
GPIOC->OTYPER |= (0 << 9);
	

GPIOC->OSPEEDR &= (1 << 12);
GPIOC->OSPEEDR &= (1 << 14);
GPIOC->OSPEEDR &= (1 << 16);
GPIOC->OSPEEDR &= (1 << 18);	

GPIOC->PUPDR &= ~(1 << 12) | (1 << 13);
GPIOC->PUPDR &= ~(1 << 14) | (1 << 15);
GPIOC->PUPDR &= ~(1 << 16) | (1 << 17);
GPIOC->PUPDR &= ~(1 << 18) | (1 << 19);
*/



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
	__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
	
	GPIO_InitTypeDef initStr = {GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_6 | GPIO_PIN_7,
GPIO_MODE_OUTPUT_PP,
GPIO_SPEED_FREQ_LOW,
GPIO_NOPULL};
HAL_GPIO_Init(GPIOC, &initStr); // Initialize pins PC8 & PC9
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // Start PC8 high
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
	GPIOA->MODER = 0; //(0 << 1) | (0 << 0);
GPIOA->OSPEEDR = 0; //(0 << 1) | (0 << 0);
GPIOA->PUPDR = 2; //0 << 0) | (1 << 1);


GPIOC->ODR |= (1 << 9);
//GPIOC->ODR &= ~(1<<6);
//GPIOC->ODR &= ~(1<<7);
//GPIOC->ODR &= ~(1<<8);
		

EXTI->IMR |= (1 << 0);
EXTI->RTSR |= (1 << 0);



SYSCFG->EXTICR[1] |= (0 << 0)|(0 << 1)|(0 << 2)|(0 << 3);

NVIC_EnableIRQ(5); // EXTI0_1_IRQn
NVIC_SetPriority(5,1);
//NVIC_SetPriority(EXTI0_1_IRQn,3);

//NVIC_EnableIRQ(-1); // SysTick_IRQn
//NVIC_SetPriority(-1,2);

//NVIC_SetPriority(5,3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_Delay(400);
		GPIOC->ODR ^= GPIO_ODR_6;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

volatile int j = 0;
void EXTI0_1_IRQHandler(void) {
	
	GPIOC->ODR ^= (GPIO_ODR_8)|(GPIO_ODR_9);
	
	//EXTI->PR |= 1;
	
	for(j = 0; j <1500000; j++) {}
	
	GPIOC->ODR ^= (GPIO_ODR_8)|(GPIO_ODR_9);
	EXTI->PR |= (1 << 0);
	
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
