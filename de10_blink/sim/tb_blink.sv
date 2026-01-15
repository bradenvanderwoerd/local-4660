`timescale 1ns/1ps

module tb_blink;
    logic clk;
    logic led;

    // Instantiate the Unit Under Test (UUT)
    blink uut (
        .clk(clk),
        .led(led)
    );

    // Generate Clock
    initial begin
        clk = 0;
        forever #10 clk = ~clk; // Toggle every 10ns
    end

    // Test Sequence
    initial begin
        $dumpfile("blink.vcd"); // Create waveform file
        $dumpvars(0, tb_blink);

        // Run for enough time to see some counting
        #100000;
        $finish;
    end
endmodule