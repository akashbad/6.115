/*******************************************************************************
* File Name: PotPin.h  
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

#if !defined(CY_PINS_PotPin_H) /* Pins PotPin_H */
#define CY_PINS_PotPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PotPin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PotPin__PORT == 15 && ((PotPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PotPin_Write(uint8 value) ;
void    PotPin_SetDriveMode(uint8 mode) ;
uint8   PotPin_ReadDataReg(void) ;
uint8   PotPin_Read(void) ;
uint8   PotPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PotPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PotPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PotPin_DM_RES_UP          PIN_DM_RES_UP
#define PotPin_DM_RES_DWN         PIN_DM_RES_DWN
#define PotPin_DM_OD_LO           PIN_DM_OD_LO
#define PotPin_DM_OD_HI           PIN_DM_OD_HI
#define PotPin_DM_STRONG          PIN_DM_STRONG
#define PotPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PotPin_MASK               PotPin__MASK
#define PotPin_SHIFT              PotPin__SHIFT
#define PotPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PotPin_PS                     (* (reg8 *) PotPin__PS)
/* Data Register */
#define PotPin_DR                     (* (reg8 *) PotPin__DR)
/* Port Number */
#define PotPin_PRT_NUM                (* (reg8 *) PotPin__PRT) 
/* Connect to Analog Globals */                                                  
#define PotPin_AG                     (* (reg8 *) PotPin__AG)                       
/* Analog MUX bux enable */
#define PotPin_AMUX                   (* (reg8 *) PotPin__AMUX) 
/* Bidirectional Enable */                                                        
#define PotPin_BIE                    (* (reg8 *) PotPin__BIE)
/* Bit-mask for Aliased Register Access */
#define PotPin_BIT_MASK               (* (reg8 *) PotPin__BIT_MASK)
/* Bypass Enable */
#define PotPin_BYP                    (* (reg8 *) PotPin__BYP)
/* Port wide control signals */                                                   
#define PotPin_CTL                    (* (reg8 *) PotPin__CTL)
/* Drive Modes */
#define PotPin_DM0                    (* (reg8 *) PotPin__DM0) 
#define PotPin_DM1                    (* (reg8 *) PotPin__DM1)
#define PotPin_DM2                    (* (reg8 *) PotPin__DM2) 
/* Input Buffer Disable Override */
#define PotPin_INP_DIS                (* (reg8 *) PotPin__INP_DIS)
/* LCD Common or Segment Drive */
#define PotPin_LCD_COM_SEG            (* (reg8 *) PotPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define PotPin_LCD_EN                 (* (reg8 *) PotPin__LCD_EN)
/* Slew Rate Control */
#define PotPin_SLW                    (* (reg8 *) PotPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PotPin_PRTDSI__CAPS_SEL       (* (reg8 *) PotPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PotPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PotPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PotPin_PRTDSI__OE_SEL0        (* (reg8 *) PotPin__PRTDSI__OE_SEL0) 
#define PotPin_PRTDSI__OE_SEL1        (* (reg8 *) PotPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PotPin_PRTDSI__OUT_SEL0       (* (reg8 *) PotPin__PRTDSI__OUT_SEL0) 
#define PotPin_PRTDSI__OUT_SEL1       (* (reg8 *) PotPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PotPin_PRTDSI__SYNC_OUT       (* (reg8 *) PotPin__PRTDSI__SYNC_OUT) 


#if defined(PotPin__INTSTAT)  /* Interrupt Registers */

    #define PotPin_INTSTAT                (* (reg8 *) PotPin__INTSTAT)
    #define PotPin_SNAP                   (* (reg8 *) PotPin__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PotPin_H */


/* [] END OF FILE */
