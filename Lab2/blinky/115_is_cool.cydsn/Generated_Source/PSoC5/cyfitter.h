#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* A */
#define A__0__MASK 0x08u
#define A__0__PC CYREG_PRT5_PC3
#define A__0__PORT 5u
#define A__0__SHIFT 3
#define A__AG CYREG_PRT5_AG
#define A__AMUX CYREG_PRT5_AMUX
#define A__BIE CYREG_PRT5_BIE
#define A__BIT_MASK CYREG_PRT5_BIT_MASK
#define A__BYP CYREG_PRT5_BYP
#define A__CTL CYREG_PRT5_CTL
#define A__DM0 CYREG_PRT5_DM0
#define A__DM1 CYREG_PRT5_DM1
#define A__DM2 CYREG_PRT5_DM2
#define A__DR CYREG_PRT5_DR
#define A__INP_DIS CYREG_PRT5_INP_DIS
#define A__LCD_COM_SEG CYREG_PRT5_LCD_COM_SEG
#define A__LCD_EN CYREG_PRT5_LCD_EN
#define A__MASK 0x08u
#define A__PORT 5u
#define A__PRT CYREG_PRT5_PRT
#define A__PRTDSI__CAPS_SEL CYREG_PRT5_CAPS_SEL
#define A__PRTDSI__DBL_SYNC_IN CYREG_PRT5_DBL_SYNC_IN
#define A__PRTDSI__OE_SEL0 CYREG_PRT5_OE_SEL0
#define A__PRTDSI__OE_SEL1 CYREG_PRT5_OE_SEL1
#define A__PRTDSI__OUT_SEL0 CYREG_PRT5_OUT_SEL0
#define A__PRTDSI__OUT_SEL1 CYREG_PRT5_OUT_SEL1
#define A__PRTDSI__SYNC_OUT CYREG_PRT5_SYNC_OUT
#define A__PS CYREG_PRT5_PS
#define A__SHIFT 3
#define A__SLW CYREG_PRT5_SLW

/* B */
#define B__0__MASK 0x04u
#define B__0__PC CYREG_PRT5_PC2
#define B__0__PORT 5u
#define B__0__SHIFT 2
#define B__AG CYREG_PRT5_AG
#define B__AMUX CYREG_PRT5_AMUX
#define B__BIE CYREG_PRT5_BIE
#define B__BIT_MASK CYREG_PRT5_BIT_MASK
#define B__BYP CYREG_PRT5_BYP
#define B__CTL CYREG_PRT5_CTL
#define B__DM0 CYREG_PRT5_DM0
#define B__DM1 CYREG_PRT5_DM1
#define B__DM2 CYREG_PRT5_DM2
#define B__DR CYREG_PRT5_DR
#define B__INP_DIS CYREG_PRT5_INP_DIS
#define B__LCD_COM_SEG CYREG_PRT5_LCD_COM_SEG
#define B__LCD_EN CYREG_PRT5_LCD_EN
#define B__MASK 0x04u
#define B__PORT 5u
#define B__PRT CYREG_PRT5_PRT
#define B__PRTDSI__CAPS_SEL CYREG_PRT5_CAPS_SEL
#define B__PRTDSI__DBL_SYNC_IN CYREG_PRT5_DBL_SYNC_IN
#define B__PRTDSI__OE_SEL0 CYREG_PRT5_OE_SEL0
#define B__PRTDSI__OE_SEL1 CYREG_PRT5_OE_SEL1
#define B__PRTDSI__OUT_SEL0 CYREG_PRT5_OUT_SEL0
#define B__PRTDSI__OUT_SEL1 CYREG_PRT5_OUT_SEL1
#define B__PRTDSI__SYNC_OUT CYREG_PRT5_SYNC_OUT
#define B__PS CYREG_PRT5_PS
#define B__SHIFT 2
#define B__SLW CYREG_PRT5_SLW

