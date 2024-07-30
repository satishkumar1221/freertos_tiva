/*
 * adc.c
 *
 *  Created on: Jul 24, 2024
 *      Author: satis
 */

#include <tm4c123gh6pm.h>
#include <stdint.h>
#include "api.h"
#include "adc.h"









/*TO DO : Biwise numbers have to be fixed */
static inline set_registers_adc(const ADC_Config *config_adc)
{
    uint32_t x = (config_adc->afsel_portselect) | (config_adc->select_bustype);

    switch(x)
    {   


        case 01 :
                  set_bits_mask_reg (GPIO_AFSEL(0,1) , config_adc->pin_config);
                  set_bits_mask_reg (GPIO_DEN(0,1) , config_adc->Digital_enable_value_pin_mask);
                  set_bits_mask_reg (GPIO_AMSEL(0,1) , config_adc->amsel_reg_mask);
                  set_bits_mask_reg (GPIOADCCTL(0,1) , config_adc->adc_trig_reg_mask);
                  set_bits_mask_reg (GPIODMACTL(0,1) , config_adc->dma_trig_reg_mask);
        break;
        case 11 :
                  set_bits_mask_reg (GPIO_AFSEL(1,1) , config_adc->pin_config);
                  set_bits_mask_reg (GPIO_DEN(1,1) , config_adc->Digital_enable_value_pin_mask);
                  set_bits_mask_reg (GPIO_AMSEL(1,1) , config_adc->amsel_reg_mask);
                  set_bits_mask_reg (GPIOADCCTL(1,1) , config_adc->adc_trig_reg_mask);
                  set_bits_mask_reg (GPIODMACTL(1,1) , config_adc->dma_trig_reg_mask);
        break;
        case 21 :
                  set_bits_mask_reg (GPIO_AFSEL(2,1) , config_adc->pin_config);
                  set_bits_mask_reg (GPIO_DEN(2,1) , config_adc->Digital_enable_value_pin_mask);
                  set_bits_mask_reg (GPIO_AMSEL(2,1) , config_adc->amsel_reg_mask);
                  set_bits_mask_reg (GPIOADCCTL(2,1) , config_adc->adc_trig_reg_mask);
                  set_bits_mask_reg (GPIODMACTL(2,1) , config_adc->dma_trig_reg_mask);
        break;
        case 31 :
                  set_bits_mask_reg (GPIO_AFSEL(3,1) , config_adc->pin_config);
                  set_bits_mask_reg (GPIO_DEN(3,1) , config_adc->Digital_enable_value_pin_mask);
                  set_bits_mask_reg (GPIO_AMSEL(3,1) , config_adc->amsel_reg_mask);
                  set_bits_mask_reg (GPIOADCCTL(3,1) , config_adc->adc_trig_reg_mask);
                  set_bits_mask_reg (GPIODMACTL(3,1) , config_adc->dma_trig_reg_mask);
        break;

        case 5 :
        {
                #if 0
                  set_bits_mask_reg (GPIODATA(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIODIR(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIOIS(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIOIBE(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIOIEV(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIOIM(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIORIS(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIOMIS(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIOICR(4,1) , config_adc->reset);
               #endif


                  set_bits_mask_reg ((GPIO_AFSEL(4,1)) , (config_adc->pin_config));
                  set_bits_mask_reg ((GPIO_DEN(4,1)) , (config_adc->Digital_enable_value_pin_mask));

                  set_bits_mask_reg (GPIOLOCK(4,1) , config_adc->reset);
                  set_bits_mask_reg (GPIOCR(4,1) , config_adc->reset);

                  set_bits_mask_reg (GPIO_AMSEL(4,1) , config_adc->amsel_reg_mask);
                  set_bits_mask_reg (GPIOADCCTL(4,1) , config_adc->adc_trig_reg_mask);
                  set_bits_mask_reg (GPIODMACTL(4,1) , config_adc->dma_trig_reg_mask);

                  if(config_adc->adc_type == ADC0)
                        {
                            /*configure control register for the DIether mode and sampler register */
                            ADC0_CTL_R  = (ADC0_CTL_R |  (1 << 6U));   /*bit 6 is to enable Diether mode */
                            ADC0_SAC_R = (ADC0_CTL_R | (config_adc->sampling_rate));

                        }
                        else
                        {
                            ADC1_CTL_R  = (ADC1_CTL_R |  (1 << 6U));   /*bit 6 is to enable Diether mode */
                            ADC1_SAC_R = (ADC1_CTL_R | (config_adc->sampling_rate));

                        }
    }
        break;

        case 51 :
                  set_bits_mask_reg (GPIO_AFSEL(5,1) , config_adc->pin_config);
                  set_bits_mask_reg (GPIO_DEN(5,1) , config_adc->Digital_enable_value_pin_mask);
                  set_bits_mask_reg (GPIO_AMSEL(5,1) , config_adc->amsel_reg_mask);
                  set_bits_mask_reg (GPIOADCCTL(5,1) , config_adc->adc_trig_reg_mask);
                  set_bits_mask_reg (GPIODMACTL(5,1) , config_adc->dma_trig_reg_mask);
        break;

        default :
        
    }
}




#if 0
void start_adcconversion(ADC_Sampler sampler , ADC_TYPE adc_type)
{
    if(adc_type == ADC0)
        {
        set_bits_mask_reg(ADCPSSI(0),sampler); /*enable interrupt for ss0*/

        }
    else
        {
        set_bits_mask_reg(ADCPSSI(1),sampler); /*enable interrupt for ss0*/
        }
    }

#endif

void Configure_Sampler(const ADC_Config *config_adc  )
{
#define enable_ss0_PSSi 1U
#define enable_ss1_PSSi 1U
    if(config_adc->adc_type == ADC0)
    {
        clear_bits_integer(ADCA_CTSS(0), 0);
        set_bits_mask_reg(ADCE_MUX(0),config_adc->trigger_select);/*As if now trigger is selected to processor*/
        //set_bits_mask_reg(ADSS_MUX(0),config_adc->pin_config); /*No Need to start here*/
        //set_bits_mask_reg(ADCSSCTL_0 , config_adc->adc_trig_reg_mask); /*should be set when requesting for a sample sequence*/
       // set_bits_mask_reg(ADC_RIS(0),config_adc->Interrupt_enable_mask);
        //set_bits_mask_reg(ADCIM_0,1U); /*enable interrupt for ss0*/
       // set_bits_mask_reg(ADCPSSI(0) , (enable_ss0_PSSi)); // No need to start here

        /*Enable the sequencer*/
        //set_bits_mask_reg(ADCA_CTSS(0), 1);


    }

    else
    {
        clear_bits_integer(ADCA_CTSS(1), 0);
        set_bits_mask_reg(ADCE_MUX(1),((uint32_t)0x0F));/*As if now trigger is selected to processor*/
        set_bits_mask_reg(ADSS_MUX(1),config_adc->pin_config);
       // set_bits_mask_reg(ADCSSCTL(1),config_adc->ADC_CTLREG_CONFIG);
       // set_bits_mask_reg(ADC_RIS(1),config_adc->Interrupt_enable_mask);
        set_bits_mask_reg(ADCIM_1,1U); /*enable interrupt for ss0*/
        set_bits_mask_reg(ADCPSSI(0) , (enable_ss1_PSSi ));
        set_bits_mask_reg(ADCA_CTSS(1), 1);
    }



}

uint32_t fifo_value_Adc;
void Read_value_ADC()
{
    fifo_value_Adc = *((volatile uint32_t*) 0x40038048);
}

void clear_adc_interrupt(const ADC_Config *config_adc)
{
      if(config_adc->adc_type == ADC0)
      {
          if(config_adc->sampler == SS0)
          {
              set_bits_mask_reg(ADCISC(0), 1U); /*clear ADC interrupt*/
          }
      }
}

void ISR_ADC_Sequence0()
{
    clear_adc_interrupt(&C_ADC_Config[0]);
}




void ADC_Init(const ADC_Config *config_adc)
{
    int i =0 ;
    SYSCTL_RCGCGPIO_R |= (config_adc->enable_adc_port);
    /*Enable Diether mode for the ADC.*/


    /*Also configure sampling for ADC for roobustness */

    for (i = 0 ; i < TOTAL_ADC_CONFIG ; i++)
    {
        SYSCTL_RCGCADC_R |= (config_adc[i].enable_adc_module_mask);
        set_registers_adc(&config_adc[i]);
        Configure_Sampler(&config_adc[i]);/*either ADC 0 or ADC 1 */
    }
}


static ADC_Status ADC_BUSY_STATUS(ADC_TYPE adc)
{
    if(adc == ADC0)
    {
            if(ADC0_ACTSS_R & ADC_BUSY_MASK > 0U)
            {
                return(ADC_BUSY);
            }
            else
            {
                return(ADC_IDLE);
            }
    }

    else
    {
        if(ADC0_ACTSS_R & ADC_BUSY_MASK > 0U)
       {
            return(ADC_BUSY);
       }
       else
       {
             return(ADC_IDLE);
       }

    }
}
QueueHandle_t xQueue2;

uint8_t V_Values_ADC[Total_sensors];

//StaticQueue_t xStaticQueue; /*structure to hold the static data structure of the queue */
void Initilize_ADC()
{
    uint32_t storagearea = ((Total_sensors * sizeof(ADC_Values)) + 1U);
    ADC_Init(&C_ADC_Config[0]);
    /*Create a queue in the freeros for the maintainence of the ADC*/
    initlize_circular_queue(&V_Values_ADC[0] , (sizeof(V_Values_ADC)/ sizeof(V_Values_ADC[0])),ADC_MANGMT_STATUS ,  sizeof(uint8_t) );


}







