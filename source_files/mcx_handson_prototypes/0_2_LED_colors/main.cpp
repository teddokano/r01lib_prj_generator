//FILEHEAD
#include	"r01lib.h"

DigitalOut	r( RED   );
DigitalOut	g( GREEN );
DigitalOut	b( BLUE  );

int main( void )
{
	printf( "Hello, world!\r\n" );

	while ( true )
	{
		r	= 0;
		g	= 1;
		b	= 1;
		wait( 0.5 );

		r	= 1;
		g	= 0;
		b	= 1;
		wait( 0.5 );

		r	= 1;
		g	= 1;
		b	= 0;
		wait( 0.5 );
	}
}
