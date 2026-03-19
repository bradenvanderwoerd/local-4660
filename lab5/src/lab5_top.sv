module lab5_top
  ( input logic clk50, // 50 MHz clock
    output logic lcd_cs, lcd_sda, lcd_rst, lcd_rs, lcd_scl, // LCD
    input logic s1, // button s1 (active-low reset)
    output logic ADC_CONVST, ADC_SCK, ADC_SDI, // LTC2308 ADC
    input logic ADC_SDO, 
    // PIO port
    output logic [7:0] LED // LEDs, LCD CS, RS and RST
    ) ;

    lab5 u0
    (
    .adc_sck (ADC_SCK), // adc.sck
    .adc_sdo (ADC_SDO), // .sdo
    .adc_sdi (ADC_SDI), // .sdi
    .adc_convst (ADC_CONVST), // .convst
    .pio_export ({LED[4:0],lcd_cs,lcd_rs,lcd_rst}), // pio.export
    .spi_MISO (1'b0), // spi.MISO
    .spi_MOSI (lcd_sda), // .MOSI
    .spi_SCLK (lcd_scl),a // .SCLK
    .spi_SS_n (LED[6]), // .SS_n
    .clk50_clk (clk50), // clk50.clk
    .reset_reset_n (s1) // reset.reset_n
    );
    
endmodule