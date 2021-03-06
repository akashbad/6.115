    IF :LNOT::DEF:INCLUDED_CYFITTERRV_INC
INCLUDED_CYFITTERRV_INC EQU 1
    GET cydevicerv.inc
    GET cydevicerv_trm.inc

; ADC_Ext_CP_Clk
ADC_Ext_CP_Clk__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
ADC_Ext_CP_Clk__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
ADC_Ext_CP_Clk__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
ADC_Ext_CP_Clk__CFG2_SRC_SEL_MASK EQU 0x07
ADC_Ext_CP_Clk__INDEX EQU 0x00
ADC_Ext_CP_Clk__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
ADC_Ext_CP_Clk__PM_ACT_MSK EQU 0x01
ADC_Ext_CP_Clk__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
ADC_Ext_CP_Clk__PM_STBY_MSK EQU 0x01

; ADC_theACLK
ADC_theACLK__CFG0 EQU CYREG_CLKDIST_ACFG0_CFG0
ADC_theACLK__CFG1 EQU CYREG_CLKDIST_ACFG0_CFG1
ADC_theACLK__CFG2 EQU CYREG_CLKDIST_ACFG0_CFG2
ADC_theACLK__CFG2_SRC_SEL_MASK EQU 0x07
ADC_theACLK__CFG3 EQU CYREG_CLKDIST_ACFG0_CFG3
ADC_theACLK__CFG3_PHASE_DLY_MASK EQU 0x0F
ADC_theACLK__INDEX EQU 0x00
ADC_theACLK__PM_ACT_CFG EQU CYREG_PM_ACT_CFG1
ADC_theACLK__PM_ACT_MSK EQU 0x01
ADC_theACLK__PM_STBY_CFG EQU CYREG_PM_STBY_CFG1
ADC_theACLK__PM_STBY_MSK EQU 0x01

; LCD_LCDPort
LCD_LCDPort__0__MASK EQU 0x01
LCD_LCDPort__0__PC EQU CYREG_PRT2_PC0
LCD_LCDPort__0__PORT EQU 2
LCD_LCDPort__0__SHIFT EQU 0
LCD_LCDPort__1__MASK EQU 0x02
LCD_LCDPort__1__PC EQU CYREG_PRT2_PC1
LCD_LCDPort__1__PORT EQU 2
LCD_LCDPort__1__SHIFT EQU 1
LCD_LCDPort__2__MASK EQU 0x04
LCD_LCDPort__2__PC EQU CYREG_PRT2_PC2
LCD_LCDPort__2__PORT EQU 2
LCD_LCDPort__2__SHIFT EQU 2
LCD_LCDPort__3__MASK EQU 0x08
LCD_LCDPort__3__PC EQU CYREG_PRT2_PC3
LCD_LCDPort__3__PORT EQU 2
LCD_LCDPort__3__SHIFT EQU 3
LCD_LCDPort__4__MASK EQU 0x10
LCD_LCDPort__4__PC EQU CYREG_PRT2_PC4
LCD_LCDPort__4__PORT EQU 2
LCD_LCDPort__4__SHIFT EQU 4
LCD_LCDPort__5__MASK EQU 0x20
LCD_LCDPort__5__PC EQU CYREG_PRT2_PC5
LCD_LCDPort__5__PORT EQU 2
LCD_LCDPort__5__SHIFT EQU 5
LCD_LCDPort__6__MASK EQU 0x40
LCD_LCDPort__6__PC EQU CYREG_PRT2_PC6
LCD_LCDPort__6__PORT EQU 2
LCD_LCDPort__6__SHIFT EQU 6
LCD_LCDPort__AG EQU CYREG_PRT2_AG
LCD_LCDPort__AMUX EQU CYREG_PRT2_AMUX
LCD_LCDPort__BIE EQU CYREG_PRT2_BIE
LCD_LCDPort__BIT_MASK EQU CYREG_PRT2_BIT_MASK
LCD_LCDPort__BYP EQU CYREG_PRT2_BYP
LCD_LCDPort__CTL EQU CYREG_PRT2_CTL
LCD_LCDPort__DM0 EQU CYREG_PRT2_DM0
LCD_LCDPort__DM1 EQU CYREG_PRT2_DM1
LCD_LCDPort__DM2 EQU CYREG_PRT2_DM2
LCD_LCDPort__DR EQU CYREG_PRT2_DR
LCD_LCDPort__INP_DIS EQU CYREG_PRT2_INP_DIS
LCD_LCDPort__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
LCD_LCDPort__LCD_EN EQU CYREG_PRT2_LCD_EN
LCD_LCDPort__MASK EQU 0x7F
LCD_LCDPort__PORT EQU 2
LCD_LCDPort__PRT EQU CYREG_PRT2_PRT
LCD_LCDPort__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
LCD_LCDPort__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
LCD_LCDPort__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
LCD_LCDPort__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
LCD_LCDPort__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
LCD_LCDPort__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
LCD_LCDPort__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
LCD_LCDPort__PS EQU CYREG_PRT2_PS
LCD_LCDPort__SHIFT EQU 0
LCD_LCDPort__SLW EQU CYREG_PRT2_SLW

