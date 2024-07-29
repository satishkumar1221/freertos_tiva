/*
 *  Mcal_Queue.c
 *
 * 
 */

#include "Mcal_Queue.h"




Generic_Queue_DataStruct V_Queue_Datastruct[TOTAL_NUMBER_OF_ELEMENTS]; 
size_compare V_Size_Queue_Datastruct[TOTAL_NUMBER_OF_ELEMENTS]; 


static void mem_cpy(void *dst,const void * src, uint32_t length);
static  inline void Validate_Queue_Data_Structure(Generic_Queue_Name queue_enum); 
void Update_Queue_DataStruct_size(Generic_Queue_Name queue_enum);



static void mem_cpy(void *dst,const void * src, uint32_t length)
{

   while(length--)
   {
       (*(uint8_t*)dst) = (*(uint8_t*)src);
      dst++;
      src++;
   }
}




static inline void Validate_Queue_Data_Structure(Generic_Queue_Name queue_enum)
{
    if((queue_enum >= (Generic_Queue_Name)0) && (queue_enum < TOTAL_NUMBER_OF_ELEMENTS)){
        if((V_Queue_Datastruct[queue_enum].front > V_Queue_Datastruct[queue_enum].size) || (V_Queue_Datastruct[queue_enum].front < QUEUE_EMPTY) ||
        (V_Queue_Datastruct[queue_enum].rear > V_Queue_Datastruct[queue_enum].size)  || (V_Queue_Datastruct[queue_enum].rear < QUEUE_EMPTY ) || 
        (V_Size_Queue_Datastruct[queue_enum].size != V_Queue_Datastruct[queue_enum].size) ||  (V_Size_Queue_Datastruct[queue_enum].size_of_datatype != V_Queue_Datastruct[queue_enum].size_of_datatype)) 	/*polyspace-begin MISRA2012:18.1 [Justified:Low] "Pointer points to the value inside the bounds" polyspace-end */
        {
            /*Reset the Queue as the memory corruption has occured*/
            V_Queue_Datastruct[queue_enum].front = QUEUE_EMPTY; 
            V_Queue_Datastruct[queue_enum].rear = QUEUE_EMPTY; 
            V_Queue_Datastruct[queue_enum].size = V_Size_Queue_Datastruct[queue_enum].size; 
            V_Queue_Datastruct[queue_enum].size_of_datatype = V_Size_Queue_Datastruct[queue_enum].size_of_datatype; 
            /* To Do : Trigger a reset if this happens */
        }
        else 
        {
            
        } 
    }
}



Queue_Stat process_enqueue(void *ptr_usrdata, Generic_Queue_Name queue_enum) 
{ 
    Queue_Stat ret_type = QUEUE_OK;
    uint8_t *ptr_initial_element = NULL_PTR;
    uint8_t *ptr_rear_element = NULL_PTR;
     
	Validate_Queue_Data_Structure(queue_enum); 
     if((ptr_usrdata != NULL_PTR) && (queue_enum<TOTAL_NUMBER_OF_ELEMENTS) && (queue_enum >= (Generic_Queue_Name)0)) /* NULL_PTR pointer check */       /* polyspace MISRA-C3:14.3 [Justified:Low] "Condition needed to perform range check for the array index." */
     {
        ptr_initial_element = (uint8_t *) V_Queue_Datastruct[queue_enum].ptr_initial_element;
        /*ptr_rear_element =  (uint8_t *)V_Queue_Datastruct[queue_enum].ptr_buffer;*/
   
    
            /* Check for the Queue FULL status */
            if((V_Queue_Datastruct[queue_enum].front == (V_Queue_Datastruct[queue_enum].rear + 1)) || (( V_Queue_Datastruct[queue_enum].front == 0 ) && (V_Queue_Datastruct[queue_enum].rear == (V_Queue_Datastruct[queue_enum].size - 1 ) )))	/*polyspace-begin RTE:OVFL [Justified:Low] "The value never gets over flow" polyspace-end*/ /* polyspace MISRA-C3:D4.1 [Justified:Low] "The value never gets over flow" */ /* polyspace MISRA-C3:D4.1 [Justified:Low] "The value never gets over flow" */
            {
                ret_type = FULL_QUEUE; 
                V_Queue_Datastruct[queue_enum].queue_status = FULL_QUEUE; 
            }
            else 
            {
                if(V_Queue_Datastruct[queue_enum].front == QUEUE_EMPTY)
                {
                    V_Queue_Datastruct[queue_enum].front = 0; 
                }
                
                V_Queue_Datastruct[queue_enum].rear = (((V_Queue_Datastruct[queue_enum].rear) + 1) % (V_Queue_Datastruct[queue_enum].size));
                ptr_rear_element = (ptr_initial_element + (V_Queue_Datastruct[queue_enum].rear * (sint32_t)V_Queue_Datastruct[queue_enum].size_of_datatype));
                mem_cpy(ptr_rear_element ,ptr_usrdata,V_Queue_Datastruct[queue_enum].size_of_datatype);
                V_Queue_Datastruct[queue_enum].queue_status = QUEUE_OK; 
            }
    }
    else
    {
        ret_type = NULL_PTR_PASSED; 
    }
    
     return(ret_type); 
       
}



