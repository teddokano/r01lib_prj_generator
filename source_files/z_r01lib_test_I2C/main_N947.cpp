/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"

I2C		i2c( I2C_SDA, I2C_SCL );

int main( void )
{
	PRINTF( "I2C output is available on D18/SDA and D19/SCL.\r\n" );
	PRINTF( "Pull-up resisters are required to connect I2C target(s)\r\n" );
	PRINTF( "\r\n" );
	PRINTF( "This code intended to communicate temp-sensor which has target address = 0x4C (0x98)\r\n" );

	constexpr uint8_t	address		= 0x4C;
	uint8_t				w_data[]	= { 0 };
	uint8_t				r_data[ 2 ];

	while ( true )
	{
		i2c.write( address, w_data, sizeof( w_data ), I2C::NO_STOP );
		i2c.read(  address, r_data, sizeof( r_data ) );

		PRINTF( "0x %02X %02X\r\n", r_data[ 0 ], r_data[ 1 ] );
		wait( 1 );
	}
}