; ADCclock
ADCclock__CFG0 EQU CYREG_CLKDIST_ACFG1_CFG0
ADCclock__CFG1 EQU CYREG_CLKDIST_ACFG1_CFG1
ADCclock__CFG2 EQU CYREG_CLKDIST_ACFG1_CFG2
ADCclock__CFG2_SRC_SEL_MASK EQU 0x07
ADCclock__CFG3 EQU CYREG_CLKDIST_ACFG1_CFG3
ADCclock__CFG3_PHASE_DLY_MASK EQU 0x0F
ADCclock__INDEX EQU 0x01
ADCclock__PM_ACT_CFG EQU CYREG_PM_ACT_CFG1
ADCclock__PM_ACT_MSK EQU 0x02
ADCclock__PM_STBY_CFG EQU CYREG_PM_STBY_CFG1
ADCclock__PM_STBY_MSK EQU 0x02

; ADC_DEC
ADC_DEC__COHER EQU CYREG_DEC_COHER
ADC_DEC__CR EQU CYREG_DEC_CR
ADC_DEC__DR1 EQU CYREG_DEC_DR1
ADC_DEC__DR2 EQU CYREG_DEC_DR2
ADC_DEC__DR2H EQU CYREG_DEC_DR2H
ADC_DEC__GCOR EQU CYREG_DEC_GCOR
ADC_DEC__GCORH EQU CYREG_DEC_GCORH
ADC_DEC__GVAL EQU CYREG_DEC_GVAL
ADC_DEC__OCOR EQU CYREG_DEC_OCOR
ADC_DEC__OCORH EQU CYREG_DEC_OCORH
ADC_DEC__OCORM EQU CYREG_DEC_OCORM
ADC_DEC__OUTSAMP EQU CYREG_DEC_OUTSAMP
ADC_DEC__OUTSAMPH EQU CYREG_DEC_OUTSAMPH
ADC_DEC__OUTSAMPM EQU CYREG_DEC_OUTSAMPM
ADC_DEC__OUTSAMPS EQU CYREG_DEC_OUTSAMPS
ADC_DEC__PM_ACT_CFG EQU CYREG_PM_ACT_CFG10
ADC_DEC__PM_ACT_MSK EQU 0x01
ADC_DEC__PM_STBY_CFG EQU CYREG_PM_STBY_CFG10
ADC_DEC__PM_STBY_MSK EQU 0x01
ADC_DEC__SHIFT1 EQU CYREG_DEC_SHIFT1
ADC_DEC__SHIFT2 EQU CYREG_DEC_SHIFT2
ADC_DEC__SR EQU CYREG_DEC_SR
ADC_DEC__TRIM__M1 EQU CYREG_FLSHID_CUST_TABLES_DEC_M1
ADC_DEC__TRIM__M2 EQU CYREG_FLSHID_CUST_TABLES_DEC_M2
ADC_DEC__TRIM__M3 EQU CYREG_FLSHID_CUST_TABLES_DEC_M3
ADC_DEC__TRIM__M4 EQU CYREG_FLSHID_CUST_TABLES_DEC_M4
ADC_DEC__TRIM__M5 EQU CYREG_FLSHID_CUST_TABLES_DEC_M5
ADC_DEC__TRIM__M6 EQU CYREG_FLSHID_CUST_TABLES_DEC_M6
ADC_DEC__TRIM__M7 EQU CYREG_FLSHID_CUST_TABLES_DEC_M7
ADC_DEC__TRIM__M8 EQU CYREG_FLSHID_CUST_TABLES_DEC_M8

