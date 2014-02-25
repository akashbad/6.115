/*******************************************************************************
* File Name: D.h  
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

#if !defined(CY_PINS_D_H) /* Pins D_H */
#define CY_PINS_D_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "D_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 D__PORT == 15 && ((D__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    D_Write(uint8 value) ;
void    D_SetDriveMode(uint8 mode) ;
uint8   D_ReadDataReg(void) ;
uint8   D_Read(void) ;
uint8   D_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define D_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define D_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define D_DM_RES_UP          PIN_DM_RES_UP
#define D_DM_RES_DWN         PIN_DM_RES_DWN
#define D_DM_OD_LO           PIN_DM_OD_LO
#define D_DM_OD_HI           PIN_DM_OD_HI
#define D_DM_STRONG          PIN_DM_STRONG
#define D_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define D_MASK               D__MASK
#define D_SHIFT              D__SHIFT
#define D_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define D_PS                     (* (reg8 *) D__PS)
/* Data Register */
#define D_DR                     (* (reg8 *) D__DR)
/* Port Number */
#define D_PRT_NUM                (* (reg8 *) D__PRT) 
/* Connect to Analog Globals */                                                  
#define D_AG                     (* (reg8 *) D__AG)                       
/* Analog MUX bux enable */
#define D_AMUX                   (* (reg8 *) D__AMUX) 
/* Bidirectional Enable */                                                        
#define D_BIE                    (* (reg8 *) D__BIE)
/* Bit-mask for Aliased Register Access */
#define D_BIT_MASK               (* (reg8 *) D__BIT_MASK)
/* Bypass Enable */
#define D_BYP                    (* (reg8 *) D__BYP)
/* Port wide control signals */                                                   
#define D_CTL                    (* (reg8 *) D__CTL)
/* Drive Modes */
#define D_DM0                    (* (reg8 *) D__DM0) 
#define D_DM1                    (* (reg8 *) D__DM1)
#define D_DM2                    (* (reg8 *) D__DM2) 
/* Input Buffer Disable Override */
#define D_INP_DIS                (* (reg8 *) D__INP_DIS)
/* LCD Common or Segment Drive */
#define D_LCD_COM_SEG            (* (reg8 *) D__LCD_COM_SEG)
/* Enable Segment LCD */
#define D_LCD_EN                 (* (reg8 *) D__LCD_EN)
/* Slew Rate Control */
#define D_SLW                    (* (reg8 *) D__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define D_PRTDSI__CAPS_SEL       (* (reg8 *) D__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define D_PRTDSI__DBL_SYNC_IN    (* (reg8 *) D__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define D_PRTDSI__OE_SEL0        (* (reg8 *) D__PRTDSI__OE_SEL0) 
#define D_PRTDSI__OE_SEL1        (* (reg8 *) D__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define D_PRTDSI__OUT_SEL0       (* (reg8 *) D__PRTDSI__OUT_SEL0) 
#define D_PRTDSI__OUT_SEL1       (* (reg8 *) D__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define D_PRTDSI__SYNC_OUT       (* (reg8 *) D__PRTDSI__SYNC_OUT) 


#if defined(D__INTSTAT)  /* Interrupt Registers */

    #define D_INTSTAT                (* (reg8 *) D__INTSTAT)
    #define D_SNAP                   (* (reg8 *) D__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_D_H */


/* [] END OF FILE */
