/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"SoftPWM.h"

SoftPWM::SoftPWM( int pin_name )
	: SoftPWM_base( pin_name, 1.0, 10, false, 0.1 )
{
}

SoftPWM& SoftPWM::operator=( float d )
{
	duty( d );
	return *this;
}

SoftPWM& SoftPWM::operator=( SoftPWM& )
{
	return *this;
}
