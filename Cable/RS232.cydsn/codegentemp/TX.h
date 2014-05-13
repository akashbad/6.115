/*******************************************************************************
* File Name: TX.h  
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

#if !defined(CY_PINS_TX_H) /* Pins TX_H */
#define CY_PINS_TX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TX_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TX__PORT == 15 && ((TX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TX_Write(uint8 value) ;
void    TX_SetDriveMode(uint8 mode) ;
uint8   TX_ReadDataReg(void) ;
uint8   TX_Read(void) ;
uint8   TX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TX_DM_RES_UP          PIN_DM_RES_UP
#define TX_DM_RES_DWN         PIN_DM_RES_DWN
#define TX_DM_OD_LO           PIN_DM_OD_LO
#define TX_DM_OD_HI           PIN_DM_OD_HI
#define TX_DM_STRONG          PIN_DM_STRONG
#define TX_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TX_MASK               TX__MASK
#define TX_SHIFT              TX__SHIFT
#define TX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TX_PS                     (* (reg8 *) TX__PS)
/* Data Register */
#define TX_DR                     (* (reg8 *) TX__DR)
/* Port Number */
#define TX_PRT_NUM                (* (reg8 *) TX__PRT) 
/* Connect to Analog Globals */                                                  
#define TX_AG                     (* (reg8 *) TX__AG)                       
/* Analog MUX bux enable */
#define TX_AMUX                   (* (reg8 *) TX__AMUX) 
/* Bidirectional Enable */                                                        
#define TX_BIE                    (* (reg8 *) TX__BIE)
/* Bit-mask for Aliased Register Access */
#define TX_BIT_MASK               (* (reg8 *) TX__BIT_MASK)
/* Bypass Enable */
#define TX_BYP                    (* (reg8 *) TX__BYP)
/* Port wide control signals */                                                   
#define TX_CTL                    (* (reg8 *) TX__CTL)
/* Drive Modes */
#define TX_DM0                    (* (reg8 *) TX__DM0) 
#define TX_DM1                    (* (reg8 *) TX__DM1)
#define TX_DM2                    (* (reg8 *) TX__DM2) 
/* Input Buffer Disable Override */
#define TX_INP_DIS                (* (reg8 *) TX__INP_DIS)
/* LCD Common or Segment Drive */
#define TX_LCD_COM_SEG            (* (reg8 *) TX__LCD_COM_SEG)
/* Enable Segment LCD */
#define TX_LCD_EN                 (* (reg8 *) TX__LCD_EN)
/* Slew Rate Control */
#define TX_SLW                    (* (reg8 *) TX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TX_PRTDSI__CAPS_SEL       (* (reg8 *) TX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TX_PRTDSI__OE_SEL0        (* (reg8 *) TX__PRTDSI__OE_SEL0) 
#define TX_PRTDSI__OE_SEL1        (* (reg8 *) TX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TX_PRTDSI__OUT_SEL0       (* (reg8 *) TX__PRTDSI__OUT_SEL0) 
#define TX_PRTDSI__OUT_SEL1       (* (reg8 *) TX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TX_PRTDSI__SYNC_OUT       (* (reg8 *) TX__PRTDSI__SYNC_OUT) 


#if defined(TX__INTSTAT)  /* Interrupt Registers */

    #define TX_INTSTAT                (* (reg8 *) TX__INTSTAT)
    #define TX_SNAP                   (* (reg8 *) TX__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TX_H */


/* [] END OF FILE */
