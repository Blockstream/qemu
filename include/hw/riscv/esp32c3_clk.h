/*
 * ESP32-C3 CPU Clock and Reset
 *
 * Copyright (c) 2023 Espressif Systems (Shanghai) Co. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or
 * (at your option) any later version.
 */
#pragma once

#include "hw/hw.h"
#include "hw/sysbus.h"
#include "hw/registerfields.h"
#include "hw/misc/esp32c3_reg.h"

#define TYPE_ESP32C3_CLOCK "esp32c3.soc.clk"
#define ESP32C3_CLOCK(obj) OBJECT_CHECK(ESP32C3ClockState, (obj), TYPE_ESP32C3_CLOCK)


#define ESP32C3_SYSTEM_CPU_INTR_COUNT   4

/**
 * Value for SYSTEM_SOC_CLK_SEL
 */
#define ESP32C3_CLK_SEL_XTAL    0
#define ESP32C3_CLK_SEL_PLL     1
#define ESP32C3_CLK_SEL_RCFAST  2

/**
 * Values for SYSTEM_PLL_FREQ_SEL
 */
#define ESP32C3_FREQ_SEL_PLL_480    0
#define ESP32C3_FREQ_SEL_PLL_320    1

/**
 * Values for SYSTEM_CPUPERIOD_SEL
*/
#define ESP32C3_PERIOD_SEL_80       0
#define ESP32C3_PERIOD_SEL_160      1


typedef struct ESP32C3ClockState {
    SysBusDevice parent_obj;
    MemoryRegion iomem;

    /* Registers for clocks configuration and frequency dividers */
    uint32_t cpuperconf;
    uint32_t sysclk;


    /* IRQs for crosscore interrupts */
    qemu_irq irqs[ESP32C3_SYSTEM_CPU_INTR_COUNT];

    /* Bitmap that keeps the level of the IRQs */
    uint32_t levels;
} ESP32C3ClockState;


REG32(SYSTEM_CPU_PERI_CLK_EN, 0x000)
    FIELD(SYSTEM_CPU_PERI_CLK_EN, CLK_EN_DEDICATED_GPIO, 7, 1)
    FIELD(SYSTEM_CPU_PERI_CLK_EN, CLK_EN_ASSIST_DEBUG, 6, 1)

REG32(SYSTEM_CPU_PERI_RST_EN, 0x004)
    FIELD(SYSTEM_CPU_PERI_RST_EN, RST_EN_DEDICATED_GPIO, 7, 1)
    FIELD(SYSTEM_CPU_PERI_RST_EN, RST_EN_ASSIST_DEBUG, 6, 1)

REG32(SYSTEM_CPU_PER_CONF, 0x008)
    FIELD(SYSTEM_CPU_PER_CONF, CPU_WAITI_DELAY_NUM, 4, 4)
    FIELD(SYSTEM_CPU_PER_CONF, CPU_WAIT_MODE_FORCE_ON, 3, 1)
    FIELD(SYSTEM_CPU_PER_CONF, PLL_FREQ_SEL, 2, 1)
    FIELD(SYSTEM_CPU_PER_CONF, CPUPERIOD_SEL, 0, 2)

REG32(SYSTEM_MEM_PD_MASK, 0x00C)
    FIELD(SYSTEM_MEM_PD_MASK, LSLP_MEM_PD_MASK, 0, 1)

REG32(SYSTEM_PERIP_CLK_EN0, 0x010)
    FIELD(SYSTEM_PERIP_CLK_EN0, SPI4_CLK_EN, 31, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, ADC2_ARB_CLK_EN, 30, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, SYSTIMER_CLK_EN, 29, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, APB_SARADC_CLK_EN, 28, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, SPI3_DMA_CLK_EN, 27, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, PWM3_CLK_EN, 26, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, PWM2_CLK_EN, 25, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, UART_MEM_CLK_EN, 24, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, USB_DEVICE_CLK_EN, 23, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, SPI2_DMA_CLK_EN, 22, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, I2S1_CLK_EN, 21, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, PWM1_CLK_EN, 20, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, CAN_CLK_EN, 19, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, EXT1_CLK_EN, 18, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, PWM0_CLK_EN, 17, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, SPI3_CLK_EN, 16, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, TIMERGROUP1_CLK_EN, 15, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, EFUSE_CLK_EN, 14, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, TIMERGROUP_CLK_EN, 13, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, UHCI1_CLK_EN, 12, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, LEDC_CLK_EN, 11, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, PCNT_CLK_EN, 10, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, RMT_CLK_EN, 9, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, UHCI0_CLK_EN, 8, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, EXT0_CLK_EN, 7, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, SPI2_CLK_EN, 6, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, UART1_CLK_EN, 5, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, I2S0_CLK_EN, 4, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, WDG_CLK_EN, 3, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, UART_CLK_EN, 2, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, SPI01_CLK_EN, 1, 1)
    FIELD(SYSTEM_PERIP_CLK_EN0, TIMERS_CLK_EN, 0, 1)

