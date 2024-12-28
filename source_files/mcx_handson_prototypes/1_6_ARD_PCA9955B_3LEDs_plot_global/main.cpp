//FILEHEAD
#include	"r01lib.h"
#include	"led/PCA9955B.h"
#include	<math.h>

I2C			i2c( A4, A5 );	//	SDA, SCL
PCA9955B	drv( i2c );

#define		PERIOD	1000

float		x, y, z;

int main( void )
{
	printf( "***** Hello, PCA9955B! *****\r\n" );
	printf( "pi     = %f\r\n", M_PI   );
	printf( "PERIOD = %d\r\n", PERIOD );

	printf( "\r\nThis is a sample to demo the \"Global variables\" pane can plot variable values in plot\r\n" );
	printf( "Set sample rate to 500ms and watch the waveform of 'x', 'y' and 'z'\r\n" );

	drv.begin( 1.0, PCA9955B::ARDUINO_SHIELD );

	float	a, b, c, d;


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
