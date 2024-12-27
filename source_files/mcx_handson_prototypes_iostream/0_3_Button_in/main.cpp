/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
using namespace	std;

DigitalIn	btn( SW3 );

int main( void )
{
	cout << "Hello, world!" << endl;
	cout << "Press button (SW3) to show the count" << endl;

	int	count	= 0;

	while ( true )
	{
		if ( btn == 0 )
		{
			++count;

			cout << count << endl;

			wait( 0.2 );
		}
	}
}
