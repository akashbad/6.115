/*******************************************************************************
* File Name: LCD_Seg_Int_Clock.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_LCD_Seg_Int_Clock_H)
#define CY_CLOCK_LCD_Seg_Int_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void LCD_Seg_Int_Clock_Start(void) ;
void LCD_Seg_Int_Clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void LCD_Seg_Int_Clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void LCD_Seg_Int_Clock_StandbyPower(uint8 state) ;
void LCD_Seg_Int_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 LCD_Seg_Int_Clock_GetDividerRegister(void) ;
void LCD_Seg_Int_Clock_SetModeRegister(uint8 modeBitMask) ;
void LCD_Seg_Int_Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 LCD_Seg_Int_Clock_GetModeRegister(void) ;
void LCD_Seg_Int_Clock_SetSourceRegister(uint8 clkSource) ;
uint8 LCD_Seg_Int_Clock_GetSourceRegister(void) ;
#if defined(LCD_Seg_Int_Clock__CFG3)
void LCD_Seg_Int_Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 LCD_Seg_Int_Clock_GetPhaseRegister(void) ;
#endif /* defined(LCD_Seg_Int_Clock__CFG3) */

#define LCD_Seg_Int_Clock_Enable()                       LCD_Seg_Int_Clock_Start()
#define LCD_Seg_Int_Clock_Disable()                      LCD_Seg_Int_Clock_Stop()
#define LCD_Seg_Int_Clock_SetDivider(clkDivider)         LCD_Seg_Int_Clock_SetDividerRegister(clkDivider, 1)
#define LCD_Seg_Int_Clock_SetDividerValue(clkDivider)    LCD_Seg_Int_Clock_SetDividerRegister((clkDivider) - 1, 1)
#define LCD_Seg_Int_Clock_SetMode(clkMode)               LCD_Seg_Int_Clock_SetModeRegister(clkMode)
#define LCD_Seg_Int_Clock_SetSource(clkSource)           LCD_Seg_Int_Clock_SetSourceRegister(clkSource)
#if defined(LCD_Seg_Int_Clock__CFG3)
#define LCD_Seg_Int_Clock_SetPhase(clkPhase)             LCD_Seg_Int_Clock_SetPhaseRegister(clkPhase)
#define LCD_Seg_Int_Clock_SetPhaseValue(clkPhase)        LCD_Seg_Int_Clock_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(LCD_Seg_Int_Clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define LCD_Seg_Int_Clock_CLKEN              (* (reg8 *) LCD_Seg_Int_Clock__PM_ACT_CFG)
#define LCD_Seg_Int_Clock_CLKEN_PTR          ((reg8 *) LCD_Seg_Int_Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define LCD_Seg_Int_Clock_CLKSTBY            (* (reg8 *) LCD_Seg_Int_Clock__PM_STBY_CFG)
#define LCD_Seg_Int_Clock_CLKSTBY_PTR        ((reg8 *) LCD_Seg_Int_Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define LCD_Seg_Int_Clock_DIV_LSB            (* (reg8 *) LCD_Seg_Int_Clock__CFG0)
#define LCD_Seg_Int_Clock_DIV_LSB_PTR        ((reg8 *) LCD_Seg_Int_Clock__CFG0)
#define LCD_Seg_Int_Clock_DIV_PTR            ((reg16 *) LCD_Seg_Int_Clock__CFG0)

/* Clock MSB divider configuration register. */
#define LCD_Seg_Int_Clock_DIV_MSB            (* (reg8 *) LCD_Seg_Int_Clock__CFG1)
#define LCD_Seg_Int_Clock_DIV_MSB_PTR        ((reg8 *) LCD_Seg_Int_Clock__CFG1)

/* Mode and source configuration register */
#define LCD_Seg_Int_Clock_MOD_SRC            (* (reg8 *) LCD_Seg_Int_Clock__CFG2)
#define LCD_Seg_Int_Clock_MOD_SRC_PTR        ((reg8 *) LCD_Seg_Int_Clock__CFG2)

#if defined(LCD_Seg_Int_Clock__CFG3)
/* Analog clock phase configuration register */
#define LCD_Seg_Int_Clock_PHASE              (* (reg8 *) LCD_Seg_Int_Clock__CFG3)
#define LCD_Seg_Int_Clock_PHASE_PTR          ((reg8 *) LCD_Seg_Int_Clock__CFG3)
#endif /* defined(LCD_Seg_Int_Clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define LCD_Seg_Int_Clock_CLKEN_MASK         LCD_Seg_Int_Clock__PM_ACT_MSK
#define LCD_Seg_Int_Clock_CLKSTBY_MASK       LCD_Seg_Int_Clock__PM_STBY_MSK

/* CFG2 field masks */
#define LCD_Seg_Int_Clock_SRC_SEL_MSK        LCD_Seg_Int_Clock__CFG2_SRC_SEL_MASK
#define LCD_Seg_Int_Clock_MODE_MASK          (~(LCD_Seg_Int_Clock_SRC_SEL_MSK))

#if defined(LCD_Seg_Int_Clock__CFG3)
/* CFG3 phase mask */
#define LCD_Seg_Int_Clock_PHASE_MASK         LCD_Seg_Int_Clock__CFG3_PHASE_DLY_MASK
#endif /* defined(LCD_Seg_Int_Clock__CFG3) */

#endif /* CY_CLOCK_LCD_Seg_Int_Clock_H */


/* [] END OF FILE */
