module blink (
    input  logic clk,      // 50MHz Clock
    output logic led       // LED 0
);

    // 32-bit counter
    logic [31:0] counter;

    always_ff @(posedge clk) begin
        counter <= counter + 1;
    end

    // Take the 24th bit (approx 1.5Hz blink rate at 50MHz)
    assign led = counter[24];

endmodule