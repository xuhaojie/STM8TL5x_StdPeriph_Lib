/**
  ******************************************************************************
  * @file    stm8tl5x_exti.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all the functions for the EXTI peripheral.
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
#include "stm8tl5x_exti.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @addtogroup EXTI_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the external interrupt control registers to their default reset value.
  * @param None
  * @retval None
  */
void EXTI_DeInit(void)
{
  EXTI->CR1 = EXTI_CR1_RESET_VALUE;
  EXTI->CR2 = EXTI_CR2_RESET_VALUE;
  EXTI->CR3 = EXTI_CR3_RESET_VALUE;
  EXTI->SR1 = EXTI_SR1_RESET_VALUE;
  EXTI->SR2 = EXTI_SR2_RESET_VALUE;
  EXTI->CONF = EXTI_CONF_RESET_VALUE;
}

/**
  * @brief Set the external interrupt sensitivity of the selected port.
  * @param[in] EXTI_Port         The port number to access.
  * @param[in] EXTI_TriggerValue The external interrupt sensitivity value to set.
  * @retval None
  * @note
  * - The modification of external interrupt sensitivity is only possible when the interrupts are disabled.
  * - The normal behavior is to disable the interrupts before calling this function, and re-enable them after.
  * - Global interrupts must be disabled before calling this function.
  */
void EXTI_SetPortSensitivity(EXTI_Port_TypeDef EXTI_Port,
                             EXTI_Trigger_TypeDef EXTI_TriggerValue)
{

  /* Check function parameters */
  assert_param(IS_EXTI_PORT(EXTI_Port));
  assert_param(IS_EXTI_Trigger_VALUE(EXTI_TriggerValue));

  /* Clear EXTI  port sensitivity */
  if (EXTI_Port != EXTI_Port_B)
  {
    EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PDIS);
  }
  else /* PortNum == EXTI_Port_B */
  {
    EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PBIS);
  }

  /* Write EXTI  port sensitivity */
  EXTI->CR3 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_Port);

}

/**
  * @brief Set the external interrupt sensitivity of the selected pin.
  * @param[in] EXTI_PinNum       The pin to configure.
  * @param[in] EXTI_TriggerValue The external interrupt sensitivity value to set.
  * @retval None
  * @note
  * - The modification of external interrupt sensitivity is only possible when the interrupts are disabled.
  * - The normal behavior is to disable the interrupts before calling this function, and re-enable them after.
  * - Global interrupts must be disabled before calling this function.
  */
void EXTI_SetPinSensitivity(EXTI_Pin_TypeDef EXTI_PinNum,
                            EXTI_Trigger_TypeDef EXTI_TriggerValue)
{

  /* Check function parameters */
  assert_param(IS_EXTI_PINNUM(EXTI_PinNum));
  assert_param(IS_EXTI_Trigger_VALUE(EXTI_TriggerValue));

  /* Clear port sensitivity bits */
  switch (EXTI_PinNum)
  {
    case EXTI_Pin_0:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P0IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_PinNum);
      break;
    case EXTI_Pin_1:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P1IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_PinNum);
      break;
    case EXTI_Pin_2:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P2IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_PinNum);
      break;
    case EXTI_Pin_3:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P3IS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << (uint8_t)EXTI_PinNum);
      break;
    case EXTI_Pin_4:
      EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P4IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << ((uint8_t)EXTI_PinNum & (uint8_t)0xEF));
      break;
    case EXTI_Pin_5:
      EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P5IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << ((uint8_t)EXTI_PinNum & (uint8_t)0xEF));
      break;
    case EXTI_Pin_6:
      EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P6IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << ((uint8_t)EXTI_PinNum & (uint8_t)0xEF));
      break;
    case EXTI_Pin_7:
      EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P7IS);
      EXTI->CR2 |= (uint8_t)((uint8_t)(EXTI_TriggerValue) << ((uint8_t)EXTI_PinNum & (uint8_t)0xEF));
      break;
    default:
      break;
  }
}

/**
  * @brief Configure the half port interrupt selection.
  * @param[in] EXTI_HalfPort The port part  to access (MSB or LSB).
  * @param[in] NewState      The external interrupt new state.
  * @retval None
  * @note This function must be called once the port sensitivity is configured,
  * otherwise this function call won't have any effect on the port external interrupt.
  */
void EXTI_SetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort,
                               FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_EXTI_HALFPORT(EXTI_HalfPort));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    EXTI->CONF |= (uint8_t)EXTI_HalfPort; /* Enable port interrupt selector */
  }
  else /*NewState == DISABLE */
  {
    EXTI->CONF &= (uint8_t)(~(uint8_t)EXTI_HalfPort); /* Disable port interrupt selector */
  }
}

/**
  * @brief Get the external interrupt sensitivity of the selected port.
  * @param[in] EXTI_Port The port number to access.
  * @retval EXTI_Trigger_TypeDef The external interrupt sensitivity of the selected port.
  */
