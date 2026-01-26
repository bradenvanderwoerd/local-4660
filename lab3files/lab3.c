// lab3.c - read and print ADC register values from ltc2308 interface
// and display LED heartbeat on FPGA board.
// Ed.Casas 2026-1-26

/* Nios V command shell commands to rebuilt BSP and application:
   
cd <project folder>

niosv-bsp -c -t=hal --sopcinfo=lab3.sopcinfo software/bsp/settings.bsp
niosv-app -a=software/app -b=software/bsp -s=software/app/lab3.c

To view JTAG UART output, run:

juart-terminal

*/


#include "system.h"
#include <alt_types.h>
#include <io.h>
#include <stdio.h>
#include <unistd.h>

int main ( void ) {

   printf ( "Hello, world!\n" ) ;
        
   for ( int i=0 ; 1 ; i++ ) {

      // hearbeat
      IOWR_32DIRECT(PIO_0_BASE,0,1<<(i%8)) ;
      usleep(200000) ;

      // read & print values from the 8 ADC data registers
      int v ;
      for ( int j=0 ; j<8 ; j++ ) {
         v = IORD_32DIRECT(LTC2308_0_BASE, 4*j);
         printf ("%8d",v) ;
      }
      printf("\n");

   }

   return 0 ;
}
