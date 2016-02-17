/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
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
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include <stdio.h>
#include "stm32f_shcho.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myWriteTaskHandle;
osThreadId myVsyncTaskHandle;
osThreadId myUartTaskHandle;
osThreadId myTask05Handle;
osMessageQId myQueueUartHandle;
osTimerId myTimer01Handle;
osTimerId myTimer02Handle;
osMutexId myMutexVsyncHandle;

/* USER CODE BEGIN Variables */
osThreadId LEDThread1Handle, LEDThread2Handle;

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartWriteTask(void const * argument);
void StartVyncTask(void const * argument);
void StartUartTask(void const * argument);
void StartTask05(void const * argument);
void Callback01(void const * argument);
void HAK_IncTick(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* Create the mutex(es) */
  /* definition and creation of myMutexVsync */
  osMutexDef(myMutexVsync);
  myMutexVsyncHandle = osMutexCreate(osMutex(myMutexVsync));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of myTimer01 */
  osTimerDef(myTimer01, Callback01);
  myTimer01Handle = osTimerCreate(osTimer(myTimer01), osTimerPeriodic, NULL);

  /* definition and creation of myTimer02 */
  osTimerDef(myTimer02, HAK_IncTick);
  myTimer02Handle = osTimerCreate(osTimer(myTimer02), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myWriteTask */
  osThreadDef(myWriteTask, StartWriteTask, osPriorityNormal, 0, 128);
  myWriteTaskHandle = osThreadCreate(osThread(myWriteTask), NULL);

  /* definition and creation of myVsyncTask */
  osThreadDef(myVsyncTask, StartVyncTask, osPriorityNormal, 0, 128);
  myVsyncTaskHandle = osThreadCreate(osThread(myVsyncTask), NULL);

  /* definition and creation of myUartTask */
  osThreadDef(myUartTask, StartUartTask, osPriorityHigh, 0, 128);
  myUartTaskHandle = osThreadCreate(osThread(myUartTask), NULL);

  /* definition and creation of myTask05 */
  osThreadDef(myTask05, StartTask05, osPriorityIdle, 0, 128);
  myTask05Handle = osThreadCreate(osThread(myTask05), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  /* Configure LED1 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED4);
  BSP_LED_Off(LED2);
  BSP_LED_Off(LED4);

  
  /* Thread 1 definition */
  osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
   /*  Thread 2 definition */
  osThreadDef(LED3, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
  /* Start thread 1 */
  LEDThread1Handle = osThreadCreate (osThread(LED1), NULL);
  
  /* Start thread 2 */
  LEDThread2Handle = osThreadCreate (osThread(LED3), NULL);

  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of myQueueUart */
  osMessageQDef(myQueueUart, 32, uint8_t);
  myQueueUartHandle = osMessageCreate(osMessageQ(myQueueUart), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* StartWriteTask function */
void StartWriteTask(void const * argument)
{
  /* USER CODE BEGIN StartWriteTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartWriteTask */
}

/* StartVyncTask function */
void StartVyncTask(void const * argument)
{
  /* USER CODE BEGIN StartVyncTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartVyncTask */
}

/* StartUartTask function */
void StartUartTask(void const * argument)
{
  /* USER CODE BEGIN StartUartTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartUartTask */
}

/* StartTask05 function */
void StartTask05(void const * argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask05 */
}

/* Callback01 function */
void Callback01(void const * argument)
{
  /* USER CODE BEGIN Callback01 */
  
  /* USER CODE END Callback01 */
}

/* HAK_IncTick function */
void HAK_IncTick(void const * argument)
{
  /* USER CODE BEGIN HAK_IncTick */
  
  /* USER CODE END HAK_IncTick */
}

/* USER CODE BEGIN Application */

/**
  * @brief  Toggle LED1 and LED4 thread
  * @param  thread not used
  * @retval None
  */
static void LED_Thread1(void const *argument)
{
  uint32_t count = 0;
  (void) argument;
	uint32_t count1 = 0;
  
  for(;;)
  {
    count = osKernelSysTick() + 4800;
    
		count1 = 0 ;
    /* Toggle LED1 every 200 ms for 4.8 s */
    while (count >= osKernelSysTick())
    {
      BSP_LED_Toggle(LED1);
      osDelay(200);

     	printf("1-1=%d.\n",count1++); 
    }
    
    /* Turn off LED1 */
    BSP_LED_Off(LED1);
    
    /* Suspend Thread 1 */
    osThreadSuspend(NULL);
    
    count = osKernelSysTick() + 4800;
    
		count1 = 0 ;
    /* Toggle LED1 every 400 ms for 4.8 s */
    while (count >= osKernelSysTick())
    {
      BSP_LED_Toggle(LED1);
      osDelay(400);

     	printf("1-2=%d.\n",count1++); 
    }
    printf("======================================\n"); 

    /* Resume Thread 2*/
    osThreadResume(LEDThread2Handle);
  }
}

/**
  * @brief  Toggle LED3 thread
  * @param  argument not used
  * @retval None
  */
static void LED_Thread2(void const *argument)
{
  uint32_t count;
  (void) argument;
  uint32_t count2;
  
  for(;;)
  {
    count = osKernelSysTick() + 10000;
    
		count2 = 0 ;
    /* Toggle LED3 every 500 ms for 10 s */
    while (count >= osKernelSysTick())
    {
      BSP_LED_Toggle(LED3);
      osDelay(500);

			printf("2=%d\n",count2++);

    }
    
    /* Turn off LED3 */
    BSP_LED_Off(LED3);
    
    /* Resume Thread 1 */
    osThreadResume(LEDThread1Handle);
    
    /* Suspend Thread 2 */
    osThreadSuspend(NULL);  
  }
}	     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
