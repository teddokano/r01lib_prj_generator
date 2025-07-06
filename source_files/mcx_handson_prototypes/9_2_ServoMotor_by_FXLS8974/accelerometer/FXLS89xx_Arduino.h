/*
 * Copyright 2024 ryraki
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
/**
 * @file FXLS89xx_Arduino.h
 * @brief This file contains the header for FXLS89xx Accelerometer evaluation by Arduino
 */
#ifndef _FXLS89xx_Arduino_h
#define _FXLS89xx_Arduino_h

#include 	"r01lib.h"
//#include "fxls89xx.h"
#include	"I2C_device.h"

#define FXLS89xx_I2C_ADDRESS_SA0_L (uint8_t) 0x18 /*!< 7-bit I2C Address when SA0 is low. */
#define FXLS89xx_I2C_ADDRESS_SA0_H (uint8_t) 0x19 /*!< 7-bit I2C Address when SA0 is high. */

/**
* @brief Class to evaluate FXLS89xx
*/
class FXLS89xx : public I2C_device{
  public:
    /**
   **  @brief The FXLS89xx Sensor Internal Register Map.
   */
    enum FXLS89xx_REG {
      _INT_STATUS = 0x00,
      _TEMP_OUT,
      _VECM_LSB,
      _VECM_MSB,
      _OUT_X_LSB,
      _OUT_X_MSB,
      _OUT_Y_LSB,
      _OUT_Y_MSB,
      _OUT_Z_LSB,
      _OUT_Z_MSB,
      _RESERVED_REG1,
      _BUF_STATUS,
      _BUF_X_LSB,
      _BUF_X_MSB,
      _BUF_Y_LSB,
      _BUF_Y_MSB,
      _BUF_Z_LSB,
      _BUF_Z_MSB,
      _PROD_REV,
      _WHO_AM_I,
      _SYS_MODE,
      _SENS_CONFIG1,
      _SENS_CONFIG2,
      _SENS_CONFIG3,
      _SENS_CONFIG4,
      _SENS_CONFIG5,
      _WAKE_IDLE_LSB,
      _WAKE_IDLE_MSB,
      _SLEEP_IDLE_LSB,
      _SLEEP_IDLE_MSB,
      _ASLP_COUNT_LSB,
      _ASLP_COUNT_MSB,
      _INT_EN,
      _INT_PIN_SEL,
      _OFF_X,
      _OFF_Y,
      _OFF_Z,
      _RESERVED_REG2,
      _BUF_CONFIG1,
      _BUF_CONFIG2,
      _ORIENT_STATUS,
      _ORIENT_CONFIG,
      _ORIENT_DBCOUNT ,
      _ORIENT_BF_ZCOMP,
      _ORIENT_THS_REG,
      _SDCD_INT_SRC1,
      _SDCD_INT_SRC2,
      _SDCD_CONFIG1,
      _SDCD_CONFIG2,
      _SDCD_OT_DBCNT,
      _SDCD_WT_DBCNT,
      _SDCD_LTHS_LSB,
      _SDCD_LTHS_MSB,
      _SDCD_UTHS_LSB,
      _SDCD_UTHS_MSB,
      _SELF_TEST_CONFIG1,
      _SELF_TEST_CONFIG2,
      _RESERVED_REG12,
      _RESERVED_REG13,
    };

    /*
    ** INT_STATUS
    */
    enum INT_STATUS : uint8_t {
      SRC_BOOT_H    = (uint8_t) 0x01,
      SRC_ASLP_H    = (uint8_t) 0x02,
      SRC_ORIENT_H  = (uint8_t) 0x04,
      SRC_SDCD_WT_H = (uint8_t) 0x08,
      SRC_SDCD_OT_H = (uint8_t) 0x10,
      SRC_BUF_H     = (uint8_t) 0x20,
      SRC_OVF_H     = (uint8_t) 0x40,
      SRC_DRDY_H    = (uint8_t) 0x80
    };

    /*
    ** BUF_STATUS
    */
    enum BUF_STATUS : uint8_t {
      BUF_CNT_SHIFT = 0,
      BUF_OVF_SHIFT = 6,
      BUF_WMRK_SHIFT= 7,
      
      BUF_CNT_MASK = (uint8_t) 0x3F,
      
      BUF_OVF_H   = (uint8_t) 0x40,
      BUF_WMRK_H  = (uint8_t) 0x80
    };

    /*
    ** WHO_AM_I
    */
    #define FXLS8961_WHOAMI_VALUE (0x81)         /*!< WHO_AM_I Value of FXLS8961AF */
    #define FXLS8962_WHOAMI_VALUE (0x62)         /*!< WHO_AM_I Value of FXLS8962AF */
    #define FXLS8964_WHOAMI_VALUE (0x84)         /*!< WHO_AM_I Value of FXLS8964AF */
    #define FXLS8967_WHOAMI_VALUE (0x87)         /*!< WHO_AM_I Value of FXLS8967AF */
    #define FXLS8971_WHOAMI_VALUE (0x83)         /*!< WHO_AM_I Value of FXLS8971CF */
    #define FXLS8974_WHOAMI_VALUE (0x86)         /*!< WHO_AM_I Value of FXLS8974CF */

    /*
    ** SYS_MODE
    */
    enum SYS_MODE : uint8_t {
      BUF_GATE_CNT_SHIFT = 2,

      BUF_GATE_ERR_MASK = (uint8_t) 0x03,
      BUF_GATE_CNT_MASK = (uint8_t) 0x7C,
      
