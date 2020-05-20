/*******************************************************************************
* File Name: Timer5_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer5.h"

static Timer5_backupStruct Timer5_backup;


/*******************************************************************************
* Function Name: Timer5_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer5_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer5_SaveConfig(void) 
{
    #if (!Timer5_UsingFixedFunction)
        Timer5_backup.TimerUdb = Timer5_ReadCounter();
        Timer5_backup.InterruptMaskValue = Timer5_STATUS_MASK;
        #if (Timer5_UsingHWCaptureCounter)
            Timer5_backup.TimerCaptureCounter = Timer5_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer5_UDB_CONTROL_REG_REMOVED)
            Timer5_backup.TimerControlRegister = Timer5_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer5_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer5_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer5_RestoreConfig(void) 
{   
    #if (!Timer5_UsingFixedFunction)

        Timer5_WriteCounter(Timer5_backup.TimerUdb);
        Timer5_STATUS_MASK =Timer5_backup.InterruptMaskValue;
        #if (Timer5_UsingHWCaptureCounter)
            Timer5_SetCaptureCount(Timer5_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer5_UDB_CONTROL_REG_REMOVED)
            Timer5_WriteControlRegister(Timer5_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer5_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer5_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer5_Sleep(void) 
{
    #if(!Timer5_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer5_CTRL_ENABLE == (Timer5_CONTROL & Timer5_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer5_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer5_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer5_Stop();
    Timer5_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer5_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer5_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer5_Wakeup(void) 
{
    Timer5_RestoreConfig();
    #if(!Timer5_UDB_CONTROL_REG_REMOVED)
        if(Timer5_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer5_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
