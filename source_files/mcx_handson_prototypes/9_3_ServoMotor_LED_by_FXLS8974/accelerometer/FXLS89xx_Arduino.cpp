/*
 * Copyright 2024 ryraki
 * All rights reserved.
 *
 *	ported to r01lib project on FRDM-MCXN236 / Tedd OKANO (2024-Dec-24) 
 *
 * SPDX-License-Identifier: MIT
 */
/**
 * @file FXLS89xx_Arduino.cpp
 * @brief This file contains the functions for FXLS89xx Accelerometer evaluation by Arduino
 */
 
#include "accelerometer/FXLS89xx_Arduino.h"
#include <cmath>

#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic ignored "-Wnarrowing"

FXLS89xx::FXLS89xx(I2C & wire, uint8_t i2c_address):I2C_device(wire, i2c_address) {}
FXLS89xx::~FXLS89xx() {} 

void FXLS89xx::run(bool sdcd)
{
	bit_op8 (_SENS_CONFIG1, ~SENS_CONFIG1::ACTIVE_MASK, 0);
	bit_op8 (_SENS_CONFIG1, ~SENS_CONFIG1::FSR_MASK, sensor_range << SENS_CONFIG1::FSR_SHIFT);
	bit_op8 (_SENS_CONFIG2, ~(SENS_CONFIG2::SLEEP_PM_MASK | SENS_CONFIG2::WAKE_PM_MASK), 
			(wake_pm << SENS_CONFIG2::WAKE_PM_SHIFT) | (sleep_pm << SENS_CONFIG2::SLEEP_PM_SHIFT));
		
	write_r8 (_SENS_CONFIG3, (wake_odr << SENS_CONFIG3::WAKE_ODR_SHIFT) | sleep_odr);
		
	if (!sdcd)
		bit_op8 (_INT_EN, ~INT_EN::DRDY_EN_EN, INT_EN::DRDY_EN_EN);
		
	bit_op8 (_SENS_CONFIG1, ~SENS_CONFIG1::ACTIVE_ACT, SENS_CONFIG1::ACTIVE_ACT);
} 

void FXLS89xx::sdcd(ref_updm ref, XYZ xyz, float upper_threshold, float lower_threshold, uint8_t debounce)
{
	//Set upper threshold 
	uint16_t upper_threshold_12bit = upper_threshold / 0.98 / pow (2, sensor_range);
	if (upper_threshold > 1024 * pow (2, sensor_range + 1))
		upper_threshold_12bit = 0x07ff;
	else if (upper_threshold < -1024 * pow (2, sensor_range + 1))
		upper_threshold_12bit = 0x0800;
    
	//Serial.println (upper_threshold_12bit, HEX);
    
	//Set lower threshold 
	uint16_t lower_threshold_12bit = lower_threshold / 0.98 / pow (2, sensor_range);
    
	if (lower_threshold > 1024 * pow (2, sensor_range + 1))
		lower_threshold_12bit = 0x07ff;
	else if (lower_threshold < -1024 * pow (2, sensor_range + 1))
		lower_threshold_12bit = 0x0800;
    
	//Serial.println (lower_threshold_12bit, HEX);
    
	
	//Set configuration of debounce counters and lower / upper thresholds 
	uint8_t reg[6] =
    {
		debounce, 
		debounce, 
		lower_threshold_12bit & 0xff, 
		lower_threshold_12bit >> 8, 
		upper_threshold_12bit & 0xff, 
		upper_threshold_12bit >> 8
    };
    
	reg_w (_SDCD_OT_DBCNT, reg, 6);
    
	uint8_t sdcd_conf[2] =
    {
	    xyz << 3 | xyz, 
		ref << SDCD_CONFIG2::REF_UPDM_SHIFT | SDCD_CONFIG2::SDCD_EN_EN 
    };
    
	reg_w (_SDCD_CONFIG1, sdcd_conf, 2);
    
	//Serial.println (sdcd_conf[1], HEX);
    
	
	//Route SDCD interruption to INT2 
	bit_op8 (_INT_EN, 
		~(INT_EN::SDCD_WT_EN_EN | INT_EN::SDCD_OT_EN_EN), 
		sdcd_wt ? INT_EN ::SDCD_WT_EN_EN:INT_EN::SDCD_OT_EN_EN);
    
	
	bit_op8 (_INT_PIN_SEL, 
		~(INT_PIN_SEL::SDCD_WT_INT2_INT2 | INT_PIN_SEL::SDCD_OT_INT2_INT2), 
		sdcd_wt ? INT_PIN_SEL ::SDCD_WT_INT2_INT2:INT_PIN_SEL::SDCD_OT_INT2_INT2);
} 

void FXLS89xx::enable_sleep(uint16_t asleep)
{
	uint8_t aslp_reg[2] =
    {
		asleep & 0xff, 
		asleep >> 8
    };
    
	reg_w (_ASLP_COUNT_LSB, aslp_reg, 2);
		
	bit_op8 (_SENS_CONFIG4, ~(SENS_CONFIG4::WK_SDCD_OT_EN | SENS_CONFIG4::WK_SDCD_WT_EN), 
	sdcd_wt ? SENS_CONFIG4 ::WK_SDCD_WT_EN:SENS_CONFIG4::WK_SDCD_OT_EN);
} 

void FXLS89xx::read_XYZ(float *pOutBuffer)
{
	uint8_t output[6];
    
	reg_r (_OUT_X_LSB, output, 6);
    
	for (int i = 0; i < 3; i++)
    {
	    if (output[2 * i + 1] & 0xf8)
			pOutBuffer[i] = ((float)((((uint8_t) ~ output[2 * i + 1]) & 0x0f) << 8) + ((uint8_t) ~ output[2 * i]) + 1) * (-0.98) * (sensor_range + 1);
	    else
		    pOutBuffer[i] = ((float)(((uint8_t) output[2 * i + 1] & 0x0f) << 8) + (uint8_t) output[2 * i]) * 0.98 * (sensor_range + 1);
    } 
} 

void FXLS89xx::EXT_TRIG_init(bool pinconfig)
{
	DigitalOut	pin( A0, 0 );
    
	bit_op8 (_SENS_CONFIG1, ~SENS_CONFIG1::ACTIVE_MASK, 0);
	bit_op8 (_INT_EN, ~INT_EN::DRDY_EN_EN, INT_EN::DRDY_EN_EN);
	bit_op8 (_SENS_CONFIG4, 0, SENS_CONFIG4::EXT_TRIG_M_M | SENS_CONFIG4::INT2_FUNC_EXT | SENS_CONFIG4::INT_POL_ACT_H);
} 

void FXLS89xx::EXT_TRIG_Trigger()
{    
	DigitalInOut	pin(A0);
    
	pin.mode (DigitalInOut::INPUT);
	wait (0.001);
	pin.mode (DigitalInOut::OUTPUT);
    
} 

uint8_t FXLS89xx::init(bool pinconfig)
{
	DigitalIn	pin(D2);
    
	write_r8 (_SENS_CONFIG1, SENS_CONFIG1::RST_RESET);
    
	//while (!pin);
	//while (pin);
	wait (0.1);
    
	return read_r8 (_WHO_AM_I);
} 