      SYS_MODE_STB   = (uint8_t) 0x00, // The device is in Standby mode.
      SYS_MODE_WAK   = (uint8_t) 0x01, // The device is in Wake Mode.
      SYS_MODE_SLP   = (uint8_t) 0x02, // The device is in Sleep Mode.
      SYS_MODE_EXT   = (uint8_t) 0x03, // The device is in External Trigger Mode.
      BUF_GATE_ERR_L = (uint8_t) 0x00, // Buffer Gate Error is NOT detected.
      BUF_GATE_ERR_H = (uint8_t) 0x80 // Buffer Gate Error is Detected.
    };

    /*
    ** SENS_CONFIG1
    */
    enum SENS_CONFIG1 : uint8_t {
      FSR_SHIFT = 1,

      FSR_MASK  =        (uint8_t)0x06,
      ST_AXIS_SEL_MASK = (uint8_t)0x60,
      ACTIVE_MASK =      (uint8_t)0x01,

      RST_RESET = (uint8_t) 0x80,       // Reset
      ST_AXIS_SEL_DIS = (uint8_t) 0x00, // Self-Test function is disabled.
      ST_AXIS_SEL_ENX = (uint8_t) 0x20, // X-axis Self-Test is enabled.
      ST_AXIS_SEL_ENY = (uint8_t) 0x40, // Y-axis Self-Test is enabled.
      ST_AXIS_SEL_ENZ = (uint8_t) 0x60, // Z-axis Self-Test is enabled.
      ST_POL_POS = (uint8_t) 0x00,      // Positive polarity when Self-Test
      ST_POL_NEG = (uint8_t) 0x10,      // Negative polarity when Self-Test
      SPI_M_4 = (uint8_t) 0x00,         // 4-wire SPI
      SPI_M_3 = (uint8_t) 0x08,         // 3-wire SPI
      FSR_2G = (uint8_t) 0x00,          // FSR=+/-2G
      FSR_4G = (uint8_t) 0x02,          // FSR=+/-4G
      FSR_8G = (uint8_t) 0x04,          // FSR=+/-8G
      FSR_16G = (uint8_t) 0x06,         // FSR=+/-16G
      ACTIVE_STB = (uint8_t) 0x00,      // Transition to Standby
      ACTIVE_ACT = (uint8_t) 0x01,      // Transition to Active
    };

    /*
    ** SENS_CONFIG2
    */
    enum SENS_CONFIG2 : uint8_t {
      SLEEP_PM_SHIFT = 4,
      WAKE_PM_SHIFT  = 6,

      SLEEP_PM_MASK = (uint8_t) 0x30,
      WAKE_PM_MASK  = (uint8_t) 0xC0,

      WAKE_PM_LPM = (uint8_t) 0x00,   // Low Power mode during WAKE
      WAKE_PM_HPM = (uint8_t) 0x40,   // High Performance mode during WAKE
      WAKE_PM_FPM = (uint8_t) 0x80,   // Flexible Performance mode during WAKE
      SLEEP_PM_LPM = (uint8_t) 0x00,  // Low Power mode during SLEEP
      SLEEP_PM_HPM = (uint8_t) 0x10,  // High Performance mode during SLEEP
      SLEEP_PM_FPM = (uint8_t) 0x20,  // Flexible Performance mode during SLEEP
      LE_BE_LE = (uint8_t) 0x00,      // Little-endian
      LE_BE_BE = (uint8_t) 0x08,      // Big-endian
      ANIC_TEMP_DIS = (uint8_t) 0x00, // TEMP_OUT register is NOT included when auto-increment.
      ANIC_TEMP_EN = (uint8_t) 0x02,  // TEMP_OUT register is included when auto-increment.
      F_READ_NORM = (uint8_t) 0x00,   // Normal read mode
      F_READ_FAST = (uint8_t) 0x01,   // Fast read mode
    };

    /*
    ** SENS_CONFIG3
    */
    enum SENS_CONFIG3 : uint8_t {
      WAKE_ODR_SHIFT = 4,

      SLEEP_ODR_MASK = (uint8_t) 0x0F,
      WAKE_ODR_MASK =  (uint8_t) 0xF0,

