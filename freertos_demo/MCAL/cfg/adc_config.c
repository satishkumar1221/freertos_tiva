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
    ports    afsel_portselect;0
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

uint16_t V_sensor1[8];
uint16_t V_sensor2[8];
uint16_t V_sensor3[8];
uint16_t V_sensor4[8];
/*configuring it pin wise */
const ADC_Config C_ADC_Config[ADC_CONFIG] =
{
    {3 , ENABLE_PORTE_GPIO , PORTE , APB ,ADC_PIN_CONFIGURE_PIN_3_MUXSS , 0x00 , 0x00 , ADC_PIN_CONFIGURE_PIN_0, ADC_PIN_CONFIGURE_PIN_0, ADC_PIN_CONFIGURE_PIN_0, RESET_CONFIG , ADC0 , SS0 , Processor_default , CTL_REGISTER_MASK_PE_P0 , &V_sensor1[0] ,8,CTL_REGISTER_MASK_STOP_PE_P0 },
    {3 , ENABLE_PORTE_GPIO , PORTE , APB ,ADC_PIN_CONFIGURE_PIN_2_MUXSS , 0x00, 0x00 , ADC_PIN_CONFIGURE_PIN_1, ADC_PIN_CONFIGURE_PIN_1, ADC_PIN_CONFIGURE_PIN_1, RESET_CONFIG , ADC0 , SS0 , Processor_default , CTL_REGISTER_MASK_PE_P1 ,  &V_sensor2[0]  ,8,CTL_REGISTER_MASK_STOP_PE_P1},
    {3 , ENABLE_PORTE_GPIO , PORTE , APB ,ADC_PIN_CONFIGURE_PIN_1_MUXSS , 0x00, 0x00 , ADC_PIN_CONFIGURE_PIN_2, ADC_PIN_CONFIGURE_PIN_2, ADC_PIN_CONFIGURE_PIN_2, RESET_CONFIG , ADC0 , SS0 , Processor_default , CTL_REGISTER_MASK_PE_P2 ,  &V_sensor3[0] ,8,CTL_REGISTER_MASK_STOP_PE_P2},
    {3 , ENABLE_PORTE_GPIO , PORTE , APB ,ADC_PIN_CONFIGURE_PIN_0_MUXSS , 0x00 , 0x00 , ADC_PIN_CONFIGURE_PIN_3, ADC_PIN_CONFIGURE_PIN_3, ADC_PIN_CONFIGURE_PIN_3, RESET_CONFIG , ADC0 , SS0 , Processor_default , CTL_REGISTER_MASK_PE_P3 , &V_sensor4[0] , 8,CTL_REGISTER_MASK_STOP_PE_P3}
};
