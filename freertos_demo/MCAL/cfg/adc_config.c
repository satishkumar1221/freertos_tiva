/*
 * adc_config.c
 *
 *  Created on: Jul 27, 2024
 *      Author: satis
 */


#include <tm4c123gh6pm.h>
#include <stdint.h>
#include "api.h"
#include "adc.h"

#if 0
typedef struct
{
    uint32_t enable_adc_module_mask;
    uint32_t enable_adc_port;
    ports    afsel_portselect;
    BUSTYPE  select_bustype;
    uint32_t pin_config;
    uint32_t  afsel_value;
    uint32_t Digital_enable_value_pin_mask;
    uint32_t amsel_reg_mask;/*disable the isolation */
    uint32_t adc_trig_reg_mask;
    uint32_t dma_trig_reg_mask;
    uint32_t reset;
    ADC_TYPE adc_type; /*either adc0 or adc 1 */
    /*split it as a part of sampler structure*/
    ADC_Sampler sampler;
    ADC_Trigger_Select trigger_select;
    uint32_t ADC_CTLREG_CONFIG;
}ADC_Config;
#endif
const ADC_Config C_ADC_Config[ADC_CONFIG] =
{
    {3 , ENABLE_PORTE_GPIO , PORTE , APB ,ADC_PIN_MASK_CONFIGURE , 0x00 , 0x0F, ADC_CTRL_MASK_CONFIGURE, DMA_CTRL_MASK_CONFIGURE, RESET_CONFIG , ADC0 , SS0 , Alwayssample , CTL_REGISTER_MASK }
};