      WAKE_ODR_3200HZ =   (uint8_t) 0x00, // 3200Hz when WAKE
      WAKE_ODR_1600HZ =   (uint8_t) 0x10, // 1600Hz when WAKE
      WAKE_ODR_800HZ =    (uint8_t) 0x20, // 800Hz when WAKE
      WAKE_ODR_400HZ =    (uint8_t) 0x30, // 400Hz when WAKE
      WAKE_ODR_200HZ =    (uint8_t) 0x40, // 200Hz when WAKE
      WAKE_ODR_100HZ =    (uint8_t) 0x50, // 100Hz when WAKE
      WAKE_ODR_50HZ =     (uint8_t) 0x60, // 50Hz when WAKE
      WAKE_ODR_25HZ =     (uint8_t) 0x70, // 25Hz when WAKE
      WAKE_ODR_12_5HZ =   (uint8_t) 0x80, // 12.5Hz when WAKE
      WAKE_ODR_6_25HZ =   (uint8_t) 0x90, // 6.25Hz when WAKE
      WAKE_ODR_3_125HZ =  (uint8_t) 0xa0, // 3.125Hz when WAKE
      WAKE_ODR_1_563HZ =  (uint8_t) 0xb0, // 1.563Hz when WAKE
      WAKE_ODR_0_781HZ =  (uint8_t) 0xc0, // 0.781Hz when WAKE
      SLEEP_ODR_3200HZ =  (uint8_t) 0x00, // 3200Hz when SLEEP
      SLEEP_ODR_1600HZ =  (uint8_t) 0x01, // 1600Hz when SLEEP
      SLEEP_ODR_800HZ =   (uint8_t) 0x02, // 800Hz when SLEEP
      SLEEP_ODR_400HZ =   (uint8_t) 0x03, // 400Hz when SLEEP
      SLEEP_ODR_200HZ =   (uint8_t) 0x04, // 200Hz when SLEEP
      SLEEP_ODR_100HZ =   (uint8_t) 0x05, // 100Hz when SLEEP
      SLEEP_ODR_50HZ =    (uint8_t) 0x06, // 50Hz when SLEEP
      SLEEP_ODR_25HZ =    (uint8_t) 0x07, // 25Hz when SLEEP
      SLEEP_ODR_12_5HZ =  (uint8_t) 0x08, // 12.5Hz when SLEEP
      SLEEP_ODR_6_25HZ =  (uint8_t) 0x09, // 6.25Hz when SLEEP
      SLEEP_ODR_3_125HZ = (uint8_t) 0x0a, // 3.125Hz when SLEEP
      SLEEP_ODR_1_563HZ = (uint8_t) 0x0b, // 1.563Hz when SLEEP
      SLEEP_ODR_0_781HZ = (uint8_t) 0x0c, // 0.781Hz when SLEEP
    };

    /*
    ** SENS_CONFIG4
    */
    enum SENS_CONFIG4 : uint8_t {
      EXT_TRIG_M_S = (uint8_t) 0x00,   // Each trigger a single ADC when EXT_TRIG
      EXT_TRIG_M_M = (uint8_t) 0x80,   // Each trigger multiple ADC when EXT_TRIG
      WK_SDCD_WT_DIS = (uint8_t) 0x00, // SDCD WT event does nothing for state transition.
      WK_SDCD_WT_EN = (uint8_t) 0x40,  // SDCD WT event leads SLEEP-to-WAKE transition.
      WK_SDCD_OT_DIS = (uint8_t) 0x00, // SDCD OT event does nothing for state transition.
      WK_SDCD_OT_EN = (uint8_t) 0x20,  // SDCD OT event leads SLEEP-to-WAKE transition.
      WK_ORIENT_DIS = (uint8_t) 0x00,  // Orientation change event does nothing for state transition.
      WK_ORIENT_EN = (uint8_t) 0x10,   // Orientation change event leads SLEEP-to-WAKE transition.
      DRDY_PUL_DIS = (uint8_t) 0x00,   // A SRC_DRDY event is latched on INT until being read.
      DRDY_PUL_EN = (uint8_t) 0x08,    // A SRC_DRDY event is 32us pulse on INT
      INT2_FUNC_INT = (uint8_t) 0x00,  // INT2/EXT_TRIG pin is configured as INT2.
      INT2_FUNC_EXT = (uint8_t) 0x04,  // INT2/EXT_TRIG pin is configured as EXT_TRIG.
      INT_PP_OD_PP = (uint8_t) 0x00,   // INTx output pin is push-pull.
      INT_PP_OD_OD = (uint8_t) 0x02,   // INTx output pin is open-drain.
      INT_POL_ACT_L = (uint8_t) 0x00,  // INTx polarity is active-low.
      INT_POL_ACT_H = (uint8_t) 0x01,  // INTx polarity is active-high.
    };

    /*
    ** SENS_CONFIG5
    */
    enum SENS_CONFIG5 : uint8_t {
      VECM_EN_DIS = (uint8_t) 0x00,     // Vector magnitude calculation disabled
      VECM_EN_EN = (uint8_t) 0x10,      // Vector magnitude calculation enabled
      X_DIS_EN = (uint8_t) 0x00,        // X-axis is included in auto-increment.
      X_DIS_DIS = (uint8_t) 0x08,       // X-axis is excluded in auto-increment.
      Y_DIS_EN = (uint8_t) 0x00,        // Y-axis is included in auto-increment.
      Y_DIS_DIS = (uint8_t) 0x04,       // Y-axis is excluded in auto-increment.
      Z_DIS_EN = (uint8_t) 0x00,        // Z-axis is included in auto-increment.
      Z_DIS_DIS = (uint8_t) 0x02,       // Z-axis is excluded in auto-increment.
      HIBERNATE_EN_EN = (uint8_t) 0x01, // Transition to Hibernate is made.
    };

    /*
    ** INT_EN - Bit field mask definitions
    */
    enum INT_EN : uint8_t {
      DRDY_EN_DIS = (uint8_t) 0x00,     // Interrupt is disabled for DRDY.
      DRDY_EN_EN = (uint8_t) 0x80,      // Interrupt enabled for DRDY.
      BUF_EN_DIS = (uint8_t) 0x00,      // Interrupt is disabled for buffer.
      BUF_EN_EN = (uint8_t) 0x40,       // Interrupt enabled for buffer.
      SDCD_OT_EN_DIS = (uint8_t) 0x00,  // Interrupt is disabled for SDCD_OT.
      SDCD_OT_EN_EN = (uint8_t) 0x20,   // Interrupt is enabled for SDCD_OT.
      SDCD_WT_EN_DIS = (uint8_t) 0x00,  // Interrupt is disabled for SDCD_WT.
      SDCD_WT_EN_EN = (uint8_t) 0x10,   // Interrupt is enabled for SDCD_WT.
      ORIENT_EN_DIS = (uint8_t) 0x00,   // Interrupt is disabled for orientation.
      ORIENT_EN_EN = (uint8_t) 0x08,    // Interrupt is enabled for orientation.
      ASLP_EN_DIS = (uint8_t) 0x00,     // Interrupt is disabled for WAKE/SLEEP transition.
      ASLP_EN_EN = (uint8_t) 0x04,      // Interrupt is enabled for WAKE/SLEEP transition.
      BOOT_DIS_EN = (uint8_t) 0x00,     // Boot interrupt is enabled.
      BOOT_DIS_DIS = (uint8_t) 0x02,    // Boot interrupt is disabled.
      WAKE_OUT_EN_DIS = (uint8_t) 0x00, // The device does not signal the WAKE operating mode.
      WAKE_OUT_EN_EN = (uint8_t) 0x01,  // The device signals that it is currently in WAKE mode.
    };

