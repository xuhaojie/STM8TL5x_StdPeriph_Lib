/** @page TIM2_PWM_DutyCycleConfiguration TIM2 - Generate two different signals with two different duty cycles 
  
  @verbatim
  *********************** (C) COPYRIGHT STMicroelectronics *********************
  * @file    TIM2/TIM2_PWM_DutyCycleConfiguration/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    06-March-2012
  * @brief   Generate two different signals with two different duty cycles 
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
  @endverbatim


  @par Example description

  This example shows how to configure the TIM2 peripheral in PWM (Pulse Width Modulation) 
  mode.
  
  The TIM2CLK frequency is 2MHz with a Prescaler of 1.

  The TIM2 CCR1 register value is equal to 32767, so the TIM2 Channel 1 generates a 
  PWM signal with a frequency equal to 30 Hz and a duty cycle equal to 50%:
  TIM2 Channel1 duty cycle = [TIM2_CCR1/(TIM2_ARR + 1)] * 100 = 50%

  The TIM2 CCR2 register value is equal to 16383, so the TIM2 Channel 2 generates a 
  PWM signal with a frequency equal to 30 Hz and a duty cycle equal to 25%:
  TIM2 Channel2 duty cycle = [TIM2_CCR2/ (TIM2_ARR + 1)] * 100 = 25%


  The PWM waveform can be monitored on an oscilloscope.


  @par Directory contents

  - TIM2\TIM2_PWM_DutyCycleConfiguration\main.c                      Main file containing the "main" function
  - TIM2\TIM2_PWM_DutyCycleConfiguration\stm8tl5x_conf.h             Library Configuration file
  - TIM2\TIM2_PWM_DutyCycleConfiguration\stm8tl5x_it.c               Interrupt routines source
  - TIM2\TIM2_PWM_DutyCycleConfiguration\stm8tl5x_it.h               Interrupt routines declaration


  @par Hardware and Software environment

  - This example runs on STM8TL5x devices.

  - This example has been tested on a generic
    board and ST Visual Develop (STVD) toolchain (Cosmic and Raisonance compilers).
    And can be easily tailored to any other development board.
    
  - Board Set-up
    - Connect the following pins to an oscilloscope:
    - TIM2_CH1 pin (GPIOD.4)  
    - TIM2_CH2 pin (GPIOD.5)  


  @par How to use it ?

  In order to make the program work, you must do the following :
  - Create a project and setup all project configuration
  - Add the required Library files :
    - stm8tl5x_tim2.c
    - stm8tl5x_gpio.c
    - stm8tl5x_clk.c
  

  - Rebuild all files: Build-> Rebuild all. 
  - Load project image: Debug->Start Debugging
  - Run program: Debug->Run (Ctrl+F5)
  - Connect TIM2_CH1 and TIM2_CH2 pins to an oscilloscope.
  
* <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
*/
