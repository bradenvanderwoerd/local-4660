// enc.sv
// Description:
// Braden Vanderwoerd, 1/18/2026

module lab2
	( input logic clk,
	  output logic up, enable,
	  input logic enc1a, enc1b ) ;

    always_ff @(posedge clk) state
		<= { state[1:0], enc1a, enc1b } ;

    assign enable = state == 4'b1101 || state == 4'b0100 ||
                    state == 4'b0010 || state == 4'b1011 ||
                    state == 4'b1110 || state == 4'b1000 ||
                    state == 4'b0001 || state == 4'b0111 ;
			
	assign up = state == 4'b1101 || state == 4'b0100 ||
                state == 4'b0010 || state == 4'b1011 ;

endmodule