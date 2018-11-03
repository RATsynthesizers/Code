
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "i2s.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
//=====================================================================
// explanations for tags with "?" are located in ./WeirdProj/words.txt
//=====================================================================
#include <stdio.h>
#include <stdlib.h>
//#include "arm_math.h"      ?? math and FPU defines
#include <math.h>

#include <Globals.hpp>       // some global parameters
#include <Generic.hpp>       // ?? like voice
#include <Modules.hpp>       // all modules includes

#include <CodecDriver.hpp>
#include <MIDIparser.hpp>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
	MIDI::MIDIparser parser;
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t buf[3];    // ?i2s
uint8_t bufCnt = 0;
uint8_t tempBufUART = 0;
#include "tables.h" // ?i2s


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
 if(huart->Instance==UART4)
 {

	 parser.PushByte(tempBufUART);


 }

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	// wire reconnect example
	Generator g1(1,440,0);
	Amp a1(1);
	Wire w1(a1, g1, Parameter::ParamName::AMPLIFICATION);

	Amp a2(1);
	Generator g2(1,440,0);
	w1.replugConsumer(g2, Parameter::ParamName::AMPLIFICATION);
	w1.replugProvider(a2);

	CodecDriver Codec1(hi2c1, 0);




  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  __disable_irq();  // ??
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_I2S2_Init();
  MX_TIM2_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  Codec1.initCodec();

  buf[0] = 0; // ?i2s
  buf[1] = 0; // ?i2s
  buf[2] = 0;  // ?i2s

//  uint16_t outBuff[SIN_1000_SMP_SZ * 2];  // ?i2s
//  float sin_1000_smp[SIN_1000_SMP_SZ] = {
//  			 0.00000,     0.00628,     0.01257,     0.01885,     0.02513,
//  			 0.03769,     0.04397,     0.05024,     0.05652,     0.06279,
//  			 0.07533,     0.08159,     0.08785,     0.09411,     0.10036,
//  			 0.11286,     0.11910,     0.12533,     0.13156,     0.13779,
//  			 0.15023,     0.15643,     0.16264,     0.16883,     0.17502,
//  			 0.18738,     0.19355,     0.19971,     0.20586,     0.21201,
//  			 0.22427,     0.23039,     0.23650,     0.24260,     0.24869,
//  			 0.26084,     0.26690,     0.27295,     0.27899,     0.28502,
//  			 0.29704,     0.30304,     0.30902,     0.31499,     0.32094,
//  			 0.33282,     0.33874,     0.34464,     0.35053,     0.35641,
//  			 0.36812,     0.37396,     0.37978,     0.38558,     0.39137,
//  			 0.40291,     0.40865,     0.41438,     0.42009,     0.42578,
//  			 0.43712,     0.44276,     0.44838,     0.45399,     0.45958,
//  			 0.47070,     0.47624,     0.48175,     0.48725,     0.49273,
//  			 0.50362,     0.50904,     0.51444,     0.51982,     0.52517,
//  			 0.53583,     0.54112,     0.54639,     0.55165,     0.55688,
//  			 0.56727,     0.57243,     0.57757,     0.58269,     0.58779,
//  			 0.59790,     0.60293,     0.60793,     0.61291,     0.61786,
//  			 0.62769,     0.63257,     0.63742,     0.64225,     0.64706,
//  			 0.65659,     0.66131,     0.66601,     0.67069,     0.67533
//  	};


  //HAL_I2S_Transmit_DMA(&hi2s2, packForCodec(sin_1000_smp, static_cast<uint32_t>(100)), 200); // ?i2s

  __enable_irq();   // ??
  __HAL_UART_ENABLE_IT(&huart4, UART_IT_RXNE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  volatile uint8_t o = (SPI2->DR);
	  if( (SPI2->DR) ) {
	  	o = 0; }
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
