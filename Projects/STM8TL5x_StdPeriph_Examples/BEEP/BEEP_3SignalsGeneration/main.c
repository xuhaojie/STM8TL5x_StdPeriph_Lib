/**
  ******************************************************************************
  * @file    BEEP/BEEP_3SignalsGeneration/main.c
  * @brief   This file contains the main function for BEEP 3 Signals Generation example
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
#include "mono_lcd.h"

/**
  * @addtogroup BEEP_3SignalsGeneration
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

// Uncomment this line if you want to use the LCD display
#define USE_LCD

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
uint32_t LSIMeasurment(void);
/* Private functions ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
bool ButtonPressed = FALSE;

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

    /* Clock divider to HSI/1 */
    CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv1);

    /* Disable SWIM due to the BEEP function mapped on the same I/O */
    //CFG->GCR |= CFG_GCR_SWD;
		
		/* Enable TIM2 clock */
	  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
	  /* Enable AWU clock */
	  CLK_PeripheralClockConfig(CLK_Peripheral_AWU, ENABLE);
		
    /* Initialization of I/Os for the LEDs */
    GPIO_Init(LEDS_PORT, (LED1_PIN | LED2_PIN), GPIO_Mode_Out_PP_Low_Fast);
   
    /* LED1 and LED2 OFF */
    GPIO_SetBits(LEDS_PORT, (LED1_PIN | LED2_PIN));

    /* Initialization of I/O for the button */
    GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_Mode_In_FL_IT);

    /* Initialization of BEEP I/O */
    GPIO_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast);
   
		/* Initialization of the Interrupt sensitivity for the button */
    EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Falling);

#ifdef USE_LCD

    /* Enable SPI clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_SPI, ENABLE);
   
    /* Initialize SPI for LCD */
    SPI_DeInit();
    SPI_Init(SPI_FirstBit_MSB, SPI_BaudRatePrescaler_256, SPI_Mode_Master, SPI_CPOL_High, SPI_CPHA_2Edge, SPI_Direction_1Line_Tx, SPI_NSS_Soft);
   
    /* Initialization of SPI_MOSI and SPI_SCK pins */
    GPIO_Init(GPIOA, (GPIO_Pin_2 | GPIO_Pin_4), GPIO_Mode_Out_PP_Low_Fast);
   
    SPI_Cmd(ENABLE);
   
    /* Initialize LCD */
    LCD_Init();
   
    /* Clear LCD lines */
		LCD_Clear();
   
    LCD_PrintString(LCD_LINE1, ENABLE, DISABLE, "  BEEPER OFF");
    LCD_PrintString(LCD_LINE2, ENABLE, DISABLE, "   Press Key");
   
#endif

    /* Enable general interrupts for Key button reading */
    enableInterrupts();
		
		/* BEEP calibration */
    BEEP_LSICalibrationConfig(LSIMeasurment());
		
    while (1)
    {
        /* Check button status */
        if (ButtonPressed == TRUE) /* Button is pressed */
        {
            ButtonPressed = FALSE;
            /* Change BEEP frequency */
            switch (i)
            {
            case 0:
                BEEP_Cmd(DISABLE);
                Delay(100);
                BEEP_Init(BEEP_Frequency_1KHz);
                BEEP_Cmd(ENABLE);
                GPIO_Write(LEDS_PORT, (uint8_t)(~LED1_PIN)); /* LED1 ON */
#ifdef USE_LCD
                LCD_PrintString(LCD_LINE1, ENABLE, DISABLE, "  BEEPER 1kHz");
#endif
                i = 1;
                break;
            case 1:
                BEEP_Cmd(DISABLE);
                Delay(100);
                BEEP_Init(BEEP_Frequency_2KHz);
                BEEP_Cmd(ENABLE);
                GPIO_Write(LEDS_PORT, (uint8_t)(~LED2_PIN)); /* LED2 ON */
#ifdef USE_LCD								
                LCD_PrintString(LCD_LINE1, ENABLE, DISABLE, "  BEEPER 2kHz");
#endif								
                i = 2;
                break;
            case 2:
                BEEP_Cmd(DISABLE);
                Delay(100);
                BEEP_Init(BEEP_Frequency_4KHz);
                BEEP_Cmd(ENABLE);
                GPIO_Write(LEDS_PORT, (uint8_t)~(LED1_PIN | LED2_PIN)); /* LED1 and LED2 ON */
#ifdef USE_LCD								
                LCD_PrintString(LCD_LINE1, ENABLE, DISABLE, "  BEEPER 4kHz");
#endif								
                i = 3;
                break;
            case 3:
                BEEP_Cmd(DISABLE);
                GPIO_Write(LEDS_PORT, (LED1_PIN | LED2_PIN)); /* LED1 and LED2 OFF */
#ifdef USE_LCD								
                LCD_PrintString(LCD_LINE1, ENABLE, DISABLE, "  BEEPER OFF");
#endif								
                i = 0;
                break;
						default:
						    break;
            }
        }

    }

}
/**
  ******************************************************************************
  * @brief Measure the LSI frequency using timer IC1 and update the calibration registers.
  * @param None
  * @retval uint32_t LSI frequency measured value 
  * @note It is recommanded to use a timer clock frequency of at least 10MHz in order 
  * to obtain a better LSI frequency measurement.
  ******************************************************************************
  */
uint32_t LSIMeasurment(void)
{

  uint32_t lsi_freq_hz = 0x0;
  uint32_t fmaster = 0x0;
  uint16_t ICValue1 = 0x0;
  uint16_t ICValue2 = 0x0;

  /* Get master frequency */
  fmaster = CLK_GetClockFreq();

	/* Enable the LSI measurement: LSI clock connected to timer Input Capture 1 */
  AWU->CSR |= AWU_CSR_MSR;

  /* Capture only every 8 events!!! */
  TIM2_ICInit(	TIM2_Channel_1, TIM2_ICPolarity_Rising, TIM2_ICSelection_DirectTI, TIM2_ICPSC_Div8, 0x0);

  /* Enable TIM2 */
  TIM2_Cmd(ENABLE);

  /* wait a capture on cc1 */
  while ((TIM2->SR1 & (uint8_t)TIM2_FLAG_CC1) != TIM2_FLAG_CC1);
  /* Get CCR1 value*/
  ICValue1 = TIM2_GetCapture1();
  TIM2_ClearFlag(TIM2_FLAG_CC1);

  /* wait a capture on cc1 */
  while ((TIM2->SR1 & (uint8_t)TIM2_FLAG_CC1) != TIM2_FLAG_CC1);
  /* Get CCR1 value*/
  ICValue2 = TIM2_GetCapture1();
  TIM2_ClearFlag(TIM2_FLAG_CC1);

  /* Disable IC1 input capture */
  TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  /* Disable TIM2 */
  TIM2_Cmd(DISABLE);

  /* Compute LSI clock frequency */
  lsi_freq_hz = (8 * fmaster) / (ICValue2 - ICValue1);

	/* Disable the LSI measurement: LSI clock disconnected from timer Input Capture 1 */
  AWU->CSR &= (uint8_t)(~AWU_CSR_MSR);
  
  return (lsi_freq_hz);

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
