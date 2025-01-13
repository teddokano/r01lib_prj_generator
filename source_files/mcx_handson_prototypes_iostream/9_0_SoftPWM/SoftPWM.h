/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"

using namespace	std;

class SoftPWM : public DigitalOut
{
public:
	using DigitalOut::operator=;

	SoftPWM( int pin_name, float f = 1.0 );
	void callback( void );
	float frequency( float f = 0.0 );
	float duty( float d );
	float duty( void );

private:
	Ticker	timer;
	float	freq;
	float	duty_ratio;
	int		count;
};
