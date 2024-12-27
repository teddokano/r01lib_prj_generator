/** test code for r01lib
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
using namespace	std;

class	Blink : public DigitalOut
{
public:
	using DigitalInOut::operator=;

	Blink( int pin, int count ) : DigitalOut( pin ), repeat( count ) {}
	~Blink() {}

	void count( int count )
	{
		repeat	= count;
	}

	void blink( void )
	{
		for ( int i = 0; i < repeat; i++ )
		{
			*this	= 0;
			wait( 0.1 );

			*this	= 1;
			wait( 0.1 );
		}
	}

private:
	int			repeat;
};

Blink	r( RED,   1 );
Blink	g( GREEN, 2 );
Blink	b( BLUE,  3 );

int main( void )
{
	cout << "Hello, Blink class!" << endl;

	while ( true )
	{
		for ( int i = 0; i < 5; i++ )
		{
			r	= 0;
			wait( 0.1 );
			r	= 1;
			wait( 0.1 );

			g	= 0;
			wait( 0.1 );
			g	= 1;
			wait( 0.1 );

			b	= 0;
			wait( 0.1 );
			b	= 1;
			wait( 0.1 );
		}

		wait( 0.5 );

		for ( int i = 0; i < 5; i++ )
		{
			r.blink();
			wait( 0.5 );

			g.blink();
			wait( 0.5 );

			b.blink();
			wait( 0.5 );
		}
	}
}
