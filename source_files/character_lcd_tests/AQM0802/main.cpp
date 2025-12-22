//FILEHEAD
#include	"r01lib.h"
#include	"misc/lcd/I2C_Character_LCD.h"

DigitalOut	led( BLUE );
I2C			i2c( I2C_SDA, I2C_SCL );
AQM0802		lcd( i2c );

int main( void )
{
	led	= true;

	printf( "Hello, world!\r\n" );

	lcd.puts( "Hello,", 0 );
	lcd.puts( "world!", 1 );
	wait( 0.5 );

	lcd.clear();

	while ( true )
	{
		led	= !led;

		for ( int i = 0; i < 1000; i++ )
			lcd.printf( 1, "n=%*d", 3, i );
	}
}
