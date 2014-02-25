/*******************************************************************************
* File Name: G.h  
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

#if !defined(CY_PINS_G_H) /* Pins G_H */
#define CY_PINS_G_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "G_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 G__PORT == 15 && ((G__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    G_Write(uint8 value) ;
void    G_SetDriveMode(uint8 mode) ;
uint8   G_ReadDataReg(void) ;
uint8   G_Read(void) ;
uint8   G_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define G_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define G_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define G_DM_RES_UP          PIN_DM_RES_UP
#define G_DM_RES_DWN         PIN_DM_RES_DWN
#define G_DM_OD_LO           PIN_DM_OD_LO
#define G_DM_OD_HI           PIN_DM_OD_HI
#define G_DM_STRONG          PIN_DM_STRONG
#define G_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define G_MASK               G__MASK
#define G_SHIFT              G__SHIFT
#define G_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define G_PS                     (* (reg8 *) G__PS)
/* Data Register */
#define G_DR                     (* (reg8 *) G__DR)
/* Port Number */
#define G_PRT_NUM                (* (reg8 *) G__PRT) 
/* Connect to Analog Globals */                                                  
#define G_AG                     (* (reg8 *) G__AG)                       
/* Analog MUX bux enable */
#define G_AMUX                   (* (reg8 *) G__AMUX) 
/* Bidirectional Enable */                                                        
#define G_BIE                    (* (reg8 *) G__BIE)
/* Bit-mask for Aliased Register Access */
#define G_BIT_MASK               (* (reg8 *) G__BIT_MASK)
/* Bypass Enable */
#define G_BYP                    (* (reg8 *) G__BYP)
/* Port wide control signals */                                                   
#define G_CTL                    (* (reg8 *) G__CTL)
/* Drive Modes */
#define G_DM0                    (* (reg8 *) G__DM0) 
#define G_DM1                    (* (reg8 *) G__DM1)
#define G_DM2                    (* (reg8 *) G__DM2) 
/* Input Buffer Disable Override */
#define G_INP_DIS                (* (reg8 *) G__INP_DIS)
/* LCD Common or Segment Drive */
#define G_LCD_COM_SEG            (* (reg8 *) G__LCD_COM_SEG)
/* Enable Segment LCD */
#define G_LCD_EN                 (* (reg8 *) G__LCD_EN)
/* Slew Rate Control */
#define G_SLW                    (* (reg8 *) G__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define G_PRTDSI__CAPS_SEL       (* (reg8 *) G__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define G_PRTDSI__DBL_SYNC_IN    (* (reg8 *) G__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define G_PRTDSI__OE_SEL0        (* (reg8 *) G__PRTDSI__OE_SEL0) 
#define G_PRTDSI__OE_SEL1        (* (reg8 *) G__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define G_PRTDSI__OUT_SEL0       (* (reg8 *) G__PRTDSI__OUT_SEL0) 
#define G_PRTDSI__OUT_SEL1       (* (reg8 *) G__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define G_PRTDSI__SYNC_OUT       (* (reg8 *) G__PRTDSI__SYNC_OUT) 


#if defined(G__INTSTAT)  /* Interrupt Registers */

    #define G_INTSTAT                (* (reg8 *) G__INTSTAT)
    #define G_SNAP                   (* (reg8 *) G__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_G_H */


/* [] END OF FILE */