    /*
    ** INT_PIN_SEL
    */
    enum INT_PIN_SEL : uint8_t {
      DRDY_INT2_INT1 = (uint8_t) 0x00,
      DRDY_INT2_INT2 = (uint8_t) 0x80,
      BUF_INT2_INT1 = (uint8_t) 0x00,
      BUF_INT2_INT2 = (uint8_t) 0x40,
      SDCD_OT_INT2_INT1 = (uint8_t) 0x00,
      SDCD_OT_INT2_INT2 = (uint8_t) 0x20,
      SDCD_WT_INT2_INT1 = (uint8_t) 0x00,
      SDCD_WT_INT2_INT2 = (uint8_t) 0x10,
      ORIENT_INT2_INT1 = (uint8_t) 0x00,
      ORIENT_INT2_INT2 = (uint8_t) 0x08,
      ASLP_INT2_INT1 = (uint8_t) 0x00,
      ASLP_INT2_INT2 = (uint8_t) 0x04,
      BOOT_INT2_INT1 = (uint8_t) 0x00,
      BOOT_INT2_INT2 = (uint8_t) 0x02,
      WK_OUT_INT2_INT1 = (uint8_t) 0x00,
      WK_OUT_INT2_INT2 = (uint8_t) 0x01,
    };

    /*
    ** BUF_CONFIG1
    */
    enum BUF_CONFIG1 : uint8_t {
      BUF_MODE_MASK = (uint8_t) 0x60,

      BUF_TYPE_FIFO =         (uint8_t) 0x00, // FIFO
      BUF_TYPE_FILO =         (uint8_t) 0x80, // FILO
      BUF_MODE_DIS =          (uint8_t) 0x00,  // Buffer is disabled.
      BUF_MODE_STREAM_MODE =  (uint8_t) 0x20,  // Buffer is enabled as Stream Mode.
      BUF_MODE_STOP_MODE =    (uint8_t) 0x40,  // Buffer is enabled as Stop mode.
      BUF_MODE_TRIGGER_MODE = (uint8_t) 0x60,  // Buffer is enabled as Trigger Mode.
      BUF_GATE_BY_PASSED =    (uint8_t) 0x00,  // Buffer is flushed when WAKE/SLEEP transition
      BUF_GATE_ENABLED =      (uint8_t) 0x10,  // Buffer remains when WAKE/SLEEP transition. Must be manually flushed.
      TRG_SDCD_WT_DIS =       (uint8_t) 0x00,  // Trigger source is disabled for SDCD_WT.
      TRG_SDCD_WT_EN =        (uint8_t) 0x08,  // Trigger source is enabled for SDCD_WT.
      TRG_SDCD_OT_DIS =       (uint8_t) 0x00,  // Trigger source is disabled for SDCD_OT.
      TRG_SDCD_OT_EN =        (uint8_t) 0x04,  // Trigger source is enabled for SDCD_OT.
      TRG_ORIENT_DIS =        (uint8_t) 0x00,  // Trigger source is disabled for orientation.
      TRG_ORIENT_EN =         (uint8_t) 0x01,  // Trigger source is enabled for orientation.
    };

    /*
    ** BUF_CONFIG2
    */
    enum BUF_CONFIG2 : uint8_t {
      BUF_WMRK_MASK = (uint8_t) 0x3F,

      BUF_FLUSH_CMP =    (uint8_t) 0x00,  //  Buffer flush operation is completed or not pending.
      BUF_FLUSH_EN =     (uint8_t) 0x80,  //  Buffer flush is enabled or being pending.
      WAKE_SRC_BUF_DIS = (uint8_t) 0x00,  //  BUF_WMRK and BUF_OVF is ignored by WAKE/SLEEP transition.
      WAKE_SRC_BUF_EN =  (uint8_t) 0x40,  //  BUF_WMRK and BUF_OVF is used for WAKE/SLEEP transition.
    };

    /*
    ** ORIENT_STATUS
    */
    enum ORIENT_STATUS : uint8_t {
      LAPO_MASK = (uint8_t)0x06,

      NEW_ORIENT_NOT = (uint8_t) 0x00,  // No change in orientation detected.
      NEW_ORIENT_DET = (uint8_t) 0x80,  // BAFRO and/or LAPO and/or Z-tilt lockout value has changed.
      LO_NOT = (uint8_t) 0x00,          // Lockout condition has not been detected.
      LO_DET = (uint8_t) 0x40,          // Z-tilt lockout trip angle has been exceeded. Lockout condition has been detected.
      LAPO_UP = (uint8_t) 0x00,         // Portrait up
      LAPO_DOWN = (uint8_t) 0x02,       // Portrait down
      LAPO_RIGHT = (uint8_t) 0x04,      // Landscape right
      LAPO_LEFT = (uint8_t) 0x06,       // Landscape left
      BAFRO_FRONT = (uint8_t) 0x00,     // Front-facing
      BAFRO_BACK = (uint8_t) 0x01,      // Back-facing
    };

