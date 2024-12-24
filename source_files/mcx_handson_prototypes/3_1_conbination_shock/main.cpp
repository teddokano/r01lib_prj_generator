/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"led/PCA9955B.h"
#include	"accelerometer/FXLS89xx_Arduino.h"
#include	<math.h>

//
//	Since the FRDM-MCXN236 I2C on A4/A5 and MB_SDA/MB_SCL are using same peripheral unit.
//	However, the IO pins are assigned to different ones and those cannot be routed in parallel.
//	So, when this demo is being tried, connect following pins
//		1. PCA9955BTW-ARD J89 pin4 -- FRDM-MCXN236 J8 pin4
//		2. PCA9955BTW-ARD J89 pin2 -- FRDM-MCXN236 J8 pin3
//
I2C			i2c( A4, A5 );	//	SDA, SCL
PCA9955B	drv(    i2c );
FXLS89xx	sensor( i2c );

float	abs_g( float *data );

int main( void )
{
	printf( "***** Hello, PCA9955B and FXLS89xx! *****\r\n" );
	printf( "Shows direction of tilt in color\r\n" );
	i2c.scan();

	drv.begin( 1.0, PCA9955B::ARDUINO_SHIELD );

	sensor.init();

	sensor.wake_odr		= FXLS89xx::_100HZ;
	sensor.wake_pm		= FXLS89xx::_HPM;
	sensor.sensor_range	= FXLS89xx::_2G;
	sensor.run();

	float	sensor_data[ 3 ];
	float	a, b, c, theta;
	float	white	= 0;
	
	while ( true )
	{
		sensor.read_XYZ( sensor_data );

		theta	= atan2( sensor_data[ 0 ], sensor_data[ 1 ] );

		a	= sin( theta + (2.0 * M_PI) * (0.0 / 3.0) );
		b	= sin( theta + (2.0 * M_PI) * (1.0 / 3.0) );
		c	= sin( theta + (2.0 * M_PI) * (2.0 / 3.0) );
		a	= 0.5 + 0.5 * a;
		b	= 0.5 + 0.5 * b;
		c	= 0.5 + 0.5 * c;

		drv.pwm( 0, a * a );
		drv.pwm( 1, b * b );
		drv.pwm( 2, c * c );

		if ( abs_g( sensor_data ) > 1500 )
			white	= 1.0;

		drv.pwm( 15, white );

		white	*= 0.9;

		wait( 0.01 );
	}
}

float abs_g( float *data )
{
	float	g	= 0.0;

	for ( int i = 0; i < 3; i++ )
		g	+= pow( data[ i ], 2.0 );

	return pow( g, 0.5 );
}
