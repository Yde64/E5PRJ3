/*******************************************************************************
* File Name: PlayerSelect.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_PlayerSelect_H)
#define CY_AMUX_PlayerSelect_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void PlayerSelect_Start(void) ;
#define PlayerSelect_Init() PlayerSelect_Start()
void PlayerSelect_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void PlayerSelect_Stop(void); */
/* void PlayerSelect_Select(uint8 channel); */
/* void PlayerSelect_Connect(uint8 channel); */
/* void PlayerSelect_Disconnect(uint8 channel); */
/* void PlayerSelect_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define PlayerSelect_CHANNELS  2u
#define PlayerSelect_MUXTYPE   1
#define PlayerSelect_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define PlayerSelect_NULL_CHANNEL 0xFFu
#define PlayerSelect_MUX_SINGLE   1
#define PlayerSelect_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if PlayerSelect_MUXTYPE == PlayerSelect_MUX_SINGLE
# if !PlayerSelect_ATMOSTONE
#  define PlayerSelect_Connect(channel) PlayerSelect_Set(channel)
# endif
# define PlayerSelect_Disconnect(channel) PlayerSelect_Unset(channel)
#else
# if !PlayerSelect_ATMOSTONE
void PlayerSelect_Connect(uint8 channel) ;
# endif
void PlayerSelect_Disconnect(uint8 channel) ;
#endif

#if PlayerSelect_ATMOSTONE
# define PlayerSelect_Stop() PlayerSelect_DisconnectAll()
# define PlayerSelect_Select(channel) PlayerSelect_FastSelect(channel)
void PlayerSelect_DisconnectAll(void) ;
#else
# define PlayerSelect_Stop() PlayerSelect_Start()
void PlayerSelect_Select(uint8 channel) ;
# define PlayerSelect_DisconnectAll() PlayerSelect_Start()
#endif

#endif /* CY_AMUX_PlayerSelect_H */


/* [] END OF FILE */
