/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"

using namespace	std;

class SoftPWM_base : public DigitalOut
{
public:
	using DigitalOut::operator=;

	SoftPWM_base( int pin_name, float frequency = 50.0, unsigned int resolution = 1000, bool polarity = true, float duty = 0.1 );
	virtual void	callback( void );
	virtual float	frequency( float f = 0.0 );
	virtual float	resolution( int r = -1 );
	virtual float	duty( float d = -1.0 );

protected:
	float	freq;
	int		res;
	bool	pol;
	float	duty_ratio;
	int		count;

private:
	Ticker	timer;
};

class SoftPWM : public SoftPWM_base
{
public:
	SoftPWM( int pin_name );
};

class ServoMotor : public SoftPWM_base
{
public:
	ServoMotor( int pin_name, float pulse_min = 0.5 / 1000.0, float pulse_max = 2.4 / 1000.0 );
	float	angle( float degree );
	float	angle( void );

private:
	float	min;
	float	range;
	float	deg;
};
