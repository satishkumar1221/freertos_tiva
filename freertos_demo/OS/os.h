#pragma once

#include<stdio.h> 
#include<stdint.h>

#include "FreeRTOS.h"
#include "task.h"

#include "task.h"
#include "api.h"

/* Macro Definitions */
#define get_scheduler_status_core0() (port_xSchedulerRunning == 1 ) ? 1 : 0

/*Add*/
#define ms20task_setbit  0
#define ms50task_setbit  1 
#define ms100task_setbit 2
#define ms200task_setbit 3 
#define ms500task_setbit 4 
#define ms1000task_setbit 5 
/*One more Task added to monitor all other tasks*/
#define EventBasedPriorityTask_Setbit 6
#define ms2000task_setbit 7


#define CHECK_ERROR_CODE(returned, expected) ({                        \
            if(returned != expected){                                  \
                printf("TWDT ERROR\n");                                \
                abort();                                               \
            }                                                          \
})

typedef enum 
{
	start_os_tasks = 0U,
	cyclic_task_10ms = start_os_tasks,
    cyclic_task_20ms ,
    cyclic_task_50ms,
    cyclic_task_100ms,
    cyclic_task_200ms,
    cyclic_task_500ms,
    cyclic_task_1000ms,
   // Event_Based_High_Priority_Task, 
    cyclic_task_2000ms,
    Total_Number_Of_Tasks

}Task_rate; 

typedef union 
{
    uint32_t R; 
    struct 
    {
       uint32_t cyclictask20ms:1; 
       uint32_t cyclictask50ms:1;
       uint32_t cyclictask100ms:1;  
       uint32_t cyclictask200ms:1; 
       uint32_t cyclictask500ms:1; 
       uint32_t cyclictask1000ms:1; 
      /// uint32_t EventBasedPriorityTask:1; 
       uint32_t cyclictask2000ms:1;
       uint32_t Reserved : 25;
    };
}Task_Complete_Stat; 

typedef union  
{
   uint16_t  R; 
   struct 
   {
      uint16_t cyclictask_20ms_overflow : 1;
      uint16_t cyclictask_50ms_overflow : 1;
      uint16_t cyclictask_100ms_overflow : 1;
      uint16_t cyclictask_200ms_overflow : 1;
      uint16_t cyclictask_500ms_overflow : 1;
      uint16_t cyclictask_1000ms_overflow : 1;
      uint16_t cyclictask_2000ms_overflow : 1;
   }Diagnostics;
}Stack_Diagnostic_Status; 

 typedef struct 
 {
     uint32_t Stackusage_tasks[Total_Number_Of_Tasks]; 
     Stack_Diagnostic_Status stack_diag_status; 
 }Task_Usage_Struct; 




typedef enum
{
	scheduler_notrunning,
	scheduer_running

}scheduler_status;

typedef enum 
{
    core0, 
    core1
}coreid;

typedef enum 
{
    set,
    clear
}set_clr_stat; 

/*typedef enum 
{
   high_priority_task = 15, 

}priority;*/ 
typedef struct 
{
    void (*task_func_ptr)();
    const char task_name[10];
    uint32_t stack_depth; 
    void *pv_parameters; 
    int task_priority; 
    void *pv_createdtask;
    int coreid;

}Task_control_Block;




/* Global Variables */
extern  Task_control_Block Task_control_struct_core0[Total_Number_Of_Tasks];
extern uint64_t os_task_counters[Total_Number_Of_Tasks];
extern volatile int port_xSchedulerRunning;
extern TaskHandle_t x_taskhandle[Total_Number_Of_Tasks];

/* Function Prototypes */

extern void system_initilazation_sequence();

void wake_up_core1();

void os_printf(); 

extern void task20ms();

void task50ms();

void task100ms();

void task200ms();

void task500ms();

void task1000ms();

void task2000ms();

void invoke_tasks_core0();


void Hpriotsk(); 
void task10ms();
void task2ms();
void task1ms();
/*inline functions */

inline uint32_t calculate_totaltaskmask()
{
    uint32_t returnvalue_mask = 0;
    int i = 0;
    for( i = 0 ; i < Total_Number_Of_Tasks ;i++ )
    {
          Set_bits_32(&returnvalue_mask,(1<<i));
    }
    return(returnvalue_mask);
}

/* Mutexes for acquiring the SPI BUS */
