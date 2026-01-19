// lab2.sv
// Description:
// Braden Vanderwoerd, 1/18/2026

module lab2
	( input logic clk50,
	  output logic [7:0] leds,
	  output logic [3:0] ct,
	  input logic enc1a, enc1b, s1 ) ;

	// 7-segment decoder values for hexadecimal digits 0-F
	logic [7:0] decoder7 [0:15] ;
	assign decoder7 = '{ 63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113} ;
	
	// Clock divider
	logic clk, clk131k;
    clkdiv c0(clk50, clk);
    clkdiv c1(clk50, clk131k);
	
	// Encoder state machine and counter
	logic [3:0] counter ;
	logic [3:0] state ;
	logic enable, up;
	
	enc e0(clk, up, enable, enc1a, enc1b) ;
			
	always_ff @(posedge clk) counter
		<= ~s1 ? 0 :
           ~enable ? counter :
			up ? counter + 1 :
			counter - 1 ;
	
    // Output to 7-segment display and LEDs
	assign ct = 4'b1110 ;
	assign leds = decoder7[counter[3:0]] ;
	
endmodule