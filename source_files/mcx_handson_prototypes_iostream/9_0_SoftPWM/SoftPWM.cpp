/*
*  @author Tedd OKANO
*
*  Released under the MIT license License
*/

#include	"r01lib.h"
#include	"SoftPWM.h"

SoftPWM::SoftPWM( int pin_name, float f )
	: DigitalOut( pin_name ), duty_ratio( 0.1 ), count( 0 )
{
}

void SoftPWM::callback( void )
{
	if ( (count++ % 10) < (int)(duty_ratio * 10.0) )
		*this	= 0;
	else
		*this	= 1;
}

float SoftPWM::frequency( float f )
{
	if ( f != 0.0 )
	{
		freq	= f;
		timer.attach( [this](void){ callback(); }, 0.1 / freq );
	}

	return freq;
}

float SoftPWM::duty( float d )
{
	return duty_ratio	= d;
}

float SoftPWM::duty( void )
{
	return duty( duty_ratio	);
}
