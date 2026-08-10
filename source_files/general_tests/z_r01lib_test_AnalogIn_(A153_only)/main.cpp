//FILEHEAD
/** main.cpp
 *
 *  AnalogIn クラス テスト – FRDM-MCXA153
 *
 *  Arduino ヘッダ A0〜A3 の電圧を LPADC0 で読み取り、
 *  シリアル (VCOM 115200 baud) に出力する。
 *
 *  接続方法:
 *    A0〜A3 に可変抵抗 (0〜3.3V, VDDA基準) を接続し、
 *    表示される値がつまみの位置に応じて変化することを確認する。
 *    何も接続しない場合はフローティング入力となり値が安定しないが、
 *    read()/read_u16() が異常終了しないことは確認できる。
 */

#include	"r01lib.h"

DigitalOut	led_r( RED );
DigitalOut	led_g( GREEN );
DigitalOut	led_b( BLUE );

AnalogIn	a0( A0 );	//  P1_10 / ADC0_A8
AnalogIn	a1( A1 );	//  P1_12 / ADC0_A10
AnalogIn	a2( A2 );	//  P1_13 / ADC0_A11
AnalogIn	a3( A3 );	//  P2_0  / ADC0_A0

constexpr float	VDDA	= 3.3f;
constexpr float	PERIOD	= 0.5f;

static void print_header( void )
{
	printf( "\r\n" );
	printf( "==============================================\r\n" );
	printf( "  FRDM-MCXA153  AnalogIn  test\r\n" );
	printf( "==============================================\r\n" );
}

static void print_result( const char *label, AnalogIn &ain )
{
	float		fv	= ain.read();
	uint16_t	u16	= ain.read_u16();
	uint32_t	mv	= (uint32_t)( fv * VDDA * 1000.0f );

	printf( "  %-4s  %5.3f  %5u  %4lu mV\r\n", label, (double)fv, u16, (unsigned long)mv );
}

int main( void )
{
	print_header();

	//  ── テスト 1: read() / read_u16() / operator float() ─────────────
	printf( "[1] read() / read_u16() / operator float()\r\n" );
	printf( "  a0.read()     = %.4f\r\n", (double)a0.read() );
	printf( "  a0.read_u16() = %u\r\n", a0.read_u16() );

	float	implicit	= a0;	//  暗黙変換
	printf( "  (float)a0     = %.4f\r\n", (double)implicit );
	printf( "\r\n" );

	//  ── テスト 2: 全チャネル一覧 (single shot) ────────────────────────
	printf( "[2] all channels (single shot)\r\n" );
	print_result( "A0", a0 );
	print_result( "A1", a1 );
	print_result( "A2", a2 );
	print_result( "A3", a3 );
	printf( "\r\n" );

	//  ── テスト 3: 連続測定ループ ───────────────────────────────────────
	printf( "[3] continuous measurement (%.1f s interval)\r\n", (double)PERIOD );
	printf( "----------------------------------------------\r\n" );
	printf( "  pin   float    u16    mV\r\n" );
	printf( "----------------------------------------------\r\n" );

	AnalogIn	*ch[]		= { &a0, &a1, &a2, &a3 };
	const char	*labels[]	= { "A0", "A1", "A2", "A3" };

	while ( true )
	{
		for ( int i = 0; i < 4; i++ )
		{
			float		fv	= ch[ i ]->read();
			uint16_t	u16	= ch[ i ]->read_u16();
			uint32_t	mv	= (uint32_t)( fv * VDDA * 1000.0f );

			printf( "  %-4s  %5.3f  %5u  %4lu mV\r\n", labels[ i ], (double)fv, u16, (unsigned long)mv );
		}

		//  A0 の値に応じて RGB LED を点灯 (動作確認インジケータ)
		float	v	= a0;
		led_r	= ( v < 0.33f )                     ? 1 : 0;	//  低電圧 → 赤
		led_g	= ( v > 0.66f )                     ? 1 : 0;	//  高電圧 → 緑
		led_b	= ( v >= 0.33f && v <= 0.66f )      ? 1 : 0;	//  中間   → 青

		printf( "\033[4A" );	//  VT100: 4行上へ戻して上書き
		wait( PERIOD );
	}
}
