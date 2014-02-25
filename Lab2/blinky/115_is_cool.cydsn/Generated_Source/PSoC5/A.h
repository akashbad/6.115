/*******************************************************************************
* File Name: A.h  
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

#if !defined(CY_PINS_A_H) /* Pins A_H */
#define CY_PINS_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "A_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 A__PORT == 15 && ((A__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    A_Write(uint8 value) ;
void    A_SetDriveMode(uint8 mode) ;
uint8   A_ReadDataReg(void) ;
uint8   A_Read(void) ;
uint8   A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define A_DM_RES_UP          PIN_DM_RES_UP
#define A_DM_RES_DWN         PIN_DM_RES_DWN
#define A_DM_OD_LO           PIN_DM_OD_LO
#define A_DM_OD_HI           PIN_DM_OD_HI
#define A_DM_STRONG          PIN_DM_STRONG
#define A_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define A_MASK               A__MASK
#define A_SHIFT              A__SHIFT
#define A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define A_PS                     (* (reg8 *) A__PS)
/* Data Register */
#define A_DR                     (* (reg8 *) A__DR)
/* Port Number */
#define A_PRT_NUM                (* (reg8 *) A__PRT) 
/* Connect to Analog Globals */                                                  
#define A_AG                     (* (reg8 *) A__AG)                       
/* Analog MUX bux enable */
#define A_AMUX                   (* (reg8 *) A__AMUX) 
/* Bidirectional Enable */                                                        
#define A_BIE                    (* (reg8 *) A__BIE)
/* Bit-mask for Aliased Register Access */
#define A_BIT_MASK               (* (reg8 *) A__BIT_MASK)
/* Bypass Enable */
#define A_BYP                    (* (reg8 *) A__BYP)
/* Port wide control signals */                                                   
#define A_CTL                    (* (reg8 *) A__CTL)
/* Drive Modes */
#define A_DM0                    (* (reg8 *) A__DM0) 
#define A_DM1                    (* (reg8 *) A__DM1)
#define A_DM2                    (* (reg8 *) A__DM2) 
/* Input Buffer Disable Override */
#define A_INP_DIS                (* (reg8 *) A__INP_DIS)
/* LCD Common or Segment Drive */
#define A_LCD_COM_SEG            (* (reg8 *) A__LCD_COM_SEG)
/* Enable Segment LCD */
#define A_LCD_EN                 (* (reg8 *) A__LCD_EN)
/* Slew Rate Control */
#define A_SLW                    (* (reg8 *) A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define A_PRTDSI__CAPS_SEL       (* (reg8 *) A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define A_PRTDSI__OE_SEL0        (* (reg8 *) A__PRTDSI__OE_SEL0) 
#define A_PRTDSI__OE_SEL1        (* (reg8 *) A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define A_PRTDSI__OUT_SEL0       (* (reg8 *) A__PRTDSI__OUT_SEL0) 
#define A_PRTDSI__OUT_SEL1       (* (reg8 *) A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define A_PRTDSI__SYNC_OUT       (* (reg8 *) A__PRTDSI__SYNC_OUT) 


#if defined(A__INTSTAT)  /* Interrupt Registers */

    #define A_INTSTAT                (* (reg8 *) A__INTSTAT)
    #define A_SNAP                   (* (reg8 *) A__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_A_H */


/* [] END OF FILE */
