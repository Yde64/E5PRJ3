/*******************************************************************************
* File Name: PlayerSelect.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "PlayerSelect.h"

static uint8 PlayerSelect_lastChannel = PlayerSelect_NULL_CHANNEL;


/*******************************************************************************
* Function Name: PlayerSelect_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void PlayerSelect_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < PlayerSelect_CHANNELS ; chan++)
    {
#if (PlayerSelect_MUXTYPE == PlayerSelect_MUX_SINGLE)
        PlayerSelect_Unset(chan);
#else
        PlayerSelect_CYAMUXSIDE_A_Unset(chan);
        PlayerSelect_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    PlayerSelect_lastChannel = PlayerSelect_NULL_CHANNEL;
}


#if (!PlayerSelect_ATMOSTONE)
/*******************************************************************************
* Function Name: PlayerSelect_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void PlayerSelect_Select(uint8 channel) 
{
    PlayerSelect_DisconnectAll();        /* Disconnect all previous connections */
    PlayerSelect_Connect(channel);       /* Make the given selection */
    PlayerSelect_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: PlayerSelect_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void PlayerSelect_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( PlayerSelect_lastChannel != PlayerSelect_NULL_CHANNEL)
    {
        PlayerSelect_Disconnect(PlayerSelect_lastChannel);
    }

    /* Make the new channel connection */
#if (PlayerSelect_MUXTYPE == PlayerSelect_MUX_SINGLE)
    PlayerSelect_Set(channel);
#else
    PlayerSelect_CYAMUXSIDE_A_Set(channel);
    PlayerSelect_CYAMUXSIDE_B_Set(channel);
#endif


    PlayerSelect_lastChannel = channel;   /* Update last channel */
}


#if (PlayerSelect_MUXTYPE == PlayerSelect_MUX_DIFF)
#if (!PlayerSelect_ATMOSTONE)
/*******************************************************************************
* Function Name: PlayerSelect_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void PlayerSelect_Connect(uint8 channel) 
{
    PlayerSelect_CYAMUXSIDE_A_Set(channel);
    PlayerSelect_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: PlayerSelect_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void PlayerSelect_Disconnect(uint8 channel) 
{
    PlayerSelect_CYAMUXSIDE_A_Unset(channel);
    PlayerSelect_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (PlayerSelect_ATMOSTONE)
/*******************************************************************************
* Function Name: PlayerSelect_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void PlayerSelect_DisconnectAll(void) 
{
    if(PlayerSelect_lastChannel != PlayerSelect_NULL_CHANNEL) 
    {
        PlayerSelect_Disconnect(PlayerSelect_lastChannel);
        PlayerSelect_lastChannel = PlayerSelect_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
