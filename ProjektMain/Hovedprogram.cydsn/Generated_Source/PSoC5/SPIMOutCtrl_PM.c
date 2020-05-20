/*******************************************************************************
* File Name: SPIMOutCtrl_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIMOutCtrl.h"

/* Check for removal by optimization */
#if !defined(SPIMOutCtrl_Sync_ctrl_reg__REMOVED)

static SPIMOutCtrl_BACKUP_STRUCT  SPIMOutCtrl_backup = {0u};

    
/*******************************************************************************
* Function Name: SPIMOutCtrl_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIMOutCtrl_SaveConfig(void) 
{
    SPIMOutCtrl_backup.controlState = SPIMOutCtrl_Control;
}


/*******************************************************************************
* Function Name: SPIMOutCtrl_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void SPIMOutCtrl_RestoreConfig(void) 
{
     SPIMOutCtrl_Control = SPIMOutCtrl_backup.controlState;
}


/*******************************************************************************
* Function Name: SPIMOutCtrl_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIMOutCtrl_Sleep(void) 
{
    SPIMOutCtrl_SaveConfig();
}


/*******************************************************************************
* Function Name: SPIMOutCtrl_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIMOutCtrl_Wakeup(void)  
{
    SPIMOutCtrl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
