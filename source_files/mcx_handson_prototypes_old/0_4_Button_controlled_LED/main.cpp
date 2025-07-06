//FILEHEAD
#include	"r01lib.h"

DigitalOut	r( RED   );
DigitalOut	g( GREEN );
DigitalOut	b( BLUE  );

DigitalIn	btn( SW3 );

int main( void )
{
	printf( "Hello, world!\r\n" );
	printf( "Press button to change color\r\n" );

	int	count	= 0;

	printf( "%d   ", count );
	printf( "\033[31mred\033[39m\r\n" );

	
	while ( true )
	{
		if ( btn == 0 )
		{
			count	= (count + 1) % 3;
			
			printf( "%d   ", count );

			if ( count == 0 )
			{
				printf( "\033[31mred\033[39m\r\n" );

				r	= PIN_LED_ON;
				g	= PIN_LED_OFF;
				b	= PIN_LED_OFF;
			}

			if ( count == 1 )
			{
				printf( "\033[32mgreen\033[39m\r\n" );

				r	= PIN_LED_OFF;
				g	= PIN_LED_ON;
				b	= PIN_LED_OFF;
			}

			if ( count == 2 )
			{
				printf( "\033[34mblue\033[39m\r\n" );

				r	= PIN_LED_OFF;
				g	= PIN_LED_OFF;
				b	= PIN_LED_ON;
			}

			wait( 0.2 );
		}
	}
}