; ADC_DSM
ADC_DSM__BUF0 EQU CYREG_DSM0_BUF0
ADC_DSM__BUF1 EQU CYREG_DSM0_BUF1
ADC_DSM__BUF2 EQU CYREG_DSM0_BUF2
ADC_DSM__BUF3 EQU CYREG_DSM0_BUF3
ADC_DSM__CLK EQU CYREG_DSM0_CLK
ADC_DSM__CR0 EQU CYREG_DSM0_CR0
ADC_DSM__CR1 EQU CYREG_DSM0_CR1
ADC_DSM__CR10 EQU CYREG_DSM0_CR10
ADC_DSM__CR11 EQU CYREG_DSM0_CR11
ADC_DSM__CR12 EQU CYREG_DSM0_CR12
ADC_DSM__CR13 EQU CYREG_DSM0_CR13
ADC_DSM__CR14 EQU CYREG_DSM0_CR14
ADC_DSM__CR15 EQU CYREG_DSM0_CR15
ADC_DSM__CR16 EQU CYREG_DSM0_CR16
ADC_DSM__CR17 EQU CYREG_DSM0_CR17
ADC_DSM__CR2 EQU CYREG_DSM0_CR2
ADC_DSM__CR3 EQU CYREG_DSM0_CR3
ADC_DSM__CR4 EQU CYREG_DSM0_CR4
ADC_DSM__CR5 EQU CYREG_DSM0_CR5
ADC_DSM__CR6 EQU CYREG_DSM0_CR6
ADC_DSM__CR7 EQU CYREG_DSM0_CR7
ADC_DSM__CR8 EQU CYREG_DSM0_CR8
ADC_DSM__CR9 EQU CYREG_DSM0_CR9
ADC_DSM__DEM0 EQU CYREG_DSM0_DEM0
ADC_DSM__DEM1 EQU CYREG_DSM0_DEM1
ADC_DSM__MISC EQU CYREG_DSM0_MISC
ADC_DSM__OUT0 EQU CYREG_DSM0_OUT0
ADC_DSM__OUT1 EQU CYREG_DSM0_OUT1
ADC_DSM__REF0 EQU CYREG_DSM0_REF0
ADC_DSM__REF1 EQU CYREG_DSM0_REF1
ADC_DSM__REF2 EQU CYREG_DSM0_REF2
ADC_DSM__REF3 EQU CYREG_DSM0_REF3
ADC_DSM__RSVD1 EQU CYREG_DSM0_RSVD1
ADC_DSM__SW0 EQU CYREG_DSM0_SW0
ADC_DSM__SW2 EQU CYREG_DSM0_SW2
ADC_DSM__SW3 EQU CYREG_DSM0_SW3
ADC_DSM__SW4 EQU CYREG_DSM0_SW4
ADC_DSM__SW6 EQU CYREG_DSM0_SW6
ADC_DSM__TR0 EQU CYREG_NPUMP_DSM_TR0
ADC_DSM__TST0 EQU CYREG_DSM0_TST0
ADC_DSM__TST1 EQU CYREG_DSM0_TST1

