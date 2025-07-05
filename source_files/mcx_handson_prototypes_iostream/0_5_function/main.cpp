//FILEHEAD
#include	"r01lib.h"

DigitalOut	r( RED   );
DigitalOut	g( GREEN );
DigitalOut	b( BLUE  );

DigitalIn	btn( SW3 );

void output( int n )
{
	std::cout << n;

	if ( n == 0 )
	{
	   std::cout << "   \033[31mred\033[39m" << std::endl;

		r	= PIN_LED_ON;
		g	= PIN_LED_OFF;
		b	= PIN_LED_OFF;
	}

	if ( n == 1 )
	{
		std::cout << "   \033[32mgreen\033[39m" << std::endl;

		r	= PIN_LED_OFF;
		g	= PIN_LED_ON;
		b	= PIN_LED_OFF;
   }

	if ( n == 2 )
	{
		std::cout << "   \033[34mblue\033[39m" << std::endl;

		r	= PIN_LED_OFF;
		g	= PIN_LED_OFF;
		b	= PIN_LED_ON;
	}
}

int main( void )
{
	std::cout << "Hello, world!" << std::endl;
	std::cout << "Press button to change color" << std::endl;

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
