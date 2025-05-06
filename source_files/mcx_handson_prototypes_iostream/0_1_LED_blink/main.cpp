//FILEHEAD
#include	"r01lib.h"

using namespace	std;

DigitalOut	led( BLUE );

int main( void )
{
	cout << "Hello, world!" << endl;

	while ( true )
	{
		led	= PIN_LED_ON;
		wait( 0.5 );

		led	= PIN_LED_OFF;
		wait( 0.5 );
	}
}
