/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"accelerometer/FXLS89xx_Arduino.h"
#include	<math.h>

I2C			i2c( MB_SDA, MB_SCL );	//	SDA, SCL
FXLS89xx	sensor( i2c );

float	abs_g( float *data );

int main( void )
{
	printf( "***** Hello, FXLS89xx! *****\r\n" );
	i2c.scan();

	sensor.init();

	sensor.wake_odr 	= FXLS89xx::_6_25HZ;
	sensor.wake_pm  	= FXLS89xx::_HPM;
	sensor.sensor_range = FXLS89xx::_2G;
	sensor.run();

	float	sensor_data[ 3 ];
	
	while ( true )
	{
		sensor.read_XYZ( sensor_data );

		printf( "%f, %f, %f, %f\r\n", sensor_data[ 0 ], sensor_data[ 1 ], sensor_data[ 2 ], abs_g( sensor_data ) );
		wait( 0.2 );
	}
}

float abs_g( float *data )
{
	float	g	= 0.0;

	for ( int i = 0; i < 3; i++ )
		g	+= pow( data[ i ], 2.0 );

	return pow( g, 0.5 );
}
