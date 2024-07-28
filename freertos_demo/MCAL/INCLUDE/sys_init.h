#include "api.h"
#include "tm4c123gh6pm.h"

/*According to discussion with oxophobe it is better to have a generic interface */
setpinportandfunctionality(uint8_t portnumber,uint8_t pin_number , uint8_t set_drive_strngth);

void corereset();
void systemresetfunction();
void sys_init();
void system_clkregister_initilize();
void systick_initlize();
void powerdown_sequence();
void intilize_rcc2_registers();
void initilize_rcc_registers();
void initilize_gpio();
void i2c_exception_handler(uint32_t *MSR_Status);
