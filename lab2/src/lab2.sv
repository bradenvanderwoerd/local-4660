// lab1.sv
// This module displays the number of clicks on the encoder on the 7-segment display.
// Braden Vanderwoerd, 1/13/2026

module lab1
	( input logic clk50,
	  output logic [7:0] leds,
	  output logic [3:0] ct,
	  input logic enc1a, enc1b ) ;

	// 7-segment decoder values for hexadecimal digits 0-F
	logic [7:0] decoder7 [0:15] ;
	assign decoder7 = '{ 63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113} ;
	
	// Clock divider
	logic [15:0] clk_count ;
	always_ff @(posedge clk50) clk_count
		<= clk_count == 16'b0 ? 16'd24999 :
			clk_count - 1 ;
			
	logic clk1 ;
	always_ff @(posedge clk50) clk1
		<=  clk_count == 16'b0 ? ~clk1 :
			clk1 ;
	
	// Encoder state machine and counter
	logic [5:0] counter ;
	logic [3:0] state ;
	logic enable, up;
	
	always_ff @(posedge clk1) state
		<= { state[1:0], enc1a, enc1b } ;
	
	assign enable = state[3] == state[1] && state[2] != state[0] ||
			        state[3] != state[1] && state[2] == state[0] ;
			
	assign up = ~enable ? 1'b0 :
				state[3] && state[0] ||
				~state[3] && ~state[0] ;
			
	always_ff @(posedge clk1) counter
		<= ~enable ? counter :
			up ? counter + 1 :
			counter - 1 ;
	
    // Output to 7-segment display and LEDs
	assign ct = 4'b1110 ;
	assign leds = decoder7[counter[5:2]] ;
	
endmodule