; ADC_IRQ
ADC_IRQ__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
ADC_IRQ__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
ADC_IRQ__INTC_MASK EQU 0x20000000
ADC_IRQ__INTC_NUMBER EQU 29
ADC_IRQ__INTC_PRIOR_NUM EQU 7
ADC_IRQ__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_29
ADC_IRQ__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
ADC_IRQ__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0

; PotPin
PotPin__0__MASK EQU 0x20
PotPin__0__PC EQU CYREG_PRT6_PC5
PotPin__0__PORT EQU 6
PotPin__0__SHIFT EQU 5
PotPin__AG EQU CYREG_PRT6_AG
PotPin__AMUX EQU CYREG_PRT6_AMUX
PotPin__BIE EQU CYREG_PRT6_BIE
PotPin__BIT_MASK EQU CYREG_PRT6_BIT_MASK
PotPin__BYP EQU CYREG_PRT6_BYP
PotPin__CTL EQU CYREG_PRT6_CTL
PotPin__DM0 EQU CYREG_PRT6_DM0
PotPin__DM1 EQU CYREG_PRT6_DM1
PotPin__DM2 EQU CYREG_PRT6_DM2
PotPin__DR EQU CYREG_PRT6_DR
PotPin__INP_DIS EQU CYREG_PRT6_INP_DIS
PotPin__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
PotPin__LCD_EN EQU CYREG_PRT6_LCD_EN
PotPin__MASK EQU 0x20
PotPin__PORT EQU 6
PotPin__PRT EQU CYREG_PRT6_PRT
PotPin__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
PotPin__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
PotPin__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
PotPin__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
PotPin__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
PotPin__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
PotPin__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
PotPin__PS EQU CYREG_PRT6_PS
PotPin__SHIFT EQU 5
PotPin__SLW EQU CYREG_PRT6_SLW

; LED0
LED0__0__MASK EQU 0x01
LED0__0__PC EQU CYREG_PRT5_PC0
LED0__0__PORT EQU 5
LED0__0__SHIFT EQU 0
LED0__AG EQU CYREG_PRT5_AG
LED0__AMUX EQU CYREG_PRT5_AMUX
LED0__BIE EQU CYREG_PRT5_BIE
LED0__BIT_MASK EQU CYREG_PRT5_BIT_MASK
LED0__BYP EQU CYREG_PRT5_BYP
LED0__CTL EQU CYREG_PRT5_CTL
LED0__DM0 EQU CYREG_PRT5_DM0
LED0__DM1 EQU CYREG_PRT5_DM1
LED0__DM2 EQU CYREG_PRT5_DM2
LED0__DR EQU CYREG_PRT5_DR
LED0__INP_DIS EQU CYREG_PRT5_INP_DIS
LED0__LCD_COM_SEG EQU CYREG_PRT5_LCD_COM_SEG
LED0__LCD_EN EQU CYREG_PRT5_LCD_EN
LED0__MASK EQU 0x01
LED0__PORT EQU 5
LED0__PRT EQU CYREG_PRT5_PRT
LED0__PRTDSI__CAPS_SEL EQU CYREG_PRT5_CAPS_SEL
LED0__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT5_DBL_SYNC_IN
LED0__PRTDSI__OE_SEL0 EQU CYREG_PRT5_OE_SEL0
LED0__PRTDSI__OE_SEL1 EQU CYREG_PRT5_OE_SEL1
LED0__PRTDSI__OUT_SEL0 EQU CYREG_PRT5_OUT_SEL0
LED0__PRTDSI__OUT_SEL1 EQU CYREG_PRT5_OUT_SEL1
LED0__PRTDSI__SYNC_OUT EQU CYREG_PRT5_SYNC_OUT
LED0__PS EQU CYREG_PRT5_PS
LED0__SHIFT EQU 0
LED0__SLW EQU CYREG_PRT5_SLW

