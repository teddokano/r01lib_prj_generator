//FILEHEAD
#include	"r01lib.h"
#include	"afe/NAFE13388_UIM.h"
#include	"utils.h"
#include	<variant>

using	microvolt_t	= NAFE13388_UIM::microvolt_t;

SPI				spi( ARD_MOSI, ARD_MISO, ARD_SCK, ARD_CS );	//	MOSI, MISO, SCLK, CS
NAFE13388_UIM	afe( spi );

constexpr auto		normal_lc		= 8;
constexpr auto		monitor_lc		= normal_lc + 6;
volatile bool		conversion_done	= false;

void drdy_callback( void )
{
	conversion_done	= true;
}

int main( void )
{
	printf( "***** Hello, NAFE13388 UIM board! *****\r\n" );

	spi.frequency( 1'000'000 );
	spi.mode( 1 );

	afe.begin();
	afe.blink_leds();

	uint64_t	sn	= afe.serial_number();

	printf( "part number   = %04lX (revision: %01X)\r\n", afe.part_number(), afe.revision_number() );
	printf( "serial number = %06lX%06lX\r\n", (uint32_t)(sn >> 24), (uint32_t)sn & 0xFFFFFF );	//	to use NewlibNano
	printf( "die temperature = %f℃\r\n", afe.temperature() );

	RegVct	registers	= { PN2, PN1, PN0, SERIAL1, SERIAL0, DIE_TEMP, SYS_CONFIG0, SYS_STATUS0 };
	reg_dump( registers );

	constexpr uint16_t	cc0	= 0x0010;
	constexpr uint16_t	cc1	= 0x007C;
	constexpr uint16_t	cc2	= 0x4C00;
	constexpr uint16_t	cc3	= 0x0000;

	for (  auto i = 0; i < normal_lc / 2; i++ )
	{
		afe.logical_channel[ i * 2 + 0 ].configure( cc0 | (i + 1) << 12 | 7       << 8, cc1, cc2, cc3 );
		afe.logical_channel[ i * 2 + 1 ].configure( cc0 | 7       << 12 | (i + 1) << 8, cc1, cc2, cc3 );
	}

	afe.logical_channel[ normal_lc + 0 ].configure( 0x9900, 0x007C, 0x4C00, 0x0000 );
	afe.logical_channel[ normal_lc + 1 ].configure( 0xAA02, 0x007C, 0x4C00, 0x0000 );
	afe.logical_channel[ normal_lc + 2 ].configure( 0xBB04, 0x007C, 0x4C00, 0x0000 );
	afe.logical_channel[ normal_lc + 3 ].configure( 0xCC06, 0x007C, 0x4C00, 0x0000 );
	afe.logical_channel[ normal_lc + 4 ].configure( 0xDD08, 0x007C, 0x4C00, 0x0000 );
	afe.logical_channel[ normal_lc + 5 ].configure( 0xEE0A, 0x007C, 0x4C00, 0x0000 );

	const char *ch_name[]	= {
		"ch0  freq0/phase0",
		"ch1  freq0/phase1",
		"ch2  freq0/phase2",
		"ch3  freq1/phase0",
		"ch4  freq1/phase1",
		"ch5  freq1/phase2",
		"ch6  sawtooth",
		"ch7  square",
		"ch8  REF2-REF2",
		"ch9  GPIO-GPIO1",
		"ch10  REF_Coarse-REF2",
		"ch11  VADD",
		"ch12  VHDD",
		"ch13  VHSS",
	};

	printf( "\r\nenabled logical channel(s) %2d\r\n", afe.enabled_logical_channels() );
	logical_ch_config_view();

	afe.set_DRDY_callback( drdy_callback );	//	set callback function for when DRDY detected
	afe.DRDY_by_sequencer_done( true );		//	generate DRDY at all logical channel conversions are done

	std::vector<microvolt_t>	dv( monitor_lc );
	
	afe.start_continuous_conversion();

	while ( true )
	{
		if ( conversion_done )
		{
			conversion_done	= false;

			afe.read( dv );

			int i = 0;
			for ( auto&& v: dv )
			{
				printf( ">%s: %12.9lf\r\n", ch_name[ i ], v * 1e-6 );
				i++;
			}

			printf( "\r\n" );
		}
	}
}
