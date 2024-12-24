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

int main( void )
{
	printf( "***** Hello, FXLS89xx! *****\r\n" );
	printf( "Shows direction of tilt\r\n" );
	i2c.scan();

	sensor.init();

	sensor.wake_odr = FXLS89xx::_6_25HZ;
	sensor.wake_pm  = FXLS89xx::_HPM;
	sensor.sensor_range = FXLS89xx::_2G;
	sensor.run();

	float	sensor_data[ 3 ];
	float	theta;
	
	while ( true )
	{
		sensor.read_XYZ( sensor_data );

		theta	= atan2( sensor_data[ 0 ], sensor_data[ 1 ] );

		printf( "%f\r\n", theta / M_PI * 100 );
		wait( 0.2 );
	}
}
