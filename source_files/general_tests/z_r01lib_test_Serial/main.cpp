//FILEHEAD
#include "r01lib.h"

Serial		uart( USBTX, USBRX );
//Serial	uart( D1, D0, 9600);			//	supported on A153 and C444
//Serial	uart( MB_TX, MB_RX, 115200);	//	supported on A153 and C444

DigitalOut	led(GREEN);

int main(void)
{
    uart.printf("Hello, world!\r\n");

    while (true)
    {
        if ( uart.readable() )
        {
            int	c	= uart.getc();
            uart.putc(c);   // echo back
            led = !led;
        }
    }
}