/* C */
#define C__0__MASK 0x02u
#define C__0__PC CYREG_PRT5_PC1
#define C__0__PORT 5u
#define C__0__SHIFT 1
#define C__AG CYREG_PRT5_AG
#define C__AMUX CYREG_PRT5_AMUX
#define C__BIE CYREG_PRT5_BIE
#define C__BIT_MASK CYREG_PRT5_BIT_MASK
#define C__BYP CYREG_PRT5_BYP
#define C__CTL CYREG_PRT5_CTL
#define C__DM0 CYREG_PRT5_DM0
#define C__DM1 CYREG_PRT5_DM1
#define C__DM2 CYREG_PRT5_DM2
#define C__DR CYREG_PRT5_DR
#define C__INP_DIS CYREG_PRT5_INP_DIS
#define C__LCD_COM_SEG CYREG_PRT5_LCD_COM_SEG
#define C__LCD_EN CYREG_PRT5_LCD_EN
#define C__MASK 0x02u
#define C__PORT 5u
#define C__PRT CYREG_PRT5_PRT
#define C__PRTDSI__CAPS_SEL CYREG_PRT5_CAPS_SEL
#define C__PRTDSI__DBL_SYNC_IN CYREG_PRT5_DBL_SYNC_IN
#define C__PRTDSI__OE_SEL0 CYREG_PRT5_OE_SEL0
#define C__PRTDSI__OE_SEL1 CYREG_PRT5_OE_SEL1
#define C__PRTDSI__OUT_SEL0 CYREG_PRT5_OUT_SEL0
#define C__PRTDSI__OUT_SEL1 CYREG_PRT5_OUT_SEL1
#define C__PRTDSI__SYNC_OUT CYREG_PRT5_SYNC_OUT
#define C__PS CYREG_PRT5_PS
#define C__SHIFT 1
#define C__SLW CYREG_PRT5_SLW

/* D */
#define D__0__MASK 0x04u
#define D__0__PC CYREG_PRT12_PC2
#define D__0__PORT 12u
#define D__0__SHIFT 2
#define D__AG CYREG_PRT12_AG
#define D__BIE CYREG_PRT12_BIE
#define D__BIT_MASK CYREG_PRT12_BIT_MASK
#define D__BYP CYREG_PRT12_BYP
#define D__DM0 CYREG_PRT12_DM0
#define D__DM1 CYREG_PRT12_DM1
#define D__DM2 CYREG_PRT12_DM2
#define D__DR CYREG_PRT12_DR
#define D__INP_DIS CYREG_PRT12_INP_DIS
#define D__MASK 0x04u
#define D__PORT 12u
#define D__PRT CYREG_PRT12_PRT
#define D__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define D__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define D__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define D__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define D__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define D__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define D__PS CYREG_PRT12_PS
#define D__SHIFT 2
#define D__SIO_CFG CYREG_PRT12_SIO_CFG
#define D__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define D__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define D__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define D__SLW CYREG_PRT12_SLW

/* E */
#define E__0__MASK 0x02u
#define E__0__PC CYREG_PRT12_PC1
#define E__0__PORT 12u
#define E__0__SHIFT 1
#define E__AG CYREG_PRT12_AG
#define E__BIE CYREG_PRT12_BIE
#define E__BIT_MASK CYREG_PRT12_BIT_MASK
#define E__BYP CYREG_PRT12_BYP
#define E__DM0 CYREG_PRT12_DM0
#define E__DM1 CYREG_PRT12_DM1
#define E__DM2 CYREG_PRT12_DM2
#define E__DR CYREG_PRT12_DR
#define E__INP_DIS CYREG_PRT12_INP_DIS
#define E__MASK 0x02u
#define E__PORT 12u
#define E__PRT CYREG_PRT12_PRT
#define E__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define E__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define E__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define E__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define E__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define E__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define E__PS CYREG_PRT12_PS
#define E__SHIFT 1
#define E__SIO_CFG CYREG_PRT12_SIO_CFG
#define E__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define E__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define E__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define E__SLW CYREG_PRT12_SLW

