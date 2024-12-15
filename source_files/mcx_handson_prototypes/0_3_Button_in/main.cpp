/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"

DigitalIn	btn( SW3 );

int main( void )
{
	printf( "Hello, world!\r\n" );
	printf( "Press button (SW3) to show the count\r\n" );

	int	count	= 0;

	while ( true )
	{
		if ( btn == 0 )
		{
			++count;

			printf( "%d\r\n", count );
			wait( 0.2 );
		}
	}
}
