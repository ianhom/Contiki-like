/******************************************************************************
* File       : Hello.c
* Function   : Basic app demo printf "Hello World!"
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 11th May 2016
* History    :  No.  When           Who           What
*               1    11/May/2016    Ian           Create
******************************************************************************/

#include "contiki.h"
#include <stdio.h> 

PROCESS(hello_world_process, "Hello world process");  
AUTOSTART_PROCESSES(&hello_world_process);

PROCESS_THREAD(hello_world_process, ev, data)
{

  PROCESS_BEGIN();

  printf("Hello World!\n");

  PROCESS_END();
}
