/*
 * adc.h
 *
 *  Created on: Jul 24, 2024
 *      Author: satis
 */

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#define ENABLE_ADC0_MASK  1U
#define ENABLE_ADC1_MASK  2U

#define ENABLE_PORTA_GPIO  1U
#define ENABLE_PORTB_GPIO  2U
#define ENABLE_PORTC_GPIO  4U
#define ENABLE_PORTD_GPIO  8U
#define ENABLE_PORTE_GPIO  16U
#define ENABLE_PORTF_GPIO  32U

#define ADC_PIN_MASK_CONFIGURE 0x0F /*configuring pins 0,1,2,3 in port E */
#define ADC_CONFIG 1U
#define ADC_CTRL_MASK_CONFIGURE 0x0F 
#define DMA_CTRL_MASK_CONFIGURE 0x0F
#define RESET_CONFIG 0x00

#define CTL_REGISTER_MASK 0xE000

typedef enum
{
   ADC0,
   ADC1
}ADC_TYPE;

typedef enum
{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
}ports;

typedef enum
{
    AHB,
    APB
}BUSTYPE;

typedef enum
{
    SS0,
    SS1,
    SS2,
    SS3

}ADC_Sampler;

typedef enum
{
    Processor_default,/*initialted vy settinf the SSn bit of ADCPSSI register*/
    Analog_compcntl_ACCTL0,
    Analog_compcntl_ACCTL1,
    reserved,
    External_gpio,
    Timer,
    PWM_Generator_0, /*PWM0_IMTEN*/
    PWM_Generator_1, /*PWM0_IMTEN*/
    PWM_Generator_2, /*PWM0_IMTEN*/
    PWM_Generator_3, /*PWM0_IMTEN*/
    Alwayssample = 0x0F
}ADC_Trigger_Select;


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

extern void Read_value_ADC();


void ISR_ADC_Sequence0();
#define GPIODATA(port,bus) GPIODATA_## port ##_##bus
#define GPIODIR(port,bus) GPIODIR_## port ##_##bus
#define GPIOIS(port,bus) GPIOIS_## port ##_##bus
#define GPIOIBE(port,bus) GPIOIBE_## port ##_##bus
#define GPIOIEV(port,bus) GPIOIEV_## port ##_##bus
#define GPIOIM(port,bus) GPIOIM_## port ##_##bus
#define GPIORIS(port,bus) GPIORIS_## port ##_##bus
#define GPIOMIS(port,bus) GPIOMIS_## port ##_##bus
#define GPIOICR(port,bus) GPIO_AFSEL_## port ##_##bus

#define GPIO_AFSEL(port,bus) GPIO_AFSEL_## port ##_##bus
#define GPIO_DEN(port,bus) GPIO_DEN_##port##_##bus

#define GPIOLOCK(port,bus) GPIOLOCK_## port ##_##bus
#define GPIOCR(port,bus) GPIOCR_## port ##_##bus
#define GPIO_AMSEL(port,bus) GPIO_AMSEL_##port##_##bus

#define GPIOPCTL(port,bus) GPIOPCTL_## port ##_##bus
#define GPIOADCCTL(port,bus) GPIO_AMSEL_##port##_##bus
#define GPIODMACTL(port,bus) GPIO_AMSEL_##port##_##bus

#define ADC_BUSY_MASK (uint32_t)(1 << 16U)


/*PORT A APB related values */
#define GPIODATA_0_1 (uint32_t*) 0x40004000
#define GPIODIR_0_1 (uint32_t*) 0x40004400
#define GPIOIS_0_1 (uint32_t*) 0x40004404
#define GPIOIBE_0_1 (uint32_t*) 0x40004408
#define GPIOIEV_0_1 (uint32_t*) 0x4000440C
#define GPIOIM_0_1 (uint32_t*) 0x40004410
#define GPIORIS_0_1 (uint32_t*) 0x40004414
#define GPIOMIS_0_1 (uint32_t*) 0x40004418
#define GPIOICR_0_1 (uint32_t*) 0x4000441C
#define GPIOPUR_0_1 (uint32_t*) 0x40004510

#define GPIO_AFSEL_0_1 (uint32_t*)0x40004420
#define GPIO_DEN_0_1 (uint32_t*) 0x4000451C
#define GPIOLOCK_0_1 (uint32_t*) 0x40004520
#define GPIOCR_0_1 (uint32_t*) 0x40004524
#define GPIO_AMSEL_0_1 (uint32_t*) 0x40004528
#define GPIOADCCTL_0_1 (uint32_t*) 0x40004530
#define GPIODMACTL_0_1 (uint32_t*) 0x40004534

/*PORT B APB related values */
#define GPIODATA_1_1 (uint32_t*) 0x40005000
#define GPIODIR_1_1 (uint32_t*) 0x40005400
#define GPIOIS_1_1 (uint32_t*) 0x40005404
#define GPIOIBE_1_1 (uint32_t*) 0x40005408
#define GPIOIEV_1_1 (uint32_t*) 0x4000540C
#define GPIOIM_1_1 (uint32_t*) 0x40005410
#define GPIORIS_1_1 (uint32_t*) 0x40005414
#define GPIOMIS_1_1 (uint32_t*) 0x40005418
#define GPIOICR_1_1 (uint32_t*) 0x4000541C
#define GPIOPUR_1_1 (uint32_t*) 0x40005510

#define GPIO_AFSEL_1_1 (uint32_t*)0x40005420
#define GPIO_DEN_1_1 (uint32_t*) 0x4000551C
#define GPIOLOCK_1_1 (uint32_t*) 0x40005520
#define GPIOCR_1_1 (uint32_t*) 0x40005524
#define GPIO_AMSEL_1_1 (uint32_t*) 0x40005528
#define GPIOADCCTL_1_1 (uint32_t*) 0x40005530
#define GPIODMACTL_1_1 (uint32_t*) 0x40005534

