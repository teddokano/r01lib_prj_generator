//FILEHEAD
#include	"r01lib.h"
#include	"accelerometer/FXLS89xx_Arduino.h"
#include	<math.h>
#define		M_PI	3.1415926535897

I2C			i2c( MB_SDA, MB_SCL );	//	SDA, SCL
FXLS89xx	sensor( i2c );

int main( void )
{
	std::cout << "***** Hello, FXLS89xx! *****" << std::endl;
	std::cout << "Shows direction of tilt" << std::endl;
	i2c.scan();

	sensor.init();

	sensor.wake_odr		= FXLS89xx::_6_25HZ;
	sensor.wake_pm		= FXLS89xx::_HPM;
	sensor.sensor_range	= FXLS89xx::_2G;
	sensor.run();

	float	sensor_data[ 3 ];
	float	theta;
	
	while ( true )
	{
		sensor.read_XYZ( sensor_data );
		theta	= atan2( sensor_data[ 0 ], sensor_data[ 1 ] );
		
		std::cout << theta / M_PI * 180.0 << std::endl;
		
		wait( 0.2 );
	}
}
