//FILEHEAD
#include	"r01lib.h"

using namespace	std;

DigitalOut	r( RED   );
DigitalOut	g( GREEN );
DigitalOut	b( BLUE  );

DigitalIn	btn( SW3 );

void output( int n )
{
	cout << n;

	if ( n == 0 )
	{
	   cout << "   \033[31mred\033[39m" << endl;

		r	= PIN_LED_ON;
		g	= PIN_LED_OFF;
		b	= PIN_LED_OFF;
	}

	if ( n == 1 )
	{
		cout << "   \033[32mgreen\033[39m" << endl;

		r	= PIN_LED_OFF;
		g	= PIN_LED_ON;
		b	= PIN_LED_OFF;
   }

	if ( n == 2 )
	{
		cout << "   \033[34mblue\033[39m" << endl;

		r	= PIN_LED_OFF;
		g	= PIN_LED_OFF;
		b	= PIN_LED_ON;
	}
}

int main( void )
{
	cout << "Hello, world!" << endl;
	cout << "Press button to change color" << endl;

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