/*PORT C APB related values */
#define GPIODATA_2_1 (uint32_t*) 0x40006000
#define GPIODIR_2_1 (uint32_t*) 0x40006400
#define GPIOIS_2_1 (uint32_t*) 0x40006404
#define GPIOIBE_2_1 (uint32_t*) 0x40006408
#define GPIOIEV_2_1 (uint32_t*) 0x4000640C
#define GPIOIM_2_1 (uint32_t*) 0x40006410
#define GPIORIS_2_1 (uint32_t*) 0x40006414
#define GPIOMIS_2_1 (uint32_t*) 0x40006418
#define GPIOICR_2_1 (uint32_t*) 0x4000641C
#define GPIOPUR_2_1 (uint32_t*) 0x40006510

#define GPIO_AFSEL_2_1 (uint32_t*)0x40006420
#define GPIO_DEN_2_1 (uint32_t*) 0x4000651C
#define GPIOLOCK_2_1 (uint32_t*) 0x40006520
#define GPIOCR_2_1 (uint32_t*) 0x40006524
#define GPIO_AMSEL_2_1 (uint32_t*) 0x40006528
#define GPIOADCCTL_2_1 (uint32_t*) 0x40006530
#define GPIODMACTL_2_1 (uint32_t*) 0x40006534

/*PORT D APB related values */
#define GPIODATA_3_1 (uint32_t*) 0x40007000
#define GPIODIR_3_1 (uint32_t*) 0x40007400
#define GPIOIS_3_1 (uint32_t*) 0x40007404
#define GPIOIBE_3_1 (uint32_t*) 0x40007408
#define GPIOIEV_3_1 (uint32_t*) 0x4000740C
#define GPIOIM_3_1 (uint32_t*) 0x40007410
#define GPIORIS_3_1 (uint32_t*) 0x40007414
#define GPIOMIS_3_1 (uint32_t*) 0x40007418
#define GPIOICR_3_1 (uint32_t*) 0x4000741C
#define GPIOPUR_3_1 (uint32_t*) 0x40007510

#define GPIO_AFSEL_3_1 (uint32_t*)0x40007420
#define GPIO_DEN_3_1 (uint32_t*) 0x4000751C
#define GPIOLOCK_3_1 (uint32_t*) 0x40007520
#define GPIOCR_3_1 (uint32_t*) 0x40007524
#define GPIO_AMSEL_3_1 (uint32_t*) 0x40007528
#define GPIOADCCTL_3_1 (uint32_t*) 0x40007530
#define GPIODMACTL_3_1 (uint32_t*) 0x40007534

/*PORT E APB related values */
#define GPIODATA_4_1 (uint32_t*) 0x40024000
#define GPIODIR_4_1 (uint32_t*) 0x40024400
#define GPIOIS_4_1 (uint32_t*) 0x40024404
#define GPIOIBE_4_1 (uint32_t*) 0x40024408
#define GPIOIEV_4_1 (uint32_t*) 0x4002440C
#define GPIOIM_4_1 (uint32_t*) 0x40024410
#define GPIORIS_4_1 (uint32_t*) 0x40024414
#define GPIOMIS_4_1 (uint32_t*) 0x40024418
#define GPIOICR_4_1 (uint32_t*) 0x4002441C
#define GPIOPUR_4_1 (uint32_t*) 0x40024510

#define GPIO_AFSEL_4_1 (volatile uint32_t*)0x40024420
#define GPIO_DEN_4_1 (uint32_t*) 0x4002451C
#define GPIOLOCK_4_1 (uint32_t*) 0x40024520
#define GPIOCR_4_1 (uint32_t*) 0x40024524
#define GPIO_AMSEL_4_1 (uint32_t*) 0x40024528
#define GPIOADCCTL_4_1 (uint32_t*) 0x40024530
#define GPIODMACTL_4_1 (uint32_t*) 0x40024534

/*PORT F APB related values */
#define GPIODATA_5_1 (uint32_t*) 0x40025000
#define GPIODIR_5_1 (uint32_t*) 0x40025400
#define GPIOIS_5_1 (uint32_t*) 0x40025404
#define GPIOIBE_5_1 (uint32_t*) 0x40025408
#define GPIOIEV_5_1 (uint32_t*) 0x4002540C
#define GPIOIM_5_1 (uint32_t*) 0x40025410
#define GPIORIS_5_1 (uint32_t*) 0x40025414
#define GPIOMIS_5_1 (uint32_t*) 0x40025418
#define GPIOICR_5_1 (uint32_t*) 0x4002541C
#define GPIOPUR_5_1 (uint32_t*) 0x40025510

#define GPIO_AFSEL_5_1 (uint32_t*)0x40025420
#define GPIO_DEN_5_1 (uint32_t*) 0x4002551C
#define GPIOLOCK_5_1 (uint32_t*) 0x40025520
#define GPIOCR_5_1 (uint32_t*) 0x40025524
#define GPIO_AMSEL_5_1 (uint32_t*) 0x40025528
#define GPIOADCCTL_5_1 (uint32_t*) 0x40025530
#define GPIODMACTL_5_1 (uint32_t*) 0x40025534

extern void ADC_Init(const ADC_Config *config_adc);
extern const ADC_Config C_ADC_Config[ADC_CONFIG];
extern void Initilize_ADC();
extern const ADC_Config C_ADC_Config[ADC_CONFIG];


#endif /* INCLUDE_ADC_H_ */
