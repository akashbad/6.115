/*******************************************************************************
* File Name: LCD_Seg.h
* Version 3.30
*
* Description:
*  This header file contains definitions associated with the Segment LCD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SEGLCD_LCD_Seg_H)
#define CY_SEGLCD_LCD_Seg_H

#include "cytypes.h"
#include "cydevice_trm.h"
#include "cyfitter.h"
#include "CyLib.h"
#include <LCD_Seg_Int_Clock.h>


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define LCD_Seg_COMM_NUM            (1u)

#define LCD_Seg_BIT_MASK            (0x0007u)
#define LCD_Seg_BYTE_MASK           (0x00F0u)
#define LCD_Seg_ROW_MASK            (0x0F00u)

#define LCD_Seg_BYTE_SHIFT          (0x04u)
#define LCD_Seg_ROW_SHIFT           (0x08u)

#define LCD_Seg__TYPE_A 0
#define LCD_Seg__TYPE_B 1


#define LCD_Seg_WAVEFORM_TYPE       (0u)

/* Print error if cy_boot version is below 3.0 */
#ifndef CY_PSOC5LP
    #error Component SegLCD_v3_30 requires cy_boot v3.0 or later
#endif /* CY_PSOC5LP */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} LCD_Seg_BACKUP_STRUCT;

/* DMA_PROTO_GROUP_NAME=SegLcdPort */
struct LCD_Seg_DMA_TD_PROTO_ENTRY
{
	uint8 offset;	/* offset of the first register in this TD */
	uint8 length;	/* length of the register block in this TD */
};

/***************************************
*        Function Prototypes
***************************************/

void    LCD_Seg_Init(void) ;
uint8   LCD_Seg_Enable(void) ;
uint8   LCD_Seg_Start(void) ;
void    LCD_Seg_Stop(void) ;
void    LCD_Seg_EnableInt(void) ;
void    LCD_Seg_DisableInt(void) ;
uint8   LCD_Seg_SetBias(uint8 biasLevel) ;
uint8   LCD_Seg_WriteInvertState(uint8 invertState) ;
uint8   LCD_Seg_ReadInvertState(void) ;
void    LCD_Seg_ClearDisplay(void) ;
uint8   LCD_Seg_WritePixel(uint16 pixelNumber, uint8 pixelState)
                                                                    ;
uint8   LCD_Seg_ReadPixel(uint16 pixelNumber);
void    LCD_Seg_Sleep(void) ;
uint8   LCD_Seg_Wakeup(void) ;
void    LCD_Seg_SaveConfig(void) ;
void    LCD_Seg_RestoreConfig(void) ;

#define LCD_Seg_7SEG
void    LCD_Seg_Write7SegDigit_0(uint8 digit, uint8 position) ;
void    LCD_Seg_Write7SegNumber_0(uint16 value, uint8 position, uint8 mode) ;
void    LCD_Seg_WriteBargraph_1(uint16 location, int8 mode) ;
CY_ISR_PROTO(LCD_Seg_ISR);
CY_ISR_PROTO(LCD_Seg_WAKEUP_ISR);

#define LCD_Seg_WRITE_PIXEL(pixelNumber,pixelState) (void) LCD_Seg_WritePixel(pixelNumber,pixelState)
#define LCD_Seg_READ_PIXEL(pixelNumber)             LCD_Seg_ReadPixel(pixelNumber)

/* Calculates pixel location in the frame buffer. */
#define LCD_Seg_FIND_PIXEL(port, pin, row)          ((uint16)(((((uint16)(row)) << LCD_Seg_ROW_SHIFT) + \
                                                             (((uint16)(port)) << LCD_Seg_BYTE_SHIFT)) + ((uint16)(pin))))

/* Internal macros that extract pixel information from a pixel number */
#define LCD_Seg_EXTRACT_ROW(pixel)                  ((uint8)(((pixel) & LCD_Seg_ROW_MASK) >> \
                                                                            LCD_Seg_ROW_SHIFT))
#define LCD_Seg_EXTRACT_PORT(pixel)                 ((uint8)(((pixel) & LCD_Seg_BYTE_MASK) >> \
                                                                            LCD_Seg_BYTE_SHIFT))
#define LCD_Seg_EXTRACT_PIN(pixel)                  ((uint8)((pixel) & LCD_Seg_BIT_MASK))


/***************************************
*           Global Variables
***************************************/

extern uint8 LCD_Seg_initVar;


