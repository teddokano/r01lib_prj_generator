/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

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

	printf( "%5.0fHz, %2.0f%%  ", pwm.frequency(), duty * 100 );

	for ( int i = 0; i < 10; i++ )
		printf( "%c", (i < (int)(duty * 10)) ? '*' : '_' );

	printf( "\r\n" );
}

int main( void )
{
	printf( "*** SoftPWM demo ***\r\n" );
	printf( "press SW2 to change frequency\r\n" );
	printf( "press SW3 to change duty cycle\r\n" );
	

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