Queue_Stat process_dequeue(void *ptr_user_data , Generic_Queue_Name queue_enum)
{

    Queue_Stat  ret_type = QUEUE_OK; 
    Validate_Queue_Data_Structure(queue_enum); 
if((queue_enum<TOTAL_NUMBER_OF_ELEMENTS) && (queue_enum >= (Generic_Queue_Name)0))
{
 
   /* check for the queue empty status */
   if(V_Queue_Datastruct[queue_enum].front == QUEUE_EMPTY)
   {
       ret_type = EMPTY_QUEUE; 
       V_Queue_Datastruct[queue_enum].queue_status = EMPTY_QUEUE; 
   }
   else
   {
       Get_Current_Elementfrom_Queue(ptr_user_data,queue_enum);
       /* Reset the Queue if the Front and Rear are equal */ 
       if((V_Queue_Datastruct[queue_enum].front) == (V_Queue_Datastruct[queue_enum].rear))
       {
           V_Queue_Datastruct[queue_enum].front = QUEUE_EMPTY; 
           V_Queue_Datastruct[queue_enum].rear = QUEUE_EMPTY;
           V_Queue_Datastruct[queue_enum].queue_status = EMPTY_QUEUE; 
           ret_type = EMPTY_QUEUE; 
       }
       else
       {
           V_Queue_Datastruct[queue_enum].front = ((V_Queue_Datastruct[queue_enum].front + 1) % (V_Queue_Datastruct[queue_enum].size));
           V_Queue_Datastruct[queue_enum].queue_status = QUEUE_OK;
       }
   }
}
   return(ret_type);
}



void Get_Current_Elementfrom_Queue(void *dest , Generic_Queue_Name queue_enum)
{
    uint8_t *src_address = NULL_PTR;


    /*Only get the user data if the queue is not empty . NULL_PTR pointer check is added here so no need to add it in dequeue */ 
    if((dest != NULL_PTR) && (queue_enum<TOTAL_NUMBER_OF_ELEMENTS) && (queue_enum >= (Generic_Queue_Name)0) && (V_Queue_Datastruct[queue_enum].queue_status != EMPTY_QUEUE))
    {
        uint8_t *ptr_initial_element = (uint8_t*)V_Queue_Datastruct[queue_enum].ptr_initial_element;
        src_address = (uint8_t*)((ptr_initial_element) + (V_Queue_Datastruct[queue_enum].front * (sint32_t)V_Queue_Datastruct[queue_enum].size_of_datatype));
        mem_cpy(dest, src_address , V_Queue_Datastruct[queue_enum].size_of_datatype);
    }
    else
    {
        
    }

}



void initlize_circular_queue(void *ptr_usr_buffer ,  uint32_t size_of_buffer , Generic_Queue_Name queue_enum , uint32_t size_of_datatype)
{
    if((ptr_usr_buffer != NULL_PTR) && (queue_enum<TOTAL_NUMBER_OF_ELEMENTS) && (queue_enum >= (Generic_Queue_Name)0))
    {
        V_Queue_Datastruct[queue_enum].ptr_buffer = ptr_usr_buffer;  
        V_Queue_Datastruct[queue_enum].front = QUEUE_EMPTY ;  
        V_Queue_Datastruct[queue_enum].rear = QUEUE_EMPTY; 
        V_Queue_Datastruct[queue_enum].size = (sint32_t)size_of_buffer;
        V_Queue_Datastruct[queue_enum].ptr_initial_element  = ptr_usr_buffer;
        V_Queue_Datastruct[queue_enum].size_of_datatype = size_of_datatype;
        V_Queue_Datastruct[queue_enum].queue_status = EMPTY_QUEUE;
        /*Update the refrence datatypes. These should never change*/ 
        V_Size_Queue_Datastruct[queue_enum].size = (sint32_t)size_of_buffer;
        V_Size_Queue_Datastruct[queue_enum].size_of_datatype = size_of_datatype;

    }

}

Queue_Stat Get_Queue_Status( Generic_Queue_Name queue_enum)
{
    Queue_Stat queueStatus = NULL_PTR_PASSED;
    if((queue_enum >= (Generic_Queue_Name)0) && (queue_enum < TOTAL_NUMBER_OF_ELEMENTS)){
        queueStatus = V_Queue_Datastruct[queue_enum].queue_status;
    }
    else{

    }

    return(queueStatus);
}
