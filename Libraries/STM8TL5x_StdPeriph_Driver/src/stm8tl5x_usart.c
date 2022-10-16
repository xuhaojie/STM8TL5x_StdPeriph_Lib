/**
  ********************************************************************************
  * @file    stm8tl5x_usart.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    01-March-2012
  * @brief   This file contains all the functions for the USART peripheral.
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
#include "stm8tl5x_usart.h"
#include "stm8tl5x_clk.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @addtogroup USART_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the USART peripheral.
  * @param None
  * @retval None
  */
void USART_DeInit(void)
{
  /* Clear the Idle Line Detected bit in the status rerister by a read
     to the USART_SR register followed by a Read to the USART_DR register */
  (void)USART->SR;
  (void)USART->DR;

  USART->BRR2 = USART_BRR2_RESET_VALUE;  /* Set USART_BRR2 to reset value 0x00 */
  USART->BRR1 = USART_BRR1_RESET_VALUE;  /* Set USART_BRR1 to reset value 0x00 */

  USART->CR1 = USART_CR1_RESET_VALUE;  /* Set USART_CR1 to reset value 0x00 */
  USART->CR2 = USART_CR2_RESET_VALUE;  /* Set USART_CR2 to reset value 0x00 */
  USART->CR3 = USART_CR3_RESET_VALUE;  /* Set USART_CR3 to reset value 0x00 */
  USART->CR4 = USART_CR4_RESET_VALUE;  /* Set USART_CR4 to reset value 0x00 */
}

/**
  * @brief Initializes the USART according to the specified parameters.
  * @param[in] USART_WordLength This parameter can be any of the @ref USART_WordLength_TypeDef enumeration.
  * @param[in] USART_StopBits   This parameter can be any of the @ref USART_StopBits_TypeDef enumeration.
  * @param[in] USART_Parity     This parameter can be any of the @ref USART_Parity_TypeDef enumeration.
  * @param[in] BaudRate         The baudrate.
  * @param[in] USART_Mode       This parameter can be any of the @ref USART_Mode_TypeDef values
  * @retval None
  * @note Configure in Push-Pull or Open-Drain mode the Tx I/O line by setting the correct I/O Port register
  * according the product package and line configuration
  */
void USART_Init(uint32_t BaudRate, USART_WordLength_TypeDef USART_WordLength,
                USART_StopBits_TypeDef USART_StopBits, USART_Parity_TypeDef
                USART_Parity, USART_Mode_TypeDef USART_Mode)
{
  uint32_t BaudRate_Mantissa = 0;

  /* Check the parameters */
  assert_param(IS_USART_BAUDRATE(BaudRate));

  assert_param(IS_USART_WordLength(USART_WordLength));

  assert_param(IS_USART_STOPBITS(USART_StopBits));

  assert_param(IS_USART_PARITY(USART_Parity));

  assert_param(IS_USART_MODE(USART_Mode));

  /* Clear the word length and Parity Control bits */
  USART->CR1 &= (uint8_t)(~(USART_CR1_PCEN | USART_CR1_PS | USART_CR1_M));
  /* Set the word length bit according to USART_WordLength value */
  /* Set the Parity Control bit to USART_Parity value */
  USART->CR1 |= (uint8_t)((uint8_t)USART_WordLength | (uint8_t)USART_Parity);

  /* Clear the STOP bits */
  USART->CR3 &= (uint8_t)(~USART_CR3_STOP);
  /* Set the STOP bits number according to USART_StopBits value */
  USART->CR3 |= (uint8_t)USART_StopBits;

  /* Clear the LSB mantissa of USARTDIV */
  USART->BRR1 &= (uint8_t)(~USART_BRR1_DIVM);
  /* Clear the MSB mantissa of USARTDIV */
  USART->BRR2 &= (uint8_t)(~USART_BRR2_DIVM);
  /* Clear the Fraction bits of USARTDIV */
  USART->BRR2 &= (uint8_t)(~USART_BRR2_DIVF);

  BaudRate_Mantissa  = ((uint32_t)CLK_GetClockFreq() / BaudRate);
  /* Set the fraction of USARTDIV */
  USART->BRR2 = (uint8_t)((BaudRate_Mantissa >> (uint8_t)8) & (uint8_t)0xF0);
  /* Set the MSB mantissa of USARTDIV */
  USART->BRR2 |= (uint8_t)(BaudRate_Mantissa & (uint8_t)0x0F);
  /* Set the LSB mantissa of USARTDIV */
  USART->BRR1 = (uint8_t)(BaudRate_Mantissa >> (uint8_t)4);

  /* Disable the Transmitter and Receiver */
  USART->CR2 &= (uint8_t)~(USART_CR2_TEN | USART_CR2_REN);
  /* Set TEN and REN bits according to USART_Mode value */
  USART->CR2 |= (uint8_t)USART_Mode;
}

