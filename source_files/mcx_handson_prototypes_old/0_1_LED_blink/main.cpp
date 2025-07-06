//FILEHEAD
#include	"r01lib.h"

DigitalOut	led( BLUE );

int main( void )
{
	printf( "Hello, world!\r\n" );

	while ( true )
	{
		led	= PIN_LED_ON;
		wait( 0.5 );

		led	= PIN_LED_OFF;
		wait( 0.5 );
	}
}
