//FILEHEAD
#include	"r01lib.h"

using namespace	std;

DigitalOut	led( BLUE );
InterruptIn	btn2( SW2 );
InterruptIn	btn3( SW3 );
Ticker		t;

const vector	freq_v{ 1.0, 2.0, 10.0, 100.0 };
volatile bool	event	= false;
int				f_select	= 0;
int				duty		= 1;

void ticker_callback( void )
{
	static int	count	= 0;

	if ( (count++ % 10) < duty )
		led	= 0;
	else
		led	= 1;
}

void btn2_callback( void )
{
	f_select++;
	f_select	%= freq_v.size();
	t.attach( ticker_callback, 0.1 / freq_v[ f_select ] );	
	event	= true;
}

void btn3_callback( void )
{
	duty	= (duty & 0x7) ? duty << 1 : 1;
	event	= true;
}

int main( void )
{
	cout << "PWM demo" << endl;
	cout << "press SW2 to change frequency" << endl;
	cout << "press SW3 to change duty cycle" << endl;

	btn2.rise( btn2_callback );
	btn3.rise( btn3_callback );
	
	t.attach( ticker_callback, 0.1 / freq_v[ 0 ] );
		
	cout << freq_v[ f_select ] << "Hz, " << duty * 10 << "%" << endl;

	while ( true )
	{
		if ( event )
		{
			cout << freq_v[ f_select ] << "Hz, " << duty * 10 << "%" << endl;
			event	= false;
		}
	}
}
