;
; File Name: cyfitteriar.inc
; 
; PSoC Creator  4.2
;
; Description:
; 
;
;-------------------------------------------------------------------------------
; Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;-------------------------------------------------------------------------------

#ifndef INCLUDED_CYFITTERIAR_INC
#define INCLUDED_CYFITTERIAR_INC
    INCLUDE cydeviceiar.inc
    INCLUDE cydeviceiar_trm.inc

/* SS */
SS__0__INTTYPE EQU CYREG_PICU3_INTTYPE6
SS__0__MASK EQU 0x40
SS__0__PC EQU CYREG_PRT3_PC6
SS__0__PORT EQU 3
SS__0__SHIFT EQU 6
SS__AG EQU CYREG_PRT3_AG
SS__AMUX EQU CYREG_PRT3_AMUX
SS__BIE EQU CYREG_PRT3_BIE
SS__BIT_MASK EQU CYREG_PRT3_BIT_MASK
SS__BYP EQU CYREG_PRT3_BYP
SS__CTL EQU CYREG_PRT3_CTL
SS__DM0 EQU CYREG_PRT3_DM0
SS__DM1 EQU CYREG_PRT3_DM1
SS__DM2 EQU CYREG_PRT3_DM2
SS__DR EQU CYREG_PRT3_DR
SS__INP_DIS EQU CYREG_PRT3_INP_DIS
SS__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU3_BASE
SS__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
SS__LCD_EN EQU CYREG_PRT3_LCD_EN
SS__MASK EQU 0x40
SS__PORT EQU 3
SS__PRT EQU CYREG_PRT3_PRT
SS__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
SS__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
SS__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
SS__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
SS__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
SS__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
SS__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
SS__PS EQU CYREG_PRT3_PS
SS__SHIFT EQU 6
SS__SLW EQU CYREG_PRT3_SLW

/* MISO */
MISO__0__INTTYPE EQU CYREG_PICU3_INTTYPE4
MISO__0__MASK EQU 0x10
MISO__0__PC EQU CYREG_PRT3_PC4
MISO__0__PORT EQU 3
MISO__0__SHIFT EQU 4
MISO__AG EQU CYREG_PRT3_AG
MISO__AMUX EQU CYREG_PRT3_AMUX
MISO__BIE EQU CYREG_PRT3_BIE
MISO__BIT_MASK EQU CYREG_PRT3_BIT_MASK
MISO__BYP EQU CYREG_PRT3_BYP
MISO__CTL EQU CYREG_PRT3_CTL
MISO__DM0 EQU CYREG_PRT3_DM0
MISO__DM1 EQU CYREG_PRT3_DM1
MISO__DM2 EQU CYREG_PRT3_DM2
MISO__DR EQU CYREG_PRT3_DR
MISO__INP_DIS EQU CYREG_PRT3_INP_DIS
MISO__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU3_BASE
MISO__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
MISO__LCD_EN EQU CYREG_PRT3_LCD_EN
MISO__MASK EQU 0x10
MISO__PORT EQU 3
MISO__PRT EQU CYREG_PRT3_PRT
MISO__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
MISO__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
MISO__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
MISO__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
MISO__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
MISO__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
MISO__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
MISO__PS EQU CYREG_PRT3_PS
MISO__SHIFT EQU 4
MISO__SLW EQU CYREG_PRT3_SLW

