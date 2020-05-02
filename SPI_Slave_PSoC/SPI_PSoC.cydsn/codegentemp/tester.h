/*******************************************************************************
* File Name: tester.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_tester_H)
#define CY_ISR_tester_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void tester_Start(void);
void tester_StartEx(cyisraddress address);
void tester_Stop(void);

CY_ISR_PROTO(tester_Interrupt);

void tester_SetVector(cyisraddress address);
cyisraddress tester_GetVector(void);

void tester_SetPriority(uint8 priority);
uint8 tester_GetPriority(void);

void tester_Enable(void);
uint8 tester_GetState(void);
void tester_Disable(void);

void tester_SetPending(void);
void tester_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the tester ISR. */
#define tester_INTC_VECTOR            ((reg32 *) tester__INTC_VECT)

/* Address of the tester ISR priority. */
#define tester_INTC_PRIOR             ((reg8 *) tester__INTC_PRIOR_REG)

/* Priority of the tester interrupt. */
#define tester_INTC_PRIOR_NUMBER      tester__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable tester interrupt. */
#define tester_INTC_SET_EN            ((reg32 *) tester__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the tester interrupt. */
#define tester_INTC_CLR_EN            ((reg32 *) tester__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the tester interrupt state to pending. */
#define tester_INTC_SET_PD            ((reg32 *) tester__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the tester interrupt. */
#define tester_INTC_CLR_PD            ((reg32 *) tester__INTC_CLR_PD_REG)


#endif /* CY_ISR_tester_H */


/* [] END OF FILE */
