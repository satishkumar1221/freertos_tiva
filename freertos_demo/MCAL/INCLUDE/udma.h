/*
 * udma.h
 *
 *  Created on: Jul 31, 2024
 *      Author: satis
 */

#ifndef MCAL_INCLUDE_UDMA_H_
#define MCAL_INCLUDE_UDMA_H_

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "api.h"
#include "udma_types.h"

#define RCGCDMA_REG (volatile uint32_t*)0x400FE60C
#define DMACFG_REG   (volatile uint32_t*)0x400FF004
#define DMACTLBASE_REG (volatile uint32_t*)0x400FF008
#define DMAPRIOCLR  (volatile uint32_t*)0x400FF03C
#define ENABLE_DMA_MASK 1U


#if 0
typedef struct
{
  uint8_t *ptr_control_dma_ctltable;
  uint32_t mode;
  uint32_t *DMA_PRIO_SET;
  uint32_t *DMA_PRIO_CLEAR;
  uint32_t *DMAALTSET_REG;  /*setting a bit here clears the alt set register . Not applicable for ping pong mode */
  uint32_t *DMA_ALTCLR_REG;


};
#endif


typedef union
{
    uint32_t R;
    struct B
    {
  uint32_t transfermode:3; /*the transfer mode can be basic , autirequest ,pingpong  scattergather etc */
  uint32_t NXTUSEBURST : 1; /*see if the use burst set in scatter gater operation*/
 uint32_t xfersize_byte:10; /*Number of bytes to transfer 0 to 1024 */
   uint32_t arb_size:4;/* 0  t transfer . 2 : 4 transfers , 3 : 8 transfers, 4 :16 transfers ......No of xfers occur when udma rearbitrates */
 uint32_t reserved :6;
   uint32_t src_size:2;
   uint32_t src_address_inc:2;
   uint8_t dst_size :2;
   uint32_t dst_addr_inc:2;

  }B;

}DMA_ControlWord_Structure;

DMA_ControlWord_Structure V_DMA_Control_struct;

typedef struct
{
    uint32_t *source_startpointer;
    uint32_t *destination_startpointer;
    uint32_t *controlword;
    uint32_t reserved;

}DMA_CtrlStructure;

extern uint32_t V_Dest_A[64];
extern uint32_t V_Src_A[64];





typedef enum
{
    SW_TRANSFER_0,
    ADC_TRANSFER

}DMA_Application;

typedef struct
{
   uint32_t DMAPRIOSET;
   uint32_t DMAPRIOCLEAR;
   uint32_t DMABURSTCLEAR;
   uint32_t DMA_ALTCR;
   uint32_t REQMASKCLEAR;
   uint32_t Interrupt_Set;

}DMA_ChannelAttributes ;

typedef struct
{
    DMA_Application DMA_Appl;
    DMA_Channel channel_activated;
    DMA_CtrlStructure config_DMA;
    DMA_ChannelAttributes config_DMA_chnl;

}DMA_CONTROL_STRUCTURE;
#if 0


#endif
#define TOTAL_CHANNELS_CONFIGURED 2U
extern const DMA_SIZEMAP C_DMA_SIZEMAP[3];
extern uint32_t V_Configure_controlstructure[TOTAL_CHANNELS_CONFIGURED];

extern const DMA_CONTROL_STRUCTURE C_DMA_Control_struct[TOTAL_CHANNELS_CONFIGURED ];


void Disable_Interrupts_DMA(DMA_Channel chnname);
void Enable_Interrupts_DMA(DMA_Channel chnname);
void Enable_DMA_Transfer(DMA_Channel chnname);
void Disable_DMA_Transfer(DMA_Channel chnname);
void Init_udma();
extern void ISR_Transfer_Status();




#endif /* MCAL_INCLUDE_UDMA_H_ */