/* MOSI */
MOSI__0__INTTYPE EQU CYREG_PICU3_INTTYPE3
MOSI__0__MASK EQU 0x08
MOSI__0__PC EQU CYREG_PRT3_PC3
MOSI__0__PORT EQU 3
MOSI__0__SHIFT EQU 3
MOSI__AG EQU CYREG_PRT3_AG
MOSI__AMUX EQU CYREG_PRT3_AMUX
MOSI__BIE EQU CYREG_PRT3_BIE
MOSI__BIT_MASK EQU CYREG_PRT3_BIT_MASK
MOSI__BYP EQU CYREG_PRT3_BYP
MOSI__CTL EQU CYREG_PRT3_CTL
MOSI__DM0 EQU CYREG_PRT3_DM0
MOSI__DM1 EQU CYREG_PRT3_DM1
MOSI__DM2 EQU CYREG_PRT3_DM2
MOSI__DR EQU CYREG_PRT3_DR
MOSI__INP_DIS EQU CYREG_PRT3_INP_DIS
MOSI__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU3_BASE
MOSI__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
MOSI__LCD_EN EQU CYREG_PRT3_LCD_EN
MOSI__MASK EQU 0x08
MOSI__PORT EQU 3
MOSI__PRT EQU CYREG_PRT3_PRT
MOSI__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
MOSI__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
MOSI__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
MOSI__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
MOSI__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
MOSI__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
MOSI__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
MOSI__PS EQU CYREG_PRT3_PS
MOSI__SHIFT EQU 3
MOSI__SLW EQU CYREG_PRT3_SLW

/* SCLK */
SCLK__0__INTTYPE EQU CYREG_PICU3_INTTYPE5
SCLK__0__MASK EQU 0x20
SCLK__0__PC EQU CYREG_PRT3_PC5
SCLK__0__PORT EQU 3
SCLK__0__SHIFT EQU 5
SCLK__AG EQU CYREG_PRT3_AG
SCLK__AMUX EQU CYREG_PRT3_AMUX
SCLK__BIE EQU CYREG_PRT3_BIE
SCLK__BIT_MASK EQU CYREG_PRT3_BIT_MASK
SCLK__BYP EQU CYREG_PRT3_BYP
SCLK__CTL EQU CYREG_PRT3_CTL
SCLK__DM0 EQU CYREG_PRT3_DM0
SCLK__DM1 EQU CYREG_PRT3_DM1
SCLK__DM2 EQU CYREG_PRT3_DM2
SCLK__DR EQU CYREG_PRT3_DR
SCLK__INP_DIS EQU CYREG_PRT3_INP_DIS
SCLK__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU3_BASE
SCLK__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
SCLK__LCD_EN EQU CYREG_PRT3_LCD_EN
SCLK__MASK EQU 0x20
SCLK__PORT EQU 3
SCLK__PRT EQU CYREG_PRT3_PRT
SCLK__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
SCLK__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
SCLK__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
SCLK__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
SCLK__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
SCLK__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
SCLK__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
SCLK__PS EQU CYREG_PRT3_PS
SCLK__SHIFT EQU 5
SCLK__SLW EQU CYREG_PRT3_SLW

