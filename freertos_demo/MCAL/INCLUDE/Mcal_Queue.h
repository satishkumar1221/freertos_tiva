/*
 *  Queue.h
 *  Description : General Purpose Queue API to be used throughout the project.
 *  Author: satish.kumar
 *  Revision  : 1.0 
 */

#ifndef MCAL_QUEUE_H
#define MCAL_QUEUE_H

#include<stdint.h>
#include "api.h"

/*Macro Defanitions */
#define QUEUE_EMPTY -1

#define NULL_PTR (void*) 0
/* Enumeration and Type Declarations  */
typedef enum 
{
    QUEUE_OK = 0, 
    EMPTY_QUEUE, 
    FULL_QUEUE, 
    NULL_PTR_PASSED 
}Queue_Stat;

typedef int sint32_t;

typedef enum
{
    Init, 
    Run
}statemachine;

typedef enum 
{
   Enqueue, 
   Dequeue 
}Operation;

/*Add the new enumeration here every time user wants to use the queue API. */
typedef enum 
{
    ADC_MANGMT_STATUS,
    TOTAL_NUMBER_OF_ELEMENTS

}Generic_Queue_Name;

typedef struct 
{
    void *ptr_buffer;  /*Pointer to user buffer*/
    sint32_t front;
    sint32_t rear;
    sint32_t size;
    uint32_t size_of_datatype;
    void *ptr_initial_element;
    Queue_Stat queue_status;  
    

}Generic_Queue_DataStruct;

typedef struct
{
    sint32_t size;
    uint32_t size_of_datatype;
}size_compare;





extern Queue_Stat process_enqueue(void *ptr_usrdata, Generic_Queue_Name queue_enum);  
extern Queue_Stat process_dequeue(void *ptr_user_data , Generic_Queue_Name queue_enum);
extern void Get_Current_Elementfrom_Queue(void *dest , Generic_Queue_Name queue_enum);

extern void initlize_circular_queue(void *ptr_usr_buffer ,  uint32_t size_of_buffer , Generic_Queue_Name queue_enum , uint32_t size_of_datatype);
extern Queue_Stat Get_Queue_Status( Generic_Queue_Name queue_enum); 
extern Generic_Queue_DataStruct V_Queue_Datastruct[TOTAL_NUMBER_OF_ELEMENTS];
extern size_compare V_Size_Queue_Datastruct[TOTAL_NUMBER_OF_ELEMENTS];

#endif
