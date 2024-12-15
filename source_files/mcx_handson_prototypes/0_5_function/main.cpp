/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"

DigitalOut	r( RED   );
DigitalOut	g( GREEN );
DigitalOut	b( BLUE  );

DigitalIn	btn( SW3 );

void output( int n )
{
   printf( "%d   ", n );

   if ( n == 0 )
   {
	   printf( "\033[31mred\033[39m\r\n" );

	   r	= 0;
	   g	= 1;
	   b	= 1;
   }

   if ( n == 1 )
   {
	   printf( "\033[32mgreen\033[39m\r\n" );

	   r	= 1;
	   g	= 0;
	   b	= 1;
   }

   if ( n == 2 )
   {
	   printf( "\033[34mblue\033[39m\r\n" );

	   r	= 1;
	   g	= 1;
	   b	= 0;
   }
}

int main( void )
{
	printf( "Hello, world!\r\n" );
	printf( "Press button to change color\r\n" );

	int	count	= 0;

	output( count );

	while ( true )
	{
		if ( btn == 0 )
		{
			output( ++count % 3 );
			wait( 0.2 );
		}
	}
}
