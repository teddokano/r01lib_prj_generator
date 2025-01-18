/*
*  @author Tedd OKANO
*
*  Released under the MIT license License
*/

#include	"r01lib.h"
#include	"SoftPWM.h"

SoftPWM_base::SoftPWM_base( int pin_name, float frequency, unsigned int resolution, bool polarity, float duty )
	: DigitalOut( pin_name ), freq( frequency ), res( resolution ), pol( polarity ), duty_ratio( duty ), count( 0 )
{
}

void SoftPWM_base::callback( void )
{
	if ( (count++ % res) < (int)(duty_ratio * (float)res) )
		*this	= pol;
	else
		*this	= !pol;
}

float SoftPWM_base::frequency( float f )
{
	if ( f != 0.0 )
	{
		freq	= f;
		timer.attach( [this](void){ callback(); }, (1.0 / (float)res) / freq );
	}

	return freq;
}

float SoftPWM_base::duty( float d )
{
	if ( !( d < 0.0 ) )
		duty_ratio	= d;

	return duty_ratio;
}

float SoftPWM_base::resolution( int r )
{
	if ( r )
	{
		res	= r;
		frequency( freq );
	}

	return res;
}

SoftPWM::SoftPWM( int pin_name )
	: SoftPWM_base( pin_name, 1.0, 10, false, 0.1 )
{
}

ServoMotor::ServoMotor( int pin_name, float pulse_min, float pulse_max )
	: SoftPWM_base( pin_name, 50.0, 1000, true, 0.1 ), min( pulse_min / (1.0 / freq) ), range( pulse_max  / (1.0 / freq) - min )
{
}

float ServoMotor::angle( float degree )
{
	deg	= degree;
	
	float	pulse_width	= ((degree + 90.0) / 180.0) * range + min;
	duty( pulse_width );
	
	return deg;
}

float ServoMotor::angle( void )
{
	return deg;
}
