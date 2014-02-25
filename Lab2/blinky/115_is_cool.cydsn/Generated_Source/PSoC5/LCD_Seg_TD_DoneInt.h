/*******************************************************************************
* File Name: LCD_Seg_TD_DoneInt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_LCD_Seg_TD_DoneInt_H)
#define CY_ISR_LCD_Seg_TD_DoneInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LCD_Seg_TD_DoneInt_Start(void);
void LCD_Seg_TD_DoneInt_StartEx(cyisraddress address);
void LCD_Seg_TD_DoneInt_Stop(void);

CY_ISR_PROTO(LCD_Seg_TD_DoneInt_Interrupt);

void LCD_Seg_TD_DoneInt_SetVector(cyisraddress address);
cyisraddress LCD_Seg_TD_DoneInt_GetVector(void);

void LCD_Seg_TD_DoneInt_SetPriority(uint8 priority);
uint8 LCD_Seg_TD_DoneInt_GetPriority(void);

void LCD_Seg_TD_DoneInt_Enable(void);
uint8 LCD_Seg_TD_DoneInt_GetState(void);
void LCD_Seg_TD_DoneInt_Disable(void);

void LCD_Seg_TD_DoneInt_SetPending(void);
void LCD_Seg_TD_DoneInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LCD_Seg_TD_DoneInt ISR. */
#define LCD_Seg_TD_DoneInt_INTC_VECTOR            ((reg32 *) LCD_Seg_TD_DoneInt__INTC_VECT)

/* Address of the LCD_Seg_TD_DoneInt ISR priority. */
#define LCD_Seg_TD_DoneInt_INTC_PRIOR             ((reg8 *) LCD_Seg_TD_DoneInt__INTC_PRIOR_REG)

/* Priority of the LCD_Seg_TD_DoneInt interrupt. */
#define LCD_Seg_TD_DoneInt_INTC_PRIOR_NUMBER      LCD_Seg_TD_DoneInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LCD_Seg_TD_DoneInt interrupt. */
#define LCD_Seg_TD_DoneInt_INTC_SET_EN            ((reg32 *) LCD_Seg_TD_DoneInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LCD_Seg_TD_DoneInt interrupt. */
#define LCD_Seg_TD_DoneInt_INTC_CLR_EN            ((reg32 *) LCD_Seg_TD_DoneInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LCD_Seg_TD_DoneInt interrupt state to pending. */
#define LCD_Seg_TD_DoneInt_INTC_SET_PD            ((reg32 *) LCD_Seg_TD_DoneInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LCD_Seg_TD_DoneInt interrupt. */
#define LCD_Seg_TD_DoneInt_INTC_CLR_PD            ((reg32 *) LCD_Seg_TD_DoneInt__INTC_CLR_PD_REG)


#endif /* CY_ISR_LCD_Seg_TD_DoneInt_H */


/* [] END OF FILE */
