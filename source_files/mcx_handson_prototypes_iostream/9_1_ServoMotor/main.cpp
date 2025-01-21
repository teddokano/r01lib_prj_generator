/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"SoftPWM/ServoMotor.h"

using namespace	std;

ServoMotor	srv( A5 );
DigitalIn	btn2( SW2 );
DigitalIn	btn3( SW3 );

void show_current_setting( ServoMotor &srv )
{
	cout << setw( 7 )
			<< srv.angle()
			<< "°"
			<< endl;
}

int main( void )
{	cout << "*** ServoMotor demo ***" << endl;
	cout << "press SW2 for [+] direction" << endl;
	cout << "press SW3 for [-] direction" << endl;
	cout << right;

	srv.start();

	show_current_setting( srv );

	float	angle	= 0.0;

	srv.angle(  90.0 );
	wait( 0.5 );

	srv.angle( -90.0 );
	wait( 0.5 );

	srv.angle(  90.0 );
	wait( 0.5 );

	srv.angle( -90.0 );
	wait( 0.5 );


	while ( true )
	{
		if ( !btn2 || !btn3 )
		{
			angle	+= btn3 ? 1.0 : -1.0;

			angle	= angle >  90.0 ?  90.0 : angle;
			angle	= angle < -90.0 ? -90.0 : angle;

			srv.angle( angle );

			show_current_setting( srv );
		}
	}
}
