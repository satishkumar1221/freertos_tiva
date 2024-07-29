/**
 * @author Satish Kumar B.B. 
 * @email satishkumar1221@gmail.com
 * @create date 2021-09-21 00:55:08
 * @modify date 2021-09-21  00:55:08
 * @desc Contains details about operating system implementation */ 
#include "os.h"   
#include <stdint.h>
#include "adc.h"


//#include "adc_appl.h"
//#include "spi.h"

//#include "nvm.h"
#define TWDT_TIMEOUT_S 1 //1 seconds
#define OS_NULL ((void *)0)
uint64_t os_task_counters[Total_Number_Of_Tasks] = {0};
int task_create_status[Total_Number_Of_Tasks];
TaskHandle_t x_taskhandle[Total_Number_Of_Tasks] = {NULL};
static Task_Usage_Struct V_task_exec_stat; 
static Task_Complete_Stat task_exec_stat;



/*Function was added in this file to avoid unnecessary cyclic includes for headers */

/* Static Function Definitions */

 void invoke_tasks_core0();
 void os_start();
void task_execution_stat(Task_rate task_exec ,  set_clr_stat status);
static void Get_Stack_sizes();


#define Set_Clear_bits_TskRate(task_exec,status,shift) (status ==((set_clr_stat)set)) ? (Set_bits_32(&task_exec_stat.R,(1 << shift))) : (Clear_bits_32(&task_exec_stat.R,(1 << shift)))

static void Mcal_Init()
{
    Initilize_ADC();
}
/**system initilization sequence */
 void system_initilazation_sequence()
{

		//initilization_routine();
       // initlize_drivers();
        //init_mcpwm();
        //Enable_freerunning_Timer(0);
		/*invoke all the Tasks */
         Mcal_Init();
		invoke_tasks_core0();
		/*Enable the interrupts*/


	}


/** Function to invoke tasks for core 0 */
void invoke_tasks_core0()
{
	int i =0;
	//Get_Chip_Info();
    for(i = start_os_tasks ; i < Total_Number_Of_Tasks ; i++ )
	{
	  task_create_status[i] = xTaskCreate(Task_control_struct_core0[i].task_func_ptr, Task_control_struct_core0[i].task_name, Task_control_struct_core0[i].stack_depth ,
			  OS_NULL ,(Task_control_struct_core0[i].task_priority),((TaskHandle_t)( Task_control_struct_core0[i].pv_createdtask))
                            );

	}
}


/** 20 ms cyclic task rate. This function is run periodic every 20 milli seconds */
void task20ms()
{

     TickType_t xLastWakeTime = xTaskGetTickCount ();
     const TickType_t xDelay20ms = pdMS_TO_TICKS(20);
     for(;;)
     {
		// task_exec_stat()
		 os_task_counters[cyclic_task_20ms] = os_task_counters[cyclic_task_20ms]+1;

		 Read_value_ADC();
		// os_task20ms_if();
		 /*Keep this at the end of the task*/
		 ADC_Sequencer_Runnable_task();
		 #if ENABLE_WDG
		 if(!Verify_bits(task_exec_stat.R,ms20task_setbit))
  		 {
			   task_execution_stat(cyclic_task_20ms,set);
			   esp_task_wdt_reset();
		 }
		 #endif


    	 vTaskDelayUntil( &xLastWakeTime, xDelay20ms);
     }
}


/** 50 ms cyclic task rate. This function is run periodic every 50 milli seconds */
void task50ms()
{
	/*Execute only if the Bit is not set */
   
   TickType_t xLastWakeTime = xTaskGetTickCount ();
   const TickType_t xDelay50ms = pdMS_TO_TICKS(50);

   for(;;)
   {
	   os_task_counters[cyclic_task_50ms] = os_task_counters[cyclic_task_50ms]+1;
	  // os_task50ms_if();

	   vTaskDelayUntil( &xLastWakeTime, xDelay50ms);
   }

}
/** 100 ms cyclic task rate. This function is run periodic every 100 milli seconds */
void task100ms()
{ 
	
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay100ms = pdMS_TO_TICKS(100);
    for(;;)
    {
		
    	os_task_counters[cyclic_task_100ms] = os_task_counters[cyclic_task_100ms]+ 1;
    	// os_task100ms_if();
    	vTaskDelayUntil( &xLastWakeTime, xDelay100ms);

    }
}

/** 200 ms cyclic task rate. This function is run periodic every 200 milli seconds */
void task200ms()
{
	TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
   for(;;)
   {
	   
	 
	  
	   os_task_counters[cyclic_task_200ms] = os_task_counters[cyclic_task_200ms]+ 1;
	   //os_task200ms_if();
	   #if ENABLE_WDG
	   if(!Verify_bits(task_exec_stat.R,ms200task_setbit))
       {
		 task_execution_stat(cyclic_task_200ms,set);
    	 esp_task_wdt_reset();
       }
	   #endif
	   vTaskDelayUntil( &xLastWakeTime, xDelay200ms);
   }
}

