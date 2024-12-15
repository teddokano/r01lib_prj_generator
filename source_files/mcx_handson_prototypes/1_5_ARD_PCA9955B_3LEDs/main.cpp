/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"r01lib.h"
#include	"led/PCA9955B.h"
#include	<math.h>

I2C			i2c( A4, A5 );	//	SDA, SCL
PCA9955B	drv( i2c );

#define		PERIOD	100

int main( void )
{
	printf( "***** Hello, PCA9955B! *****\r\n" );
	printf( "pi     = %f\r\n", M_PI   );
	printf( "PERIOD = %d\r\n", PERIOD );

	drv.begin( 1.0, PCA9955B::ARDUINO_SHIELD );

	float	a, b, c, d, x, y, z;


	while ( true )
	{
		for ( int i = 0; i < PERIOD; i++ )
		{
			a	= (2.0 * M_PI) * i / PERIOD;
			b	= sin( a + (2.0 * M_PI) * (0.0 / 3.0) * PERIOD );
			c	= sin( a + (2.0 * M_PI) * (1.0 / 3.0) * PERIOD );
			d	= sin( a + (2.0 * M_PI) * (2.0 / 3.0) * PERIOD );
			x	= 0.5 + 0.5 * b;
			y	= 0.5 + 0.5 * c;
			z	= 0.5 + 0.5 * d;

			drv.pwm( 0, x );
			drv.pwm( 4, y );
			drv.pwm( 8, z );
			wait( 0.01 );
		}
	}
}
