//FILEHEAD
#include	"r01lib.h"

DigitalOut	r( RED   );
DigitalOut	g( GREEN );
DigitalOut	b( BLUE  );

DigitalIn	btn( SW3 );

int main( void )
{
	std::cout << "Hello, world!" << std::endl;
	std::cout << "Press button to change color" << std::endl;

	int	count	= 0;

	std::cout << count;
	std::cout << "   \033[31mred\033[39m" << std::endl;

	r	= PIN_LED_ON;
	g	= PIN_LED_OFF;
	b	= PIN_LED_OFF;

	while ( true )
	{
		if ( btn == 0 )
		{
			count	= (count + 1) % 3;

			std::cout << count;

			if ( count == 0 )
			{
				std::cout << "   \033[31mred\033[39m" << std::endl;

				r	= PIN_LED_ON;
				g	= PIN_LED_OFF;
				b	= PIN_LED_OFF;
			}

			if ( count == 1 )
			{
				std::cout << "   \033[32mgreen\033[39m" << std::endl;

				r	= PIN_LED_OFF;
				g	= PIN_LED_ON;
				b	= PIN_LED_OFF;
			}

			if ( count == 2 )
			{
				std::cout << "   \033[34mblue\033[39m" << std::endl;

				r	= PIN_LED_OFF;
				g	= PIN_LED_OFF;
				b	= PIN_LED_ON;
			}

			wait( 0.2 );
		}
	}
}
