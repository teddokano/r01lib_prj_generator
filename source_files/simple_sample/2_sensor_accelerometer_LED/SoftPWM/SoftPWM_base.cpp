/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"SoftPWM_base.h"

float	SoftPWM_base::freq	= 50.0;
int		SoftPWM_base::res	= 1000;
int		SoftPWM_base::count	= 0;
int		SoftPWM_base::instance_count	= 0;
Ticker	SoftPWM_base::timer;
std::vector<instance_callback_fp_t>	SoftPWM_base::cbs;

SoftPWM_base::SoftPWM_base( int pin_name, float f, unsigned int r, bool polarity, float duty )
	: DigitalOut( pin_name ), pol( polarity ), duty_ratio( duty )
{
	if ( !instance_count )
	{
		freq	= f;
		res		= r;
	}
	
	instance_count++;
	cbs.push_back( [this](void){ instance_callback(); } );
}

void SoftPWM_base::instance_callback( void )
{
	if ( count < (int)(duty_ratio * (float)res) )
	{
		*this	= pol;
	}
	else
	{
		*this	= !pol;
	}
}

void SoftPWM_base::class_callback( void )
{
	for ( auto&& func: cbs )
		func();
	
	count++;
	count	%= res;
}

float SoftPWM_base::frequency( float f )
{
	if ( f != 0.0 )
	{
		freq	= f;
		timer.attach( class_callback, (1.0 / (float)res) / freq );
	}

	return freq;
}

void SoftPWM_base::start( void )
{
	frequency( freq );
}

float SoftPWM_base::duty( float d )
{
	if ( !( d < 0.0 ) )
		duty_ratio	= d;

	return duty_ratio;
}

float SoftPWM_base::polarity( bool p )
{
	return pol	= p;
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