/* F */
#define F__0__MASK 0x08u
#define F__0__PC CYREG_PRT12_PC3
#define F__0__PORT 12u
#define F__0__SHIFT 3
#define F__AG CYREG_PRT12_AG
#define F__BIE CYREG_PRT12_BIE
#define F__BIT_MASK CYREG_PRT12_BIT_MASK
#define F__BYP CYREG_PRT12_BYP
#define F__DM0 CYREG_PRT12_DM0
#define F__DM1 CYREG_PRT12_DM1
#define F__DM2 CYREG_PRT12_DM2
#define F__DR CYREG_PRT12_DR
#define F__INP_DIS CYREG_PRT12_INP_DIS
#define F__MASK 0x08u
#define F__PORT 12u
#define F__PRT CYREG_PRT12_PRT
#define F__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define F__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define F__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define F__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define F__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define F__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define F__PS CYREG_PRT12_PS
#define F__SHIFT 3
#define F__SIO_CFG CYREG_PRT12_SIO_CFG
#define F__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define F__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define F__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define F__SLW CYREG_PRT12_SLW

/* G */
#define G__0__MASK 0x01u
#define G__0__PC CYREG_PRT12_PC0
#define G__0__PORT 12u
#define G__0__SHIFT 0
#define G__AG CYREG_PRT12_AG
#define G__BIE CYREG_PRT12_BIE
#define G__BIT_MASK CYREG_PRT12_BIT_MASK
#define G__BYP CYREG_PRT12_BYP
#define G__DM0 CYREG_PRT12_DM0
#define G__DM1 CYREG_PRT12_DM1
#define G__DM2 CYREG_PRT12_DM2
#define G__DR CYREG_PRT12_DR
#define G__INP_DIS CYREG_PRT12_INP_DIS
#define G__MASK 0x01u
#define G__PORT 12u
#define G__PRT CYREG_PRT12_PRT
#define G__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define G__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define G__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define G__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define G__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define G__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define G__PS CYREG_PRT12_PS
#define G__SHIFT 0
#define G__SIO_CFG CYREG_PRT12_SIO_CFG
#define G__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define G__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define G__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define G__SLW CYREG_PRT12_SLW

/* P */
#define P__0__MASK 0x01u
#define P__0__PC CYREG_PRT5_PC0
#define P__0__PORT 5u
#define P__0__SHIFT 0
#define P__AG CYREG_PRT5_AG
#define P__AMUX CYREG_PRT5_AMUX
#define P__BIE CYREG_PRT5_BIE
#define P__BIT_MASK CYREG_PRT5_BIT_MASK
#define P__BYP CYREG_PRT5_BYP
#define P__CTL CYREG_PRT5_CTL
#define P__DM0 CYREG_PRT5_DM0
#define P__DM1 CYREG_PRT5_DM1
#define P__DM2 CYREG_PRT5_DM2
#define P__DR CYREG_PRT5_DR
#define P__INP_DIS CYREG_PRT5_INP_DIS
#define P__LCD_COM_SEG CYREG_PRT5_LCD_COM_SEG
#define P__LCD_EN CYREG_PRT5_LCD_EN
#define P__MASK 0x01u
#define P__PORT 5u
#define P__PRT CYREG_PRT5_PRT
#define P__PRTDSI__CAPS_SEL CYREG_PRT5_CAPS_SEL
#define P__PRTDSI__DBL_SYNC_IN CYREG_PRT5_DBL_SYNC_IN
#define P__PRTDSI__OE_SEL0 CYREG_PRT5_OE_SEL0
#define P__PRTDSI__OE_SEL1 CYREG_PRT5_OE_SEL1
#define P__PRTDSI__OUT_SEL0 CYREG_PRT5_OUT_SEL0
#define P__PRTDSI__OUT_SEL1 CYREG_PRT5_OUT_SEL1
#define P__PRTDSI__SYNC_OUT CYREG_PRT5_SYNC_OUT
#define P__PS CYREG_PRT5_PS
#define P__SHIFT 0
#define P__SLW CYREG_PRT5_SLW

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_MEMBER_5B 4u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_DIE_PSOC5LP 4u
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_DIE_PSOC5LP
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 3u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x2E123069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_5A 3u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5B
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5B_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REV_PSOC5LP_PRODUCTION
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DEBUG_ENABLE_MASK 0x20u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x1000
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000000u
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x4000
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 0
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5
#define CYDEV_VIO3_MV 5000
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
