// bcdcnt.sv
// BCD counter module
// Braden Vanderwoerd, 1/18/2026

module bcdcnt
    ( input logic clk,
      input logic up, down, reset,
      output logic [3:0] n ,
      output logic carry, borrow) ;

    always_ff @(posedge clk) n
        <= reset ? 4'd0 :
            ~up && ~down ? n :
            up ? n == 4'd9 ? 4'd0 : n + 1 :
                 n == 4'd0 ? 4'd9 : n - 1 ;

    assign carry = up && n == 4'd9 ;
    assign borrow = down && n == 4'd0 ;

endmodule