/***************************************
*           API Constants
***************************************/
#if(CY_PSOC3)
    #define LCD_Seg_DMA_ADDRESS_MASK          (0x0000FFFFul)
#endif /* (CY_PSOC3) */

#define LCD_Seg_LOW_POWER                 (0x01u)

/* Frame buffer row length */
#define LCD_Seg_ROW_LENGTH                (0x10u)
#define LCD_Seg_BUFFER_LENGTH             (LCD_Seg_COMM_NUM * LCD_Seg_ROW_LENGTH)

#if(LCD_Seg_WAVEFORM_TYPE == LCD_Seg__TYPE_A)
    #define LCD_Seg_CONTROL_WRITE_COUNT   (0x02u)
#else
    #define LCD_Seg_CONTROL_WRITE_COUNT   (2u * LCD_Seg_COMM_NUM)
#endif /* (LCD_Seg_WAVEFORM_TYPE == LCD_Seg__TYPE_A) */

#define LCD_Seg_INVERT_BIT_MASK           (0x04u)
#define LCD_Seg_INVERT_SHIFT              (0x02u)

#define LCD_Seg_LCD_STATE_DISABLED        (0x00u)
#define LCD_Seg_LCD_STATE_ENABLED         (0x01u)

#define LCD_Seg_NORMAL_STATE              (0x00u)
#define LCD_Seg_INVERTED_STATE            (0x01u)
#define LCD_Seg_STATE_MASK                (0x01u)

/* Number of pixels for different kind of LCDs */
#define LCD_Seg_7SEG_PIX_NUM              (0x07u)
#define LCD_Seg_14SEG_PIX_NUM             (0x0Eu)
#define LCD_Seg_16SEG_PIX_NUM             (0x10u)
#define LCD_Seg_DM_CHAR_HEIGHT            (0x08u)
#define LCD_Seg_DM_CHAR_WIDTH             (0x05u)

/* API parameter pixel state constants */
#define LCD_Seg_PIXEL_STATE_OFF           (0x00u)
#define LCD_Seg_PIXEL_STATE_ON            (0x01u)
#define LCD_Seg_PIXEL_STATE_INVERT        (0x02u)
#define LCD_Seg_PIXEL_UNKNOWN_STATE       (0xFFu)

/* 0 - No leadig zeros, 1 - leadig zeros */
#define LCD_Seg_MODE_0                    (0x00u)
#define LCD_Seg_MODE_1                    (0x01u)

#define LCD_Seg_MAX_BUFF_ROWS             (0x10u)
#define LCD_Seg_ROW_BYTE_LEN              (0x10u)

#define LCD_Seg_ISR_NUMBER                ((uint8) LCD_Seg_TD_DoneInt__INTC_NUMBER)
#define LCD_Seg_ISR_PRIORITY              ((uint8) LCD_Seg_TD_DoneInt__INTC_PRIOR_NUM)

#if(CY_PSOC5LP)
    #define LCD_Seg_WAKEUP_ISR_NUMBER         ((uint8) LCD_Seg_Wakeup__INTC_NUMBER)
    #define LCD_Seg_WAKEUP_ISR_PRIORITY       ((uint8) LCD_Seg_Wakeup__INTC_PRIOR_NUM)
#endif /* CY_PSOC5LP */

#define LCD_Seg_DIGIT_NUM_0            (1u)
#define LCD_Seg_DIGIT_NUM_1            (1u)

#define LCD_Seg_COM0_PORT            LCD_Seg_Com__LCD_COM_PORT__0
#define LCD_Seg_COM0_PIN            LCD_Seg_Com__LCD_COM_PIN__0

#define LCD_Seg_Com0            LCD_Seg_FIND_PIXEL(LCD_Seg_COM0_PORT,  LCD_Seg_COM0_PIN,  0)