/** 500 ms cyclic task rate. This function is run periodic every 500 milli seconds */
void task500ms()
{

  TickType_t xLastWakeTime = xTaskGetTickCount ();
  const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

  for(;;)
  {
	  
	  os_task_counters[cyclic_task_500ms] = os_task_counters[cyclic_task_500ms]+1;

	  #if ENABLE_WDG
	  if(!Verify_bits(task_exec_stat.R,ms500task_setbit))
      {
		task_execution_stat(cyclic_task_500ms,set);
    	esp_task_wdt_reset();
      }
	  #endif 

	  vTaskDelayUntil( &xLastWakeTime, xDelay500ms);
  }
}

/** 1000 ms cyclic task rate. This function is run periodic every 1000 milli seconds */
void task1000ms()
{

  TickType_t xLastWakeTime = xTaskGetTickCount ();
  const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);

  for(;;)
  {
	 
	
	 os_task_counters[cyclic_task_1000ms] = os_task_counters[cyclic_task_1000ms]+1;

	 #if ENABLE_WDG
	 if(!Verify_bits(task_exec_stat.R,ms1000task_setbit))
     {
		task_execution_stat(cyclic_task_1000ms,set);
    	esp_task_wdt_reset();
     }
	 #endif 
     Get_Stack_sizes();
	 vTaskDelayUntil( &xLastWakeTime, xDelay1000ms);
  }
}

/** 2000 ms cyclic task rate. This function is run periodic every 2000 milli seconds */
void task2000ms()
{
	/*Task is created to monitor all the tasks. Take a look at the timing in the esp idf menuconfig.*/
	/*clearing all the flags must be done in this function. */
	TickType_t xLastWakeTime = xTaskGetTickCount ();
    const TickType_t xDelay2000ms = pdMS_TO_TICKS(2000);
	for(;;)
	{
		#if ENABLE_WDG
		if(!Verify_bits(task_exec_stat.R,ms2000task_setbit))
        {
			task_execution_stat(cyclic_task_2000ms,set);
    		esp_task_wdt_reset();
        }
		if(Are_AllBits_Set_32(&task_exec_stat.R,calculate_totaltaskmask()))
		{
			  //clear all 
			  task_exec_stat.R = 0x00 ; 
		}
        #endif 

		vTaskDelayUntil( &xLastWakeTime, xDelay2000ms);
	}
}

/** High Priority task to record the events from BLE and Wifi.  */
void Hpriotsk()
{

 const TickType_t xDelay = pdMS_TO_TICKS(20);
 for(;;)
 {
    
	 //os_task_counters[Event_Based_High_Priority_Task] = os_task_counters[Event_Based_High_Priority_Task]+1;
	 #if ENABLE_WDG
	 if(!Verify_bits(task_exec_stat.R,EventBasedPriorityTask_Setbit))
	         {
	 		//	task_execution_stat(Event_Based_High_Priority_Task,set);
	     	//	esp_task_wdt_reset();
	         }
	#endif
	 vTaskDelay(xDelay);
 }
}



void task10ms()
{
	 TickType_t xLastWakeTime = xTaskGetTickCount ();

	 ADC_StateMachine();
		 const TickType_t xDelay10ms = pdMS_TO_TICKS(10);
		for(;;)
		{
			 os_task_counters[cyclic_task_10ms] = os_task_counters[cyclic_task_10ms]+1;
			// os_task10ms_if();
					 /*Keep this at the end of the task*/

			 vTaskDelayUntil( &xLastWakeTime, xDelay10ms);
		}

}



/** Watch Dog execution status. The bits for a task can be set if the task is executed sucessfully */
void task_execution_stat(Task_rate task_exec , set_clr_stat status)
{
  switch(task_exec)
  {
	  case cyclic_task_20ms : Set_Clear_bits_TskRate(task_exec,status,ms20task_setbit);
	  						  break; 
	  case cyclic_task_50ms : Set_Clear_bits_TskRate(task_exec,status,ms50task_setbit);
	  						   break; 
	  case cyclic_task_100ms : Set_Clear_bits_TskRate(task_exec,status,ms100task_setbit);
	  						   break; 
      case cyclic_task_200ms : Set_Clear_bits_TskRate(task_exec,status,ms200task_setbit);
	  						   break; 
	  case cyclic_task_500ms : Set_Clear_bits_TskRate(task_exec,status,ms500task_setbit);
	  							break; 
	  case cyclic_task_1000ms : Set_Clear_bits_TskRate(task_exec,status,ms1000task_setbit);
	  						    break; 
	  case cyclic_task_2000ms : Set_Clear_bits_TskRate(task_exec,status,ms2000task_setbit);
	  							break; 
	  default : 
	           break;

  }
}


void os_printf()
{
    printf(" OS File is successfully included ");
}

static void Get_Stack_sizes()
{
    uint32_t task_usage = 0; 
    int itr = 0;
	/*This functions give amount of the */
	for(itr = 0 ; itr < Total_Number_Of_Tasks ; itr++ )
	{
		/*V_task_exec_stat will be converted to percentage if we get default stack allocated */
	//	V_task_exec_stat.Stackusage_tasks[itr] = uxTaskGetStackHighWaterMark(&x_taskhandle[itr]);
		if (V_task_exec_stat.Stackusage_tasks[itr] == 0 )
		{
             V_task_exec_stat.stack_diag_status.R = (V_task_exec_stat.stack_diag_status.R | (V_task_exec_stat.stack_diag_status.R << itr)); 
		}
	}
	
}
