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

#ifdef ORIGINAL_CODE

PROCESS(hello_world_process, "Hello world process");    /* Define a process      */
AUTOSTART_PROCESSES(&hello_world_process);              /* Make it auto starting */

PROCESS_THREAD(hello_world_process, ev, data)           /* Procss body           */
{

  PROCESS_BEGIN();                                      /* The start of process  */

  printf("Hello World!\n");                             /* Just do it......later */

  PROCESS_END();                                        /* The end of process    */
}

#else
/********************************************************************************/
/* Let's translate: */
/* PROCESS(hello_world_process, "Hello world process"); */
static char process_thread_hello_world_process(struct pt *process_pt, process_event_t ev, process_data_t data); /* Function declaration */
struct process hello_world_process = 
{
    NULL,
    "Hello world process",
    process_thread_hello_world_process,
    {0},
    0,
    0
};                                                     /* Data structure of process. */

/* AUTOSTART_PROCESSES(&hello_world_process); */
struct process * const autostart_processes[] = 
{
    &hello_world_process,
    NULL;
};                                                     /* Array of auto starting processes */

/* PROCESS_THREAD(hello_world_process, ev, data) */
static char process_thread_hello_world_process(struct pt *process_pt, process_event_t ev, process_data_t data)
{
    /* PROCESS_BEGIN(); */
    {
        char PT_YIELD_FLAG = 1;                   /* Set Yield flag first */
        if (PT_YIELD_FLAG)
        {
            ;                                     /* ?? Do something here ?? */
        }
        switch (process_pt->lc)                   /* Check run with which line */
        {
            case 0:                               
                ;
                printf("Hello World!\n");         /* Your works here*/
            
    /* PROCESS_BEGIN(); */
        };
        PT_YIELD_FLAG  = 0;
        process_pt->lc = 0;;
        return PT_ENDED;
    };
}
#endif

/* End of file */
