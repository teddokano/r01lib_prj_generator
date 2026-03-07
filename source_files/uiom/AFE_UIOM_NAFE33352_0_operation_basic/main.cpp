#include	"r01lib.h"
#include	"afe/NAFE33352_UIOM.h"

SPI				spi( ARD_MOSI, ARD_MISO, ARD_SCK, ARD_CS );	//	MOSI, MISO, SCLK, CS
NAFE33352_UIOM	shasta( spi, 0 );

using enum NAFE33352_UIOM::Register16;
using enum NAFE33352_UIOM::Register24;
using enum NAFE33352_UIOM::Command;

int main( void )
{
	printf( "***** Hello, SHASTA board! *****\r\n" );
	printf( "\r\n" );
	printf( "  ##### REQUIRED HARDWARE SETUP #####\r\n" );
	printf( "  This ample code demonstrates ADC input and DAC output on NAFE33352 UIOM board.\r\n" );
	printf( "  Connect a wire between pin1(DUT_AO) and pin5(AIP) on J3 terminal block to loopback the voltage output.\r\n" );
	printf( "  The DAC output voltage can be seen at logical-channel 0on the ADC input.\r\n" );
	printf( "\r\n" );

	spi.frequency( 1'000'000 );
	spi.mode( 1 );

	shasta.begin();

	//	ADC logical channel setting
	shasta.command( CMD_CH0 );
	shasta.reg( AI_CONFIG0, 0x0020 );
	shasta.reg( AI_CONFIG1, 0x50B4 );
	shasta.reg( AI_CONFIG2, 0x5000 );

	//	DAC setting
	shasta.reg( AIO_CONFIG,   0x6040 );
	shasta.reg( AO_CAL_COEF,  0x0000 );
	shasta.reg( AIO_PROT_CFG, 0x87FF );
	shasta.reg( AO_SLR_CTRL,  0x8200 );
	shasta.reg( AO_SYSCFG,    0x0C00 );

	double	output_voltage	= 5.00;
	int32_t	output_data		= (int32_t)((double)(1 << (18 -1)) * -1.00 * output_voltage / 12.50);

	shasta.reg( AO_DATA,    output_data << 6 );

	//	check analog input setting data
	printf( "* readback values from ADC logical channel-0 setting registers\r\n" );
	shasta.command( CMD_CH0 );
	printf( "  AI_CONFIG0: 0x%04X\r\n", shasta.reg( AI_CONFIG0 ) );
	printf( "  AI_CONFIG1: 0x%04X\r\n", shasta.reg( AI_CONFIG1 ) );
	printf( "  AI_CONFIG2: 0x%04X\r\n", shasta.reg( AI_CONFIG2 ) );
	printf( "\r\n" );

	//	check analog output setting data
	printf( "* readback values from DAC (analog output) setting registers\r\n" );
	printf( "  AIO_CONFIG:   0x%04X\r\n",  shasta.reg( AIO_CONFIG   ) );
	printf( "  AO_CAL_COEF:  0x%04X\r\n",  shasta.reg( AO_CAL_COEF  ) );
	printf( "  AIO_PROT_CFG: 0x%04X\r\n",  shasta.reg( AIO_PROT_CFG ) );
	printf( "  AO_SLR_CTRL:  0x%04X\r\n",  shasta.reg( AO_SLR_CTRL  ) );
	printf( "  AO_SYSCFG:    0x%04X\r\n",  shasta.reg( AO_SYSCFG    ) );
	printf( "  AO_DATA:      0x%06lX\r\n", shasta.reg( AO_DATA      ) );
	printf( "\r\n" );

	int32_t	data;
	double	volt;
	
	wait( 1.0 );
	
	printf( "* ADC logical channel-0 reading voltage and AIO_STATUS register value\r\n" );

	while ( true )
	{
		shasta.command( CMD_SS );
		wait( 0.11 );
		
		data	= shasta.reg( AI_DATA0 );
		volt	= (double)data * (20.00 * 2.50) / (1.00 * (double)(1 << 24));

		printf( "    % lfV", volt );
		printf( "    AIO_STATUS = 0x%04X\r\n", shasta.reg( AIO_STATUS ) );

		wait( 1.0 );
	}
}
