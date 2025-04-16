//FILEHEAD
#ifndef R01LIB_SOFTPWM_SOFTPWM_H
#define R01LIB_SOFTPWM_SOFTPWM_H

#include	"SoftPWM_base.h"

/** SoftPWM class
 *	
 *  @class SoftPWM
 *
 *	A software based PWM controls an output pin
 */

class SoftPWM : public SoftPWM_base
{
public:

	/** Create a SoftPWM instance with specified pin
	 *
	 * @param pin_num pin number
	 */
	SoftPWM( int pin_name );
	
	/** A short hand for setting pins
	 */
	SoftPWM&	operator=( float duty );
	SoftPWM&	operator=( SoftPWM& rhs );
};

#endif // R01LIB_SOFTPWM_SOFTPWM_H
