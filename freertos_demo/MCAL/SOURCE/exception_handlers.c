
#include "sys_init.h"

#define i2c_busy 0x01
#define time_out_configuredvalue  0x320000

/*Register access */
#define APIINT (*(volatile uint32_t*)0xE000ED0C)
uint32_t timercount;
//#define systemreset  0x04
void disable_interrupts()
{
    // Added tab before CPSID for compiling without errors.
    __asm(" CPSID I");
}

void enable_interrupts()
{
    // Added tab before CPSIE for compiling without errors
    __asm(" CPSIE I");
}



void i2c_exception_handler(uint32_t *MSR_Status)
{


}

void systemresetfunction()
{

}

void corereset()
{
     APIINT = (NVIC_APINT_VECTKEY | 0x01);
} 
