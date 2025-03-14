/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"afe/NAFE13388_UIM.h"
#include	<math.h>
#include	<array>

#include	"PrintOutput.h"

SPI				spi( D11, D12, D13, D10 );	//	MOSI, MISO, SCLK, CS
NAFE13388_UIM	afe( spi );
PrintOutput		out( "test" );
//PrintOutput	out;			//use this line to disable file output

using enum	NAFE13388_UIM::Register16;
using enum	NAFE13388_UIM::Register24;
using enum	NAFE13388_UIM::Command;

using 	raw_t			= NAFE13388_UIM::raw_t;
using 	ref_points		= NAFE13388_UIM::ref_points;
using	ch_setting_t	= NAFE13388_UIM::ch_setting_t;

constexpr int	INPUT_GND			= 0x0010;
constexpr int	INPUT_A1P_SINGLE	= 0x1710;

enum CoeffIndex {
	CAL_FOR_PGA_0_2	= 0,
	CAL_NONE		= 8,
	CAL__5V_NONE,
	CAL_10V_NONE,
	CAL__5V_CUSTOM,
	CAL_10V_CUSTOM,
	CAL_1V5V_NONE,
	CAL_1V5V_CUSTOM,
};

constexpr NAFE13388_UIM::ref_points	r[]	= {
	{ CAL__5V_NONE,    {  5.0, 2000 }, {  0.0, 0 }, CAL_NONE        },
	{ CAL_10V_NONE,    { 10.0, 2000 }, {  0.0, 0 }, CAL_NONE        },
	{ CAL__5V_CUSTOM,  {  5.0, 2000 }, {  0.0, 0 }, CAL_FOR_PGA_0_2 },
	{ CAL_10V_CUSTOM,  { 10.0, 2000 }, {  0.0, 0 }, CAL_FOR_PGA_0_2 },
	{ CAL_1V5V_NONE,   {  5.0, 2015 }, { 1.0, 16 }, CAL_NONE        },
	{ CAL_1V5V_CUSTOM, {  5.0, 2015 }, { 1.0, 16 }, CAL_FOR_PGA_0_2 },
};