/* SPIS */
SPIS_BSPIS_BitCounter__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB04_05_ACTL
SPIS_BSPIS_BitCounter__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB04_05_CTL
SPIS_BSPIS_BitCounter__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB04_05_CTL
SPIS_BSPIS_BitCounter__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB04_05_CTL
SPIS_BSPIS_BitCounter__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB04_05_CTL
SPIS_BSPIS_BitCounter__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB04_05_MSK
SPIS_BSPIS_BitCounter__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB04_05_MSK
SPIS_BSPIS_BitCounter__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB04_05_MSK
SPIS_BSPIS_BitCounter__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB04_05_MSK
SPIS_BSPIS_BitCounter__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB04_ACTL
SPIS_BSPIS_BitCounter__CONTROL_REG EQU CYREG_B0_UDB04_CTL
SPIS_BSPIS_BitCounter__CONTROL_ST_REG EQU CYREG_B0_UDB04_ST_CTL
SPIS_BSPIS_BitCounter__COUNT_REG EQU CYREG_B0_UDB04_CTL
SPIS_BSPIS_BitCounter__COUNT_ST_REG EQU CYREG_B0_UDB04_ST_CTL
SPIS_BSPIS_BitCounter__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB04_MSK_ACTL
SPIS_BSPIS_BitCounter__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB04_MSK_ACTL
SPIS_BSPIS_BitCounter__PERIOD_REG EQU CYREG_B0_UDB04_MSK
SPIS_BSPIS_BitCounter_ST__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB04_05_ACTL
SPIS_BSPIS_BitCounter_ST__16BIT_STATUS_REG EQU CYREG_B0_UDB04_05_ST
SPIS_BSPIS_BitCounter_ST__MASK_REG EQU CYREG_B0_UDB04_MSK
SPIS_BSPIS_BitCounter_ST__MASK_ST_AUX_CTL_REG EQU CYREG_B0_UDB04_MSK_ACTL
SPIS_BSPIS_BitCounter_ST__PER_ST_AUX_CTL_REG EQU CYREG_B0_UDB04_MSK_ACTL
SPIS_BSPIS_BitCounter_ST__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB04_ACTL
SPIS_BSPIS_BitCounter_ST__STATUS_CNT_REG EQU CYREG_B0_UDB04_ST_CTL
SPIS_BSPIS_BitCounter_ST__STATUS_CONTROL_REG EQU CYREG_B0_UDB04_ST_CTL
SPIS_BSPIS_BitCounter_ST__STATUS_REG EQU CYREG_B0_UDB04_ST
SPIS_BSPIS_RxStsReg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB05_06_ACTL
SPIS_BSPIS_RxStsReg__16BIT_STATUS_REG EQU CYREG_B0_UDB05_06_ST
SPIS_BSPIS_RxStsReg__3__MASK EQU 0x08
SPIS_BSPIS_RxStsReg__3__POS EQU 3
SPIS_BSPIS_RxStsReg__4__MASK EQU 0x10
SPIS_BSPIS_RxStsReg__4__POS EQU 4
SPIS_BSPIS_RxStsReg__5__MASK EQU 0x20
SPIS_BSPIS_RxStsReg__5__POS EQU 5
SPIS_BSPIS_RxStsReg__6__MASK EQU 0x40
SPIS_BSPIS_RxStsReg__6__POS EQU 6
SPIS_BSPIS_RxStsReg__MASK EQU 0x78
SPIS_BSPIS_RxStsReg__MASK_REG EQU CYREG_B0_UDB05_MSK
SPIS_BSPIS_RxStsReg__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB05_ACTL
SPIS_BSPIS_RxStsReg__STATUS_REG EQU CYREG_B0_UDB05_ST
SPIS_BSPIS_sR8_Dp_u0__16BIT_A0_REG EQU CYREG_B0_UDB04_05_A0
SPIS_BSPIS_sR8_Dp_u0__16BIT_A1_REG EQU CYREG_B0_UDB04_05_A1
SPIS_BSPIS_sR8_Dp_u0__16BIT_D0_REG EQU CYREG_B0_UDB04_05_D0
SPIS_BSPIS_sR8_Dp_u0__16BIT_D1_REG EQU CYREG_B0_UDB04_05_D1
SPIS_BSPIS_sR8_Dp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB04_05_ACTL
SPIS_BSPIS_sR8_Dp_u0__16BIT_F0_REG EQU CYREG_B0_UDB04_05_F0
SPIS_BSPIS_sR8_Dp_u0__16BIT_F1_REG EQU CYREG_B0_UDB04_05_F1
SPIS_BSPIS_sR8_Dp_u0__A0_A1_REG EQU CYREG_B0_UDB04_A0_A1
SPIS_BSPIS_sR8_Dp_u0__A0_REG EQU CYREG_B0_UDB04_A0
SPIS_BSPIS_sR8_Dp_u0__A1_REG EQU CYREG_B0_UDB04_A1
SPIS_BSPIS_sR8_Dp_u0__D0_D1_REG EQU CYREG_B0_UDB04_D0_D1
SPIS_BSPIS_sR8_Dp_u0__D0_REG EQU CYREG_B0_UDB04_D0
SPIS_BSPIS_sR8_Dp_u0__D1_REG EQU CYREG_B0_UDB04_D1
SPIS_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB04_ACTL
SPIS_BSPIS_sR8_Dp_u0__F0_F1_REG EQU CYREG_B0_UDB04_F0_F1
SPIS_BSPIS_sR8_Dp_u0__F0_REG EQU CYREG_B0_UDB04_F0
SPIS_BSPIS_sR8_Dp_u0__F1_REG EQU CYREG_B0_UDB04_F1
SPIS_BSPIS_sR8_Dp_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB04_MSK_ACTL
SPIS_BSPIS_sR8_Dp_u0__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB04_MSK_ACTL
SPIS_BSPIS_TxStsReg__0__MASK EQU 0x01
SPIS_BSPIS_TxStsReg__0__POS EQU 0
SPIS_BSPIS_TxStsReg__1__MASK EQU 0x02
SPIS_BSPIS_TxStsReg__1__POS EQU 1
SPIS_BSPIS_TxStsReg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB06_07_ACTL
SPIS_BSPIS_TxStsReg__16BIT_STATUS_REG EQU CYREG_B0_UDB06_07_ST
SPIS_BSPIS_TxStsReg__2__MASK EQU 0x04
SPIS_BSPIS_TxStsReg__2__POS EQU 2
SPIS_BSPIS_TxStsReg__6__MASK EQU 0x40
SPIS_BSPIS_TxStsReg__6__POS EQU 6
SPIS_BSPIS_TxStsReg__MASK EQU 0x47
SPIS_BSPIS_TxStsReg__MASK_REG EQU CYREG_B0_UDB06_MSK
SPIS_BSPIS_TxStsReg__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB06_ACTL
SPIS_BSPIS_TxStsReg__STATUS_REG EQU CYREG_B0_UDB06_ST
SPIS_IntClock__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
SPIS_IntClock__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
SPIS_IntClock__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
SPIS_IntClock__CFG2_SRC_SEL_MASK EQU 0x07
SPIS_IntClock__INDEX EQU 0x00
SPIS_IntClock__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
SPIS_IntClock__PM_ACT_MSK EQU 0x01
SPIS_IntClock__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
SPIS_IntClock__PM_STBY_MSK EQU 0x01
SPIS_RxInternalInterrupt__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
SPIS_RxInternalInterrupt__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
SPIS_RxInternalInterrupt__INTC_MASK EQU 0x01
SPIS_RxInternalInterrupt__INTC_NUMBER EQU 0
SPIS_RxInternalInterrupt__INTC_PRIOR_NUM EQU 7
SPIS_RxInternalInterrupt__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_0
SPIS_RxInternalInterrupt__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
SPIS_RxInternalInterrupt__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0

