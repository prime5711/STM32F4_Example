Example for

using  STM32F4_Example_FreeRTOS_Alarm_Wakeup_printf.ioc as Template

1. printf  using UART2
2. Trasnmit using blockiing/Non-blocking 
3. Thread  Pause/Resume
4. Alarm : Not Periodic
5. Wakeup : Could not debug(in interrupt handler does not display printf)  during debugging using Debugger HW
6. If Alarm and Wakeup interrupt occurs at same time .
     according to  Cortex-M4 Interrupt handling scheme, it handles  both
		 But Alarm occurs before Wakeup ????

