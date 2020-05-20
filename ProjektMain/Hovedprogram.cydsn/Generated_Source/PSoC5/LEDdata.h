/*******************************************************************************
* File Name: LEDdata.h  
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

#if !defined(CY_PINS_LEDdata_H) /* Pins LEDdata_H */
#define CY_PINS_LEDdata_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDdata_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDdata__PORT == 15 && ((LEDdata__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDdata_Write(uint8 value);
void    LEDdata_SetDriveMode(uint8 mode);
uint8   LEDdata_ReadDataReg(void);
uint8   LEDdata_Read(void);
void    LEDdata_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDdata_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDdata_SetDriveMode() function.
     *  @{
     */
        #define LEDdata_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDdata_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDdata_DM_RES_UP          PIN_DM_RES_UP
        #define LEDdata_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDdata_DM_OD_LO           PIN_DM_OD_LO
        #define LEDdata_DM_OD_HI           PIN_DM_OD_HI
        #define LEDdata_DM_STRONG          PIN_DM_STRONG
        #define LEDdata_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDdata_MASK               LEDdata__MASK
#define LEDdata_SHIFT              LEDdata__SHIFT
#define LEDdata_WIDTH              1u

/* Interrupt constants */
#if defined(LEDdata__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDdata_SetInterruptMode() function.
     *  @{
     */
        #define LEDdata_INTR_NONE      (uint16)(0x0000u)
        #define LEDdata_INTR_RISING    (uint16)(0x0001u)
        #define LEDdata_INTR_FALLING   (uint16)(0x0002u)
        #define LEDdata_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDdata_INTR_MASK      (0x01u) 
#endif /* (LEDdata__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDdata_PS                     (* (reg8 *) LEDdata__PS)
/* Data Register */
#define LEDdata_DR                     (* (reg8 *) LEDdata__DR)
/* Port Number */
#define LEDdata_PRT_NUM                (* (reg8 *) LEDdata__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDdata_AG                     (* (reg8 *) LEDdata__AG)                       
/* Analog MUX bux enable */
#define LEDdata_AMUX                   (* (reg8 *) LEDdata__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDdata_BIE                    (* (reg8 *) LEDdata__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDdata_BIT_MASK               (* (reg8 *) LEDdata__BIT_MASK)
/* Bypass Enable */
#define LEDdata_BYP                    (* (reg8 *) LEDdata__BYP)
/* Port wide control signals */                                                   
#define LEDdata_CTL                    (* (reg8 *) LEDdata__CTL)
/* Drive Modes */
#define LEDdata_DM0                    (* (reg8 *) LEDdata__DM0) 
#define LEDdata_DM1                    (* (reg8 *) LEDdata__DM1)
#define LEDdata_DM2                    (* (reg8 *) LEDdata__DM2) 
/* Input Buffer Disable Override */
#define LEDdata_INP_DIS                (* (reg8 *) LEDdata__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDdata_LCD_COM_SEG            (* (reg8 *) LEDdata__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDdata_LCD_EN                 (* (reg8 *) LEDdata__LCD_EN)
/* Slew Rate Control */
#define LEDdata_SLW                    (* (reg8 *) LEDdata__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDdata_PRTDSI__CAPS_SEL       (* (reg8 *) LEDdata__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDdata_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDdata__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDdata_PRTDSI__OE_SEL0        (* (reg8 *) LEDdata__PRTDSI__OE_SEL0) 
#define LEDdata_PRTDSI__OE_SEL1        (* (reg8 *) LEDdata__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDdata_PRTDSI__OUT_SEL0       (* (reg8 *) LEDdata__PRTDSI__OUT_SEL0) 
#define LEDdata_PRTDSI__OUT_SEL1       (* (reg8 *) LEDdata__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDdata_PRTDSI__SYNC_OUT       (* (reg8 *) LEDdata__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDdata__SIO_CFG)
    #define LEDdata_SIO_HYST_EN        (* (reg8 *) LEDdata__SIO_HYST_EN)
    #define LEDdata_SIO_REG_HIFREQ     (* (reg8 *) LEDdata__SIO_REG_HIFREQ)
    #define LEDdata_SIO_CFG            (* (reg8 *) LEDdata__SIO_CFG)
    #define LEDdata_SIO_DIFF           (* (reg8 *) LEDdata__SIO_DIFF)
#endif /* (LEDdata__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDdata__INTSTAT)
    #define LEDdata_INTSTAT            (* (reg8 *) LEDdata__INTSTAT)
    #define LEDdata_SNAP               (* (reg8 *) LEDdata__SNAP)
    
	#define LEDdata_0_INTTYPE_REG 		(* (reg8 *) LEDdata__0__INTTYPE)
#endif /* (LEDdata__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDdata_H */


/* [] END OF FILE */
