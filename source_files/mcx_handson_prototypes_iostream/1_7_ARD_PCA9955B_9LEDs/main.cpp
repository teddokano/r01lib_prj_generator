/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"
#include	"led/PCA9955B.h"
#include	<math.h>

using namespace	std;

I2C			i2c( A4, A5 );	//	SDA, SCL
PCA9955B	drv( i2c );

constexpr int	period	= 100;
constexpr float	pi2		= 2.0 * M_PI;
constexpr float	amp		= 0.5;
constexpr float	offset	= 0.5;

float	sin_wave_value( float phase );

int main( void )
{
#if 0
	cout << "***** Hello, PCA9955B! *****" << endl;
	cout << "pi2     = " << pi2 << endl;
	cout << "period = " << period << endl;
#endif

	drv.begin( 1.0, PCA9955B::ARDUINO_SHIELD );

	while ( true )
	{
		for ( int i = 0; i < period; i++ )
		{
			for ( int ch = 0; ch < 9; ch++ )
			{
				drv.pwm( ch, sin_wave_value( (float)i / (float)period + (ch % 3) / 3.0) );
			}			
			wait( 0.01 );
		}
	}
}

float sin_wave_value( float phase )
{
	return	offset + amp * sin( pi2 * phase );
}