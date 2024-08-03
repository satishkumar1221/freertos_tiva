/*
 * udma.c
 *
 *  Created on: Jul 31, 2024
 *      Author: satis
 */

#include "udma.h"




/*DMA has to be alligned to the 1024 bytw boundry */
#if defined(GCC_COMPILER)

uint8_t ui8ControlTable[1024] __attribute__ ((aligned(1024))); /*for gccc*/

#else
/* controlt able used by udma , must always be 1024 bytes */   /* Query: waht is its purpose? */

#pragma DATA_ALIGN(dmaControlTable, 1024)
uint8_t dmaControlTable[1024];
#endif

#define debug() while(1){}


#define EXTRACTFIRST_24BITS (value) 0x00FFFFFF
uint32_t temp_address[2] = {0};


void set_base_control_register(void *dma_ctltable)
{
    /*proper alignment is there will ahve to write a logic to check alignment */
 //  uint32_t baseaddress =  (V_DMA_ControlTable & 0x00FFFFFF);
   // temp_address[0] =  ((uint32_t *)(0x20002000));
  //  temp_address[1] = (((uint32_t)dma_ctltable) & ~ 0x3FFF);
   //if((((uint32_t)dma_ctltable) & ~ 0x3FFF) == ((uint32_t)dma_ctltable))
   //{
        /*checking for the 1024 bit alighnment*/
    *DMACTLBASE_REG |= (uint32_t)dma_ctltable;
   //}
  //  else
  //  {
    //     debug();
  //  }
}


#define BYTES_TO_BITS 8U
#define DMA_TABLE_ENTRY_SIZE  16U

static inline uint32_t calculate_DMAOFFSET_Channel(DMA_Channel Chn)
{

    return (Chn * 16U);

}

void memcopy(void *src ,  void *dest , uint32_t size)
{
     uint8_t *dst = (uint8_t*)dest;
     uint32_t itr = 0U;
     while (itr < size)
     {
         dst[itr]  = (*(uint8_t*)(&src[itr]));
         itr++;
     }
}



uint32_t  Extract_Size_FromControlWord(uint32_t controlword)
{
    #define EXTRACT_SIZE_MASK  0x3FF0
    #define EXTRACT_INCR_SIZE  ((1<<25) | (1<<24)) /*24 and 25 bit */
    uint32_t extract_incrsize = (controlword & EXTRACT_INCR_SIZE) >> 24U;
    uint32_t size  =  (((controlword & EXTRACT_SIZE_MASK) >> 4U) * (C_DMA_SIZEMAP[extract_incrsize].size)); /*as we are starting from the 4 position for the control word*/
    return(size);
}

DMA_CtrlStructure Temp_ConfigDMA;
static void Write_ControlStrucutre_DMATABLE(DMA_CONTROL_STRUCTURE *ctrl_struct)
{
    uint32_t itr  = 0 ;
    uint32_t offset = calculate_DMAOFFSET_Channel(ctrl_struct->channel_activated);
     /*configure the copy table accordingly*/

    uint32_t size =  Extract_Size_FromControlWord (ctrl_struct->config_DMA.controlword);
    /*source end pointer */
    Temp_ConfigDMA.source_startpointer = (uint32_t*)(((uint32_t*)ctrl_struct->config_DMA.source_startpointer) + (size)) ;
    /*destination end pointer */
    Temp_ConfigDMA.destination_startpointer =  (uint32_t*)(((uint32_t*)ctrl_struct->config_DMA.destination_startpointer) + (size));
    Temp_ConfigDMA.controlword = *(ctrl_struct->config_DMA.controlword);

    uint8_t *start_ptr = (uint8_t*)(((uint8_t*)dmaControlTable) + (offset * sizeof(uint8_t)));
    memcopy((&(Temp_ConfigDMA)), start_ptr ,DMA_TABLE_ENTRY_SIZE);

}

/*User function */
DMA_ControlWord_Structure S_DMACtlWord;/*temp fix */
void configure_control_structure(DMA_CONTROL_STRUCTURE *dma_struct)
{

    DMA_Application S_Appl = dma_struct->DMA_Appl;
    uint32_t control_reg_value= 0U;

    DMA_ControlWord_Structure  dma_ctl_struct;
  if(dma_struct != NULL)
  {
    switch(S_Appl)
    {
            /*this api has to be fixed.  It is upto the user to configure the modes. they can use bit wise or uint32_t as a whole. This should be in user code.*/
            case SW_TRANSFER_0 :

                               dma_ctl_struct.B.transfermode = Auto_Request;
                                 dma_ctl_struct.B.NXTUSEBURST = (uint8_t)FALSE;
                                 dma_ctl_struct.B.xfersize_byte = 64U; /*Just to test this can be changed . These are number of items*/
                                 dma_ctl_struct.B.arb_size = four_transfers;
                                 dma_ctl_struct.B.src_size = Word;
                                 dma_ctl_struct.B.src_address_inc = Word;
                                 dma_ctl_struct.B.dst_addr_inc = Word;
                                 dma_ctl_struct.B.dst_size = Word;
                                 S_DMACtlWord = dma_ctl_struct;
                                 dma_struct->config_DMA.controlword = dma_ctl_struct.R;
                                 break;

        case ADC_TRANSFER  :
                              break;

        default : break;

    }

    Write_ControlStrucutre_DMATABLE(dma_struct);
  }
    return(control_reg_value);
}

void Configure_DMA_Channel_Attributes(DMA_Channel chn)
{

    UDMA_PRIOSET_R    |= (1 << ((uint32_t)chn));
    UDMA_ALTCLR_R     |= (1 << ((uint32_t)chn));

    UDMA_USEBURSTCLR_R|= (1 << ((uint32_t)chn));
    UDMA_REQMASKSET_R |= (1 << ((uint32_t)chn));

}
uint32_t V_DMA_Count_Stat;
void ISR_Transfer_Status()
{
    V_DMA_Count_Stat++;
}

void Disable_Interrupts_DMA(DMA_Channel chnname)
{
    UDMA_ENASET_R |=  (1U << chnname);
}

void Enable_Interrupts_DMA(DMA_Channel chnname)
{
    UDMA_ENASET_R  &= (~(1U << chnname));
}

void Enable_DMA_Transfer(DMA_Channel chnname)
{
    UDMA_ENASET_R |= (1 << chnname);
    UDMA_SWREQ_R  |= (1 << chnname);
}

void Disable_DMA_Transfer(DMA_Channel chnname)
{
    UDMA_ENASET_R &= (~(1 << chnname));
    UDMA_SWREQ_R  |= (~(1 << chnname));
}

void Clear_DMA_Table()
{
    uint32_t itr =0 ;
    for(itr = 0U ; itr < 1024 ; itr++)
    {
        dmaControlTable[itr] = 0 ;
    }

}

/**/
void Init_udma()
{
   uint32_t itr =0;
  set_bits_mask_reg(RCGCDMA_REG , ENABLE_DMA_MASK);
  UDMA_CFG_R|=ENABLE_DMA_MASK;
  /* set the DMA control */
  //Enable_Interrupts_DMA(channel_30);
  Clear_DMA_Table();
  set_base_control_register(&dmaControlTable[0]);
  /*can be called in between os as well */

  /*Configure the channel attributes */


//for(itr = 0U ; itr < TOTAL_CHANNELS_CONFIGURED ; itr++)
//  {
      Configure_DMA_Channel_Attributes((&C_DMA_Control_struct[0].channel_activated));
      configure_control_structure(&C_DMA_Control_struct[0]); /*delibrate bug for testing the DMA first*/


//  }





}


