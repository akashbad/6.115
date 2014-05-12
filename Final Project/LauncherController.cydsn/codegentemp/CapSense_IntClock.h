/*******************************************************************************
* File Name: CapSense_IntClock.h
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

#if !defined(CY_CLOCK_CapSense_IntClock_H)
#define CY_CLOCK_CapSense_IntClock_H

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

void CapSense_IntClock_Start(void) ;
void CapSense_IntClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void CapSense_IntClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void CapSense_IntClock_StandbyPower(uint8 state) ;
void CapSense_IntClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 CapSense_IntClock_GetDividerRegister(void) ;
void CapSense_IntClock_SetModeRegister(uint8 modeBitMask) ;
void CapSense_IntClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 CapSense_IntClock_GetModeRegister(void) ;
void CapSense_IntClock_SetSourceRegister(uint8 clkSource) ;
uint8 CapSense_IntClock_GetSourceRegister(void) ;
#if defined(CapSense_IntClock__CFG3)
void CapSense_IntClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 CapSense_IntClock_GetPhaseRegister(void) ;
#endif /* defined(CapSense_IntClock__CFG3) */

#define CapSense_IntClock_Enable()                       CapSense_IntClock_Start()
#define CapSense_IntClock_Disable()                      CapSense_IntClock_Stop()
#define CapSense_IntClock_SetDivider(clkDivider)         CapSense_IntClock_SetDividerRegister(clkDivider, 1)
#define CapSense_IntClock_SetDividerValue(clkDivider)    CapSense_IntClock_SetDividerRegister((clkDivider) - 1, 1)
#define CapSense_IntClock_SetMode(clkMode)               CapSense_IntClock_SetModeRegister(clkMode)
#define CapSense_IntClock_SetSource(clkSource)           CapSense_IntClock_SetSourceRegister(clkSource)
#if defined(CapSense_IntClock__CFG3)
#define CapSense_IntClock_SetPhase(clkPhase)             CapSense_IntClock_SetPhaseRegister(clkPhase)
#define CapSense_IntClock_SetPhaseValue(clkPhase)        CapSense_IntClock_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(CapSense_IntClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define CapSense_IntClock_CLKEN              (* (reg8 *) CapSense_IntClock__PM_ACT_CFG)
#define CapSense_IntClock_CLKEN_PTR          ((reg8 *) CapSense_IntClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define CapSense_IntClock_CLKSTBY            (* (reg8 *) CapSense_IntClock__PM_STBY_CFG)
#define CapSense_IntClock_CLKSTBY_PTR        ((reg8 *) CapSense_IntClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define CapSense_IntClock_DIV_LSB            (* (reg8 *) CapSense_IntClock__CFG0)
#define CapSense_IntClock_DIV_LSB_PTR        ((reg8 *) CapSense_IntClock__CFG0)
#define CapSense_IntClock_DIV_PTR            ((reg16 *) CapSense_IntClock__CFG0)

/* Clock MSB divider configuration register. */
#define CapSense_IntClock_DIV_MSB            (* (reg8 *) CapSense_IntClock__CFG1)
#define CapSense_IntClock_DIV_MSB_PTR        ((reg8 *) CapSense_IntClock__CFG1)

/* Mode and source configuration register */
#define CapSense_IntClock_MOD_SRC            (* (reg8 *) CapSense_IntClock__CFG2)
#define CapSense_IntClock_MOD_SRC_PTR        ((reg8 *) CapSense_IntClock__CFG2)

#if defined(CapSense_IntClock__CFG3)
/* Analog clock phase configuration register */
#define CapSense_IntClock_PHASE              (* (reg8 *) CapSense_IntClock__CFG3)
#define CapSense_IntClock_PHASE_PTR          ((reg8 *) CapSense_IntClock__CFG3)
#endif /* defined(CapSense_IntClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define CapSense_IntClock_CLKEN_MASK         CapSense_IntClock__PM_ACT_MSK
#define CapSense_IntClock_CLKSTBY_MASK       CapSense_IntClock__PM_STBY_MSK

/* CFG2 field masks */
#define CapSense_IntClock_SRC_SEL_MSK        CapSense_IntClock__CFG2_SRC_SEL_MASK
#define CapSense_IntClock_MODE_MASK          (~(CapSense_IntClock_SRC_SEL_MSK))

#if defined(CapSense_IntClock__CFG3)
/* CFG3 phase mask */
#define CapSense_IntClock_PHASE_MASK         CapSense_IntClock__CFG3_PHASE_DLY_MASK
#endif /* defined(CapSense_IntClock__CFG3) */

#endif /* CY_CLOCK_CapSense_IntClock_H */


/* [] END OF FILE */