    /*
    ** ORIENT_CONFIG
    */
    enum ORIENT_CONFIG : uint8_t {
      ORIENT_DBCNTM_DEC = (uint8_t) 0x00,  // Orientation debounce counter is decremented.
      ORIENT_DBCNTM_CLR = (uint8_t) 0x80,  // Orientation debounce counter is cleared.
      ORIENT_ENABLE_DIS = (uint8_t) 0x00,  // Orientation detection function is disabled.
      ORIENT_ENABLE_EN = (uint8_t) 0x40,   // Orientation detection function is enabled.
    };

    /*
    ** ORIENT_BF_ZCOMP
    */
    enum ORIENT_BF_ZCOMP : uint8_t {
      ORIENT_ZLOCK_MASK = (uint8_t) 0x07,
      ORIENT_BKFR_MASK = (uint8_t) 0xC0,

      ORIENT_BKFR_BF_80_280_FB_100_260 = (uint8_t) 0x00,  // Back-to-Front Z<80 or Z>280, Front-to-Back Z>100 and Z<260
      ORIENT_BKFR_BF_75_285_FB_105_255 = (uint8_t) 0x40,  // Back-to-Front Z<75 or Z>285, Front-to-Back Z>105 and Z<255
      ORIENT_BKFR_BF_70_290_FB_110_250 = (uint8_t) 0x80,  // Back-to-Front Z<70 or Z>290, Front-to-Back Z>110 and Z<250
      ORIENT_BKFR_BF_65_295_FB_115_245 = (uint8_t) 0xc0,  // Back-to-Front Z<65 or Z>295, Front-to-Back Z>115 and Z<245
      ORIENT_ZLOCK_13_6 = (uint8_t) 0x00,  // Resultant angle 13.6~14.5
      ORIENT_ZLOCK_17_1 = (uint8_t) 0x01,  // Resultant angle 17.1~18.2
      ORIENT_ZLOCK_20_7 = (uint8_t) 0x02,  // Resultant angle 20.7~22.0
      ORIENT_ZLOCK_24_4 = (uint8_t) 0x03,  // Resultant angle 24.4~25.9
      ORIENT_ZLOCK_28_1 = (uint8_t) 0x04,  // Resultant angle 28.1~30.0
      ORIENT_ZLOCK_32_0 = (uint8_t) 0x05,  // Resultant angle 32.0~34.2
      ORIENT_ZLOCK_36_1 = (uint8_t) 0x06,  // Resultant angle 36.1~38.7
      ORIENT_ZLOCK_40_4 = (uint8_t) 0x07,  // Resultant angle 40.4~43.4
    };

    /*
    ** ORIENT_THS
    */
    enum ORIENT_THS : uint8_t {
      REG_HYS_MASK =        (uint8_t) 0x07,
      REG_ORIENT_THS_MASK = (uint8_t) 0xF8,

      REG_ORIENT_THS_SHIFT = 3,

      ORIENT_THS_0_0 = (uint8_t) 0x00,    // 0.0
      ORIENT_THS_1_8 = (uint8_t) 0x08,    // 1.8
      ORIENT_THS_3_8 = (uint8_t) 0x10,    // 3.8
      ORIENT_THS_5_9 = (uint8_t) 0x18,    // 5.9
      ORIENT_THS_8_1 = (uint8_t) 0x20,    // 8.1
      ORIENT_THS_10_5 = (uint8_t) 0x28,   // 10.5
      ORIENT_THS_13_0 = (uint8_t) 0x30,   // 13.0
      ORIENT_THS_15_6 = (uint8_t) 0x38,   // 15.6
      ORIENT_THS_18_4 = (uint8_t) 0x40,   // 18.4
      ORIENT_THS_21_4 = (uint8_t) 0x48,   // 21.4
      ORIENT_THS_24_4 = (uint8_t) 0x50,   // 24.4
      ORIENT_THS_27_6 = (uint8_t) 0x58,   // 27.6
      ORIENT_THS_31_0 = (uint8_t) 0x60,   // 31.0
      ORIENT_THS_34_4 = (uint8_t) 0x68,   // 34.4
      ORIENT_THS_37_9 = (uint8_t) 0x70,   // 37.9
      ORIENT_THS_41_4 = (uint8_t) 0x78,   // 41.4
      ORIENT_THS_45_0 = (uint8_t) 0x80,   // 45.0
      ORIENT_THS_48_6 = (uint8_t) 0x88,   // 48.6
      ORIENT_THS_52_1 = (uint8_t) 0x90,   // 52.1
      ORIENT_THS_55_6 = (uint8_t) 0x98,   // 55.6
      ORIENT_THS_59_0 = (uint8_t) 0xa0,   // 59.0
      ORIENT_THS_62_4 = (uint8_t) 0xa8,   // 62.4
      ORIENT_THS_65_6 = (uint8_t) 0xb0,   // 65.6
      ORIENT_THS_68_6 = (uint8_t) 0xb8,   // 68.6
      ORIENT_THS_71_6 = (uint8_t) 0xc0,   // 71.6
      ORIENT_THS_74_4 = (uint8_t) 0xc8,   // 74.4
      ORIENT_THS_77_0 = (uint8_t) 0xd0,   // 77.0
      ORIENT_THS_79_5 = (uint8_t) 0xd8,   // 79.5
      ORIENT_THS_81_9 = (uint8_t) 0xe0,   // 81.9
      ORIENT_THS_84_1 = (uint8_t) 0xe8,   // 84.1
      ORIENT_THS_86_2 = (uint8_t) 0xf0,   // 86.2
      ORIENT_THS_88_2 = (uint8_t) 0xf8,   // 88.2
      ORIENT_HYS_45_45 = (uint8_t) 0x00,  // L-to-P 45 P-to-L 45
      ORIENT_HYS_49_41 = (uint8_t) 0x01,  // L-to-P 49 P-to-L 41
      ORIENT_HYS_52_38 = (uint8_t) 0x02,  // L-to-P 52 P-to-L 38
      ORIENT_HYS_56_34 = (uint8_t) 0x03,  // L-to-P 56 P-to-L 34
      ORIENT_HYS_59_31 = (uint8_t) 0x04,  // L-to-P 59 P-to-L 31
      ORIENT_HYS_62_28 = (uint8_t) 0x05,  // L-to-P 62 P-to-L 28
      ORIENT_HYS_66_24 = (uint8_t) 0x06,  // L-to-P 66 P-to-L 24
      ORIENT_HYS_69_21 = (uint8_t) 0x07,  // L-to-P 69 P-to-L 21
    };

