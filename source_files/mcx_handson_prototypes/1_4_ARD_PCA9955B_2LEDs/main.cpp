/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
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

	float	a, b, c, d;

	while ( true )
	{
		for ( int i = 0; i < PERIOD; i++ )
		{
			a	= (2.0 * M_PI) * i / PERIOD;
			b	= sin( a );
			c	= 0.5 + 0.5 * b;
			d	= 0.5 - 0.5 * b;

			drv.pwm( 0, c );
			drv.pwm( 4, d );
			wait( 0.01 );
		}
	}
}