/* rx_isr */
rx_isr__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
rx_isr__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
rx_isr__INTC_MASK EQU 0x02
rx_isr__INTC_NUMBER EQU 1
rx_isr__INTC_PRIOR_NUM EQU 7
rx_isr__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_1
rx_isr__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
rx_isr__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0

/* tester */
tester__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
tester__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
tester__INTC_MASK EQU 0x04
tester__INTC_NUMBER EQU 2
tester__INTC_PRIOR_NUM EQU 7
tester__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_2
tester__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
tester__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0

/* SPI_int */
SPI_int__0__INTTYPE EQU CYREG_PICU3_INTTYPE7
SPI_int__0__MASK EQU 0x80
SPI_int__0__PC EQU CYREG_PRT3_PC7
SPI_int__0__PORT EQU 3
SPI_int__0__SHIFT EQU 7
SPI_int__AG EQU CYREG_PRT3_AG
SPI_int__AMUX EQU CYREG_PRT3_AMUX
SPI_int__BIE EQU CYREG_PRT3_BIE
SPI_int__BIT_MASK EQU CYREG_PRT3_BIT_MASK
SPI_int__BYP EQU CYREG_PRT3_BYP
SPI_int__CTL EQU CYREG_PRT3_CTL
SPI_int__DM0 EQU CYREG_PRT3_DM0
SPI_int__DM1 EQU CYREG_PRT3_DM1
SPI_int__DM2 EQU CYREG_PRT3_DM2
SPI_int__DR EQU CYREG_PRT3_DR
SPI_int__INP_DIS EQU CYREG_PRT3_INP_DIS
SPI_int__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU3_BASE
SPI_int__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
SPI_int__LCD_EN EQU CYREG_PRT3_LCD_EN
SPI_int__MASK EQU 0x80
SPI_int__PORT EQU 3
SPI_int__PRT EQU CYREG_PRT3_PRT
SPI_int__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
SPI_int__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
SPI_int__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
SPI_int__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
SPI_int__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
SPI_int__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
SPI_int__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
SPI_int__PS EQU CYREG_PRT3_PS
SPI_int__SHIFT EQU 7
SPI_int__SLW EQU CYREG_PRT3_SLW

