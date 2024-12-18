/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include	"r01lib.h"
#include	"rtc/PCF2131.h"
#include	"rtc/tzcode/strptime.h"
#include	<time.h>

I2C			i2c( I2C_SDA, I2C_SCL );	//	SDA, SCL
PCF2131		rtc( i2c );

void	set_time( void );

int main( void )
{
	printf( "***** Hello, PCF2131! (SPI interface) *****\r\n" );

	if ( rtc.oscillator_stop() )
	{
		printf( "==== oscillator_stop detected :( ====\r\n" );
		set_time();
	}
	else
	{
		printf( "---- RTC has beeing kept running! :) ----\r\n" );
	}

	time_t	current_time;

	while ( true )
	{
		current_time	= rtc.time( NULL );

		printf( "time : %lu, %s", (unsigned long)current_time, ctime( &current_time ) );
		wait( 1 );
	}
}

void set_time( void ) {
	const char* current_time	= "2024-12-18 23:59:30";
	const char* format			= "%Y-%m-%d %H:%M:%S";
	struct tm	now_tm;

	strptime( current_time, format, &now_tm );
	rtc.set( &now_tm );

	printf( "RTC got new time information\r\n" );
}
