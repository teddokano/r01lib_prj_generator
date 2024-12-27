/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"led/PCA9955B.h"
using namespace	std;

I2C			i2c( A4, A5 );	//	SDA, SCL
PCA9955B	drv( i2c );

int main( void )
{
	cout << "***** Hello, PCA9955B! *****" << endl;

	drv.begin( 1.0, PCA9955B::ARDUINO_SHIELD );

	while ( true )
	{
		for ( float v = 0.0; v <=1.0; v += 0.01 )
		{
			drv.pwm( 0, v );
			wait( 0.01 );
		}
	}
}
