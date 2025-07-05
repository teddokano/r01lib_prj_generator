//FILEHEAD
#include	"r01lib.h"

DigitalOut	led( BLUE );

int main( void )
{
	std::cout << "Hello, world!" << std::endl;

	while ( true )
	{
		led	= PIN_LED_ON;
		wait( 0.5 );

		led	= PIN_LED_OFF;
		wait( 0.5 );
	}
}
