// lab5.c - display joystick coordinates on 128x128 LCD dislay via ST7735S controller
// Ed.Casas 2026-2-9

/* Nios V command shell commands to rebuild BSP and application:
   
cd <project folder>

niosv-bsp -c -t=hal --sopcinfo=lab5.sopcinfo software/bsp/settings.bsp
niosv-app -a=software/app -b=software/bsp -s=software/app

To view JTAG UART output, run:

juart-terminal

*/

#include "system.h"
#include <alt_types.h>
#include <io.h>
#include <stdio.h>
#include <unistd.h>

#include "st7735s.h"
#include "fonts.h"
#include "gfx.h"

extern void set_debug_leds(uint8_t pattern);

int main ( void ) {

	// uint8_t f = 0;
    uint16_t x=0, y=0 ;
    uint16_t lastx=0, lasty=0 ;
    char buf [80];

    set_debug_leds(0x01);

   // configure the first and last ADC channels to sample
   int firstch=0, lastch=1 ;
   IOWR_32DIRECT(LTC2308_BASE, 0, ((lastch&7)<<3) | (firstch&7) );

    set_debug_leds(0x02);

   // set up controller, including Booster Pack orientation
   ST7735S_Init();

    set_debug_leds(0x04);

   setOrientation(R90);

   printf("ST7735S initialized.\n") ;

   	// clear screen and set 12-pixel font
	setColor(0,0,0);
	fillScreen();
    setbgColor(0,0,0);
	setFont(ter_u12b);
    
    int state = 0x08 ;

    while (1) {

        state ^= 0x18; // toggle bits 3 and 4 to indicate we're in the main loop
        set_debug_leds(state); // toggle bit 3 to indicate we're in the main loop

    	// read joystick x and y
        for ( int n=0 ; n != 3 ; ) {
        	int s = IORD_32DIRECT(LTC2308_BASE,0);
        	switch ( (s>>12) & 0xf ) {
        		case 0: x = s & 0xfff ; n|=1 ; break ;
        		case 1: y = s & 0xfff ; n|=2 ; break ;
        	}
        }

        // convert to display coordinates
        x = (x - 40) / 25 ;
        y = (y - 20) / 25 ;
        y = 128 - y ;

        // only redraw when coordinates change
        if ( x == lastx && y == lasty ) continue ;

    	// erase old
    	setColor(0,0,0);
        drawLine(0,lasty,WIDTH-1,lasty);
        drawLine(lastx,0,lastx,HEIGHT-1);

        lastx = x ;
        lasty = y ;

        // draw new
        setColor(31,63,0);
        drawLine(0,y,WIDTH-1,y);
        setColor(0,63,31);
        drawLine(x,0,x,HEIGHT-1);

        // show coordinates
        sprintf(buf, "x=%3d y=%3d\n", x, y ) ;
        setColor(31,63,31);
        drawText(0,HEIGHT-12, buf);

        drawText(0,0, "Braden Vanderwoerd\n");

    }
    /*

    for (int i = 0; 1; i++) {
        IOWR_32DIRECT(PIO_BASE,0,1<<(i%8)) ;
        usleep(100000) ;
    }*/
}