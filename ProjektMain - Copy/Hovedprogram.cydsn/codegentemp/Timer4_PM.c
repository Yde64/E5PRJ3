/*******************************************************************************
* File Name: Timer4_PM.c
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

#include "Timer4.h"

static Timer4_backupStruct Timer4_backup;


/*******************************************************************************
* Function Name: Timer4_SaveConfig
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
*  Timer4_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer4_SaveConfig(void) 
{
    #if (!Timer4_UsingFixedFunction)
        Timer4_backup.TimerUdb = Timer4_ReadCounter();
        Timer4_backup.InterruptMaskValue = Timer4_STATUS_MASK;
        #if (Timer4_UsingHWCaptureCounter)
            Timer4_backup.TimerCaptureCounter = Timer4_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer4_UDB_CONTROL_REG_REMOVED)
            Timer4_backup.TimerControlRegister = Timer4_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer4_RestoreConfig
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
*  Timer4_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer4_RestoreConfig(void) 
{   
    #if (!Timer4_UsingFixedFunction)

        Timer4_WriteCounter(Timer4_backup.TimerUdb);
        Timer4_STATUS_MASK =Timer4_backup.InterruptMaskValue;
        #if (Timer4_UsingHWCaptureCounter)
            Timer4_SetCaptureCount(Timer4_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer4_UDB_CONTROL_REG_REMOVED)
            Timer4_WriteControlRegister(Timer4_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer4_Sleep
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
*  Timer4_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer4_Sleep(void) 
{
    #if(!Timer4_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer4_CTRL_ENABLE == (Timer4_CONTROL & Timer4_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer4_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer4_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer4_Stop();
    Timer4_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer4_Wakeup
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
*  Timer4_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer4_Wakeup(void) 
{
    Timer4_RestoreConfig();
    #if(!Timer4_UDB_CONTROL_REG_REMOVED)
        if(Timer4_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer4_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