/* SW_tester */
SW_tester__0__INTTYPE EQU CYREG_PICU2_INTTYPE2
SW_tester__0__MASK EQU 0x04
SW_tester__0__PC EQU CYREG_PRT2_PC2
SW_tester__0__PORT EQU 2
SW_tester__0__SHIFT EQU 2
SW_tester__AG EQU CYREG_PRT2_AG
SW_tester__AMUX EQU CYREG_PRT2_AMUX
SW_tester__BIE EQU CYREG_PRT2_BIE
SW_tester__BIT_MASK EQU CYREG_PRT2_BIT_MASK
SW_tester__BYP EQU CYREG_PRT2_BYP
SW_tester__CTL EQU CYREG_PRT2_CTL
SW_tester__DM0 EQU CYREG_PRT2_DM0
SW_tester__DM1 EQU CYREG_PRT2_DM1
SW_tester__DM2 EQU CYREG_PRT2_DM2
SW_tester__DR EQU CYREG_PRT2_DR
SW_tester__INP_DIS EQU CYREG_PRT2_INP_DIS
SW_tester__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
SW_tester__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
SW_tester__LCD_EN EQU CYREG_PRT2_LCD_EN
SW_tester__MASK EQU 0x04
SW_tester__PORT EQU 2
SW_tester__PRT EQU CYREG_PRT2_PRT
SW_tester__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
SW_tester__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
SW_tester__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
SW_tester__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
SW_tester__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
SW_tester__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
SW_tester__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
SW_tester__PS EQU CYREG_PRT2_PS
SW_tester__SHIFT EQU 2
SW_tester__SLW EQU CYREG_PRT2_SLW

/* LED_tester */
LED_tester__0__INTTYPE EQU CYREG_PICU2_INTTYPE1
LED_tester__0__MASK EQU 0x02
LED_tester__0__PC EQU CYREG_PRT2_PC1
LED_tester__0__PORT EQU 2
LED_tester__0__SHIFT EQU 1
LED_tester__AG EQU CYREG_PRT2_AG
LED_tester__AMUX EQU CYREG_PRT2_AMUX
LED_tester__BIE EQU CYREG_PRT2_BIE
LED_tester__BIT_MASK EQU CYREG_PRT2_BIT_MASK
LED_tester__BYP EQU CYREG_PRT2_BYP
LED_tester__CTL EQU CYREG_PRT2_CTL
LED_tester__DM0 EQU CYREG_PRT2_DM0
LED_tester__DM1 EQU CYREG_PRT2_DM1
LED_tester__DM2 EQU CYREG_PRT2_DM2
LED_tester__DR EQU CYREG_PRT2_DR
LED_tester__INP_DIS EQU CYREG_PRT2_INP_DIS
LED_tester__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU2_BASE
LED_tester__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
LED_tester__LCD_EN EQU CYREG_PRT2_LCD_EN
LED_tester__MASK EQU 0x02
LED_tester__PORT EQU 2
LED_tester__PRT EQU CYREG_PRT2_PRT
LED_tester__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
LED_tester__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
LED_tester__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
LED_tester__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
LED_tester__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
LED_tester__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
LED_tester__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
LED_tester__PS EQU CYREG_PRT2_PS
LED_tester__SHIFT EQU 1
LED_tester__SLW EQU CYREG_PRT2_SLW