/**
  * @brief Initializes the USART Clock according to the specified parameters.
  * @param[in] USART_Clock   This parameter can be any of the @ref USART_Clock_TypeDef enumeration.
  * @param[in] USART_CPOL    This parameter can be any of the @ref USART_CPOL_TypeDef enumeration.
  * @param[in] USART_CPHA    This parameter can be any of the @ref USART_CPHA_TypeDef enumeration.
  * @param[in] USART_LastBit This parameter can be any of the @ref USART_LastBit_TypeDef enumeration.
  * @retval None
  */
void USART_ClockInit(USART_Clock_TypeDef USART_Clock, USART_CPOL_TypeDef USART_CPOL,
                     USART_CPHA_TypeDef USART_CPHA, USART_LastBit_TypeDef USART_LastBit)
{
  /* Check the parameters */
  assert_param(IS_USART_CLOCK(USART_Clock));
  assert_param(IS_USART_CPOL(USART_CPOL));
  assert_param(IS_USART_CPHA(USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_LastBit));

  /* Clear the Clock Polarity, lock Phase, Last Bit Clock pulse */
  USART->CR3 &= (uint8_t)~(USART_CR3_CPOL | USART_CR3_CPHA | USART_CR3_LBCL);
  /* Set the Clock Polarity, lock Phase, Last Bit Clock pulse */
  USART->CR3 |= (uint8_t)((uint8_t)USART_CPOL | (uint8_t)USART_CPHA | (uint8_t)USART_LastBit);

  if (USART_Clock != USART_Clock_Disable)
  {
    USART->CR3 |= (uint8_t)(USART_CR3_CLKEN); /* Set the Clock Enable bit */
  }
  else
  {
    USART->CR3 &= (uint8_t)(~USART_CR3_CLKEN); /* Clear the Clock Enable bit */
  }
}

/**
  * @brief Enable the USART peripheral.
  * @param[in] NewState The new state of the USART Communication.
  * @retval None
  */
void USART_Cmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    USART->CR1 &= (uint8_t)(~USART_CR1_USARTD); /**< USART Enable */
  }
  else
  {
    USART->CR1 |= USART_CR1_USARTD;  /**< USART Disable */
  }
}

/**
  * @brief Enables or disables the specified USART interrupts.
  * @param[in] USART_IT Specifies the USART interrupt sources to be enabled or disabled.
  * @param[in] NewState New state of the specified USART interrupts.
  * @retval None
  */
void USART_ITConfig(USART_IT_TypeDef USART_IT, FunctionalState NewState)
{
  uint8_t uartreg, itpos = 0x00;
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the USART register index */
  uartreg = (uint8_t)((uint16_t)USART_IT >> (uint8_t)0x08);
  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));

  if (NewState != DISABLE)
  {
    /**< Enable the Interrupt bits according to USART_IT mask */
    if (uartreg == 0x01)
    {
      USART->CR1 |= itpos;
    }
    /*uartreg =0x02*/
    else
    {
      USART->CR2 |= itpos;
    }
  }
  else
  {
    /**< Disable the interrupt bits according to USART_IT mask */
    if (uartreg == 0x01)
    {
      USART->CR1 &= (uint8_t)(~itpos);
    }
    /*uartreg =0x02*/
    else
    {
      USART->CR2 &= (uint8_t)(~itpos);
    }
  }

}

/**
  * @brief Returns the most recent received data by the USART peripheral.
  * @param None
  * @retval uint8_t The received data.
  * @note The function USART_Cmd(ENABLE) must be called first.
  */