REG32(SYSTEM_PERIP_CLK_EN1, 0x014)
    FIELD(SYSTEM_PERIP_CLK_EN1, TSENS_CLK_EN, 10, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, UART2_CLK_EN, 9, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, LCD_CAM_CLK_EN, 8, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, SDIO_HOST_CLK_EN, 7, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, DMA_CLK_EN, 6, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, CRYPTO_HMAC_CLK_EN, 5, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, CRYPTO_DS_CLK_EN, 4, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, CRYPTO_RSA_CLK_EN, 3, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, CRYPTO_SHA_CLK_EN, 2, 1)
    FIELD(SYSTEM_PERIP_CLK_EN1, CRYPTO_AES_CLK_EN, 1, 1)

REG32(SYSTEM_PERIP_RST_EN0, 0x018)
    FIELD(SYSTEM_PERIP_RST_EN0, SPI4_RST, 31, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, ADC2_ARB_RST, 30, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, SYSTIMER_RST, 29, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, APB_SARADC_RST, 28, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, SPI3_DMA_RST, 27, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, PWM3_RST, 26, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, PWM2_RST, 25, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, UART_MEM_RST, 24, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, USB_DEVICE_RST, 23, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, SPI2_DMA_RST, 22, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, I2S1_RST, 21, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, PWM1_RST, 20, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, CAN_RST, 19, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, EXT1_RST, 18, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, PWM0_RST, 17, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, SPI3_RST, 16, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, TIMERGROUP1_RST, 15, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, EFUSE_RST, 14, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, TIMERGROUP_RST, 13, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, UHCI1_RST, 12, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, LEDC_RST, 11, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, PCNT_RST, 10, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, RMT_RST, 9, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, UHCI0_RST, 8, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, EXT0_RST, 7, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, SPI2_RST, 6, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, UART1_RST, 5, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, I2S0_RST, 4, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, WDG_RST, 3, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, UART_RST, 2, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, SPI01_RST, 1, 1)
    FIELD(SYSTEM_PERIP_RST_EN0, TIMERS_RST, 0, 1)

REG32(SYSTEM_PERIP_RST_EN1, 0x01C)
    FIELD(SYSTEM_PERIP_RST_EN1, TSENS_RST, 10, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, UART2_RST, 9, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, LCD_CAM_RST, 8, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, SDIO_HOST_RST, 7, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, DMA_RST, 6, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, CRYPTO_HMAC_RST, 5, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, CRYPTO_DS_RST, 4, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, CRYPTO_RSA_RST, 3, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, CRYPTO_SHA_RST, 2, 1)
    FIELD(SYSTEM_PERIP_RST_EN1, CRYPTO_AES_RST, 1, 1)

REG32(SYSTEM_BT_LPCK_DIV_INT, 0x020)
    FIELD(SYSTEM_BT_LPCK_DIV_INT, BT_LPCK_DIV_NUM, 0, 12)

REG32(SYSTEM_BT_LPCK_DIV_FRAC, 0x024)
    FIELD(SYSTEM_BT_LPCK_DIV_FRAC, LPCLK_RTC_EN, 28, 1)
    FIELD(SYSTEM_BT_LPCK_DIV_FRAC, LPCLK_SEL_XTAL32K, 27, 1)
    FIELD(SYSTEM_BT_LPCK_DIV_FRAC, LPCLK_SEL_XTAL, 26, 1)
    FIELD(SYSTEM_BT_LPCK_DIV_FRAC, LPCLK_SEL_8M, 25, 1)
    FIELD(SYSTEM_BT_LPCK_DIV_FRAC, LPCLK_SEL_RTC_SLOW, 24, 1)
    FIELD(SYSTEM_BT_LPCK_DIV_FRAC, BT_LPCK_DIV_A, 12, 12)
    FIELD(SYSTEM_BT_LPCK_DIV_FRAC, BT_LPCK_DIV_B, 0, 12)

REG32(SYSTEM_CPU_INTR_FROM_CPU_0, 0x028)
    FIELD(SYSTEM_CPU_INTR_FROM_CPU_0, CPU_INTR_FROM_CPU_0, 0, 1)

