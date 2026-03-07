/*
 *  @author Tedd OKANO
 *
 *  Released under the MIT license
 */

#include	"r01lib.h"
#include	"afe/NAFE33352_UIOM.h"
#include	"utils.h"

extern	NAFE33352_UIOM	shasta;

void reg_dump( RegVct reg_vctr, int column )
{
	table_view(
		reg_vctr.size(),
		column,
		[ &reg_vctr ]( int v )
		{
			if ( const NAFE33352_Base::Register24 *ap	= std::get_if<NAFE33352_Base::Register24>( &(reg_vctr[ v ] ) ) )
			{
				printf( "      0x%04X: 0x%06lX", static_cast<int>( *ap ), shasta.reg( *ap ) & 0xFFFFFF );
			}
			else if ( const NAFE33352_Base::Register16 *ap	= std::get_if<NAFE33352_Base::Register16>( &(reg_vctr[ v ]) ) )
			{
				printf( "      0x%04X: 0x  %04X", static_cast<int>( *ap ), shasta.reg( *ap ) );
			}
		},   
		[]()
		{
		   printf( "\r\n" );
		}
	);
}

void reg_dump( NAFE33352_Base::Register24 addr, int length )
{
	table_view( length, 4, [ & ]( int v ){ printf( "      0x%04X: 0x%06lX", v + (uint16_t)addr, shasta.reg( v + addr ) & 0xFFFFFF ); }, [](){ printf( "\r\n" ); });
}

void logical_ch_config_view( void )
{
	uint16_t	en_ch_bitmap	= shasta.reg( AI_MULTI_CH_EN ) >> 8;
	const char	*reg_name[]		= { "AI_CONFIG0", "AI_CONFIG1", "AI_CONFIG2" };
	
	for ( auto channel = 0; channel < 16; channel++ )
	{	
		printf( "  logical channel %2d : ", channel );

		if ( en_ch_bitmap & (0x1 << channel) )
		{
			shasta.command( CMD_CH0 + channel );
			table_view( 3, 3, [ &reg_name ]( int v ){ printf( "   %s: 0x%04X", reg_name[ v ], shasta.reg( v + AI_CONFIG0 ) ); } );
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
