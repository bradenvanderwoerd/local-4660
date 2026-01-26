// Interface from LTC 2308 500 kHz (2us) 8-channel ADC to Avalon MM
// bus.  Configures the ADC as single-ended unipolar which is how it's
// connected on the DE-0-Nano FPGA board.

// This interface reads sequentially from each channel and the most
// recent value read from each channel is available in eight 32-bit
// registers. It does this continuously, with one sample per 2us.

// No status or configuration registers and no interrupts.

module ltc2308
   ( input logic clk, reset,    // 80 MHz (12.5ns) clock and reset
     input logic sdo,           // serial data from ADC

     output logic convst, sck, sdi, // ADC control

     output logic [31:0] readdata, // Avalon MM data bus
     input logic [2:0] address    // address
     ) ;

   // ADC states and state duration counter
   
   typedef enum { start, convert, transfer, acquire } state_t ;
   
   state_t state, state_next ;

   logic [6:0] count, count_next ;

`define set_next(s,c) begin state_next=(s); count_next=$bits(count)'(c)-1'b1; end

   always_comb begin

      if ( reset )
         `set_next ( start, 2 )
      else if ( count )
         `set_next ( state, count )
      else 
         case(state)
            start: `set_next ( convert, 126 ) 
            convert: `set_next ( transfer, 24 ) 
            transfer: `set_next ( acquire, 8 ) 
            acquire: `set_next ( start, 2 )
         endcase
   end
   
   always_ff @(posedge clk) begin
      state <= state_next ;
      count <= count_next ;
   end

   // ADC control signals

   always_ff @(posedge clk) begin 
      convst <= state_next == start ;
      sck <= state_next == transfer && !count_next[0] ;
   end

   // ADC input multiplexer channel number; incremented at end of
   // transfer

   logic [2:0] ch ;

   always_ff @(posedge clk)
      ch <= reset ? '0 :
            state == transfer && state_next == acquire ? ch + 1'b1 :
            ch ;

   // ADC configuration on SDI

   logic [11:0] adccfg ;
   assign adccfg = { 1'b1, ch[0], ch[2:1], 2'b10, 6'b0 }  ;

   always_ff @(posedge clk)
      sdi <= state_next == transfer ? adccfg[count_next >> 1] : '0 ;

   // ADC data on SDO

   logic [11:0] sample ;
   always_ff @(posedge clk)
      sample <= state == transfer && !sck ? { sample[10:0], sdo } : sample ;
   
   // At end of data transfer the sample value in the shift register
   // is transferred to the register file.  The channel number is the
   // one configured at the start of the previous transfer.

   logic [31:0] mem [8] ;
   
   always_ff @(posedge clk)
      if ( state == transfer && state_next == acquire ) 
         mem[ch-1'b1] <= sample ;

   // CPU interface
   
   assign readdata = mem[address] ;

endmodule
     
