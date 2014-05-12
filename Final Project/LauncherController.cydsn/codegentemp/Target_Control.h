/*******************************************************************************
* File Name: Target_Control.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Target_Control_H) /* Pins Target_Control_H */
#define CY_PINS_Target_Control_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Target_Control_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Target_Control__PORT == 15 && ((Target_Control__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Target_Control_Write(uint8 value) ;
void    Target_Control_SetDriveMode(uint8 mode) ;
uint8   Target_Control_ReadDataReg(void) ;
uint8   Target_Control_Read(void) ;
uint8   Target_Control_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Target_Control_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Target_Control_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Target_Control_DM_RES_UP          PIN_DM_RES_UP
#define Target_Control_DM_RES_DWN         PIN_DM_RES_DWN
#define Target_Control_DM_OD_LO           PIN_DM_OD_LO
#define Target_Control_DM_OD_HI           PIN_DM_OD_HI
#define Target_Control_DM_STRONG          PIN_DM_STRONG
#define Target_Control_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Target_Control_MASK               Target_Control__MASK
#define Target_Control_SHIFT              Target_Control__SHIFT
#define Target_Control_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Target_Control_PS                     (* (reg8 *) Target_Control__PS)
/* Data Register */
#define Target_Control_DR                     (* (reg8 *) Target_Control__DR)
/* Port Number */
#define Target_Control_PRT_NUM                (* (reg8 *) Target_Control__PRT) 
/* Connect to Analog Globals */                                                  
#define Target_Control_AG                     (* (reg8 *) Target_Control__AG)                       
/* Analog MUX bux enable */
#define Target_Control_AMUX                   (* (reg8 *) Target_Control__AMUX) 
/* Bidirectional Enable */                                                        
#define Target_Control_BIE                    (* (reg8 *) Target_Control__BIE)
/* Bit-mask for Aliased Register Access */
#define Target_Control_BIT_MASK               (* (reg8 *) Target_Control__BIT_MASK)
/* Bypass Enable */
#define Target_Control_BYP                    (* (reg8 *) Target_Control__BYP)
/* Port wide control signals */                                                   
#define Target_Control_CTL                    (* (reg8 *) Target_Control__CTL)
/* Drive Modes */
#define Target_Control_DM0                    (* (reg8 *) Target_Control__DM0) 
#define Target_Control_DM1                    (* (reg8 *) Target_Control__DM1)
#define Target_Control_DM2                    (* (reg8 *) Target_Control__DM2) 
/* Input Buffer Disable Override */
#define Target_Control_INP_DIS                (* (reg8 *) Target_Control__INP_DIS)
/* LCD Common or Segment Drive */
#define Target_Control_LCD_COM_SEG            (* (reg8 *) Target_Control__LCD_COM_SEG)
/* Enable Segment LCD */
#define Target_Control_LCD_EN                 (* (reg8 *) Target_Control__LCD_EN)
/* Slew Rate Control */
#define Target_Control_SLW                    (* (reg8 *) Target_Control__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Target_Control_PRTDSI__CAPS_SEL       (* (reg8 *) Target_Control__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Target_Control_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Target_Control__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Target_Control_PRTDSI__OE_SEL0        (* (reg8 *) Target_Control__PRTDSI__OE_SEL0) 
#define Target_Control_PRTDSI__OE_SEL1        (* (reg8 *) Target_Control__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Target_Control_PRTDSI__OUT_SEL0       (* (reg8 *) Target_Control__PRTDSI__OUT_SEL0) 
#define Target_Control_PRTDSI__OUT_SEL1       (* (reg8 *) Target_Control__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Target_Control_PRTDSI__SYNC_OUT       (* (reg8 *) Target_Control__PRTDSI__SYNC_OUT) 


#if defined(Target_Control__INTSTAT)  /* Interrupt Registers */

    #define Target_Control_INTSTAT                (* (reg8 *) Target_Control__INTSTAT)
    #define Target_Control_SNAP                   (* (reg8 *) Target_Control__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Target_Control_H */


/* [] END OF FILE */
