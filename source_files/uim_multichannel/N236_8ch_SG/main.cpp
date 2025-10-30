/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"SoftPWM/SoftPWM.h"
#include	<math.h>

constexpr auto	pwm_frequency	= 800.00;
constexpr auto	pwm_resolution	= 100.00;
constexpr auto	period			= (int)pwm_frequency * 2;
constexpr auto	delay			= 1.00 / pwm_frequency;

constexpr auto	frequency		= 1.00;

constexpr auto	pi2				= 2.00 * 3.1415926 * frequency;
constexpr auto	pi4				= 2.00 * pi2;

constexpr auto	phase0			= 0.00 / 3.00;
constexpr auto	phase1			= 1.00 / 3.00;
constexpr auto	phase2			= 2.00 / 3.00;

constexpr auto	out0			= D0;
constexpr auto	out1			= D1;
constexpr auto	out2			= D2;
constexpr auto	out3			= D3;
constexpr auto	out4			= D4;
constexpr auto	out5			= D5;
constexpr auto	out6			= D6;
constexpr auto	out7			= D7;

SoftPWM	s[]	= {
		SoftPWM( out0 ),
		SoftPWM( out1 ),
		SoftPWM( out2 ),
		SoftPWM( out3 ),
		SoftPWM( out4 ),
		SoftPWM( out5 ),
		SoftPWM( out6 ),
		SoftPWM( out7 ),
};

InterruptIn	btn2( SW2 );
InterruptIn	btn3( SW3 );

double	biased_sin( int count, double frequency, double phase, double offset = 0.5, double amplitude = 1.0 )
{
	return	offset + 0.50 * amplitude * sin( frequency * count / period + frequency * phase );
}

double	sawtooth( int count, double amplitude = 1.0 )
{
	return	amplitude * count / period;
}

double	square( int count, double amplitude = 1.0 )
{
	return	count < (period / 2) ? 0.00 : amplitude;
}

int main( void )
{
	for ( auto i = 0U; i < sizeof( s ) / sizeof( SoftPWM ); i++ )
	{
		s[ i ].frequency( pwm_frequency );
		s[ i ].resolution( pwm_resolution );
		s[ i ].polarity( true );
	}
	s[ 0 ].start();

	while ( true )
	{
		for ( auto i = 0; i < period; i++ )
		{
			s[ 0 ]	= biased_sin( i, pi4, phase0 );
			s[ 1 ]	= biased_sin( i, pi4, phase1 );
			s[ 2 ]	= biased_sin( i, pi4, phase2 );
			s[ 3 ]	= biased_sin( i, pi2, phase0 );
			s[ 4 ]	= biased_sin( i, pi2, phase1 );
			s[ 5 ]	= biased_sin( i, pi2, phase2 );
			s[ 6 ]	= sawtooth( i );
			s[ 7 ]	= square( i );
			wait( delay );
		}
	}
}
