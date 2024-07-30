/*
 * adc_sync.c
 *
 *  Created on: Jul 27, 2024
 *      Author: satis
 */

#include "adc.h"


typedef enum
{
    START,
    BUSY,
    RESULTS,
    STOP

}State_machine_ADC;


typedef union
{
    uint32_t R;

    struct
    {
       uint8_t TPTR :4 ; /*tail pointer*/
       uint8_t HPTR :4 ; /*head pointer*/
       uint8_t FIFO_emptystat : 1;/*FIFO empyt status */
       uint8_t reserved :3;
       uint8_t FIFO_Fullstat :1 ;
      // uint8_t Reser:10;

    }B;

}FIFO_status;

FIFO_status V_ADC_FIFO_Status;

#define ADCSSFSTAT_0 (volatile uint32_t*) 0x4003804C
#define ADCSSFSTAT_1 (volatile uint32_t*) 0x4003904C





uint8_t Get_GSYNC_Status_ADC(ADC_Sampler sampler , ADC_TYPE adc_type)
{
    uint8_t status = 0U;
    uint8_t bit_Stat = 0 ;
    if(adc_type == ADC0)
    {

        bit_Stat = Reg_Are_AllBits_Set_32(ADCPSSI(0),GSYNC_BIT);
        if(bit_Stat >0U)
        {
            status = 1U;
        }
        else
        {
            status = 0U;
        }
    }
    else
    {
        bit_Stat = Reg_Are_AllBits_Set_32(ADCPSSI(1),GSYNC_BIT);
               if(bit_Stat >0U)

               {
                   status = 1U;
               }
               else
               {
                   status = 0U;
               }
    }

    return(status);

}
uint8_t Get_SYNCWAIT_Status_ADC(ADC_Sampler sampler , ADC_TYPE adc_type)
{

    uint8_t status = 0U;
    uint8_t bit_Stat = 0;
    if(adc_type == ADC0)
    {

        bit_Stat = Reg_Are_AllBits_Set_32(ADCPSSI(0),SYNCWAIT_BIT);
        if(bit_Stat >0U)
        {
            status = 1U;
        }
        else
        {
            status = 0U;
        }
    }
    else
    {
        bit_Stat = Reg_Are_AllBits_Set_32(ADCPSSI(1),SYNCWAIT_BIT);
               if(bit_Stat >0U)
               {
                   status = 1U;
               }
               else
               {
                   status = 0U;
               }
    }

    return(status);

}


void Set_GSYNC_Status_ADC(ADC_Sampler sampler , ADC_TYPE adc_type)
{
;
    if(adc_type == ADC0)
    {
        set_bits_mask_reg((ADCPSSI(0)) , GSYNC_BIT);
    }
    else
    {
        set_bits_mask_reg((ADCPSSI(1)) , GSYNC_BIT);
    }



}
void  Set_SYNCWAIT_Status_ADC(ADC_Sampler sampler , ADC_TYPE adc_type)
{


    if(adc_type == ADC0)
    {
        set_bits_mask_reg((ADCPSSI(0)) , SYNCWAIT_BIT);
    }
    else
    {
        set_bits_mask_reg((ADCPSSI(0)) , SYNCWAIT_BIT);
    }



}

/*The low level drivier is being writtrn in a polling based approach here*/


void start_Sequence_ADC(ADC_Values sensorname)
{


    ADC_Config *config_adc = &C_ADC_Config[sensorname];

    if(config_adc->adc_type == ADC0)
    {
        /*ADC SSCTL */
        *ADCSSCTL_0|=config_adc->ADC_CTLREG_CONFIG;
        *ADCPSSI_0|= (1 << config_adc->sampler);
        /*ADC PSSI */


    }
    else
    {
        reg_write(ADCSSCTL_1,config_adc->ADC_CTLREG_CONFIG);
    }
    //reg_write()
}



#if 0
void Request_ADC_GetResult( ADC_Values sensorname)
{
  //  uint32_t temp_select_ctlreg = port | (1U <<adc_pinnumber);

     switch(sensorname)
     {
     case PORTE_PIN0_MASK : start_Sequence_ADC(sensorname);

                            break;
     case PORTE_PIN1_MASK :
                            break;
     case PORTE_PIN2_MASK :
                             break;
     case PORTE_PIN3_MASK :
                              break;
      default :
     }



}

#endif

ADC_Values Read_sensorvalue;
void ADC_Sequencer_Runnable_task()
{
     uint8_t i =0U;

     /*temp logic for queue synchronization */
     Queue_Stat queue_stat = Get_Queue_Status(ADC_MANGMT_STATUS);
     uint8_t sensortype;
     if(queue_stat == EMPTY_QUEUE)
     {
         for (i = 0 ; i < Total_sensors ; i++ )
         {
             if(queue_stat != FULL_QUEUE)
             {
                 process_enqueue(&i ,ADC_MANGMT_STATUS );
             }
         }
     }

     /*Peek from the queue to get the current element*/

     //xQueuePeek(xQueue_adc , &i , 0);

     ADC_StateMachine();
}



