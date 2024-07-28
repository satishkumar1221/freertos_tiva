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


typedef enum
{
    ADC_IDLE,
    ADC_BUSY
}ADC_Status;








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


#define ADC_RIS(adc_type)  ADC_RIS_##adc_type

#define ADC_RIS_0 (volatile uint32_t*) 0x40038004

#define ADC_RIS_1 (volatile uint32_t*) 0x40039004

#define ADCA_CTSS(adc_type)  ADCA_CTSS_##adc_type

#define ADCA_CTSS_0 (volatile uint32_t*) 0x40038000

#define ADCA_CTSS_1 (volatile uint32_t*) 0x40039000

#define ADCE_MUX(adc_type)  ADCE_MUX_##adc_type

#define ADCE_MUX_0 (volatile uint32_t*) 0x40038014

#define ADCE_MUX_1 (volatile uint32_t*) 0x400390014

#define ADSS_MUX(adc_type)  ADSS_MUX_##adc_type

#define ADSS_MUX_0 (volatile uint32_t*) 0x40038040 /*Selects the PINS to be used for the ADC*/

#define ADSS_MUX_1 (volatile uint32_t*) 0x40039040  /*Selects the PINS to be used for the ADC*/

#define ADCSSCTL(adc_type)  ADSS_MUX_##adc_type

#define ADCSSCTL_0  (volatile uint32_t*) 0x40038044
#define ADCSSCTL_1  (volatile uint32_t*) 0x40039044

#define ADCISC(adc_type) ADCISC_##adc_type

#define ADCISC_0 (volatile uint32_t*) 0x4003800C
#define ADCISC_1 (volatile uint32_t*) 0x4003900C

#define ADCIM_0  (volatile uint32_t*) 0x40038008
#define ADCIM_1  (volatile uint32_t*) 0x40039009

#define ADCPSSI_0  (volatile uint32_t*)0x40038028
#define ADCPSSI_0  (volatile uint32_t*)0x40039028

void start_adcconversion(/*const ADC_Config *config_adc*/)
{
    set_bits_mask_reg(ADCPSSI_0,1U); /*enable interrupt for ss0*/
}



void Configure_Sampler(const ADC_Config *config_adc  )
{
    uint32_t sampl_num  = (1 << config_adc->sampler);

    if(config_adc->adc_type == ADC0)
    {
        clear_bits_integer(ADCA_CTSS(0), 0);
        set_bits_mask_reg(ADCE_MUX(0),0x0F);/*As if now trigger is selected to processor*/
        set_bits_mask_reg(ADSS_MUX(0),config_adc->pin_config);
        set_bits_mask_reg(ADCSSCTL_0 , CTL_REGISTER_MASK);
       // set_bits_mask_reg(ADC_RIS(0),config_adc->Interrupt_enable_mask);
        set_bits_mask_reg(ADCIM_0,1U); /*enable interrupt for ss0*/
        set_bits_mask_reg(ADCA_CTSS(0), 1);
    }

    else
    {
        clear_bits_integer(ADCA_CTSS(1), 0);
        set_bits_mask_reg(ADCE_MUX(1),((uint32_t)0x0F));/*As if now trigger is selected to processor*/
        set_bits_mask_reg(ADSS_MUX(1),config_adc->pin_config);
        set_bits_mask_reg(ADCSSCTL(1),config_adc->ADC_CTLREG_CONFIG);
       // set_bits_mask_reg(ADC_RIS(1),config_adc->Interrupt_enable_mask);
        set_bits_mask_reg(ADCIM_1,1U); /*enable interrupt for ss0*/
    }
    start_adcconversion();


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
    SYSCTL_RCGCGPIO_R |= (config_adc->enable_adc_port);
    SYSCTL_RCGCADC_R |= (config_adc->enable_adc_module_mask);
    set_registers_adc(&config_adc[0]);
    Configure_Sampler(&C_ADC_Config[0]);/*either ADC 0 or ADC 1 */
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

void Initilize_ADC()
{
    ADC_Init(&C_ADC_Config[0]);
}