#define LCD_Seg_SEG0_PORT            LCD_Seg_Seg__LCD_SEG_PORT__0
#define LCD_Seg_SEG0_PIN            LCD_Seg_Seg__LCD_SEG_PIN__0
#define LCD_Seg_SEG1_PORT            LCD_Seg_Seg__LCD_SEG_PORT__1
#define LCD_Seg_SEG1_PIN            LCD_Seg_Seg__LCD_SEG_PIN__1
#define LCD_Seg_SEG2_PORT            LCD_Seg_Seg__LCD_SEG_PORT__2
#define LCD_Seg_SEG2_PIN            LCD_Seg_Seg__LCD_SEG_PIN__2
#define LCD_Seg_SEG3_PORT            LCD_Seg_Seg__LCD_SEG_PORT__3
#define LCD_Seg_SEG3_PIN            LCD_Seg_Seg__LCD_SEG_PIN__3
#define LCD_Seg_SEG4_PORT            LCD_Seg_Seg__LCD_SEG_PORT__4
#define LCD_Seg_SEG4_PIN            LCD_Seg_Seg__LCD_SEG_PIN__4
#define LCD_Seg_SEG5_PORT            LCD_Seg_Seg__LCD_SEG_PORT__5
#define LCD_Seg_SEG5_PIN            LCD_Seg_Seg__LCD_SEG_PIN__5
#define LCD_Seg_SEG6_PORT            LCD_Seg_Seg__LCD_SEG_PORT__6
#define LCD_Seg_SEG6_PIN            LCD_Seg_Seg__LCD_SEG_PIN__6
#define LCD_Seg_SEG7_PORT            LCD_Seg_Seg__LCD_SEG_PORT__7
#define LCD_Seg_SEG7_PIN            LCD_Seg_Seg__LCD_SEG_PIN__7


#define LCD_Seg_PIX0            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG0_PORT,  LCD_Seg_SEG0_PIN,  0)
#define LCD_Seg_PIX1            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG1_PORT,  LCD_Seg_SEG1_PIN,  0)
#define LCD_Seg_PIX2            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG2_PORT,  LCD_Seg_SEG2_PIN,  0)
#define LCD_Seg_PIX3            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG3_PORT,  LCD_Seg_SEG3_PIN,  0)
#define LCD_Seg_PIX4            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG4_PORT,  LCD_Seg_SEG4_PIN,  0)
#define LCD_Seg_PIX5            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG5_PORT,  LCD_Seg_SEG5_PIN,  0)
#define LCD_Seg_PIX6            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG6_PORT,  LCD_Seg_SEG6_PIN,  0)
#define LCD_Seg_PIX7            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG7_PORT,  LCD_Seg_SEG7_PIN,  0)
#define LCD_Seg_PIX8            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG2_PORT,  LCD_Seg_SEG2_PIN,  0)
#define LCD_Seg_PIX9            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG2_PORT,  LCD_Seg_SEG2_PIN,  1)
#define LCD_Seg_PIX10            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG2_PORT,  LCD_Seg_SEG2_PIN,  2)
#define LCD_Seg_PIX11            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG2_PORT,  LCD_Seg_SEG2_PIN,  3)
#define LCD_Seg_PIX12            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG3_PORT,  LCD_Seg_SEG3_PIN,  0)
#define LCD_Seg_PIX13            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG3_PORT,  LCD_Seg_SEG3_PIN,  1)
#define LCD_Seg_PIX14            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG3_PORT,  LCD_Seg_SEG3_PIN,  2)
#define LCD_Seg_PIX15            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG3_PORT,  LCD_Seg_SEG3_PIN,  3)
#define LCD_Seg_PIX16            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG4_PORT,  LCD_Seg_SEG4_PIN,  0)
#define LCD_Seg_PIX17            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG4_PORT,  LCD_Seg_SEG4_PIN,  1)
#define LCD_Seg_PIX18            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG4_PORT,  LCD_Seg_SEG4_PIN,  2)
#define LCD_Seg_PIX19            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG4_PORT,  LCD_Seg_SEG4_PIN,  3)
#define LCD_Seg_PIX20            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG5_PORT,  LCD_Seg_SEG5_PIN,  0)
#define LCD_Seg_PIX21            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG5_PORT,  LCD_Seg_SEG5_PIN,  1)
#define LCD_Seg_PIX22            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG5_PORT,  LCD_Seg_SEG5_PIN,  2)
#define LCD_Seg_PIX23            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG5_PORT,  LCD_Seg_SEG5_PIN,  3)
#define LCD_Seg_PIX24            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG6_PORT,  LCD_Seg_SEG6_PIN,  0)
#define LCD_Seg_PIX25            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG6_PORT,  LCD_Seg_SEG6_PIN,  1)
#define LCD_Seg_PIX26            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG6_PORT,  LCD_Seg_SEG6_PIN,  2)
#define LCD_Seg_PIX27            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG6_PORT,  LCD_Seg_SEG6_PIN,  3)
#define LCD_Seg_PIX28            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG7_PORT,  LCD_Seg_SEG7_PIN,  0)
#define LCD_Seg_PIX29            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG7_PORT,  LCD_Seg_SEG7_PIN,  1)
#define LCD_Seg_PIX30            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG7_PORT,  LCD_Seg_SEG7_PIN,  2)
#define LCD_Seg_PIX31            LCD_Seg_FIND_PIXEL(LCD_Seg_SEG7_PORT,  LCD_Seg_SEG7_PIN,  3)