REG32(SYSTEM_CPU_INTR_FROM_CPU_1, 0x02C)
    FIELD(SYSTEM_CPU_INTR_FROM_CPU_1, CPU_INTR_FROM_CPU_1, 0, 1)

REG32(SYSTEM_CPU_INTR_FROM_CPU_2, 0x030)
    FIELD(SYSTEM_CPU_INTR_FROM_CPU_2, CPU_INTR_FROM_CPU_2, 0, 1)

REG32(SYSTEM_CPU_INTR_FROM_CPU_3, 0x034)
    FIELD(SYSTEM_CPU_INTR_FROM_CPU_3, CPU_INTR_FROM_CPU_3, 0, 1)

REG32(SYSTEM_RSA_PD_CTRL, 0x038)
    FIELD(SYSTEM_RSA_PD_CTRL, RSA_MEM_FORCE_PD, 2, 1)
    FIELD(SYSTEM_RSA_PD_CTRL, RSA_MEM_FORCE_PU, 1, 1)
    FIELD(SYSTEM_RSA_PD_CTRL, RSA_MEM_PD, 0, 1)

REG32(SYSTEM_EDMA_CTRL, 0x03C)
    FIELD(SYSTEM_EDMA_CTRL, EDMA_RESET, 1, 1)
    FIELD(SYSTEM_EDMA_CTRL, EDMA_CLK_ON, 0, 1)

REG32(SYSTEM_CACHE_CONTROL, 0x040)
    FIELD(SYSTEM_CACHE_CONTROL, DCACHE_RESET, 3, 1)
    FIELD(SYSTEM_CACHE_CONTROL, DCACHE_CLK_ON, 2, 1)
    FIELD(SYSTEM_CACHE_CONTROL, ICACHE_RESET, 1, 1)
    FIELD(SYSTEM_CACHE_CONTROL, ICACHE_CLK_ON, 0, 1)

REG32(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL, 0x044)
    FIELD(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL, ENABLE_DOWNLOAD_MANUAL_ENCRYPT, 3, 1)
    FIELD(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL, ENABLE_DOWNLOAD_G0CB_DECRYPT, 2, 1)
    FIELD(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL, ENABLE_DOWNLOAD_DB_ENCRYPT, 1, 1)
    FIELD(SYSTEM_EXTERNAL_DEVICE_ENCRYPT_DECRYPT_CONTROL, ENABLE_SPI_MANUAL_ENCRYPT, 0, 1)

REG32(SYSTEM_RTC_FASTMEM_CONFIG, 0x048)
    FIELD(SYSTEM_RTC_FASTMEM_CONFIG, RTC_MEM_CRC_FINISH, 31, 1)
    FIELD(SYSTEM_RTC_FASTMEM_CONFIG, RTC_MEM_CRC_LEN, 20, 11)
    FIELD(SYSTEM_RTC_FASTMEM_CONFIG, RTC_MEM_CRC_ADDR, 9, 11)
    FIELD(SYSTEM_RTC_FASTMEM_CONFIG, RTC_MEM_CRC_START, 8, 1)

REG32(SYSTEM_RTC_FASTMEM_CRC, 0x04C)
    FIELD(SYSTEM_RTC_FASTMEM_CRC, RTC_MEM_CRC_RES, 0, 32)

REG32(SYSTEM_REDUNDANT_ECO_CTRL, 0x050)
    FIELD(SYSTEM_REDUNDANT_ECO_CTRL, REDUNDANT_ECO_RESULT, 1, 1)
    FIELD(SYSTEM_REDUNDANT_ECO_CTRL, REDUNDANT_ECO_DRIVE, 0, 1)

REG32(SYSTEM_CLOCK_GATE, 0x054)
    FIELD(SYSTEM_CLOCK_GATE, CLK_EN, 0, 1)

REG32(SYSTEM_SYSCLK_CONF, 0x058)
    FIELD(SYSTEM_SYSCLK_CONF, CLK_DIV_EN,  19,  1)
    FIELD(SYSTEM_SYSCLK_CONF, CLK_XTAL_FREQ, 12,  7)
    FIELD(SYSTEM_SYSCLK_CONF, SOC_CLK_SEL, 10,  2)
    FIELD(SYSTEM_SYSCLK_CONF, PRE_DIV_CNT, 0,  10)

