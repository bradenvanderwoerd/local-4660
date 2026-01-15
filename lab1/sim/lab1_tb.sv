

module tb_lab1;

    // 1. Signal Declaration matching your Top-Level Module
    logic clk50;
    logic enc1a;
    logic enc1b;
    logic [7:0] leds; // Anodes (active high segments)
    logic [3:0] ct;   // Cathodes (active low digit select)

    // 2. Instantiate the DUT (Device Under Test)
    // Ensure the port names match your specific "lab1" module definition
    lab1 uut (
        .clk50(clk50),
        .enc1a(enc1a),
        .enc1b(enc1b),
        .leds(leds),
        .ct(ct)
    );

    // 3. Clock Generation (50 MHz)
    // Period = 20ns
    initial begin
        clk50 = 0;
        forever #10 clk50 = ~clk50;
    end

    // VCD Generation for Waveform Viewing
    initial begin
        $dumpfile("waveform.vcd"); // Specifies the output filename
        $dumpvars(0, tb_lab1);     // Dumps all signals in the "tb_lab1" hierarchy
    end

    // 4. Tasks to Simulate Encoder Rotation
    // Note: Delays must be > 1ms because the internal clock divider
    // runs at 1 kHz (1ms period). We use 1.5ms to be safe.
    
    // Task: Move one detent Clockwise (CW)
    // Sequence: 11 -> 01 -> 00 -> 10 -> 11
    task simulate_cw_click();
        begin
            // Start at default idle (11)
            enc1a = 1; enc1b = 1; 
            #1500000; // Wait 1.5 ms
            
            // Transition 1: 01
            $display("  -> CW Step 1: 01");
            enc1a = 0; enc1b = 1; 
            #1500000;

            // Transition 2: 00
            $display("  -> CW Step 2: 00");
            enc1a = 0; enc1b = 0; 
            #1500000;

            // Transition 3: 10
            $display("  -> CW Step 3: 10");
            enc1a = 1; enc1b = 0; 
            #1500000;

            // Transition 4: 11 (Back to detent)
            $display("  -> CW Step 4: 11 (Detent Completed)");
            enc1a = 1; enc1b = 1; 
            #1500000;
        end
    endtask

    // Task: Move one detent Counter-Clockwise (CCW)
    // Sequence: 11 -> 10 -> 00 -> 01 -> 11
    task simulate_ccw_click();
        begin
            enc1a = 1; enc1b = 1; 
            #1500000;
            
            // Transition 1: 10
            $display("  -> CCW Step 1: 10");
            enc1a = 1; enc1b = 0; 
            #1500000;

            // Transition 2: 00
            $display("  -> CCW Step 2: 00");
            enc1a = 0; enc1b = 0; 
            #1500000;

            // Transition 3: 01
            $display("  -> CCW Step 3: 01");
            enc1a = 0; enc1b = 1; 
            #1500000;

            // Transition 4: 11
            $display("  -> CCW Step 4: 11 (Detent Completed)");
            enc1a = 1; enc1b = 1; 
            #1500000;
        end
    endtask

    // 5. Main Test Sequence
    initial begin
        // Initialize Inputs
        enc1a = 1; // Pull-ups imply default high 
        enc1b = 1;

        // Wait for global reset or PLL lock if applicable
        $display("Starting Simulation...");
        #2000000; // Wait 2ms for initial stability

        // --- TEST 1: Clockwise Rotation ---
        $display("\n--- Testing Clockwise Rotation ---");
        simulate_cw_click(); // Should increment count
        simulate_cw_click(); // Should increment count again

        // Check if Cathode 0 is active (low)
        if (ct[0] == 0) 
            $display("Check: Digit 0 is ENABLED (ct[0] is low).");
        else 
            $error("Error: Digit 0 should be enabled.");

        // --- TEST 2: Counter-Clockwise Rotation ---
        $display("\n--- Testing Counter-Clockwise Rotation ---");
        simulate_ccw_click(); // Should decrement count

        $display("\nSimulation Complete.");
        $stop;
    end

endmodule