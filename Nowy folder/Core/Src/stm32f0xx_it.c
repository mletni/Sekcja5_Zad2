/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f0308_discovery.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t msg_t[] = {
		1,1,1,1,3,		/* H */
		1,2,3,			/* a */
		1,2,1,1,3,		/* l */
		2,2,2,			/* o */
		4,				/*   */
		2,3,			/* t */
		1,1,2,			/* u */
		4,				/*   */
		1,1,1,3,		/* s */
		1,3,			/* e */
		2,1,2,3,		/* k */
		2,1,2,1,3,		/* c */
		1,2,2,2,3,		/* j */
		1,2,			/* a */
		4,				/*   */
		1,2,2,1,3,		/* p */
		1,1,3,			/* i */
		1,2,1,2,3,		/* ą */
		1,3,			/* t */
		1,2,			/* a */

};
uint8_t send = 0;
uint8_t el = 0;
uint8_t size_of_msg = sizeof(msg_t)/sizeof(msg_t[0]);
int8_t counter = -1;
int8_t my_delay = 0;
int8_t current_delay = 0;
int8_t dot = 100;
int8_t dash = 300;
int8_t ele_gap = 100;
int8_t sign_gap = 300;
int8_t word_gap = 700;
int8_t element_switcher = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void morse(){
	switch(el){
	case 1:
		element_switcher = 2;
		my_delay = 0;
		current_delay = dot;
		BSP_LED_On(LED_GREEN);
		break;
	case 2:
		element_switcher = 2;
		my_delay = 0;
		current_delay = dash;
		BSP_LED_On(LED_GREEN);
		break;
	case 3:
		my_delay = 0;
		current_delay = sign_gap;
		BSP_LED_Off(LED_GREEN);
		break;
	case 4:
		my_delay = 0;
		current_delay = word_gap;
		BSP_LED_Off(LED_GREEN);
		break;
	}
}
void send_message(){
		counter = counter + 1;
		el = msg_t[counter];
		morse();
}
void execute_ele_gap()
{
	element_switcher = 1;
	my_delay = 0;
	current_delay = ele_gap;
	BSP_LED_Off(LED_GREEN);
}
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	my_delay++;
	if(my_delay > current_delay){
		switch(element_switcher)
		{
		case(1):
			{
				send_message();
			}
		case(2):
			{
				execute_ele_gap();
			}
		}
	}

	/*BSP_LED_Toggle(LED_GREEN);*/
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 0 and 1 interrupts.
  */
void EXTI0_1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_1_IRQn 0 */
	if(counter>=size_of_msg || counter < 0){
		counter = -1;
	}

  /* USER CODE END EXTI0_1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_1_IRQn 1 */

  /* USER CODE END EXTI0_1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
