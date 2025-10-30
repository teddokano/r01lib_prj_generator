/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#ifndef R01LIB_SOFTPWM_SERVOMOTOR_H
#define R01LIB_SOFTPWM_SERVOMOTOR_H

#include	"SoftPWM_base.h"

/** ServoMotor class
 *	
 *  @class ServoMotor
 *
 *	A software based PWM controls a ServoMotor
 */

class ServoMotor : public SoftPWM_base
{
public:

	/** Create a SoftPWM_base instance with specified pin
	 *
	 * @param pin_num pin number
	 * @param pulse_width_min (option) minimum pulse width [sec]
	 * @param pulse_width_mmax (option) maximum pulse width [sec]
	 */
	ServoMotor( int pin_name, float pulse_width_min = 0.5 / 1000.0, float pulse_width_max = 2.4 / 1000.0, float angle_value_min = -90.0, float angle_value_max = 90.0 );

	/** Set angle
	 *
	 * @param a angle to set
	 * @return current setting value
	 */
	float	angle( float a );

	/** Get angle
	 *
	 * @return current setting value
	 */
	float	angle( void );

	/** Set angle value range
	 *
	 * @param min minimum value to set angle
	 * @param max maximum value to set angle
	 */
	void	range( float min, float max );

	ServoMotor&	operator=( float duty );
	ServoMotor&	operator=( ServoMotor& rhs );

private:
	float	min_pulse;
	float	range_pulse;
	float	min_angle;
	float	range_angle;
	float	deg;
};

#endif // R01LIB_SOFTPWM_SERVOMOTOR_H
