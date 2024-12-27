//FILEHEAD
#include	"r01lib.h"
#include	"led/PCA9955B.h"
#include	<math.h>
#include	<fstream>

using namespace	std;


I2C			i2c( A4, A5 );	//	SDA, SCL
PCA9955B	drv( i2c );

#define		PERIOD	100

int main( void )
{
	cout << "***** Hello, PCA9955B! *****" << endl;
	cout << "pi     = " << M_PI << endl;
	cout << "PERIOD = " << PERIOD << endl;

	drv.begin( 1.0, PCA9955B::ARDUINO_SHIELD );

	float	a, b, c;

	ofstream ofs( "test.csv" );
	
	while ( true )
	{
		for ( int i = 0; i < PERIOD; i++ )
		{
			a	= (2.0 * M_PI) * i / PERIOD;
			b	= sin( a );
			c	= 0.5 + 0.5 * b;

			ofs << i << ", " << a << ", " << b << ", " << c << endl;

			drv.pwm( 0, c );
			wait( 0.01 );
		}
	}
}
