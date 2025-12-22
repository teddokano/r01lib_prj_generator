//FILEHEAD
#include	"r01lib.h"
#include	"misc/lcd/I2C_Character_LCD.h"

DigitalOut	led( BLUE );
I2C			i2c( I2C_SDA, I2C_SCL );
ACM2004		lcd( i2c );

int main( void )
{
	led	= true;

	printf( "Hello, world!\r\n" );

	lcd.puts( "Living is easy with", 0 );
	lcd.puts( "eyes closed,",        1 );
	lcd.puts( "Misunderstanding",    2 );
	lcd.puts( "all you see.",        3 );
	wait( 5 );

	lcd.clear();

	while ( true )
	{
		led	= !led;

		for ( int i = 0; i < 1000; i++ )
			lcd.printf( i % 4, "n=%*d", 3, i );
	}
}