EXTI_Trigger_TypeDef EXTI_GetPortSensitivity(EXTI_Port_TypeDef EXTI_Port)
{
  uint8_t value = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_PORT(EXTI_Port));

  if (EXTI_Port != EXTI_Port_B)
  {
    value = (uint8_t)((EXTI->CR3 & EXTI_CR3_PDIS) >> 2);
  }
  else /* PortNum == EXTI_Port_B */
  {
    value = (uint8_t)(EXTI->CR3 & EXTI_CR3_PBIS);
  }
  return((EXTI_Trigger_TypeDef)value);
}

/**
  * @brief Get the external interrupt sensitivity of the selected pin.
  * @param[in] EXTI_PinNum The pin number to access.
  * @retval EXTI_Trigger_TypeDef The external interrupt sensitivity of the selected port.
  */
EXTI_Trigger_TypeDef EXTI_GetPinSensitivity(EXTI_Pin_TypeDef EXTI_PinNum)
{
  uint8_t value = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_PINNUM(EXTI_PinNum));

  switch (EXTI_PinNum)
  {
    case EXTI_Pin_0:
      value = (uint8_t)(EXTI->CR1 & EXTI_CR1_P0IS);
      break;
    case EXTI_Pin_1:
      value = (uint8_t)((EXTI->CR1 & EXTI_CR1_P1IS) >> (uint8_t)EXTI_Pin_1);
      break;
    case EXTI_Pin_2:
      value = (uint8_t)((EXTI->CR1 & EXTI_CR1_P2IS) >> (uint8_t)EXTI_Pin_2);
      break;
    case EXTI_Pin_3:
      value = (uint8_t)((EXTI->CR1 & EXTI_CR1_P3IS) >> (uint8_t)EXTI_Pin_3);
      break;
    case EXTI_Pin_4:
      value = (uint8_t)(EXTI->CR2 & EXTI_CR2_P4IS);
      break;
    case EXTI_Pin_5:
      value = (uint8_t)((EXTI->CR2 & EXTI_CR2_P5IS) >> ((uint8_t)EXTI_Pin_5 & (uint8_t)0x0F));
      break;
    case EXTI_Pin_6:
      value = (uint8_t)((EXTI->CR2 & EXTI_CR2_P6IS) >> ((uint8_t)EXTI_Pin_6 & (uint8_t)0x0F));
      break;
    case EXTI_Pin_7:
      value = (uint8_t)((EXTI->CR2 & EXTI_CR2_P7IS) >> ((uint8_t)EXTI_Pin_7 & (uint8_t)0x0F));
      break;
    default:
      break;
  }
  return((EXTI_Trigger_TypeDef)value);
}

/**
  * @brief Get the external interrupt half port configuration.
  * @param[in] EXTI_HalfPort The half port part to get (MSB or LSB).
  * @retval FunctionalState The external interrupt state of the selected port.
  */
FunctionalState EXTI_GetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort)
{
  FunctionalState value = DISABLE;
  /* Check function parameters */
  assert_param(IS_EXTI_HALFPORT(EXTI_HalfPort));
  if ((EXTI->CONF & (uint8_t)EXTI_HalfPort) != (uint8_t)DISABLE)
  {
    value = ENABLE;
  }
  else
  {
    value = DISABLE;
  }

  return(value);
}

/**
  * @brief Get the external interrupt status.
  * @param[in] EXTI_IT Specifies the interrupt to read.
  * @retval ITStatus The status of the specified interrupt.
  */
ITStatus EXTI_GetITStatus(EXTI_IT_TypeDef EXTI_IT)
{
  ITStatus status = RESET;
  /* Check function parameters */
  assert_param(IS_EXTI_ITPENDINGBIT(EXTI_IT));

  if (((uint8_t)EXTI_IT & (uint8_t)0xF0) == 0xF0)
  {
    status = (ITStatus)(EXTI->SR2 & ((uint8_t)EXTI_IT & (uint8_t)0x0F));
  }
  else
  {
    status = (ITStatus)(EXTI->SR1 & (uint8_t)EXTI_IT);
  }
  return((ITStatus)status);
}

/**
  * @brief Clear the specified interrupt pending bit
  * @param[in] EXTI_IT Specifies the interrupt to clear
  * @retval None
  */
void EXTI_ClearITPendingBit(EXTI_IT_TypeDef EXTI_IT)
{
  /* Check function parameters */
  assert_param(IS_EXTI_ITPENDINGBIT(EXTI_IT));

  if (((uint8_t)EXTI_IT & (uint8_t)0xF0) == 0xF0)
  {
    EXTI->SR2 = (uint8_t)((uint8_t)EXTI_IT & (uint8_t)0x0F);
  }
  else
  {
    EXTI->SR1 = (uint8_t)EXTI_IT;
  }
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
