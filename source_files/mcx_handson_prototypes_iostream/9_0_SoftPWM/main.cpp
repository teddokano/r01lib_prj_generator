//FILEHEAD
#include	"r01lib.h"
#include	"SoftPWM/SoftPWM.h"

using namespace	std;

SoftPWM		pwm( BLUE );
InterruptIn	btn2( SW2 );
InterruptIn	btn3( SW3 );

volatile bool	event	= false;

void btn2_callback( void )
{
	static const vector	freq_v{ 1.0, 2.0, 10.0, 100.0 };
	static int			f_select	= 0;

	if ( event )	//	check if still in debounce interval
		return;

	f_select++;
	f_select	%= freq_v.size();
	pwm.frequency( freq_v[ f_select ] );	

	event	= true;
}

void btn3_callback( void )
{
	static int	duty	= 0x1;

	if ( event )	//	check if still in debounce interval
		return;

	duty	= (duty & 0x7) ? duty << 1 : 1;
	pwm.duty( duty / 10.0 );

	event	= true;
}

void show_current_setting( SoftPWM &pwm )
{
	const float	duty	= pwm.duty();

	cout << setw( 7 )
			<< pwm.frequency()
			<< "Hz, "
			<< setw( 2 )
			<< duty * 100
			<< "%  ";

	for ( int i = 0; i < 10; i++ )
		cout <<	((i < (int)(duty * 10)) ? "*" : "_");

	cout << endl;
}

int main( void )
{
	cout << "*** SoftPWM demo ***" << endl;
	cout << "press SW2 to change frequency" << endl;
	cout << "press SW3 to change duty cycle" << endl;
	cout << right;

	btn2.rise( btn2_callback );
	btn3.rise( btn3_callback );
	
	pwm.start();

	show_current_setting( pwm );

	while ( true )
	{
		if ( event )
		{
			show_current_setting( pwm );

			wait( 0.2 );		//	for debounce
			event	= false;	//	for debounce
		}
	}
}
