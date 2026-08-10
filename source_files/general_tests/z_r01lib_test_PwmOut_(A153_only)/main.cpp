//FILEHEAD
/** main.cpp
 *
 *  PwmOut クラス テスト – FRDM-MCXA153
 *
 *  FlexPWM0 (PWM0〜PWM5 = P3_11〜P3_6) にPWM波形を出力し、
 *  シリアル (VCOM 115200 baud) に設定値を出力する。
 *
 *  確認方法:
 *    PWM0〜PWM5 (P3_11〜P3_6) をオシロスコープ/DMM/LED+抵抗で観測し、
 *    表示される period / duty と実波形が一致することを確認する。
 *
 *  | 論理ピン | 物理ピン | submodule | channel |
 *  |----------|----------|-----------|---------|
 *  | PWM0     | P3_11    | sm2       | B       |
 *  | PWM1     | P3_10    | sm2       | A       |
 *  | PWM2     | P3_9     | sm1       | B       |
 *  | PWM3     | P3_8     | sm1       | A       |
 *  | PWM4     | P3_7     | sm0       | B       |
 *  | PWM5     | P3_6     | sm0       | A       |
 *
 *  PWM0..PWM5は基板上のコネクタ方向に合わせて物理ピンと逆順になっている
 *  （io.hのコメント参照）。
 */

#include	"r01lib.h"

PwmOut	pwm0( PWM0 );	//  P3_11 / sm2 chB
PwmOut	pwm1( PWM1 );	//  P3_10 / sm2 chA
PwmOut	pwm2( PWM2 );	//  P3_9  / sm1 chB
PwmOut	pwm3( PWM3 );	//  P3_8  / sm1 chA
PwmOut	pwm4( PWM4 );	//  P3_7  / sm0 chB
PwmOut	pwm5( PWM5 );	//  P3_6  / sm0 chA

constexpr float	PERIOD_MS	= 20.0f;	//  default period for the demo
constexpr float	STEP_PERIOD	= 0.02f;	//  breathing loop tick [s]

static void print_header( void )
{
	printf( "\r\n" );
	printf( "==============================================\r\n" );
	printf( "  FRDM-MCXA153  PwmOut  test\r\n" );
	printf( "==============================================\r\n" );
}

static void print_setting( const char *label, PwmOut &pwm )
{
	printf( "  %-4s  duty=%.3f\r\n", label, (double)pwm.read() );
}

int main( void )
{
	print_header();

	//  ── テスト 1: period()/pulsewidth()/write()/read()/operator ──────
	printf( "[1] period() / pulsewidth() / write() / read() / operator\r\n" );

	pwm0.period_ms( 20 );
	pwm0.write( 0.5f );
	printf( "  pwm0.period_ms(20); pwm0.write(0.5f);  -> read() = %.3f\r\n", (double)pwm0.read() );

	pwm0.pulsewidth_us( 5000 );	//  5ms of a 20ms period = 25%
	printf( "  pwm0.pulsewidth_us(5000);              -> read() = %.3f\r\n", (double)pwm0.read() );

	pwm0 = 0.75f;	//  operator=()
	float	implicit	= pwm0;	//  operator float()
	printf( "  pwm0 = 0.75f;                          -> (float)pwm0 = %.3f\r\n", (double)implicit );
	printf( "\r\n" );

	//  ── テスト 2: 全チャネルに固定duty設定 ────────────────────────────
	printf( "[2] all channels, fixed duty (period = %.0f ms)\r\n", (double)PERIOD_MS );
	pwm0.period_ms( (int)PERIOD_MS ); pwm0.write( 0.10f );
	pwm1.period_ms( (int)PERIOD_MS ); pwm1.write( 0.25f );
	pwm2.period_ms( (int)PERIOD_MS ); pwm2.write( 0.50f );
	pwm3.period_ms( (int)PERIOD_MS ); pwm3.write( 0.75f );
	pwm4.period_ms( (int)PERIOD_MS ); pwm4.write( 0.90f );
	pwm5.period_ms( (int)PERIOD_MS ); pwm5.write( 1.00f );

	print_setting( "PWM0", pwm0 );
	print_setting( "PWM1", pwm1 );
	print_setting( "PWM2", pwm2 );
	print_setting( "PWM3", pwm3 );
	print_setting( "PWM4", pwm4 );
	print_setting( "PWM5", pwm5 );
	printf( "\r\n" );

	//  ── テスト 3: 周期共有の確認 (sm0 = PWM4/PWM5) ────────────────────
	//  period()はsubmodule単位で共有されるハードウェア仕様（バグではない）。
	//  PWM4側でperiod()を呼ぶと、PWM5オブジェクト自身のread()/period管理は
	//  変化しないが、実際のハードウェアのVAL1レジスタ（周期カウンタ）は
	//  sm0全体で書き換わるため、PWM5の実出力周期も追従して変わる。
	printf( "[3] period() is shared per submodule (sm0 = PWM4/PWM5)\r\n" );
	pwm5.period_ms( 20 ); pwm5.write( 0.5f );
	printf( "  pwm5.period_ms(20)  -> sm0 VAL1 (raw tick count) = %u\r\n",
			(unsigned)FLEXPWM0->SM[ 0 ].VAL1 );

	pwm4.period_ms( 5 ); pwm4.write( 0.5f );
	printf( "  pwm4.period_ms(5)   -> sm0 VAL1 (raw tick count) = %u  (changed! PWM5's real period followed)\r\n",
			(unsigned)FLEXPWM0->SM[ 0 ].VAL1 );
	printf( "\r\n" );

	//  ── テスト 4: 連続 breathing (全チャネル同時フェード) ─────────────
	printf( "[4] continuous breathing on all 6 channels (period = %.0f ms)\r\n", (double)PERIOD_MS );
	printf( "----------------------------------------------\r\n" );

	pwm0.period_ms( (int)PERIOD_MS );
	pwm1.period_ms( (int)PERIOD_MS );
	pwm2.period_ms( (int)PERIOD_MS );
	pwm3.period_ms( (int)PERIOD_MS );
	pwm4.period_ms( (int)PERIOD_MS );
	pwm5.period_ms( (int)PERIOD_MS );

	PwmOut	*ch[]	= { &pwm0, &pwm1, &pwm2, &pwm3, &pwm4, &pwm5 };

	float	duty	= 0.0f;
	float	step	= 0.02f;

	while ( true )
	{
		for ( int i = 0; i < 6; i++ )
			ch[ i ]->write( duty );

		printf( "  duty = %.2f\r", (double)duty );

		duty	+= step;
		if ( duty >= 1.0f || duty <= 0.0f )
			step	= -step;

		wait( STEP_PERIOD );
	}
}
