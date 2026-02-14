// ELEX 7660 202610 Lab 5 Hardware drivers for https://github.com/bersch/ST7735S
// graphics library
// Ed.Casas 2026-2-9


#include "system.h"
#include <alt_types.h>
#include <io.h>
#include <stdio.h>
#include <unistd.h>

#include "altera_avalon_spi_regs.h"
#include "altera_avalon_pio_regs.h"

#include "st7735s_compat.h"

// #define SPI_BASE 0xxxx
// 32-bit registers: 0=rxdata, 1=txdata, 2=status, 3=control, 4=reserved, 5=slave select
// #define PIO_BASE 0xxxx
// 8-bits, write-only, bit 0=RESet, bit 1=Data/Command*

uint8_t pio = 0 ;

void Pin_RES_High(void) { IOWR ( PIO_BASE, 0, pio |= 1) ; }
void Pin_RES_Low(void)  { IOWR ( PIO_BASE, 0, pio &= ~1) ; }

void Pin_DC_High(void)  { IOWR ( PIO_BASE, 0, pio |= 2) ; }
void Pin_DC_Low(void)   { IOWR ( PIO_BASE, 0, pio &= ~2) ; }

void Pin_CS_High(void)  { IOWR ( PIO_BASE, 0, pio |= 4) ; }
void Pin_CS_Low(void)   { IOWR ( PIO_BASE, 0, pio &= ~4) ; }

void Pin_BLK_Pct(uint8_t) { ; } // backlight wired on

void _Delay(uint32_t d) { usleep(d*1000) ; }

void SPI_Init(void) { pio = 0 ; }

void SPI_send(uint16_t len, uint8_t *data) {

   Pin_CS_Low() ;

   while ( len-- ) {

      // wait for "Transmitter Ready" (txdata empty) (bit 6)
      while ( ! ( IORD ( SPI_BASE, 2) & 0x40 ) ) ;
      
      // send a byte
      IOWR ( SPI_BASE, 1, *data++ ) ;

      // wait for "Receive Ready" (rxdata full) (bit 7)
      while ( ! ( IORD ( SPI_BASE, 2) & 0x80 ) ) ;
      IORD ( SPI_BASE, 0 ) ;
   }

  // wait for "Transmit shift-register empty" (bit 5)
   while ( ! ( IORD ( SPI_BASE, 2) & 0x20 ) ) ;
   
   Pin_CS_High() ;
}

void SPI_Transmit(uint16_t len, uint8_t *data) {
     SPI_TransmitCmd(1, data++);
     if (--len)
        SPI_TransmitData(len, data);
}

void SPI_TransmitCmd(uint16_t len, uint8_t *data)
{
   Pin_DC_Low() ;
   SPI_send(len,data) ;
}

void SPI_TransmitData(uint16_t len, uint8_t *data) {
   Pin_DC_High() ;
   SPI_send(len,data) ;
}

