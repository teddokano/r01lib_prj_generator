/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"

using	instance_callback_fp_t	= std::function<void(void)>;

class SoftPWM_base : public DigitalOut
{
public:
	using DigitalOut::operator=;

	SoftPWM_base( int pin_name, float frequency = 50.0, unsigned int resolution = 1000, bool polarity = true, float duty = 0.1 );
	virtual float	duty( float d = -1.0 );
	virtual float	polarity( bool p );
	virtual void	instance_callback( void );

	static float	frequency( float f = 0.0 );
	static float	resolution( int r = -1 );
	static void		class_callback( void );
	static void		start( void );

	static int		instance_count;

protected:
	bool			pol;
	float			duty_ratio;

	static float	freq;
	static int		res;
	static int		count;

private:
	static Ticker	timer;
	static std::vector<instance_callback_fp_t>	cbs;
};



class SoftPWM : public SoftPWM_base
{
public:
	SoftPWM( int pin_name );
	
	SoftPWM&	operator=( float duty );
	SoftPWM&	operator=( SoftPWM& rhs );
};



class ServoMotor : public SoftPWM_base
{
public:
	ServoMotor( int pin_name, float pulse_min = 0.5 / 1000.0, float pulse_max = 2.4 / 1000.0 );
	float	angle( float degree );
	float	angle( void );

	ServoMotor&	operator=( float duty );
	ServoMotor&	operator=( ServoMotor& rhs );

private:
	float	min;
	float	range;
	float	deg;
};