    /*
    ** SDCD_INT_SRC1
    */
    enum SDCD_INT_SRC1 : uint8_t {
      OT_EA_L = (uint8_t) 0x00,     // SDCD outside-of-thresholds event active flag NOT asserted
      OT_EA_H = (uint8_t) 0x80,     // SDCD outside-of-thresholds event active flag asserted
      X_OT_EF_L = (uint8_t) 0x00,   // X-axis data or delta-outside-of-upper-and-lower-thresholds event flag NOT asserted
      X_OT_EF_H = (uint8_t) 0x20,   // X-axis data or delta-outside-of-upper-and-lower-thresholds event flag asserted
      X_OT_POL_L = (uint8_t) 0x00,  // Less than lower threshold
      X_OT_POL_H = (uint8_t) 0x10,  // Greater than upper threshold
      Y_OT_EF_L = (uint8_t) 0x00,   // Y-axis data or delta-outside-of-upper-and-lower-thresholds event flag NOT asserted
      Y_OT_EF_H = (uint8_t) 0x08,   // Y-axis data or delta-outside-of-upper-and-lower-thresholds event flag asserted
      Y_OT_POL_L = (uint8_t) 0x00,  // Less than lower threshold
      Y_OT_POL_H = (uint8_t) 0x04,  // Greater than upper threshold
      Z_OT_EF_L = (uint8_t) 0x00,   // Z-axis data or delta-outside-of-upper-and-lower-thresholds event flag NOT asserted
      Z_OT_EF_H = (uint8_t) 0x02,   // Z-axis data or delta-outside-of-upper-and-lower-thresholds event flag asserted
      Z_OT_POL_L = (uint8_t) 0x00,  // Less than lower threshold
      Z_OT_POL_H = (uint8_t) 0x01,  // Greater than upper threshold
    };

    /*
    ** SDCD_INT_SRC2
    */
    enum SDCD_INT_SRC2 : uint8_t {
      WT_EA_L = (uint8_t) 0x00,    // SDCD within-thresholds event active flag NOT asserted
      WT_EA_H = (uint8_t) 0x80,    // SDCD within-thresholds event active flag asserted
      X_WT_EF_L = (uint8_t) 0x00,  // X-axis data is out of the range.
      X_WT_EF_H = (uint8_t) 0x20,  // X-axis data is within the range.
      Y_WT_EF_L = (uint8_t) 0x00,  // Y-axis data is out of the range.
      Y_WT_EF_H = (uint8_t) 0x08,  // Y-axis data is within the range.
      Z_WT_EF_L = (uint8_t) 0x00,  // Z-axis data is out of the range.
      Z_WT_EF_H = (uint8_t) 0x02,  // Z-axis data is within the range.
    };

    /*
    ** SDCD_CONFIG1
    */
    enum SDCD_CONFIG1 : uint8_t {
      OT_ELE_DIS = (uint8_t) 0x00,   // SDCD outside-of-thresholds event latch is disabled.
      OT_ELE_EN = (uint8_t) 0x80,    // SDCD outside-of-thresholds event latch is enabled.
      WT_ELE_DIS = (uint8_t) 0x00,   // SDCD within-thresholds event latch is disabled.
      WT_ELE_EN = (uint8_t) 0x40,    // SDCD within-thresholds event latch is enabled.
      X_OT_EN_DIS = (uint8_t) 0x00,  // SDCD function X-axis outside-of-thresholds condition is NOT used.
      X_OT_EN_EN = (uint8_t) 0x20,   // SDCD function X-axis outside-of-thresholds condition is used.
      Y_OT_EN_DIS = (uint8_t) 0x00,  // SDCD function Y-axis outside-of-thresholds condition is NOT used.
      Y_OT_EN_EN = (uint8_t) 0x10,   // SDCD function Y-axis outside-of-thresholds condition is used.
      Z_OT_EN_DIS = (uint8_t) 0x00,  // SDCD function Z-axis outside-of-thresholds condition is NOT used.
      Z_OT_EN_EN = (uint8_t) 0x08,   // SDCD function Z-axis outside-of-thresholds condition is used.
      X_WT_EN_DIS = (uint8_t) 0x00,  // SDCD function X-axis within-thresholds condition is NOT used.
      X_WT_EN_EN = (uint8_t) 0x04,   // SDCD function X-axis within-thresholds condition is used.
      Y_WT_EN_DIS = (uint8_t) 0x00,  // SDCD function Y-axis within-thresholds condition is NOT used.
      Y_WT_EN_EN = (uint8_t) 0x02,   // SDCD function Y-axis within-thresholds condition is used.
      Z_WT_EN_DIS = (uint8_t) 0x00,  // SDCD function Z-axis within-thresholds condition is NOT used.
      Z_WT_EN_EN = (uint8_t) 0x01,   // SDCD function Z-axis within-thresholds condition is used.
    };

