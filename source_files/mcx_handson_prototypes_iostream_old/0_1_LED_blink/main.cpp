//FILEHEAD
#include	"r01lib.h"

using namespace	std;

DigitalOut	led( BLUE );

int main( void )
{
	cout << "Hello, world!" << endl;

	while ( true )
	{
		led	= 1;
		wait( 0.5 );

		led	= 0;
		wait( 0.5 );
	}
}
