/** TempSensor operation library for Arduino
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"
#include	"temp_sensor/P3T1755.h"

I2C		i2c( D18, D19 );	//	SDA, SCL
P3T1755	p3t1755( i2c, 0x4C );

int main( void )
{
	printf( "***** Hello, P3T1755! *****\r\n" );
	i2c.scan();

	float	temp;

	while ( true )
	{
		temp	= p3t1755;
		printf( "Temperature: %8.4f˚C\r\n", temp );

		wait( 1 );
	}
}