    /*
    ** SDCD_CONFIG2
    */
    enum SDCD_CONFIG2 : uint8_t {
      REF_UPDM_SHIFT = 5,

      REF_UPDM_MASK = (uint8_t) 0x60,

      SDCD_EN_DIS = (uint8_t) 0x00,          // SDCD function is disabled.
      SDCD_EN_EN = (uint8_t) 0x80,           // SDCD function is Enabled.
      REF_UPDM_UPDATED = (uint8_t) 0x00,     // Updated Reference
      REF_UPDM_FIXED = (uint8_t) 0x20,       // Fixed Reference
      REF_UPDM_DIFF = (uint8_t) 0x40,        // Delta Reference
      REF_UPDM_ABSOLUTE = (uint8_t) 0x60,    // Absolute Reference
      OT_DBCTM_DECREMENT = (uint8_t) 0x00,   // Debounce counter decrement is enabled at SDCD_OT.
      OT_DBCTM_CLEARED = (uint8_t) 0x10,     // Debounce counter is cleared at SDCD_OT.
      WT_DBCTM_DECREMENT = (uint8_t) 0x00,   // Debounce counter decrement is enabled at SDCD_WT.
      WT_DBCTM_CLEARED = (uint8_t) 0x08,     // Debounce counter is cleared at SDCD_WT.
      WT_LOG_SEL_AND = (uint8_t) 0x00,       // Function uses the logical AND of the enabled axes.
      WT_LOG_SEL_OR = (uint8_t) 0x04,        // Function uses the logical OR of the enabled axes.
      MODE_XYZ = (uint8_t) 0x00,             // Function uses X, Y, Z acceleration data for the window comparison.
      MODE_VECM = (uint8_t) 0x02,            // Function uses Vector magnitude data for the window comparison on the X-axis channel only
      REF_UPD_NO_PENDING = (uint8_t) 0x00,   // No reference update pending or reference update has completed.
      REF_UPD_SYNC_UPDATE = (uint8_t) 0x01,  // Triggers a synchronous update of the internal X/Y/Z reference registers.
    };

    /*
    ** SELF_TEST_CONFIG2
    */
    enum SELF_TEST_CONFIG2 : uint8_t {
      ST_DEC_1 =    (uint8_t) 0x00,  // 0.3125ms
      ST_DEC_2 =    (uint8_t) 0x01,  // 0.625ms
      ST_DEC_4 =    (uint8_t) 0x02,  // 1.25ms
      ST_DEC_8 =    (uint8_t) 0x03,  // 2.5ms
      ST_DEC_16 =   (uint8_t) 0x04,  // 5ms
      ST_DEC_32 =   (uint8_t) 0x05,  // 10ms
      ST_DEC_64 =   (uint8_t) 0x06,  // 20ms
      ST_DEC_128 =  (uint8_t) 0x07,  // 40ms
      ST_DEC_256 =  (uint8_t) 0x08,  // 80ms
      ST_DEC_512 =  (uint8_t) 0x09,  // 160ms
      ST_DEC_1024 = (uint8_t) 0x0a,  // 320ms
      ST_DEC_2048 = (uint8_t) 0x0b,  // 640ms
      ST_DEC_4096 = (uint8_t) 0x0c,  // 1280ms
    };
  
    enum odr_freq {
      _3200HZ = ((uint8_t)0x00),
      _1600HZ = ((uint8_t)0x01),
      _800HZ = ((uint8_t)0x02),
      _400HZ = ((uint8_t)0x03),
      _200HZ = ((uint8_t)0x04),
      _100HZ = ((uint8_t)0x05),
      _50HZ = ((uint8_t)0x06),
      _25HZ = ((uint8_t)0x07),
      _12_5HZ = ((uint8_t)0x08),
      _6_25HZ = ((uint8_t)0x09),  /*  6.25 HZ                                         */
      _3_125HZ = ((uint8_t)0x0a), /*  3.125 HZ                                        */
      _1_563HZ = ((uint8_t)0x0b), /*  1.563 HZ                                        */
      _0_781HZ = ((uint8_t)0x0c) /*  0.781 HZ                                        */
    };

    enum SensorRange  {
      _2G = 0,
      _4G,
      _8G,
      _16G
    };
    
    enum PowerMode {
      _LPM=0, _HPM, _FPM
    };
    
    enum XYZ {
      ___Z=1,
      __Y_,
      __YZ,
      _X__,
      _X_Z,
      _XY_,
      _XYZ
    };
    
    enum ref_updm {
      _UPDATEDR=0,    //!< Reference value is updated when SDCD_OT_EA flag transitions from false to true (SDCD interruption occurs). Reference+/-threshold is compared with acceleration value.
      _FIXEDREF,      //!< Reference value is fixed when SDCD function is enabled or REF_UPD bit is set. Reference+/-threshold is compared with acceleration value.
      _DIFFPREV,      //!< Delta between current and previous value is compared with threshold.
      _ABSOLUTE       //!< Reference is fixed and absolute acceleration value is compared with threshold.
    };
    
