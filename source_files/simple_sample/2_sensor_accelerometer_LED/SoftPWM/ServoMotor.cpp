/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"ServoMotor.h"

ServoMotor::ServoMotor( int pin_name, float pulse_width_min, float pulse_width_max, float angle_value_min, float angle_value_max )
	:	SoftPWM_base( pin_name, 50.0, 1000, true, 0.1 ), 
		min_pulse( pulse_width_min / (1.0 / freq) ),
		range_pulse( pulse_width_max  / (1.0 / freq) - min_pulse ),
		min_angle( angle_value_min ), 
		range_angle( angle_value_max - angle_value_min )
{
}

float ServoMotor::angle( float degree )
{
	deg	= degree;
	
	float	pulse_width	= ((degree - min_angle) / range_angle) * range_pulse + min_pulse;
	duty( pulse_width );
	
	return deg;
}

float ServoMotor::angle( void )
{
	return deg;
}

void ServoMotor::range( float min, float max )
{
	min_angle	= min;
	range_angle	= max - min;
}

ServoMotor& ServoMotor::operator=( float a )
{
	angle( a );
	return *this;
}

ServoMotor& ServoMotor::operator=( ServoMotor& )
{
	return *this;
}
