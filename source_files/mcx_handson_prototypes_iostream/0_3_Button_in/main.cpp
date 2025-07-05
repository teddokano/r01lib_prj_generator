//FILEHEAD
#include	"r01lib.h"

DigitalIn	btn( SW3 );

int main( void )
{
	std::cout << "Hello, world!" << std::endl;
	std::cout << "Press button (SW3) to show the count" << std::endl;

	int	count	= 0;

	while ( true )
	{
		if ( btn == 0 )
		{
			++count;

			std::cout << count << std::endl;

			wait( 0.2 );
		}
	}
}
