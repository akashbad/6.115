/*******************************************************************************
* File Name: LED7.h  
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

#if !defined(CY_PINS_LED7_H) /* Pins LED7_H */
#define CY_PINS_LED7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED7_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED7__PORT == 15 && ((LED7__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LED7_Write(uint8 value) ;
void    LED7_SetDriveMode(uint8 mode) ;
uint8   LED7_ReadDataReg(void) ;
uint8   LED7_Read(void) ;
uint8   LED7_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED7_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED7_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED7_DM_RES_UP          PIN_DM_RES_UP
#define LED7_DM_RES_DWN         PIN_DM_RES_DWN
#define LED7_DM_OD_LO           PIN_DM_OD_LO
#define LED7_DM_OD_HI           PIN_DM_OD_HI
#define LED7_DM_STRONG          PIN_DM_STRONG
#define LED7_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED7_MASK               LED7__MASK
#define LED7_SHIFT              LED7__SHIFT
#define LED7_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED7_PS                     (* (reg8 *) LED7__PS)
/* Data Register */
#define LED7_DR                     (* (reg8 *) LED7__DR)
/* Port Number */
#define LED7_PRT_NUM                (* (reg8 *) LED7__PRT) 
/* Connect to Analog Globals */                                                  
#define LED7_AG                     (* (reg8 *) LED7__AG)                       
/* Analog MUX bux enable */
#define LED7_AMUX                   (* (reg8 *) LED7__AMUX) 
/* Bidirectional Enable */                                                        
#define LED7_BIE                    (* (reg8 *) LED7__BIE)
/* Bit-mask for Aliased Register Access */
#define LED7_BIT_MASK               (* (reg8 *) LED7__BIT_MASK)
/* Bypass Enable */
#define LED7_BYP                    (* (reg8 *) LED7__BYP)
/* Port wide control signals */                                                   
#define LED7_CTL                    (* (reg8 *) LED7__CTL)
/* Drive Modes */
#define LED7_DM0                    (* (reg8 *) LED7__DM0) 
#define LED7_DM1                    (* (reg8 *) LED7__DM1)
#define LED7_DM2                    (* (reg8 *) LED7__DM2) 
/* Input Buffer Disable Override */
#define LED7_INP_DIS                (* (reg8 *) LED7__INP_DIS)
/* LCD Common or Segment Drive */
#define LED7_LCD_COM_SEG            (* (reg8 *) LED7__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED7_LCD_EN                 (* (reg8 *) LED7__LCD_EN)
/* Slew Rate Control */
#define LED7_SLW                    (* (reg8 *) LED7__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED7_PRTDSI__CAPS_SEL       (* (reg8 *) LED7__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED7_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED7__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED7_PRTDSI__OE_SEL0        (* (reg8 *) LED7__PRTDSI__OE_SEL0) 
#define LED7_PRTDSI__OE_SEL1        (* (reg8 *) LED7__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED7_PRTDSI__OUT_SEL0       (* (reg8 *) LED7__PRTDSI__OUT_SEL0) 
#define LED7_PRTDSI__OUT_SEL1       (* (reg8 *) LED7__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED7_PRTDSI__SYNC_OUT       (* (reg8 *) LED7__PRTDSI__SYNC_OUT) 


#if defined(LED7__INTSTAT)  /* Interrupt Registers */

    #define LED7_INTSTAT                (* (reg8 *) LED7__INTSTAT)
    #define LED7_SNAP                   (* (reg8 *) LED7__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED7_H */


/* [] END OF FILE */
