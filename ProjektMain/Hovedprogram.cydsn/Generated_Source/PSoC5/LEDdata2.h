/*******************************************************************************
* File Name: LEDdata2.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LEDdata2_H) /* Pins LEDdata2_H */
#define CY_PINS_LEDdata2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDdata2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDdata2__PORT == 15 && ((LEDdata2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDdata2_Write(uint8 value);
void    LEDdata2_SetDriveMode(uint8 mode);
uint8   LEDdata2_ReadDataReg(void);
uint8   LEDdata2_Read(void);
void    LEDdata2_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDdata2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDdata2_SetDriveMode() function.
     *  @{
     */
        #define LEDdata2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDdata2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDdata2_DM_RES_UP          PIN_DM_RES_UP
        #define LEDdata2_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDdata2_DM_OD_LO           PIN_DM_OD_LO
        #define LEDdata2_DM_OD_HI           PIN_DM_OD_HI
        #define LEDdata2_DM_STRONG          PIN_DM_STRONG
        #define LEDdata2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDdata2_MASK               LEDdata2__MASK
#define LEDdata2_SHIFT              LEDdata2__SHIFT
#define LEDdata2_WIDTH              1u

/* Interrupt constants */
#if defined(LEDdata2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDdata2_SetInterruptMode() function.
     *  @{
     */
        #define LEDdata2_INTR_NONE      (uint16)(0x0000u)
        #define LEDdata2_INTR_RISING    (uint16)(0x0001u)
        #define LEDdata2_INTR_FALLING   (uint16)(0x0002u)
        #define LEDdata2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDdata2_INTR_MASK      (0x01u) 
#endif /* (LEDdata2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDdata2_PS                     (* (reg8 *) LEDdata2__PS)
/* Data Register */
#define LEDdata2_DR                     (* (reg8 *) LEDdata2__DR)
/* Port Number */
#define LEDdata2_PRT_NUM                (* (reg8 *) LEDdata2__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDdata2_AG                     (* (reg8 *) LEDdata2__AG)                       
/* Analog MUX bux enable */
#define LEDdata2_AMUX                   (* (reg8 *) LEDdata2__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDdata2_BIE                    (* (reg8 *) LEDdata2__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDdata2_BIT_MASK               (* (reg8 *) LEDdata2__BIT_MASK)
/* Bypass Enable */
#define LEDdata2_BYP                    (* (reg8 *) LEDdata2__BYP)
/* Port wide control signals */                                                   
#define LEDdata2_CTL                    (* (reg8 *) LEDdata2__CTL)
/* Drive Modes */
#define LEDdata2_DM0                    (* (reg8 *) LEDdata2__DM0) 
#define LEDdata2_DM1                    (* (reg8 *) LEDdata2__DM1)
#define LEDdata2_DM2                    (* (reg8 *) LEDdata2__DM2) 
/* Input Buffer Disable Override */
#define LEDdata2_INP_DIS                (* (reg8 *) LEDdata2__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDdata2_LCD_COM_SEG            (* (reg8 *) LEDdata2__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDdata2_LCD_EN                 (* (reg8 *) LEDdata2__LCD_EN)
/* Slew Rate Control */
#define LEDdata2_SLW                    (* (reg8 *) LEDdata2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDdata2_PRTDSI__CAPS_SEL       (* (reg8 *) LEDdata2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDdata2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDdata2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDdata2_PRTDSI__OE_SEL0        (* (reg8 *) LEDdata2__PRTDSI__OE_SEL0) 
#define LEDdata2_PRTDSI__OE_SEL1        (* (reg8 *) LEDdata2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDdata2_PRTDSI__OUT_SEL0       (* (reg8 *) LEDdata2__PRTDSI__OUT_SEL0) 
#define LEDdata2_PRTDSI__OUT_SEL1       (* (reg8 *) LEDdata2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDdata2_PRTDSI__SYNC_OUT       (* (reg8 *) LEDdata2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDdata2__SIO_CFG)
    #define LEDdata2_SIO_HYST_EN        (* (reg8 *) LEDdata2__SIO_HYST_EN)
    #define LEDdata2_SIO_REG_HIFREQ     (* (reg8 *) LEDdata2__SIO_REG_HIFREQ)
    #define LEDdata2_SIO_CFG            (* (reg8 *) LEDdata2__SIO_CFG)
    #define LEDdata2_SIO_DIFF           (* (reg8 *) LEDdata2__SIO_DIFF)
#endif /* (LEDdata2__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDdata2__INTSTAT)
    #define LEDdata2_INTSTAT            (* (reg8 *) LEDdata2__INTSTAT)
    #define LEDdata2_SNAP               (* (reg8 *) LEDdata2__SNAP)
    
	#define LEDdata2_0_INTTYPE_REG 		(* (reg8 *) LEDdata2__0__INTTYPE)
#endif /* (LEDdata2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDdata2_H */


/* [] END OF FILE */
