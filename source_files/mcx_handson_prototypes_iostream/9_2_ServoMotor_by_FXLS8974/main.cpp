//FILEHEAD
#include	"r01lib.h"
#include	"accelerometer/FXLS89xx_Arduino.h"
#include	"SoftPWM/SoftPWM.h"
#include	<math.h>

using namespace	std;

I2C			i2c( MB_SDA, MB_SCL );	//	SDA, SCL
FXLS89xx	sensor( i2c );
ServoMotor	srv( A5 );
DigitalIn	btn2( SW2 );
DigitalIn	btn3( SW3 );

int main( void )
{
	cout << "*** ServoMotor demo ***" << endl;

	i2c.scan();

	srv.start();

	sensor.init();
	sensor.wake_odr		= FXLS89xx::_25HZ;
	sensor.wake_pm		= FXLS89xx::_HPM;
	sensor.sensor_range	= FXLS89xx::_2G;
	sensor.run();

	float	sensor_data[ 3 ];
	float	theta;

	while ( true )
	{
		sensor.read_XYZ( sensor_data );
		theta	= atan2( sensor_data[ 0 ], sensor_data[ 1 ] );

//		cout << theta / M_PI * 180.0 << endl;

		srv.angle( (theta / M_PI * 180.0) -90.0 );

		wait( 0.04 );
	}
}