; LED1
LED1__0__MASK EQU 0x01
LED1__0__PC EQU CYREG_PRT12_PC0
LED1__0__PORT EQU 12
LED1__0__SHIFT EQU 0
LED1__AG EQU CYREG_PRT12_AG
LED1__BIE EQU CYREG_PRT12_BIE
LED1__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LED1__BYP EQU CYREG_PRT12_BYP
LED1__DM0 EQU CYREG_PRT12_DM0
LED1__DM1 EQU CYREG_PRT12_DM1
LED1__DM2 EQU CYREG_PRT12_DM2
LED1__DR EQU CYREG_PRT12_DR
LED1__INP_DIS EQU CYREG_PRT12_INP_DIS
LED1__MASK EQU 0x01
LED1__PORT EQU 12
LED1__PRT EQU CYREG_PRT12_PRT
LED1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LED1__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LED1__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LED1__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LED1__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LED1__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LED1__PS EQU CYREG_PRT12_PS
LED1__SHIFT EQU 0
LED1__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LED1__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LED1__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LED1__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LED1__SLW EQU CYREG_PRT12_SLW

; LED2
LED2__0__MASK EQU 0x08
LED2__0__PC EQU CYREG_PRT12_PC3
LED2__0__PORT EQU 12
LED2__0__SHIFT EQU 3
LED2__AG EQU CYREG_PRT12_AG
LED2__BIE EQU CYREG_PRT12_BIE
LED2__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LED2__BYP EQU CYREG_PRT12_BYP
LED2__DM0 EQU CYREG_PRT12_DM0
LED2__DM1 EQU CYREG_PRT12_DM1
LED2__DM2 EQU CYREG_PRT12_DM2
LED2__DR EQU CYREG_PRT12_DR
LED2__INP_DIS EQU CYREG_PRT12_INP_DIS
LED2__MASK EQU 0x08
LED2__PORT EQU 12
LED2__PRT EQU CYREG_PRT12_PRT
LED2__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LED2__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LED2__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LED2__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LED2__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LED2__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LED2__PS EQU CYREG_PRT12_PS
LED2__SHIFT EQU 3
LED2__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LED2__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LED2__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LED2__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LED2__SLW EQU CYREG_PRT12_SLW

; LED3
LED3__0__MASK EQU 0x02
LED3__0__PC EQU CYREG_PRT12_PC1
LED3__0__PORT EQU 12
LED3__0__SHIFT EQU 1
LED3__AG EQU CYREG_PRT12_AG
LED3__BIE EQU CYREG_PRT12_BIE
LED3__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LED3__BYP EQU CYREG_PRT12_BYP
LED3__DM0 EQU CYREG_PRT12_DM0
LED3__DM1 EQU CYREG_PRT12_DM1
LED3__DM2 EQU CYREG_PRT12_DM2
LED3__DR EQU CYREG_PRT12_DR
LED3__INP_DIS EQU CYREG_PRT12_INP_DIS
LED3__MASK EQU 0x02
LED3__PORT EQU 12
LED3__PRT EQU CYREG_PRT12_PRT
LED3__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LED3__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LED3__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LED3__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LED3__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LED3__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LED3__PS EQU CYREG_PRT12_PS
LED3__SHIFT EQU 1
LED3__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LED3__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LED3__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LED3__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LED3__SLW EQU CYREG_PRT12_SLW

