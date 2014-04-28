/*******************************************************************************
* File Name: ADCclock.h
* Version 2.10
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

#if !defined(CY_CLOCK_ADCclock_H)
#define CY_CLOCK_ADCclock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void ADCclock_Start(void) ;
void ADCclock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ADCclock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void ADCclock_StandbyPower(uint8 state) ;
void ADCclock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 ADCclock_GetDividerRegister(void) ;
void ADCclock_SetModeRegister(uint8 modeBitMask) ;
void ADCclock_ClearModeRegister(uint8 modeBitMask) ;
uint8 ADCclock_GetModeRegister(void) ;
void ADCclock_SetSourceRegister(uint8 clkSource) ;
uint8 ADCclock_GetSourceRegister(void) ;
#if defined(ADCclock__CFG3)
void ADCclock_SetPhaseRegister(uint8 clkPhase) ;
uint8 ADCclock_GetPhaseRegister(void) ;
#endif /* defined(ADCclock__CFG3) */

#define ADCclock_Enable()                       ADCclock_Start()
#define ADCclock_Disable()                      ADCclock_Stop()
#define ADCclock_SetDivider(clkDivider)         ADCclock_SetDividerRegister(clkDivider, 1u)
#define ADCclock_SetDividerValue(clkDivider)    ADCclock_SetDividerRegister((clkDivider) - 1u, 1u)
#define ADCclock_SetMode(clkMode)               ADCclock_SetModeRegister(clkMode)
#define ADCclock_SetSource(clkSource)           ADCclock_SetSourceRegister(clkSource)
#if defined(ADCclock__CFG3)
#define ADCclock_SetPhase(clkPhase)             ADCclock_SetPhaseRegister(clkPhase)
#define ADCclock_SetPhaseValue(clkPhase)        ADCclock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(ADCclock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ADCclock_CLKEN              (* (reg8 *) ADCclock__PM_ACT_CFG)
#define ADCclock_CLKEN_PTR          ((reg8 *) ADCclock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ADCclock_CLKSTBY            (* (reg8 *) ADCclock__PM_STBY_CFG)
#define ADCclock_CLKSTBY_PTR        ((reg8 *) ADCclock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ADCclock_DIV_LSB            (* (reg8 *) ADCclock__CFG0)
#define ADCclock_DIV_LSB_PTR        ((reg8 *) ADCclock__CFG0)
#define ADCclock_DIV_PTR            ((reg16 *) ADCclock__CFG0)

/* Clock MSB divider configuration register. */
#define ADCclock_DIV_MSB            (* (reg8 *) ADCclock__CFG1)
#define ADCclock_DIV_MSB_PTR        ((reg8 *) ADCclock__CFG1)

/* Mode and source configuration register */
#define ADCclock_MOD_SRC            (* (reg8 *) ADCclock__CFG2)
#define ADCclock_MOD_SRC_PTR        ((reg8 *) ADCclock__CFG2)

#if defined(ADCclock__CFG3)
/* Analog clock phase configuration register */
#define ADCclock_PHASE              (* (reg8 *) ADCclock__CFG3)
#define ADCclock_PHASE_PTR          ((reg8 *) ADCclock__CFG3)
#endif /* defined(ADCclock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ADCclock_CLKEN_MASK         ADCclock__PM_ACT_MSK
#define ADCclock_CLKSTBY_MASK       ADCclock__PM_STBY_MSK

/* CFG2 field masks */
#define ADCclock_SRC_SEL_MSK        ADCclock__CFG2_SRC_SEL_MASK
#define ADCclock_MODE_MASK          (~(ADCclock_SRC_SEL_MSK))

#if defined(ADCclock__CFG3)
/* CFG3 phase mask */
#define ADCclock_PHASE_MASK         ADCclock__CFG3_PHASE_DLY_MASK
#endif /* defined(ADCclock__CFG3) */

#endif /* CY_CLOCK_ADCclock_H */


/* [] END OF FILE */
