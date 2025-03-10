/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"afe/NAFE13388_UIM.h"

SPI				spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
NAFE13388_UIM	afe( spi );
InterruptIn		ADC_nDRDY( D4 );			//	Uses interrupt by ADC_nDRDY pin
volatile bool	drdy_wait;

constexpr uint32_t	timeout_limit	= 100000000;

enum	output_type	{ RAW, MICRO_VOLT };

using 	microvolt_t	= NAFE13388_UIM::microvolt_t;
using 	raw_t		= NAFE13388_UIM::raw_t;

using enum	NAFE13388_UIM::Register16;
using enum	NAFE13388_UIM::Register24;
using enum	NAFE13388_UIM::Command;

void	DRDY_int_handler( void );
void	logical_ch_config_view( void );
void	table_view( int size, int cols, std::function<void(int)> view, std::function<void(void)> linefeed = nullptr );


int main( void )
{
	printf( "***** Hello, NAFE13388 UIM board! *****\r\n" );

	auto	timeout_count	= timeout_limit;

	spi.frequency( 1'000'000 );
	spi.mode( 1 );

	afe.begin();
	afe.blink_leds();

	afe.logical_ch_config( 0, 0x1070, 0x3084, 0x2900, 0x0000 );
	afe.logical_ch_config( 1, 0x2070, 0x3084, 0x2900, 0x0000 );

	printf( "\r\nenabled logical channel(s) %2d\r\n", afe.enabled_channels );
	logical_ch_config_view();

	ADC_nDRDY.rise( DRDY_int_handler );

	//
	//	** ENABLE ONE OF NEXT TWO LINES **
	//

	constexpr bool output_type_selection	= MICRO_VOLT;
//	constexpr bool output_type_selection	= RAW;

	if ( output_type_selection == MICRO_VOLT )
		printf( "\r\nvalues in micro-volt\r\n" );
	else
		printf( "\r\nvalues in raw\r\n" );


	while ( true )
	{
		for ( auto ch = 0; ch < 2; ch++ )
		{
			drdy_wait		= true;
			timeout_count	= timeout_limit;

			afe.start( ch );

			while ( drdy_wait && --timeout_count )
				;

			if ( !timeout_count )
			{
				printf( "DRDY signal wait timeout\r\n" );
				continue;
			}

			if ( output_type_selection == MICRO_VOLT )
				printf( " %11.2f,", afe.read<microvolt_t>( ch, NAFE13388_UIM::immidiate_read ) );
			else
				printf( " %8ld,",   afe.read<raw_t>( ch, NAFE13388_UIM::immidiate_read ) );
		}
		printf( "\r\n" );
		wait( 0.05 );
	}
}

void DRDY_int_handler( void )
{
	drdy_wait	= false;
}

void logical_ch_config_view( void )
{
	uint16_t en_ch_bitmap	= afe.reg( CH_CONFIG4 );
	
	for ( auto channel = 0; channel < 16; channel++ )
	{	
		printf( "  logical channel %2d : ", channel );

		if ( en_ch_bitmap & (0x1 << channel) )
		{
			afe.command( channel );
			table_view( 4, 4, []( int v ){ printf( "  0x%04X: 0x%04X", (uint16_t)(v + CH_CONFIG0), afe.reg( v + CH_CONFIG0 ) ); } );
		}
		else
		{
			printf(  "  (disabled)\r\n" );
		}
	}
}

void table_view( int length, int cols, std::function<void(int)> value, std::function<void(void)> linefeed )
{
	const auto	raws	= (int)(length + cols - 1) / cols;
	
	for ( auto i = 0; i < raws; i++  )
	{
		if ( i )
		{
			if ( linefeed )
				linefeed();
			else
				printf( "\r\n" );
		}
		
		for ( auto j = 0; j < cols; j++  )
		{
			auto	index	= i + j * raws;
			
			if ( index < length  )
				value( index );
		}
	}
	
	if ( linefeed )
		linefeed();
	else
		printf( "\r\n" );
}
