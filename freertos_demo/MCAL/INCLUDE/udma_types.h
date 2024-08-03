/*
 * udma_types.h
 *
 *  Created on: Aug 2, 2024
 *      Author: satis
 */

#ifndef MCAL_INCLUDE_UDMA_TYPES_H_
#define MCAL_INCLUDE_UDMA_TYPES_H_

#include <stdint.h>


typedef enum
{
    stop,
    Basic, /*used for the s/w transfer */
    Auto_Request,  /*Should only be used by the peripherals*/
    PingPong, /*Only supported by SPI . Need alternate data structire to eb configured */
    Memory_scatter_Gather,
    Alternate_memory_scatter,gather,
    Peripheral_scatter_gather,
    Alternate_peripheral_scatter_gather

}transfer_mode;

typedef enum
{
    one_trasfer,
    two_transfers,
    four_transfers,
    eight_transfers,
    thirtytwo_transfers,
    sixtyfour_tranfers ,
    transfer_128,
    transfer_256,
    transfer_512,
    transfer_1024, /*max size of the contro table */

}ARBITRATION_SIZE;

typedef enum
{
    Byte, /*8 bits */
    half_word, /*16 bits*/
    Word,   /*32 bits*/
    res

}DEST_SRC_SIZE_INC;

typedef struct
{
    DEST_SRC_SIZE_INC dest;
    uint32_t size;
}DMA_SIZEMAP;

typedef enum
{
    channel_0,
    channel_1,
    channel_2,
    channel_3,
    channel_4,
    channel_5,
    channel_6,
    channel_7,
    channel_8,
    channel_9,
    channel_10,
    channel_11,
    channel_12,
    channel_13,
    channel_14,
    channel_15,
    channel_16,
    channel_17,
    channel_18,
    channel_19,
    channel_20,
    channel_21,
    channel_22,
    channel_23,
    channel_24,
    channel_25,
    channel_26,
    channel_27,
    channel_28,
    channel_29,
    channel_30,
    channel_31,

}DMA_Channel ;





#endif /* MCAL_INCLUDE_UDMA_TYPES_H_ */
