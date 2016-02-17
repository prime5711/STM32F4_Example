#include "hal_uart_printf.h"

size_t __write(int handle, uint8_t *buf, size_t bufSize)
{ 
    size_t nChars = 0; 
    if(handle == -1) return 0;
    else if(handle != 1 && handle != 2) return -1;
 
    for(;bufSize> 0; --bufSize)
    {
        HAL_UART_Transmit(&PRINTF_UART_PORT, buf, 1 ,1);
        ++buf;
        ++nChars;
    } 
 
    return nChars;
}
