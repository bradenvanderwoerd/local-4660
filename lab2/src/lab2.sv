// lab2.sv
// Description:
// Braden Vanderwoerd, 1/18/2026

module lab2
	( input logic clk50,
	  output logic [7:0] leds,
	  output logic [3:0] ct,
      output logic spkr,
	  input logic enc1a, enc1b, s1 ) ;
	
    logic reset ;
    assign reset = ~s1 ;

	// Clock divider
	logic clk, clk131k;
    clkdiv c0(clk50, clk) ;
    clkdiv #(.fout(131_072)) c1 (clk50, clk131k) ;
	
    // Rotary encoder and BCD counters
	logic enable, up, down;
	enc e0(clk, up, down, enc1a, enc1b) ;
	
    logic [15:0] counter ;
    logic carry0, carry1, carry2, carry3, borrow0, borrow1, borrow2, borrow3 ;
    bcdcnt b0(clk, up, down, reset, counter[3:0], carry0, borrow0) ;
    bcdcnt b1(clk, carry0, borrow0, reset, counter[7:4], carry1, borrow1) ;
    bcdcnt b2(clk, carry1, borrow1, reset, counter[11:8], carry2, borrow2) ;
	bcdcnt b3(clk, carry2, borrow2, reset, counter[15:12], carry3, borrow3) ;

    // 4-digit 7-segment display driver
    fourdigit f0(clk131k, counter, ct, leds) ;

    // Binary counter and tone generator
    logic [13:0] frequency ;
    bcnt bc0(clk, up, down, reset, frequency) ;
    
    logic [16:0] phase ;
    always_ff @(posedge clk131k) phase
        <= phase + {3'b0, frequency} ;
    assign spkr = phase[16] ;
	
endmodule