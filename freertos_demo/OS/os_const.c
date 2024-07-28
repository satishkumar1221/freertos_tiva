#include "os.h"

Task_control_Block Task_control_struct_core0[Total_Number_Of_Tasks] =
{
	{&task10ms  , "task10"  ,512 ,NULL ,10 ,&x_taskhandle[2] },
    {&task20ms  , "task20"  ,512 ,NULL ,10 ,&x_taskhandle[3]},
    {&task50ms  , "task50"  ,512 ,NULL ,10 ,&x_taskhandle[4] },
    {&task100ms , "task100" ,512 ,NULL ,10 ,&x_taskhandle[5]},
    {&task200ms , "task200" ,512 ,NULL ,10 ,&x_taskhandle[6] },
    {&task500ms , "task500" ,512 ,NULL ,10 ,&x_taskhandle[7]},
    {&task1000ms, "task500" ,512 ,NULL ,10 ,&x_taskhandle[8]},
    //{&Hpriotsk  , "hpritsk" ,CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE ,NULL ,12 ,&x_taskhandle[6] ,(int)core0}, 
    {&task2000ms  ,"task2000" ,256 ,NULL ,10 ,&x_taskhandle[9]}

};
