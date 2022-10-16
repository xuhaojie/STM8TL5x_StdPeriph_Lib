/**
  ******************************************************************************
  * @file    Templates/stm8tl5x_it.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   This file contains the external declarations of the interrupt routines.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8TL5X_IT_H
#define __STM8TL5X_IT_H

/* Includes ------------------------------------------------------------------*/
#include "stm8tl5x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef _COSMIC_
void _stext(void); /* RESET startup routine */
INTERRUPT void NonHandledInterrupt(void);
#endif /* _COSMIC_ */

#if !defined(_RAISONANCE_) && !defined(_SDCC_)
INTERRUPT void TRAP_IRQHandler(void); /* TRAP */
INTERRUPT void FLASH_IRQHandler(void); /* FLASH EOP/PG_DIS */
INTERRUPT void PXS_IRQHandler(void); /* PXS */
INTERRUPT void AWU_IRQHandler(void); /* AWU */
INTERRUPT void EXTIB_IRQHandler(void); /* EXTI PORTB */
INTERRUPT void EXTID_IRQHandler(void); /* EXTI PORTD */
INTERRUPT void EXTI0_IRQHandler(void); /* EXTI PIN0 */
INTERRUPT void EXTI1_IRQHandler(void); /* EXTI PIN1 */
INTERRUPT void EXTI2_IRQHandler(void); /* EXTI PIN2 */
INTERRUPT void EXTI3_IRQHandler(void); /* EXTI PIN3 */
INTERRUPT void EXTI4_IRQHandler(void); /* EXTI PIN4 */
INTERRUPT void EXTI5_IRQHandler(void); /* EXTI PIN5 */
INTERRUPT void EXTI6_IRQHandler(void); /* EXTI PIN6 */
INTERRUPT void EXTI7_IRQHandler(void); /* EXTI PIN7 */
INTERRUPT void TIM2_UPD_OVF_TRG_BRK_IRQHandler(void); /* TIM2 UPD/OVF/TRG/BRK */
INTERRUPT void TIM2_CAP_IRQHandler(void); /* TIM2 CAP*/
INTERRUPT void TIM3_UPD_OVF_TRG_BRK_IRQHandler(void); /* TIM3 UPD/OVF/TRG/BRK */
INTERRUPT void TIM3_CAP_IRQHandler(void); /* TIM3 CAP*/
INTERRUPT void TIM4_UPD_OVF_IRQHandler(void); /* TIM4 UPD/OVF */
INTERRUPT void SPI_IRQHandler(void); /* SPI */
INTERRUPT void USART_TX_IRQHandler(void); /* USART TX */
INTERRUPT void USART_RX_IRQHandler(void); /* USART RX */
INTERRUPT void I2C_IRQHandler(void); /* I2C */


// SDCC patch: __interrupt keyword required after function name --> requires new block
#elif defined (_SDCC_)

 INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler);                  /* TRAP */
 INTERRUPT_HANDLER(FLASH_IRQHandler, 1);                   /* FLASH EOP/PG_DIS */
 INTERRUPT_HANDLER(PXS_IRQHandler, 2);                     /* ProxSense */
 INTERRUPT_HANDLER(AWU_IRQHandler, 4);                     /* AWU */
 INTERRUPT_HANDLER(EXTIB_IRQHandler, 6);                   /* EXTI PORTB */
 INTERRUPT_HANDLER(EXTID_IRQHandler, 7);                   /* EXTI PORTD */
 INTERRUPT_HANDLER(EXTI0_IRQHandler, 8);                   /* EXTI PIN0 */
 INTERRUPT_HANDLER(EXTI1_IRQHandler, 9);                   /* EXTI PIN1 */
 INTERRUPT_HANDLER(EXTI2_IRQHandler, 10);                  /* EXTI PIN2 */
 INTERRUPT_HANDLER(EXTI3_IRQHandler, 11);                  /* EXTI PIN3 */
 INTERRUPT_HANDLER(EXTI4_IRQHandler, 12);                  /* EXTI PIN4 */
 INTERRUPT_HANDLER(EXTI5_IRQHandler, 13);                  /* EXTI PIN5 */
 INTERRUPT_HANDLER(EXTI6_IRQHandler, 14);                  /* EXTI PIN6 */
 INTERRUPT_HANDLER(EXTI7_IRQHandler, 15);                  /* EXTI PIN7 */
 INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_IRQHandler, 19);   /* TIM2 UPD/OVF/TRG/BRK */
 INTERRUPT_HANDLER(TIM2_CAP_IRQHandler, 20);               /* TIM2 CAP*/
 INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_IRQHandler, 21);   /* TIM3 UPD/OVF/TRG/BRK */
 INTERRUPT_HANDLER(TIM3_CAP_IRQHandler, 22);               /* TIM3 CAP*/
 INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 25);           /* TIM4 UPD/OVF */
 INTERRUPT_HANDLER(SPI_IRQHandler, 26);                    /* SPI */
 INTERRUPT_HANDLER(USART_TX_IRQHandler, 27);               /* USART TX */
 INTERRUPT_HANDLER(USART_RX_IRQHandler, 28);               /* USART RX */
 INTERRUPT_HANDLER(I2C_IRQHandler, 29);                    /* I2C */

#endif /* !(_RAISONANCE_) && !(_SDCC_) */

#endif /* __STM8TL5X_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
