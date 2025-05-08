//FILEHEAD
#include	"r01lib.h"
#include	"SoftPWM/SoftPWM.h"

SoftPWM		pwm( BLUE );
InterruptIn	btn2( SW2 );
InterruptIn	btn3( SW3 );

volatile bool	event	= false;

void btn2_callback( void )
{
	static const std::vector	freq_v{ 1.0, 2.0, 10.0, 100.0 };
	static int					f_select	= 0;

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
	pwm		= ( duty / 10.0 );

	event	= true;
}

void show_current_setting( SoftPWM &pwm )
{
	const float	duty	= pwm.duty();

	std::cout	<< std::setw( 7 )
				<< pwm.frequency()
				<< "Hz, "
				<< std::setw( 2 )
				<< duty * 100
				<< "%  ";

	for ( int i = 0; i < 10; i++ )
		std::cout <<	((i < (int)(duty * 10)) ? "*" : "_");

	std::cout << std::endl;
}

int main( void )
{
	std::cout << "*** SoftPWM demo ***" << std::endl;
	std::cout << "press SW2 to change frequency" << std::endl;
	std::cout << "press SW3 to change duty cycle" << std::endl;
	std::cout << std::right;

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
