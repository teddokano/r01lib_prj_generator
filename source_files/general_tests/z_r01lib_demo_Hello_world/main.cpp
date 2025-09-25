//FILEHEAD
#include	"r01lib.h"
#include	<math.h>

#ifndef		M_PI
#define		M_PI	3.14159265358979323
#endif

int main( void )
{
	printf( "Hello, world!\r\n" );
	printf( "test for float print: %f\r\n", M_PI );
	printf( "test for utf-8 print: %s\r\n", "℃" );

	return 0;
}