; LED4
LED4__0__MASK EQU 0x04
LED4__0__PC EQU CYREG_PRT12_PC2
LED4__0__PORT EQU 12
LED4__0__SHIFT EQU 2
LED4__AG EQU CYREG_PRT12_AG
LED4__BIE EQU CYREG_PRT12_BIE
LED4__BIT_MASK EQU CYREG_PRT12_BIT_MASK
LED4__BYP EQU CYREG_PRT12_BYP
LED4__DM0 EQU CYREG_PRT12_DM0
LED4__DM1 EQU CYREG_PRT12_DM1
LED4__DM2 EQU CYREG_PRT12_DM2
LED4__DR EQU CYREG_PRT12_DR
LED4__INP_DIS EQU CYREG_PRT12_INP_DIS
LED4__MASK EQU 0x04
LED4__PORT EQU 12
LED4__PRT EQU CYREG_PRT12_PRT
LED4__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
LED4__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
LED4__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
LED4__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
LED4__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
LED4__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
LED4__PS EQU CYREG_PRT12_PS
LED4__SHIFT EQU 2
LED4__SIO_CFG EQU CYREG_PRT12_SIO_CFG
LED4__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
LED4__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
LED4__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
LED4__SLW EQU CYREG_PRT12_SLW

; LED5
LED5__0__MASK EQU 0x02
LED5__0__PC EQU CYREG_PRT5_PC1
LED5__0__PORT EQU 5
LED5__0__SHIFT EQU 1
LED5__AG EQU CYREG_PRT5_AG
LED5__AMUX EQU CYREG_PRT5_AMUX
LED5__BIE EQU CYREG_PRT5_BIE
LED5__BIT_MASK EQU CYREG_PRT5_BIT_MASK
LED5__BYP EQU CYREG_PRT5_BYP
LED5__CTL EQU CYREG_PRT5_CTL
LED5__DM0 EQU CYREG_PRT5_DM0
LED5__DM1 EQU CYREG_PRT5_DM1
LED5__DM2 EQU CYREG_PRT5_DM2
LED5__DR EQU CYREG_PRT5_DR
LED5__INP_DIS EQU CYREG_PRT5_INP_DIS
LED5__LCD_COM_SEG EQU CYREG_PRT5_LCD_COM_SEG
LED5__LCD_EN EQU CYREG_PRT5_LCD_EN
LED5__MASK EQU 0x02
LED5__PORT EQU 5
LED5__PRT EQU CYREG_PRT5_PRT
LED5__PRTDSI__CAPS_SEL EQU CYREG_PRT5_CAPS_SEL
LED5__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT5_DBL_SYNC_IN
LED5__PRTDSI__OE_SEL0 EQU CYREG_PRT5_OE_SEL0
LED5__PRTDSI__OE_SEL1 EQU CYREG_PRT5_OE_SEL1
LED5__PRTDSI__OUT_SEL0 EQU CYREG_PRT5_OUT_SEL0
LED5__PRTDSI__OUT_SEL1 EQU CYREG_PRT5_OUT_SEL1
LED5__PRTDSI__SYNC_OUT EQU CYREG_PRT5_SYNC_OUT
LED5__PS EQU CYREG_PRT5_PS
LED5__SHIFT EQU 1
LED5__SLW EQU CYREG_PRT5_SLW

