//FILEHEAD
#include	"r01lib.h"
#include	"accelerometer/FXLS89xx_Arduino.h"
#include	"SoftPWM/SoftPWM.h"
#include	"SoftPWM/ServoMotor.h"
#include	<math.h>
#define		M_PI	3.1415926535897

using namespace	std;

I2C			i2c( MB_SDA, MB_SCL );	//	SDA, SCL
FXLS89xx	sensor( i2c );

ServoMotor	srv[]	= { ServoMotor( A5 ), ServoMotor( A4 ) };
SoftPWM		red( RED );
SoftPWM		blue( BLUE );
DigitalIn	btn2( SW2 );
DigitalIn	btn3( SW3 );

constexpr int	filter_length	= 20;

class Filter
{
public:
	Filter( int length ) : data( new float[ length ] ), len( length ), index( 0 )
	{
		for ( auto i = 0; i < len; i++ )
			data[ i ]	= 0.0;
	}
	
	float	calc( float v )
	{
		data[ index++ ]	 = v;
		index			%= len;

		float	sum	= 0;
		for ( auto i = 0; i < len; i++ )
			sum	+= data[ i ];

		return	sum / (float)len;
	}
	
private:
	float	*data;
	int		len;
	int		index;
};

int main( void )
{
	cout << "*** ServoMotor demo ***" << endl;

	i2c.scan();

	srv[ 0 ].start();
	red.polarity( false );
	blue.polarity( true );

	sensor.init();
	sensor.wake_odr		= FXLS89xx::_100HZ;
	sensor.wake_pm		= FXLS89xx::_HPM;
	sensor.sensor_range	= FXLS89xx::_2G;
	sensor.run();

	float	sensor_data[ 3 ];
	float	theta[ 2 ];

	Filter	f0( filter_length ), f1( filter_length );

	while ( true )
	{
		sensor.read_XYZ( sensor_data );
		theta[ 0 ]	= atan2( sensor_data[ 0 ], sensor_data[ 1 ] );
		theta[ 1 ]	= atan2( sensor_data[ 0 ], sensor_data[ 2 ] );

		srv[ 0 ]	= f0.calc( (theta[ 0 ] / M_PI * 180.0) -90.0 );
		srv[ 1 ]	= f1.calc( (theta[ 1 ] / M_PI * 180.0) -90.0 );

		wait( 0.01 );
	}
}