#define LCD_Seg_NOT_CON            (0xFFFFu)
#define LCD_Seg_SegLcdPort_DMA_TD_PROTO_COUNT 1

#define LCD_Seg_LCD_TD_SIZE               ((uint8) LCD_Seg_SegLcdPort_DMA_TD_PROTO_COUNT)

#define LCD_Seg_COM_TD_COUNT              ((uint8) \
                                                   ((LCD_Seg_COMM_NUM * LCD_Seg_LCD_TD_SIZE) - 1u))

#define LCD_Seg_MODE_MASK                 (0x06u)

/* Defines index of "blank" didgit in the look-up table for 7 segment helper */
#define LCD_Seg_7SEG_BLANK_DIG            (0x10u)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define LCD_Seg__NO_SLEEP 0
#define LCD_Seg__LOW_POWER_32XTAL 2
#define LCD_Seg__LOW_POWER_ILO 1


/***************************************
*    Initial Parameter Constants
***************************************/

#define LCD_Seg_SEG_NUM               (8u)
#define LCD_Seg_BIAS_TYPE             (0u)
#define LCD_Seg_BIAS_VOLTAGE          (53u)
#define LCD_Seg_POWER_MODE            (0u)
#define LCD_Seg_FRAME_RATE            (10u)
#define LCD_Seg_HI_DRIVE_TIME         (1u)
#define LCD_Seg_LOW_DRIVE_TIME        (253u)
#define LCD_Seg_HIDRIVE_STRENGTH      (2u)
#define LCD_Seg_LOWDRIVE_STRENGTH     (0u)

#if(LCD_Seg_POWER_MODE == LCD_Seg__NO_SLEEP)
    #define LCD_Seg_DRIVE_TIME        ((LCD_Seg_LOW_DRIVE_TIME + LCD_Seg_HI_DRIVE_TIME) - 1u)
#else
    #define LCD_Seg_DRIVE_TIME        (LCD_Seg_HI_DRIVE_TIME)
#endif /* LCD_Seg_POWER_MODE == LCD_Seg__NO_SLEEP */

#if(LCD_Seg_POWER_MODE == LCD_Seg__NO_SLEEP)

    /* Set PWM period for 255 in NoSleep mode */
    #define LCD_Seg_PWM_PERIOD_VAL        (0xFFu)
    /* D0 = 255 - HiDrive time */
    #define LCD_Seg_PWM_DRIVE_VAL        ((LCD_Seg_PWM_PERIOD_VAL) - (LCD_Seg_HI_DRIVE_TIME))
    /* D1 = 255 - Drive time */
    #define LCD_Seg_PWM_LOWDRIVE_VAL     ((LCD_Seg_PWM_PERIOD_VAL) - (LCD_Seg_DRIVE_TIME))

#else

    /* PWM period will be equal to 0 */
    #define LCD_Seg_PWM_PERIOD_VAL        (0x00u)
    /* D0 is equal to HiDrive time, as it used as period reg for Low Power mode */
    #define LCD_Seg_PWM_DRIVE_VAL         (LCD_Seg_HI_DRIVE_TIME - 1u)
    /* Make sure D1 is 0 */
    #define LCD_Seg_PWM_LOWDRIVE_VAL      (0x00u)

#endif /* LCD_Seg_POWER_MODE == LCD_Seg__NO_SLEEP */


/***************************************
*             Registers
***************************************/