; LED6
LED6__0__MASK EQU 0x04
LED6__0__PC EQU CYREG_PRT5_PC2
LED6__0__PORT EQU 5
LED6__0__SHIFT EQU 2
LED6__AG EQU CYREG_PRT5_AG
LED6__AMUX EQU CYREG_PRT5_AMUX
LED6__BIE EQU CYREG_PRT5_BIE
LED6__BIT_MASK EQU CYREG_PRT5_BIT_MASK
LED6__BYP EQU CYREG_PRT5_BYP
LED6__CTL EQU CYREG_PRT5_CTL
LED6__DM0 EQU CYREG_PRT5_DM0
LED6__DM1 EQU CYREG_PRT5_DM1
LED6__DM2 EQU CYREG_PRT5_DM2
LED6__DR EQU CYREG_PRT5_DR
LED6__INP_DIS EQU CYREG_PRT5_INP_DIS
LED6__LCD_COM_SEG EQU CYREG_PRT5_LCD_COM_SEG
LED6__LCD_EN EQU CYREG_PRT5_LCD_EN
LED6__MASK EQU 0x04
LED6__PORT EQU 5
LED6__PRT EQU CYREG_PRT5_PRT
LED6__PRTDSI__CAPS_SEL EQU CYREG_PRT5_CAPS_SEL
LED6__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT5_DBL_SYNC_IN
LED6__PRTDSI__OE_SEL0 EQU CYREG_PRT5_OE_SEL0
LED6__PRTDSI__OE_SEL1 EQU CYREG_PRT5_OE_SEL1
LED6__PRTDSI__OUT_SEL0 EQU CYREG_PRT5_OUT_SEL0
LED6__PRTDSI__OUT_SEL1 EQU CYREG_PRT5_OUT_SEL1
LED6__PRTDSI__SYNC_OUT EQU CYREG_PRT5_SYNC_OUT
LED6__PS EQU CYREG_PRT5_PS
LED6__SHIFT EQU 2
LED6__SLW EQU CYREG_PRT5_SLW

; LED7
LED7__0__MASK EQU 0x08
LED7__0__PC EQU CYREG_PRT5_PC3
LED7__0__PORT EQU 5
LED7__0__SHIFT EQU 3
LED7__AG EQU CYREG_PRT5_AG
LED7__AMUX EQU CYREG_PRT5_AMUX
LED7__BIE EQU CYREG_PRT5_BIE
LED7__BIT_MASK EQU CYREG_PRT5_BIT_MASK
LED7__BYP EQU CYREG_PRT5_BYP
LED7__CTL EQU CYREG_PRT5_CTL
LED7__DM0 EQU CYREG_PRT5_DM0
LED7__DM1 EQU CYREG_PRT5_DM1
LED7__DM2 EQU CYREG_PRT5_DM2
LED7__DR EQU CYREG_PRT5_DR
LED7__INP_DIS EQU CYREG_PRT5_INP_DIS
LED7__LCD_COM_SEG EQU CYREG_PRT5_LCD_COM_SEG
LED7__LCD_EN EQU CYREG_PRT5_LCD_EN
LED7__MASK EQU 0x08
LED7__PORT EQU 5
LED7__PRT EQU CYREG_PRT5_PRT
LED7__PRTDSI__CAPS_SEL EQU CYREG_PRT5_CAPS_SEL
LED7__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT5_DBL_SYNC_IN
LED7__PRTDSI__OE_SEL0 EQU CYREG_PRT5_OE_SEL0
LED7__PRTDSI__OE_SEL1 EQU CYREG_PRT5_OE_SEL1
LED7__PRTDSI__OUT_SEL0 EQU CYREG_PRT5_OUT_SEL0
LED7__PRTDSI__OUT_SEL1 EQU CYREG_PRT5_OUT_SEL1
LED7__PRTDSI__SYNC_OUT EQU CYREG_PRT5_SYNC_OUT
LED7__PS EQU CYREG_PRT5_PS
LED7__SHIFT EQU 3
LED7__SLW EQU CYREG_PRT5_SLW

; Miscellaneous
; -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_MEMBER_5B EQU 4
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_DIE_PSOC5LP EQU 4
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_DIE_PSOC5LP
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PANTHER EQU 3
CYDEV_CHIP_DIE_PSOC4A EQU 2
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E123069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 2
CYDEV_CHIP_MEMBER_5A EQU 3
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REV_PSOC5LP_PRODUCTION
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PANTHER_ES0 EQU 0
CYDEV_CHIP_REV_PANTHER_ES1 EQU 1
CYDEV_CHIP_REV_PANTHER_PRODUCTION EQU 1
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x1000
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000000
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_STACK_SIZE EQU 0x4000
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0 EQU 5
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1 EQU 5
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2 EQU 5
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3 EQU 5
CYDEV_VIO3_MV EQU 5000
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0
    ENDIF
    END