/* Miscellaneous */
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PSOC4A EQU 18
CYDEV_CHIP_DIE_PSOC5LP EQU 2
CYDEV_CHIP_DIE_PSOC5TM EQU 3
CYDEV_CHIP_DIE_TMA4 EQU 4
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_FM0P EQU 5
CYDEV_CHIP_FAMILY_FM3 EQU 6
CYDEV_CHIP_FAMILY_FM4 EQU 7
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_PSOC6 EQU 4
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E161069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 18
CYDEV_CHIP_MEMBER_4D EQU 13
CYDEV_CHIP_MEMBER_4E EQU 6
CYDEV_CHIP_MEMBER_4F EQU 19
CYDEV_CHIP_MEMBER_4G EQU 4
CYDEV_CHIP_MEMBER_4H EQU 17
CYDEV_CHIP_MEMBER_4I EQU 23
CYDEV_CHIP_MEMBER_4J EQU 14
CYDEV_CHIP_MEMBER_4K EQU 15
CYDEV_CHIP_MEMBER_4L EQU 22
CYDEV_CHIP_MEMBER_4M EQU 21
CYDEV_CHIP_MEMBER_4N EQU 10
CYDEV_CHIP_MEMBER_4O EQU 7
CYDEV_CHIP_MEMBER_4P EQU 20
CYDEV_CHIP_MEMBER_4Q EQU 12
CYDEV_CHIP_MEMBER_4R EQU 8
CYDEV_CHIP_MEMBER_4S EQU 11
CYDEV_CHIP_MEMBER_4T EQU 9
CYDEV_CHIP_MEMBER_4U EQU 5
CYDEV_CHIP_MEMBER_4V EQU 16
CYDEV_CHIP_MEMBER_5A EQU 3
CYDEV_CHIP_MEMBER_5B EQU 2
CYDEV_CHIP_MEMBER_6A EQU 24
CYDEV_CHIP_MEMBER_FM3 EQU 28
CYDEV_CHIP_MEMBER_FM4 EQU 29
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 EQU 25
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 EQU 26
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 EQU 27
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES1 EQU 1
CYDEV_CHIP_REV_PSOC5TM_PRODUCTION EQU 1
CYDEV_CHIP_REV_TMA4_ES EQU 17
CYDEV_CHIP_REV_TMA4_ES2 EQU 33
CYDEV_CHIP_REV_TMA4_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4H_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4I_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4J_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4K_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4N_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4O_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4P_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4Q_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4R_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4S_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4T_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4U_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4V_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_6A_ES EQU 17
CYDEV_CHIP_REVISION_6A_NO_UDB EQU 33
CYDEV_CHIP_REVISION_6A_PRODUCTION EQU 33
CYDEV_CHIP_REVISION_FM3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_FM4_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x80
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000007
CYDEV_IS_EXPORTING_CODE EQU 0
CYDEV_IS_IMPORTING_CODE EQU 0
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_STACK_SIZE EQU 0x0800
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3_MV EQU 5000
CYIPBLOCK_ARM_CM3_VERSION EQU 0
CYIPBLOCK_P3_ANAIF_VERSION EQU 0
CYIPBLOCK_P3_CAN_VERSION EQU 0
CYIPBLOCK_P3_CAPSENSE_VERSION EQU 0
CYIPBLOCK_P3_COMP_VERSION EQU 0
CYIPBLOCK_P3_DECIMATOR_VERSION EQU 0
CYIPBLOCK_P3_DFB_VERSION EQU 0
CYIPBLOCK_P3_DMA_VERSION EQU 0
CYIPBLOCK_P3_DRQ_VERSION EQU 0
CYIPBLOCK_P3_DSM_VERSION EQU 0
CYIPBLOCK_P3_EMIF_VERSION EQU 0
CYIPBLOCK_P3_I2C_VERSION EQU 0
CYIPBLOCK_P3_LCD_VERSION EQU 0
CYIPBLOCK_P3_LPF_VERSION EQU 0
CYIPBLOCK_P3_OPAMP_VERSION EQU 0
CYIPBLOCK_P3_PM_VERSION EQU 0
CYIPBLOCK_P3_SCCT_VERSION EQU 0
CYIPBLOCK_P3_TIMER_VERSION EQU 0
CYIPBLOCK_P3_USB_VERSION EQU 0
CYIPBLOCK_P3_VIDAC_VERSION EQU 0
CYIPBLOCK_P3_VREF_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 0
CYIPBLOCK_S8_IRQ_VERSION EQU 0
CYIPBLOCK_S8_SAR_VERSION EQU 0
CYIPBLOCK_S8_SIO_VERSION EQU 0
CYIPBLOCK_S8_UDB_VERSION EQU 0
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERIAR_INC */