uint8_t USART_ReceiveData8(void)
{
  return USART->DR;
}


/**
  * @brief Returns the most recent received data by the USART peripheral.
  * @param None
  * @retval uint16_t The received data.
  * @note The function USART_Cmd(ENABLE) must be called first.
  */
uint16_t USART_ReceiveData9(void)
{
  uint16_t temp = 0;
  
  temp = ((uint16_t)(((uint16_t)((uint16_t)USART->CR1 & (uint16_t)USART_CR1_R8)) << 1));
  return (uint16_t)( ((uint16_t)((uint16_t)USART->DR) | temp) & ((uint16_t)0x01FF));
}

/**
  * @brief Determines if the USART is in mute mode or not.
  * @param[in] NewState The new state of the USART mode.
  * @retval None
  */
void USART_ReceiverWakeUpCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the mute mode USART by setting the RWU bit in the CR2 register */
    USART->CR2 |= USART_CR2_RWU;
  }
  else
  {
    /* Disable the mute mode USART by clearing the RWU bit in the CR1 register */
    USART->CR2 &= ((uint8_t)~USART_CR2_RWU);
  }
}

/**
  * @brief Transmits break characters.
  * @param None
  * @retval None
  */
void USART_SendBreak(void)
{
  USART->CR2 |= USART_CR2_SBK;
}

/**
  * @brief Transmits 8 bit data through the USART peripheral.
  * @param[in] Data The data to transmit.
  * @retval None
  */
void USART_SendData8(uint8_t Data)
{
  /* Transmit Data */
  USART->DR = Data;
}

/**
  * @brief Transmits 9 bit data through the USART peripheral.
  * @param[in] Data The data to transmit.
  * @retval None
  * @note The parameter (Data) must be lower than 0x1FF.
  */
void USART_SendData9(uint16_t Data)
{
  assert_param(IS_USART_DATA_9BITS(Data));

  USART->CR1 &= ((uint8_t)~USART_CR1_T8);                    /* Clear the transmit data bit 8     */
  USART->CR1 |= (uint8_t)(((uint8_t)(Data >> 2)) & USART_CR1_T8); /* Write the transmit data bit [8]   */
  USART->DR   = (uint8_t)(Data);                             /* Write the transmit data bit [0:7] */

}

/**
  * @brief Sets the address of the USART node.
  * @param[in] Address Indicates the address of the USART node.
  * @retval None
  * @note The parameter (Address) must be lower than 16
  */
void USART_SetAddress(uint8_t Address)
{
  /* assert_param for USART_Address */
  assert_param(IS_USART_ADDRESS(Address));

  /* Clear the USART address */
  USART->CR4 &= ((uint8_t)~USART_CR4_ADD);
  /* Set the USART address node */
  USART->CR4 |= Address;
}

/**
  * @brief Selects the USART WakeUp method.
  * @param[in] USART_WakeUp Specifies the USART wakeup method.
  * @retval None
  */
void USART_WakeUpConfig(USART_WakeUp_TypeDef USART_WakeUp)
{
  assert_param(IS_USART_WAKEUP(USART_WakeUp));

  USART->CR1 &= ((uint8_t)~USART_CR1_WAKE);
  USART->CR1 |= (uint8_t)USART_WakeUp;
}

/**
  * @brief Checks whether the specified USART flag is set or not.
  * @param[in] USART_FLAG Specifies the flag to check.
  * @retval FlagStatus Status of the flag
  */
FlagStatus USART_GetFlagStatus(USART_FLAG_TypeDef USART_FLAG)
{
  FlagStatus status = RESET;

  /* Check parameters */
  assert_param(IS_USART_FLAG(USART_FLAG));

  if (USART_FLAG == USART_FLAG_SBK)
  {
    if ((USART->CR2 & (uint8_t)USART_FLAG) != (uint8_t)0x00)
    {
      /* USART_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART_FLAG is reset*/
      status = RESET;
    }
  }
  else
  {
    if ((USART->SR & (uint8_t)USART_FLAG) != (uint8_t)0x00)
    {
      /* USART_FLAG is set*/
      status = SET;
    }
    else
    {
      /* USART_FLAG is reset*/
      status = RESET;
    }
  }
  /* Return the USART_FLAG status*/
  return status;
}

