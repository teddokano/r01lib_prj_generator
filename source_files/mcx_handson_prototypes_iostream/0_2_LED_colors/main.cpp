//FILEHEAD
#include	"r01lib.h"

DigitalOut	r( RED   );
DigitalOut	g( GREEN );
DigitalOut	b( BLUE  );

int main( void )
{
	std::cout << "Hello, world!" << std::endl;

	while ( true )
	{
		r	= PIN_LED_ON;
		g	= PIN_LED_OFF;
		b	= PIN_LED_OFF;
		wait( 0.5 );

		r	= PIN_LED_OFF;
		g	= PIN_LED_ON;
		b	= PIN_LED_OFF;
		wait( 0.5 );

		r	= PIN_LED_OFF;
		g	= PIN_LED_OFF;
		b	= PIN_LED_ON;
		wait( 0.5 );
	}
}