/* LCD's fixed block registers */
#define LCD_Seg_LCDDAC_CONTROL_REG       (* (reg8*) LCD_Seg_LCD__CR0)
#define LCD_Seg_LCDDAC_CONTROL_PTR       ((reg8*) LCD_Seg_LCD__CR0)
#define LCD_Seg_CONTRAST_CONTROL_REG     (* (reg8*) LCD_Seg_LCD__CR1)
#define LCD_Seg_CONTRAST_CONTROL_PTR     ((reg8*) LCD_Seg_LCD__CR1)
#define LCD_Seg_DRIVER_CONTROL_REG       (* (reg8*)LCD_Seg_LCD__CR)
#define LCD_Seg_DRIVER_CONTROL_PTR       ((reg8*)LCD_Seg_LCD__CR)
#define LCD_Seg_TIMER_CONTROL_REG        (* (reg8*) LCD_Seg_LCD__CFG)
#define LCD_Seg_TIMER_CONTROL_PTR        ((reg8*) LCD_Seg_LCD__CFG)
#define LCD_Seg_ALIASED_AREA_PTR         ((reg32) CYREG_PRT0_DR_ALIAS)
#define LCD_Seg_PWR_MGR_REG              (* (reg8 *) LCD_Seg_LCD__PM_ACT_CFG)
#define LCD_Seg_PWR_MGR_PTR              ((reg8 *) LCD_Seg_LCD__PM_ACT_CFG)
#define LCD_Seg_PWR_MGR_STBY_REG         (* (reg8 *) LCD_Seg_LCD__PM_STBY_CFG)
#define LCD_Seg_PWR_MGR_STBY_PTR         ((reg8 *) LCD_Seg_LCD__PM_STBY_CFG)

#if(LCD_Seg_POWER_MODE == LCD_Seg__LOW_POWER_32XTAL)
    #define LCD_Seg_TM_WL_GFG_REG         (*(reg8 *) CYREG_PM_TW_CFG2)
    #define LCD_Seg_TM_WL_GFG_PTR         ((reg8 *) CYREG_PM_TW_CFG2)
#endif /* LCD_Seg_POWER_MODE == LCD_Seg__LOW_POWER_32XTAL */

#define LCD_Seg_LCDDAC_SWITCH_REG0_REG   (* (reg8*)LCD_Seg_LCD__SW0)
#define LCD_Seg_LCDDAC_SWITCH_REG1_REG   (* (reg8*)LCD_Seg_LCD__SW1)
#define LCD_Seg_LCDDAC_SWITCH_REG2_REG   (* (reg8*)LCD_Seg_LCD__SW2)
#define LCD_Seg_LCDDAC_SWITCH_REG3_REG   (* (reg8*)LCD_Seg_LCD__SW3)
#define LCD_Seg_LCDDAC_SWITCH_REG4_REG   (* (reg8*)LCD_Seg_LCD__SW4)

#define LCD_Seg_LCDDAC_SWITCH_REG0_PTR   ((reg8*)LCD_Seg_LCD__SW0)
#define LCD_Seg_LCDDAC_SWITCH_REG1_PTR   ((reg8*)LCD_Seg_LCD__SW1)
#define LCD_Seg_LCDDAC_SWITCH_REG2_PTR   ((reg8*)LCD_Seg_LCD__SW2)
#define LCD_Seg_LCDDAC_SWITCH_REG3_PTR   ((reg8*)LCD_Seg_LCD__SW3)
#define LCD_Seg_LCDDAC_SWITCH_REG4_PTR   ((reg8*)LCD_Seg_LCD__SW4)

/* UDB registers */
#if(LCD_Seg_POWER_MODE == LCD_Seg__NO_SLEEP)
    #define LCD_Seg_PWM_PERIOD_REG         (* (reg8 *) LCD_Seg_bLCDDSD_NoSleep_bSegLCDdp_u0__A1_REG)
    #define LCD_Seg_PWM_PERIOD_PTR         ((reg8 *) LCD_Seg_bLCDDSD_NoSleep_bSegLCDdp_u0__A1_REG)
    #define LCD_Seg_PWM_DRIVE_REG          (* (reg8 *) LCD_Seg_bLCDDSD_NoSleep_bSegLCDdp_u0__D0_REG)
    #define LCD_Seg_PWM_DRIVE_PTR          ((reg8 *) LCD_Seg_bLCDDSD_NoSleep_bSegLCDdp_u0__D0_REG)
    #define LCD_Seg_PWM_LODRIVE_REG        (* (reg8 *) LCD_Seg_bLCDDSD_NoSleep_bSegLCDdp_u0__D1_REG)
    #define LCD_Seg_PWM_LODRIVE_PTR        ((reg8 *) LCD_Seg_bLCDDSD_NoSleep_bSegLCDdp_u0__D1_REG)
