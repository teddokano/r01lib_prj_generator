/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"
#include	"SoftPWM.h"

using namespace	std;

InterruptIn	btn2( SW2 );
InterruptIn	btn3( SW3 );

volatile bool	event	= false;

SoftPWM	pwm( BLUE );

void btn2_callback( void )
{
	static const vector	freq_v{ 1.0, 2.0, 10.0, 100.0 };
	static int			f_select	= 0;

	if ( event )
		return;

	f_select++;
	f_select	%= freq_v.size();
	pwm.frequency( freq_v[ f_select ] );	

	event	= true;
}

void btn3_callback( void )
{
	static int	duty	= 0x1;

	if ( event )
		return;

	duty	= (duty & 0x7) ? duty << 1 : 1;
	pwm.duty( duty / 10.0 );

	event	= true;
}

int main( void )
{
	cout << "PWM demo" << endl;
	cout << "press SW2 to change frequency" << endl;
	cout << "press SW3 to change duty cycle" << endl;

	btn2.rise( btn2_callback );
	btn3.rise( btn3_callback );
	
	pwm.frequency( 1.0 );

	cout << pwm.frequency() << "Hz, " << pwm.duty() * 100 << "%" << endl;

	while ( true )
	{
		if ( event )
		{
			cout << pwm.frequency() << "Hz, " << pwm.duty() * 100 << "%" << endl;
			wait( 0.2 );
			event	= false;
		}
	}
}
