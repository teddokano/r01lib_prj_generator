//FILEHEAD
#include	"r01lib.h"
#include	"misc/lcd/I2C_Character_LCD.h"

DigitalOut	led( BLUE );
I2C			i2c( I2C_SDA, I2C_SCL );

int main( void )
{
	i2c.frequency( 50'000 );

	ACM1602		lcd( i2c );

	led	= true;

	printf( "Hello, world!\r\n" );

	lcd.puts( "Hello, world!",    0 );
	lcd.puts( "Happy hacking ;)", 1 );
	wait( 3 );

	lcd.clear();

	while ( true )
	{
		led	= !led;

		for ( int i = 0; i < 1000; i++ )
		{
			lcd.printf( 0, "n=%*d", 3, i );
			lcd.printf( 1, "n=0x%*X", 3, i );
		}
	}
}