uint8_t Validate_FIFO_LLD(ADC_TYPE adc)
{
    /*  SS0  has 8 samples and ss1 has 4 samples */
     uint8_t status;
    if(adc == ADC0)
      {
            V_ADC_FIFO_Status.R = (*ADCSSFSTAT_0);

      }
    else
    {
        V_ADC_FIFO_Status.R = *ADCSSFSTAT_1;
    }

    if(V_ADC_FIFO_Status.B.FIFO_Fullstat == 1)
                {
                    status = TRUE;
                }

                else
                {
                    status = FALSE;
                }


    return(status);



}

#define OUTPUT_FIFOBUFFER_00 (*(volatile uint32_t*)0x40038048)
#define OUTPUT_FIFOBUFFER_01 (*(volatile uint32_t*)0x40038068)
#define OUTPUT_FIFOBUFFER_02 (*(volatile uint32_t*)0x40038088)
#define OUTPUT_FIFOBUFFER_03 (*(volatile uint32_t*)0x400380A8)
#define OUTPUT_FIFOBUFFER_10 (*(volatile uint32_t*)0x40039048)
#define OUTPUT_FIFOBUFFER_11 (*(volatile uint32_t*)0x40039048)
#define OUTPUT_FIFOBUFFER_12 (*(volatile uint32_t*)0x40039048)
#define OUTPUT_FIFOBUFFER_13 (*(volatile uint32_t*)0x40039048)

#define OUTPUT_FIFOBUFFER(adcbase , sequencer) OUTPUT_FIFOBUFFER_##adcbase##sequencer

uint8_t status_sync = FALSE;

void Deepcopy_Data_FIFO_LLDBUFFER(ADC_Values Read_sensorvalue)
{
    ADC_Config *config_adc = &C_ADC_Config[Read_sensorvalue];
    static uint32_t  itr_t[Total_sensors] = {0} ;
    uint32_t i =0 ;

    if(itr_t[Read_sensorvalue] < config_adc->buffer_size)
    {
        if((config_adc->adc_type == ADC0) && (config_adc->sampler == 0))
        {
            config_adc->ptr_usr_buffer[itr_t[Read_sensorvalue]] = ((OUTPUT_FIFOBUFFER(0 , 0)) &(0x00000FFF));
        }
        else if((config_adc->adc_type == ADC0) &&   (config_adc->sampler == 1))
        {
            config_adc->ptr_usr_buffer[itr_t[Read_sensorvalue]] = ((OUTPUT_FIFOBUFFER(0 , 1)) &(0x00000FFF));
        }
        else
        {
            /*complete remainign combinations*/
        }
        itr_t[Read_sensorvalue]++;
    }

    else if  (itr_t[Read_sensorvalue] >= config_adc->buffer_size )
    {
        itr_t[Read_sensorvalue] = 0;
        status_sync = TRUE;
    }


}



void stop_Sequence_ADC(ADC_Values Read_sensorname)
{
    ADC_Config *config_adc = &C_ADC_Config[Read_sensorname];
    /*for now just writing 4 ports*/
       if(config_adc->adc_type == ADC0)
       {
           /*ADC SSCTL */
           reg_write(ADCSSCTL(0),config_adc->adc_stop_triggervalue);
           /*ADC PSSI */


       }
       else
       {
           reg_write(ADCSSCTL(1),config_adc->adc_stop_triggervalue);
       }

}
static ADC_Values prev_value_processed;
void ADC_StateMachine()
{
    uint8_t Read_sensorvalue;
    Queue_Stat queue_stat = Get_Queue_Status(ADC_MANGMT_STATUS);
    Get_Current_Elementfrom_Queue(&Read_sensorvalue, ADC_MANGMT_STATUS);
    static State_machine_ADC SM_Adc = START;
    ADC_Config *config_adc = &C_ADC_Config[Read_sensorvalue];
    ADC_Values sensvalue = Read_sensorvalue;
    uint8_t status = FALSE;

   if(queue_stat != QUEUE_EMPTY)
   {
    switch(SM_Adc)
    {

    case START :start_Sequence_ADC(sensvalue);
                /*enable the GSYNC bit to start thr synchronization*/
               // Set_GSYNC_Status_ADC(config_adc->sampler ,config_adc->adc_type);
                SM_Adc = BUSY;
                break;


    case BUSY :  stop_Sequence_ADC(Read_sensorvalue); /*Read the proper ADC value from the FIFO Buffer */
                 Deepcopy_Data_FIFO_LLDBUFFER(Read_sensorvalue);
                 status = Validate_FIFO_LLD(config_adc->adc_type);  /*check to see if the FIFO if full , get all the values frim the fifo to do the nosie analyhsis or write an alogorithm like  moving average */
                  if( (status == TRUE) || (status_sync == TRUE))
                  {
                      SM_Adc = STOP;
                  }
                  else
                  {
                      SM_Adc = START; /*start the next conversion and convert until fifo is full . THis it the mistake that might be done */
                  }
                  break;

    case STOP :status_sync = FALSE;
                stop_Sequence_ADC(Read_sensorvalue);
                process_dequeue(NULL_PTR, ADC_MANGMT_STATUS);
                SM_Adc = START;


    default : SM_Adc = START;




    }

   }

   else
   {

   }
}

