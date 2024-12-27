//FILEHEAD
#include	"r01lib.h"

Ticker		t;
DigitalOut	led( GREEN );

void callback( void )
{
	led	= !led;
}

int main( void )
{
	PRINTF( "Check LED is blinking\r\n" );
	t.attach( callback, 0.1 );

	while ( true )
		;
}
