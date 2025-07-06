//FILEHEAD
#include	"r01lib.h"
#include	"accelerometer/FXLS89xx_Arduino.h"
#include	"SoftPWM/SoftPWM.h"
#include	<math.h>
#define		M_PI	3.1415926535897

using namespace	std;

I2C			i2c( MB_SDA, MB_SCL );	//	SDA, SCL
FXLS89xx	sensor( i2c );
SoftPWM		red( RED );
SoftPWM		green( GREEN );
SoftPWM		blue( BLUE );

int main( void )
{
	printf( "***** Hello, FXLS89xx! *****\r\n" );
	printf( "Shows direction of tilt in color\r\n" );

	i2c.scan();

	sensor.init();

	sensor.wake_odr		= FXLS89xx::_100HZ;
	sensor.wake_pm		= FXLS89xx::_HPM;
	sensor.sensor_range	= FXLS89xx::_2G;
	sensor.run();

	float	sensor_data[ 3 ];
	float	a, b, c, theta;
	
	red.resolution(   100.0 );
	green.resolution( 100.0 );
	blue.resolution(  100.0 );

	red.frequency(    50.0 );
	green.frequency(  50.0 );
	blue.frequency(   50.0 );

	red.start();
	
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

		red		= a * a;
		green	= b * b;
		blue	= c * c;

		wait( 0.05 );
	}
}
