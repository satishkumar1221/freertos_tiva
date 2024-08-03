/*
 * udma_config.c
 *
 *  Created on: Jul 31, 2024
 *      Author: satis
 */

#include "udma.h"

uint32_t V_Configure_controlstructure[2];
 uint32_t V_Dest_A[64];
 uint32_t V_Src_A[64];

const DMA_CONTROL_STRUCTURE C_DMA_Control_struct[TOTAL_CHANNELS_CONFIGURED ] =
{
      /*Channel*/               /*DMA control struture */                                            /*No need of priority*/
     {SW_TRANSFER_0 , channel_30 ,{ &V_Src_A , &V_Dest_A ,&V_Configure_controlstructure[0], 0x00} , {0 , (1U <<channel_30), (1U<<channel_30), (1U << channel_30) , (1U << channel_30), (1U << channel_30) }},
     {ADC_TRANSFER , channel_30 ,{ &V_Dest_A , &V_Src_A ,&V_Configure_controlstructure[1], 0x00},  {0 , (1U <<channel_7), (1U<<channel_7) ,  (1U << channel_7),(1U << channel_7), (1U << channel_7) }}

};

const DMA_SIZEMAP C_DMA_SIZEMAP[3] =
{
     {Byte , 1},
     {half_word , 2},
     {Word , 4}
};