#else
    #define LCD_Seg_PWM_PERIOD_REG         (* (reg8 *) LCD_Seg_bLCDDSD_LowPower_bSegLCDdp_u0__A1_REG)
    #define LCD_Seg_PWM_PERIOD_PTR         ((reg8 *) LCD_Seg_bLCDDSD_LowPower_bSegLCDdp_u0__A1_REG)
    #define LCD_Seg_PWM_DRIVE_REG          (* (reg8 *) LCD_Seg_bLCDDSD_LowPower_bSegLCDdp_u0__D0_REG)
    #define LCD_Seg_PWM_DRIVE_PTR          ((reg8 *) LCD_Seg_bLCDDSD_LowPower_bSegLCDdp_u0__D0_REG)
    #define LCD_Seg_PWM_LODRIVE_REG        (* (reg8 *) LCD_Seg_bLCDDSD_LowPower_bSegLCDdp_u0__D1_REG)
    #define LCD_Seg_PWM_LODRIVE_PTR        ((reg8 *) LCD_Seg_bLCDDSD_LowPower_bSegLCDdp_u0__D1_REG)
#endif /* LCD_Seg_POWER_MODE == LCD_Seg__NO_SLEEP */

#define LCD_Seg_CONTROL_REG                (* (reg8 *) LCD_Seg_bLCDDSD_CtrlReg__CONTROL_REG)
#define LCD_Seg_CONTROL_PTR                ((reg8 *) LCD_Seg_bLCDDSD_CtrlReg__CONTROL_REG)

/* This is required for DmaInitialize() fou usage as a
* base destination address of conrol register. 
*/
#define LCD_Seg_CONTROL_REG_BASE           (CYDEV_PERIPH_BASE)

/***************************************
*       Register Constants
***************************************/

/* PM Control Register bits */
#define LCD_Seg_LCD_EN                    (LCD_Seg_LCD__PM_ACT_MSK)
#define LCD_Seg_LCD_STBY_EN               (LCD_Seg_LCD__PM_STBY_MSK)

/* LCD DAC Control Register Bits */
#define LCD_Seg_LCDDAC_UDB_LP_EN          (0x80u)
#define LCD_Seg_LCDDAC_CONT_DRIVE         (0x08u)
#define LCD_Seg_BIAS_TYPE_MASK            (0x03u)

#define LCD_Seg_LCDDAC_VOLTAGE_SEL        (0x01u)
#define LCD_Seg_LCDDAC_CONT_DRIVE         (0x08u)
#define LCD_Seg_LCDDAC_CONT_DRIVE_MASK    (~0x08u)

/* LCD Driver Control Register Bits */
#define LCD_Seg_LCDDRV_DISPLAY_BLNK       (0x01u)
#define LCD_Seg_LCDDRV_MODE0_MASK         (0x02u)
#define LCD_Seg_LCDDRV_MODE0_SHIFT        (0x01u)
#define LCD_Seg_LCDDRV_INVERT             (0x04u)
#define LCD_Seg_LCDDRV_PTS                (0x08u)
#define LCD_Seg_LCDDRV_BYPASS_EN          (0x10u)

#if(LCD_Seg_POWER_MODE == LCD_Seg__LOW_POWER_32XTAL)
    #define LCD_Seg_ONE_PPS_EN            (0x10u)
#endif /* LCD_Seg_POWER_MODE == LCD_Seg__LOW_POWER_32XTAL */

#if(LCD_Seg_POWER_MODE != LCD_Seg__NO_SLEEP)

    /* LCD Timer Control Register Bits */
    #define LCD_Seg_TIMER_EN                  (0x01u)
    #define LCD_Seg_TIMER_ILO_SEL             (0x00u)
    #define LCD_Seg_TIMER_32XTAL_SEL          (0x02u)
    #define LCD_Seg_TIMER_CLK_SEL_MASK        (0x02u)
    #define LCD_Seg_TIMER_PERIOD_MASK         (0xFCu)
    #define LCD_Seg_TIMER_PERIOD_SHIFT        (0x02u)

    #define LCD_Seg_TIMER_PERIOD              (15u)

#endif /* LCD_Seg_POWER_MODE != LCD_Seg__NO_SLEEP */

/* UDB Control Register bits */
#define LCD_Seg_CNTL_CLK_EN               (0x01u)
#define LCD_Seg_CNTL_CLK_EN_MASK          (~LCD_Seg_CNTL_CLK_EN)
#define LCD_Seg_CNTL_MODE_SHIFT           (0x01u)
#define LCD_Seg_CNTL_MODE_MASK            (~0x06u)
#define LCD_Seg_CNTL_FRAME_DONE           (0x08u)
#define LCD_Seg_CNTL_FRAME_DONE_MASK      (~LCD_Seg_CNTL_FRAME_DONE)


#endif  /* CY_SEGLCD_LCD_Seg_H */

/* [] END OF FILE */
