/*******************************************************************************
* File Name: Timer_Stopur_PM.c
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

#include "Timer_Stopur.h"

static Timer_Stopur_backupStruct Timer_Stopur_backup;


/*******************************************************************************
* Function Name: Timer_Stopur_SaveConfig
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
*  Timer_Stopur_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Stopur_SaveConfig(void) 
{
    #if (!Timer_Stopur_UsingFixedFunction)
        Timer_Stopur_backup.TimerUdb = Timer_Stopur_ReadCounter();
        Timer_Stopur_backup.InterruptMaskValue = Timer_Stopur_STATUS_MASK;
        #if (Timer_Stopur_UsingHWCaptureCounter)
            Timer_Stopur_backup.TimerCaptureCounter = Timer_Stopur_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Stopur_UDB_CONTROL_REG_REMOVED)
            Timer_Stopur_backup.TimerControlRegister = Timer_Stopur_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Stopur_RestoreConfig
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
*  Timer_Stopur_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Stopur_RestoreConfig(void) 
{   
    #if (!Timer_Stopur_UsingFixedFunction)

        Timer_Stopur_WriteCounter(Timer_Stopur_backup.TimerUdb);
        Timer_Stopur_STATUS_MASK =Timer_Stopur_backup.InterruptMaskValue;
        #if (Timer_Stopur_UsingHWCaptureCounter)
            Timer_Stopur_SetCaptureCount(Timer_Stopur_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Stopur_UDB_CONTROL_REG_REMOVED)
            Timer_Stopur_WriteControlRegister(Timer_Stopur_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Stopur_Sleep
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
*  Timer_Stopur_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Stopur_Sleep(void) 
{
    #if(!Timer_Stopur_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Stopur_CTRL_ENABLE == (Timer_Stopur_CONTROL & Timer_Stopur_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Stopur_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Stopur_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Stopur_Stop();
    Timer_Stopur_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Stopur_Wakeup
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
*  Timer_Stopur_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Stopur_Wakeup(void) 
{
    Timer_Stopur_RestoreConfig();
    #if(!Timer_Stopur_UDB_CONTROL_REG_REMOVED)
        if(Timer_Stopur_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Stopur_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
