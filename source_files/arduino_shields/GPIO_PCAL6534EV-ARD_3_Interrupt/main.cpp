//FILEHEAD
#include	"r01lib.h"
#include	"gpio/PCAL6534.h"

I2C			i2c( I2C_SDA, I2C_SCL );	//	SDA, SCL
PCAL6534	gpio( i2c, 0x22 );
InterruptIn	int_pin( D10 );

bool			int_flag		= false;

void callback( void ) {
	int_flag = true;
}

int main(void)
{
	printf( "***** Hello, PCAL6534! *****\r\n" );
	printf( "  Watch the LEDs are blinking\r\n" );
	printf( "  And press buttons to generate interrupts\r\n" );

	gpio.begin( PCAL6534::ARDUINO_SHIELD );
	I2C_device::scan( i2c );

	uint8_t io_config_and_pull_up[] = {
		0x00,	// Configure port0 as OUTPUT
		0x00,	// Configure port1 as OUTPUT
		0x00,	// Configure port2 as OUTPUT
		0xE0,	// Configure port3 bit 7~5 as INPUT
		0x03,	// Configure port4 bit 1 and 0 as INPUT
	};

	gpio.config( io_config_and_pull_up );					//  Port0, 1, 2 and port3 bit 4~0 are configured as output
	gpio.write_port( PULL_UD_EN,  io_config_and_pull_up );	//  Pull-up/down enabled for port3 bit 7~5 and port4 bit 1 and 0
	gpio.write_port( PULL_UD_SEL, io_config_and_pull_up );	//  Pull-up selected for port3 bit 7~5 and port4 bit 1 and 0

	gpio.write_port( INT_MASK, (uint8_t)(~0xE0), 3 );		//  Interrupt mask cleared on port3 bit 7~5
	gpio.write_port( INT_MASK, (uint8_t)(~0x03), 4 );		//  Interrupt mask cleared on port4 bit 1 and 0

	int_pin.fall( callback );

	while ( true )
	{
		static uint8_t	pat[] = {	//  LED blinking pattern
			0xFE, 0xFB, 0xFD, 0xEF, 0xF7, 0xBF, 0xDF,
			0x7F, 0xDF, 0xBF, 0xF7, 0xEF, 0xFD, 0xFB,
		};
		static int	count = 0;
		uint8_t		input3;
		uint8_t		input4;

		if ( int_flag )
		{
			int_flag = false;

			uint8_t	status[ gpio.n_ports ];

			gpio.read_port( INT_STATUS, status );

			printf( "[INT] status 0~%d:", gpio.n_ports - 1 );

			for (int i = 0; i < gpio.n_ports; i++)
				GPIO_base::print_bin( status[i] );

			input3 = gpio.input(3);
			input4 = gpio.input(4);

			printf( ",  input 3 and 4: " );
			GPIO_base::print_bin( input3 );
			GPIO_base::print_bin( input4 );
			printf( "\r\n" );
		}
		else
		{
			input3 = gpio.input( 3 );
			input4 = gpio.input( 4 );
		}

		gpio.output( 2, ((input3 & 0xFC) | input4) & pat[count++ % sizeof(pat)] );
		wait( 0.062 );
	}
}