REG32(SYSTEM_MEM_PVT, 0x05C)
    FIELD(SYSTEM_MEM_PVT, MEM_VT_SEL, 22, 2)
    FIELD(SYSTEM_MEM_PVT, MEM_TIMING_ERR_CNT, 6, 16)
    FIELD(SYSTEM_MEM_PVT, MEM_PVT_MONITOR_EN, 5, 1)
    FIELD(SYSTEM_MEM_PVT, MEM_ERR_CNT_CLR, 4, 1)
    FIELD(SYSTEM_MEM_PVT, MEM_PATH_LEN, 0, 4)

REG32(SYSTEM_COMB_PVT_LVT_CONF, 0x060)
    FIELD(SYSTEM_COMB_PVT_LVT_CONF, COMB_PVT_MONITOR_EN_LVT, 6, 1)
    FIELD(SYSTEM_COMB_PVT_LVT_CONF, COMB_ERR_CNT_CLR_LVT, 5, 1)
    FIELD(SYSTEM_COMB_PVT_LVT_CONF, COMB_PATH_LEN_LVT, 0, 5)

REG32(SYSTEM_COMB_PVT_NVT_CONF, 0x064)
    FIELD(SYSTEM_COMB_PVT_NVT_CONF, COMB_PVT_MONITOR_EN_NVT, 6, 1)
    FIELD(SYSTEM_COMB_PVT_NVT_CONF, COMB_ERR_CNT_CLR_NVT, 5, 1)
    FIELD(SYSTEM_COMB_PVT_NVT_CONF, COMB_PATH_LEN_NVT, 0, 5)

REG32(SYSTEM_COMB_PVT_HVT_CONF, 0x068)
    FIELD(SYSTEM_COMB_PVT_HVT_CONF, COMB_PVT_MONITOR_EN_HVT, 6, 1)
    FIELD(SYSTEM_COMB_PVT_HVT_CONF, COMB_ERR_CNT_CLR_HVT, 5, 1)
    FIELD(SYSTEM_COMB_PVT_HVT_CONF, COMB_PATH_LEN_HVT, 0, 5)

REG32(SYSTEM_COMB_PVT_ERR_LVT_SITE0, 0x06C)
    FIELD(SYSTEM_COMB_PVT_ERR_LVT_SITE0, COMB_TIMING_ERR_CNT_LVT_SITE0, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_NVT_SITE0, 0x070)
    FIELD(SYSTEM_COMB_PVT_ERR_NVT_SITE0, COMB_TIMING_ERR_CNT_NVT_SITE0, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_HVT_SITE0, 0x074)
    FIELD(SYSTEM_COMB_PVT_ERR_HVT_SITE0, COMB_TIMING_ERR_CNT_HVT_SITE0, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_LVT_SITE1, 0x078)
    FIELD(SYSTEM_COMB_PVT_ERR_LVT_SITE1, COMB_TIMING_ERR_CNT_LVT_SITE1, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_NVT_SITE1, 0x07C)
    FIELD(SYSTEM_COMB_PVT_ERR_NVT_SITE1, COMB_TIMING_ERR_CNT_NVT_SITE1, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_HVT_SITE1, 0x080)
    FIELD(SYSTEM_COMB_PVT_ERR_HVT_SITE1, COMB_TIMING_ERR_CNT_HVT_SITE1, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_LVT_SITE2, 0x084)
    FIELD(SYSTEM_COMB_PVT_ERR_LVT_SITE2, COMB_TIMING_ERR_CNT_LVT_SITE2, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_NVT_SITE2, 0x088)
    FIELD(SYSTEM_COMB_PVT_ERR_NVT_SITE2, COMB_TIMING_ERR_CNT_NVT_SITE2, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_HVT_SITE2, 0x08C)
    FIELD(SYSTEM_COMB_PVT_ERR_HVT_SITE2, COMB_TIMING_ERR_CNT_HVT_SITE2, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_LVT_SITE3, 0x090)
    FIELD(SYSTEM_COMB_PVT_ERR_LVT_SITE3, COMB_TIMING_ERR_CNT_LVT_SITE3, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_NVT_SITE3, 0x094)
    FIELD(SYSTEM_COMB_PVT_ERR_NVT_SITE3, COMB_TIMING_ERR_CNT_NVT_SITE3, 0, 16)

REG32(SYSTEM_COMB_PVT_ERR_HVT_SITE3, 0x098)
    FIELD(SYSTEM_COMB_PVT_ERR_HVT_SITE3, COMB_TIMING_ERR_CNT_HVT_SITE3, 0, 16)

REG32(SYSTEM_SYSTEM_DATE, 0xFFC)
    FIELD(SYSTEM_SYSTEM_DATE, SYSTEM_REG_DATE, 0, 28)