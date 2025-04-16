/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#ifndef R01LIB_SOFTPWM_BASE_H
#define R01LIB_SOFTPWM_BASE_H

#include	"r01lib.h"

/** SoftPWM_base class
 *	
 *  @class SoftPWM_base
 *
 *	A base class to making software based PWM using class. 
 *	Manages a ticker interrupt to make PWM output. 
 *	This class allows to make multiple instances but timing (frequency and resolution) is cannot be independent. 
 *	The frequency and resolution are common over the instances. 
 */

using	instance_callback_fp_t	= std::function<void(void)>;

class SoftPWM_base : public DigitalOut
{
public:
	using DigitalOut::operator=;

	/** Create a SoftPWM_base instance with specified pin
	 *
	 * @param pin_num pin number
	 * @param frequency (option) PWM frequency [Hz]
	 * @param resolution (option) resolution to control duty ratio
	 * @param polarity (option) pulse polarity: true=positive, false=negative
	 * @param duty (option) default duty ratio
	 */
	SoftPWM_base( int pin_name, float frequency = 50.0, unsigned int resolution = 1000, bool polarity = true, float duty = 0.1 );

	/** Duty ratio setting
	 *
	 * @param duty duty ratio, from 0.0 to 1.0, just returns current setting value if no argument given
	 * @return current setting value
	 */
	virtual float	duty( float d = -1.0 );

	/** Polarity setting
	 *
	 * @param p pulse polarity: true=positive, false=negative, just returns current setting value if no argument given
	 * @return current setting value
	 */
	virtual float	polarity( bool p );
	
	/** Frequency setting
	 * 
	 *	Class method to change PWM frequency
	 *
	 * @param f frequency for all software-based PWM controls, just returns current setting value if no argument given
	 * @return current setting value
	 */
	static float	frequency( float f = 0.0 );

	/** Resolution setting
	 * 
	 *	Class method to change duty-ratio resulution
	 *
	 * @param r resolution for all software-based PWM controls, just returns current setting value if no argument given
	 * @return current setting value
	 */
	static float	resolution( int r = -1 );
	
	/** Start PWM operation
	 */
	static void		start( void );

protected:
	virtual void	instance_callback( void );

	bool			pol;
	float			duty_ratio;

	static float	freq;
	static int		res;
	static int		count;
	static int		instance_count;

private:
	static void		class_callback( void );

	static Ticker	timer;
	static std::vector<instance_callback_fp_t>	cbs;
};


#endif // R01LIB_SOFTPWM_BASE_H
