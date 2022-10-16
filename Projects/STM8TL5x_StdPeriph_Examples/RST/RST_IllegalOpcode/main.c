/**
  ******************************************************************************
  * @file    RST/RST_IllegalOpcode/main.c
  * @brief   This file contains the main function for RST Illegal Opcode example.
  * @author  STMicroelectronics - MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8tl5x.h"
#include "stm8tl5x_it.h"    /* SDCC patch: required by SDCC for interrupts */

/**
  * @addtogroup RST_IllegalOpcode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Evalboard I/Os configuration */

#define LEDS_PORT (GPIOB)
#define LED1_PIN  (GPIO_Pin_2)
#define LED2_PIN  (GPIO_Pin_3)

#define BUTTON_PORT (GPIOB)
#define BUTTON_PIN  (GPIO_Pin_5)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);

/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  ******************************************************************************
  * @brief Example main entry point.
  * @param None
  * @retval None
  ******************************************************************************
  */
void main(void)
{

  uint8_t i = 0;
	FlagStatus IllOpFlag = 0;

  /* Initialization of I/Os for the LEDs */
  GPIO_Init(LEDS_PORT, (LED1_PIN | LED2_PIN), GPIO_Mode_Out_PP_Low_Fast);

  /* LEDs OFF */
  GPIO_SetBits(LEDS_PORT, (LED1_PIN | LED2_PIN));

  /* Initialization of I/O for the button */
  GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_Mode_In_FL_IT);

  /* Initialization of the Interrupt sensitivity for the button */
  EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Falling);

	/* Test if a ILLOP Reset has occured.
	   If yes toggle both LEDs */

	IllOpFlag = RST_GetFlagStatus(RST_FLAG_ILLOPF);

	if (IllOpFlag)
  {
    for (i=0; i<20; i++)
    {
      GPIO_ToggleBits(LEDS_PORT, (LED1_PIN | LED2_PIN));
			Delay(0x2000);
		}
    /* Clear IWDGF Flag */
    RST_ClearFlag(RST_FLAG_ILLOPF);
  }

  /* Write an illegal opcode in memory.
     A press on the button will jump to this address and will
     cause the program to reset */
	FLASH_Unlock(FLASH_MemType_Program);
	FLASH_ProgramByte(0x9F00, 0x75);

	enableInterrupts();

  while (1)
  {
    GPIO_ToggleBits(LEDS_PORT, LED1_PIN);
    Delay(0xFFFF);
		Delay(0xFFFF);
  }

}
/**
  ******************************************************************************
  * @brief Delay.
  * @param[in] nCount
  * @retval None
  ******************************************************************************
  */
void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  ******************************************************************************
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file Pointer to the source file name
  * @param line assert_param error line source number
  * @retval None
  ******************************************************************************
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
