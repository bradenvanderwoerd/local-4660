// bcnt.sv
// Description: 14 bit binary counter
// Braden Vanderwoerd, 1/18/2026

module bcnt
    ( input logic clk,
      input logic up, down, reset,
      output logic [13:0] n) ;

    always_ff @(posedge clk) n
        <= reset ? 14'd0 :
            ~up && ~down ? n :
                up ? n == 14'b11111111111111 ? 14'd0 : n + 1 :
                     n == 14'd0 ? 14'b11111111111111 : n - 1 ;
endmodule