/**
  * @brief Clears the USART RXNE (read data register not empty) flag.
  * @param None
  * @retval None
  * @note
  * - PE (Parity error), FE (Framing error), NE (Noise error), OR (OverRun error)
  *   and IDLE (Idle line detected) flags are cleared by software sequence: a read
  *   operation to USART_SR register (USART_GetFlagStatus())followed by a read operation
  *   to USART_DR register(USART_ReceiveData8() or USART_ReceiveData9()).
  * - RXNE flag can be also cleared by a read to the USART_DR register
  *   (USART_ReceiveData8()or USART_ReceiveData9()).
  * - TC flag can be also cleared by software sequence: a read operation to USART_SR
  *   register (USART_GetFlagStatus()) followed by a write operation to USART_DR register
  *   (USART_SendData8() or USART_SendData9()).
  * - TXE flag is cleared only by a write to the USART_DR register (USART_SendData8() or
  *   USART_SendData9()).
  * - SBK flag is cleared during the stop bit of break.
  */
void USART_ClearFlag(void)
{
  /*< Clear the Receive Register Not Empty flag */
  USART->SR = (uint8_t)~(USART_SR_RXNE);
}

/**
  * @brief Checks whether the specified USART interrupt has occurred or not.
  * @param[in] USART_IT  Specifies the USART interrupt pending bit to check.
  * @retval ITStatus The interruption status
  */
ITStatus USART_GetITStatus(USART_IT_TypeDef USART_IT)
{
  ITStatus pendingbitstatus = RESET;
  uint8_t itpos = 0;
  uint8_t itmask1 = 0;
  uint8_t itmask2 = 0;
  uint8_t enablestatus = 0;

  /* Check parameters */
  assert_param(IS_USART_GET_IT(USART_IT));

  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));
  /* Get the USART IT index */
  itmask1 = (uint8_t)((uint8_t)USART_IT >> (uint8_t)4);
  /* Set the IT mask*/
  itmask2 = (uint8_t)((uint8_t)1 << itmask1);


  /* Check the status of the specified USART pending bit*/
  if (USART_IT == USART_IT_PE)
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USART->CR1 & itmask2);
    /* Check the status of the specified USART interrupt*/

    if (((USART->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }
  else
  {
    /* Get the USART_IT enable bit status*/
    enablestatus = (uint8_t)((uint8_t)USART->CR2 & itmask2);
    /* Check the status of the specified USART interrupt*/
    if (((USART->SR & itpos) != (uint8_t)0x00) && enablestatus)
    {
      /* Interrupt occurred*/
      pendingbitstatus = SET;
    }
    else
    {
      /* Interrupt not occurred*/
      pendingbitstatus = RESET;
    }
  }

  /* Return the USART_IT status*/
  return  pendingbitstatus;
}

/**
  * @brief Clears the USART RXNE (read data register not empty) pending bit.
  * @param None
  * @retval None
  * @note
  * - PE (Parity error), FE (Framing error), NE (Noise error), OR (OverRun error) and
  *   IDLE (Idle line detected) pending bits are cleared by software sequence: a read
  *   operation to USART_SR register (USART_GetITStatus()) followed by a read operation
  *   to USART_DR register (USART_ReceiveData8() or USART_ReceiveData9()).
  * - RXNE pending bit can be also cleared by a read to the USART_DR register
  *   (USART_ReceiveData8() or USART_ReceiveData9()).
  * - TC (Transmit complet) pending bit can be cleared by software sequence: a read
  *   operation to USART_SR register (USART_GetITStatus()) followed by a write operation
  *   to USART_DR register (USART_SendData8()or USART_SendData9()).
  * - TXE pending bit is cleared only by a write to the USART_DR register
  *   (USART_SendData8() or USART_SendData9()).
  */
void USART_ClearITPendingBit(void)
{
  /*< Clear the Receive Register Not Empty pending bit */
  USART->SR = (uint8_t)~(USART_SR_RXNE);
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
