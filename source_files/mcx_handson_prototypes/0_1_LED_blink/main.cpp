/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"

DigitalOut	led( BLUE );

int main( void )
{
	printf( "Hello, world!\r\n" );

	while ( true )
	{
		led	= 1;
		wait( 0.5 );

		led	= 0;
		wait( 0.5 );
	}
}