constexpr ch_setting_t	chs[]	= {
	{ INPUT_A1P_SINGLE, (CAL_NONE        << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_A1P_SINGLE, (CAL_FOR_PGA_0_2 << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_A1P_SINGLE, (CAL__5V_NONE    << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_A1P_SINGLE, (CAL__5V_CUSTOM  << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_A1P_SINGLE, (CAL_10V_NONE    << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_A1P_SINGLE, (CAL_10V_CUSTOM  << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_A1P_SINGLE, (CAL_1V5V_NONE   << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_A1P_SINGLE, (CAL_1V5V_CUSTOM << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_GND       , (CAL_NONE        << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_GND       , (CAL_FOR_PGA_0_2 << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_GND       , (CAL__5V_NONE    << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_GND       , (CAL__5V_CUSTOM  << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_GND       , (CAL_10V_NONE    << 12) | 0x0084, 0x2900, 0x0000 },
	{ INPUT_GND       , (CAL_10V_CUSTOM  << 12) | 0x0084, 0x2900, 0x0000 },
};

void	reg_dump( NAFE13388_UIM::Register24 addr, int length );
void	logical_ch_config_view( void );
void	table_view( int size, int cols, std::function<void(int)> view, std::function<void(void)> linefeed = nullptr );


int main( void )
{
	out.printf( "***** Hello, NAFE13388 UIM board! *****\r\n" );
	out.printf( "---   custom gain & offset sample   ---\r\n" );

	spi.frequency( 1'000'000 );
	spi.mode( 1 );

	afe.begin();
	afe.blink_leds();
	
	uint64_t	sn	= afe.serial_number();

	out.printf( "part number   = %04lX (revision: %01X)\r\n", afe.part_number(), afe.revision_number() );
	out.printf( "serial number = %06lX%06lX\r\n", (uint32_t)(sn >> 24), (uint32_t)sn & 0xFFFFFF );	//	to use NewlibNano
	out.printf( "die temperature = %f℃\r\n", afe.temperature() );
	
	//
	//	logical channels setting
	//

	for ( auto i = 0U; i < sizeof( chs ) / sizeof( ch_setting_t ); i++ )
		afe.logical_ch_config( i, chs[ i ] );

	out.printf( "\r\nenabled logical channel(s) %2d\r\n", afe.enabled_channels );
	logical_ch_config_view();

	//
	//	gain/offset coefficient settings
	//

	out.printf( "\r\n=== GAIN_COEFF and OFFSET_COEFF registers default values ===\r\n" );
	reg_dump( GAIN_COEFF0, 32 );

	//	on-board re-calibration for "PGA_gain = 0.2" coefficients

	afe.self_calibrate( NAFE13388_UIM::GainPGA( 0 ) );

	out.printf( "\r\n=== GAIN_COEFF and OFFSET_COEFF registers after on-board calibration ===\r\n" );
	reg_dump( GAIN_COEFF0, 32 );

#if 0
	afe.recalibrate( 0, 2, 2.5 );

	out.printf( "\r\n=== GAIN_COEFF and OFFSET_COEFF registers after on-board calibration ===\r\n" );
	reg_dump( GAIN_COEFF0, 32 );


#endif

	//	gain/offset customization
	
	for ( auto i = 0U; i < sizeof( r ) / sizeof( ref_points ); i++ )
		afe.gain_offset_coeff( r[ i ] );

	out.printf( "\r\n=== GAIN_COEFF and OFFSET_COEFF registers after overwrite ===\r\n" );
	reg_dump( GAIN_COEFF0, 32 );

	//
	//	operation with customized gain/offset
	//

	out.printf( "\r\n" );
	out.printf( "     count" );

	out.printf( "      NONE" );
	out.printf( "  Cal_dflt" );
	out.printf( "   5V_NONE" );
	out.printf( "    5V_Cal" );
	out.printf( "  10V_NONE" );
	out.printf( "   10V_Cal" );
	out.printf( " 1V5V_NONE" );
	out.printf( "  1V5V_Cal" );

	out.printf( "      NONE" );
	out.printf( "  Cal_dflt" );
	out.printf( "   5V_NONE" );
	out.printf( "    5V_Cal" );
	out.printf( "  10V_NONE" );
	out.printf( "   10V_Cal" );
	out.printf( "\r\n" );

	raw_t			data;
	long			count		= 0;

	while ( true )
	{
		out.printf( " %8ld, ", count++ );
		
		for ( auto ch = 0; ch < afe.enabled_channels; ch++ )
		{
			data	= afe.read<raw_t>( ch );
			out.color( ch % 2 ? PrintOutput::Color::bg_none : PrintOutput::Color::bg_gray );
			out.printf( " %8ld,", data );
		}
		out.printf( "\r\n" );
		//out.printf( "\n" );

		wait( 0.05 );
	}
}

void reg_dump( NAFE13388_UIM::Register24 addr, int length )
{
	table_view( length, 4, [ & ]( int v ){ out.printf( "  %8ld @ 0x%04X", afe.reg( v + addr ), v + addr ); }, [](){ out.printf( "\r\n" ); });
}

void logical_ch_config_view( void )
{
	uint16_t en_ch_bitmap	= afe.reg( CH_CONFIG4 );
	
	for ( auto channel = 0; channel < 16; channel++ )
	{	
		out.printf( "  logical channel %2d : ", channel );

		if ( en_ch_bitmap & (0x1 << channel) )
		{
			afe.command( channel );
			table_view( 4, 4, []( int v ){ out.printf( "  0x%04X: 0x%04X", v + CH_CONFIG0, afe.reg( v + CH_CONFIG0 ) ); }, [](){ out.printf( "\r\n" ); } );
		}
		else
		{
			out.printf(  "  (disabled)\r\n" );
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
