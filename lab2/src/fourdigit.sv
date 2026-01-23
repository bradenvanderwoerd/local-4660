// fourdigit.sv
// Four digit 7-segment display driver
// Braden Vanderwoerd, 1/18/2026

module fourdigit
    ( input logic clk,
      input logic [15:0] value,
      output logic [3:0] ct,
      output logic [7:0] seg ) ;

	logic [7:0] decoder7 [0:15] ;
	assign decoder7 = '{ 63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113} ;

    always_ff @(posedge clk) ct
        <= ct == 4'b1110 ? 4'b1101 :
           ct == 4'b1101 ? 4'b1011 :
           ct == 4'b1011 ? 4'b0111 :
                           4'b1110 ;

    assign seg = ct == 4'b1110 ? decoder7[value[3:0]] :
                 ct == 4'b1101 ? decoder7[value[7:4]] :
                 ct == 4'b1011 ? decoder7[value[11:8]] :
                                 decoder7[value[15:12]] ;

endmodule