    SensorRange sensor_range = _2G;   //!< @brief Sensor range selected through 2g,4g,8g,16g
    PowerMode wake_pm = _LPM;         //!< @brief Power Mode in WAKE state selected from LPM, HPM, FPM
    PowerMode sleep_pm = _LPM;        //!< @brief Power Mode in SLEEP state selected from LPM, HPM, FPM
    odr_freq wake_odr = _100HZ;   //!< @brief ODR in WAKE state
    odr_freq sleep_odr = _12_5HZ; //!< @brief ODR in SLEEP state
    bool sdcd_wt=false;                       //!< @brief true when interruption happens inside thresholds, false when outside thresholds

    /**
    * @brief Read XYZ accelerometer value with unit milligravity
    * @param pOutBuffer Pointer to array to store register contents
    */
    void read_XYZ(float *pOutBuffer);

    /**
    * @brief Start conversion based on the settings of sensor_range, wake_pm, sleep_pm, wake_odr, sleep_odr
    * @param sdcd If you set SDCD mode (using SLEEP states), then put true here.
    */
    void run(bool sdcd=false);

    /**
    * @brief Set SDCD function
    * @param ref_updm
    * @param upper_threshold Upper threshold by milligravity
    * @param lower_threshold Lower threshold by milligravity
    * @param debounce Debounce counter threshold value set to both upper and lower threshold
    */
    void sdcd(ref_updm ref, XYZ xyz, float upper_threshold, float lower_threshold, uint8_t debounce=0);

    /**
    * @brief Sleep mode enable
    * @param asleep Asleep count threshold: The device goes to SLEEP state when count reaches to this threshold value. The count increments when no interruption occurs.
    */
    void enable_sleep(uint16_t asleep=0);

    /**
    * @brief Initialize the pin configurations and register for EXT_TRIG mode
    * @param pinconfig If you wouldn't like to config the pins by this function, put false in this parameter. This parameter can be skipped.
    */
    void EXT_TRIG_init(bool pinconfig=true);

    /**
    * @brief Trigger the pin to start one-time conversion. Make sure once EXT_TRIG init is done first.
    */
    void EXT_TRIG_Trigger();

    /**
    * @brief Initialize the device with reset
    * @param pinconfig If you wouldn't like to config the pins by this function, put false in this parameter. This parameter can be skipped.
    * @return WHO_AM_I register value
    */
    uint8_t init(bool pinconfig=true);

    /** Create a FXLS89xx_Arduino instance
	 * @param interface	I2C instance	
	 * @param i2c_address If the device is configured with SA0=H, put FXLS896x_DEVICE_ADDRESS_SA0_1.
    */
    FXLS89xx( I2C& interface, uint8_t i2c_address = FXLS89xx_I2C_ADDRESS_SA0_L );
	
  /** Destructor of FXLS89xx_Arduino
   */
  virtual ~FXLS89xx();

  #if DOXYGEN_ONLY
    /** Get temperature value in degree Celsius [°C] 
    *
    *	This method simply calls "temp()" method	
    *
    * @return temperature value in degree Celsius [°C] 
    */
    virtual float read( void );

    /** Ping the device
    *
    * @return true when ACK 
    */
    bool ping( void );
      
    /** Multiple register write
    * 
    * @param reg register index/address/pointer
    * @param data pointer to data buffer
    * @param size data size
    * @return transferred data size
    */
    int reg_w( uint8_t reg_adr, uint8_t *data, uint16_t size );

    /** Single register write
    * 
    * @param reg register index/address/pointer
    * @param data pointer to data buffer
    * @param size data size
    * @return transferred data size
    */
    int reg_w( uint8_t reg_adr, uint8_t data );

    /** Multiple register read
    * 
    * @param reg register index/address/pointer
    * @param data pointer to data buffer
    * @param size data size
    * @return transferred data size
    */
    int reg_r( uint8_t reg_adr, uint8_t *data, uint16_t size );

    /** Single register read
    * 
    * @param reg register index/address/pointer
    * @return read data
    */
    uint8_t	reg_r( uint8_t reg_adr );

    /** Register write, 8 bit
    *
    * @param reg register index/address/pointer
    * @param val data value
    */
    void write_r8( uint8_t reg, uint8_t val );

    /** Register write, 16 bit
    * 
    *	This 16 bit access may ot be common but it's useful for sensor devices
    *
    * @param reg register index/address/pointer
    * @param val data value
    */
    void write_r16( uint8_t reg, uint16_t val );

    /** Register read, 8 bit
    *
    * @param reg register index/address/pointer
    * @return data value
    */
    uint8_t read_r8( uint8_t reg );

    /** Register read, 16 bit
    *	
    *	This 16 bit access may ot be common but it's useful for sensor devices
    *
    * @param reg register index/address/pointer
    * @return data value
    */
    uint16_t read_r16( uint8_t reg );

    /** Register overwriting with bit-mask
    *	
    *	Register can be updated by bit level
    *
    * @param reg register index/address/pointer
    * @param mask bit-mask to protect overwriting
    * @param value value to overwrite
    */
    void bit_op8(  uint8_t reg,  uint8_t mask,  uint8_t value );
    void bit_op16( uint8_t reg, uint16_t mask, uint16_t value );
  #endif	// DOXYGEN_ONLY
};

#endif
