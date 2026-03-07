#include	"r01lib.h"
#include	"afe/NAFE33352_UIOM.h"
#include	"utils.h"

SPI				spi( ARD_MOSI, ARD_MISO, ARD_SCK, ARD_CS );	//	MOSI, MISO, SCLK, CS
NAFE33352_UIOM	shasta( spi, 0 );

using enum NAFE33352_UIOM::Register16;
using enum NAFE33352_UIOM::Register24;
using enum NAFE33352_UIOM::Command;
using enum NAFE33352_UIOM::DAC::ModeSelect;

#define	VOLTAGE_OUTPUT_SETTING

int main( void )
{
	printf( "***** Hello, UIOM board! *****\r\n" );

	spi.frequency( 1'000'000 );
	spi.mode( 1 );

	shasta.begin();

	printf( "Part number          = 0x%04X%04X%02X\r\n", shasta.reg( PN2 ), shasta.reg( PN1 ), shasta.reg( PN0_REV ) >> 8 );
	printf( "Revision             = 0x%02X\r\n", shasta.reg( PN0_REV ) & 0xFF );
	printf( "Unique serial number = 0x%06lX%06lX\r\n", shasta.reg( SERIAL1 ), shasta.reg( SERIAL0 ) );

#ifdef	VOLTAGE_OUTPUT_SETTING
	double	output_value	= 5.00;			//	5V
	shasta.dac.configure( VOLTAGE );
#else
	double	output_value	= 20 * 1e-3;	//	20mA
	shasta.dac.configure( CURRENT );
#endif

	shasta.dac	= output_value;

	shasta.logical_channel[  0 ].configure( 0x0020, 0x50B4, 0x5000 );
	shasta.logical_channel[  1 ].configure( 0x0080, 0x5064, 0x5000 );
	shasta.logical_channel[  2 ].configure( 0x0088, 0x5064, 0x5000 );
	shasta.logical_channel[  3 ].configure( 0x0038, 0x2064, 0x5000 );
	shasta.logical_channel[  4 ].configure( 0x0030, 0x3064, 0x5000 );

	printf( "\r\nregister dump: device info:\r\n" );
	reg_dump( { PN2, PN1, PN0_REV, SERIAL1, SERIAL0, DIE_TEMP }, 1 );
	
	printf( "\r\nregister dump: system config:\r\n" );
	reg_dump( { SYS_CONFIG, SYS_STATUS, CK_SRC_SEL_CONFIG, GLOBAL_ALARM_ENABLE } );
	
	printf( "\r\nregister dump: output config:\r\n" );
	reg_dump( { AIO_CONFIG, AO_CAL_COEF, AIO_PROT_CFG, AO_SLR_CTRL, AWG_PER, AO_SYSCFG, AIO_STATUS } );
	
	printf( "\r\nregister dump: from GAIN_COEF0 to OFFSET_COEF7:\r\n" );
	reg_dump( GAIN_COEF0, 16 );

	printf( "\r\nregister dump: logical channel info:\r\n" );
	logical_ch_config_view();

	printf( "\r\n  AIP(SE)[V]      VHDD[V]         VHSS[V]         VSNS[V]         ISNS[A]         AIO_STATUS\r\n" );

	double	data;
	auto	count	= 0;;

	while ( true )
	{
		for ( auto i = 0; i < shasta.enabled_logical_channels(); i++ )
		{
			data	= shasta.logical_channel[ i ];
			printf( "  %13.9lf,", data );
		}
		printf( "    0x%04X\r\n", shasta.reg( AIO_STATUS ) );

		shasta.dac	= output_value * (count++ & 0x1 ? +1.00 : -1.00);

		wait( 1.0 );
	}
}
