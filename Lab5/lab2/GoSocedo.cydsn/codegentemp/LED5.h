/*******************************************************************************
* File Name: LED5.h  
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

#if !defined(CY_PINS_LED5_H) /* Pins LED5_H */
#define CY_PINS_LED5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED5_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED5__PORT == 15 && ((LED5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LED5_Write(uint8 value) ;
void    LED5_SetDriveMode(uint8 mode) ;
uint8   LED5_ReadDataReg(void) ;
uint8   LED5_Read(void) ;
uint8   LED5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED5_DM_RES_UP          PIN_DM_RES_UP
#define LED5_DM_RES_DWN         PIN_DM_RES_DWN
#define LED5_DM_OD_LO           PIN_DM_OD_LO
#define LED5_DM_OD_HI           PIN_DM_OD_HI
#define LED5_DM_STRONG          PIN_DM_STRONG
#define LED5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED5_MASK               LED5__MASK
#define LED5_SHIFT              LED5__SHIFT
#define LED5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED5_PS                     (* (reg8 *) LED5__PS)
/* Data Register */
#define LED5_DR                     (* (reg8 *) LED5__DR)
/* Port Number */
#define LED5_PRT_NUM                (* (reg8 *) LED5__PRT) 
/* Connect to Analog Globals */                                                  
#define LED5_AG                     (* (reg8 *) LED5__AG)                       
/* Analog MUX bux enable */
#define LED5_AMUX                   (* (reg8 *) LED5__AMUX) 
/* Bidirectional Enable */                                                        
#define LED5_BIE                    (* (reg8 *) LED5__BIE)
/* Bit-mask for Aliased Register Access */
#define LED5_BIT_MASK               (* (reg8 *) LED5__BIT_MASK)
/* Bypass Enable */
#define LED5_BYP                    (* (reg8 *) LED5__BYP)
/* Port wide control signals */                                                   
#define LED5_CTL                    (* (reg8 *) LED5__CTL)
/* Drive Modes */
#define LED5_DM0                    (* (reg8 *) LED5__DM0) 
#define LED5_DM1                    (* (reg8 *) LED5__DM1)
#define LED5_DM2                    (* (reg8 *) LED5__DM2) 
/* Input Buffer Disable Override */
#define LED5_INP_DIS                (* (reg8 *) LED5__INP_DIS)
/* LCD Common or Segment Drive */
#define LED5_LCD_COM_SEG            (* (reg8 *) LED5__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED5_LCD_EN                 (* (reg8 *) LED5__LCD_EN)
/* Slew Rate Control */
#define LED5_SLW                    (* (reg8 *) LED5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED5_PRTDSI__CAPS_SEL       (* (reg8 *) LED5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED5_PRTDSI__OE_SEL0        (* (reg8 *) LED5__PRTDSI__OE_SEL0) 
#define LED5_PRTDSI__OE_SEL1        (* (reg8 *) LED5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED5_PRTDSI__OUT_SEL0       (* (reg8 *) LED5__PRTDSI__OUT_SEL0) 
#define LED5_PRTDSI__OUT_SEL1       (* (reg8 *) LED5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED5_PRTDSI__SYNC_OUT       (* (reg8 *) LED5__PRTDSI__SYNC_OUT) 


#if defined(LED5__INTSTAT)  /* Interrupt Registers */

    #define LED5_INTSTAT                (* (reg8 *) LED5__INTSTAT)
    #define LED5_SNAP                   (* (reg8 *) LED5__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED5_H */


/* [] END OF FILE */
