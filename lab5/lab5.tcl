package require -exact qsys 14.0

create_system {lab5}
set_project_property DEVICE_FAMILY {Cyclone V}
set_project_property DEVICE {5CSEMA4U23C6}

# Add all modules to the system
add_instance clk_0 clock_source
set_instance_parameter_value clk_0 {clockFrequency} {50000000}
set_instance_parameter_value clk_0 {clockFrequencyKnown} {true}

add_instance cpu intel_niosv_m
set_instance_parameter_value cpu {enableDebugReset} {true}
set_instance_parameter_value cpu {enableAvalonInterface} {true}
set_instance_parameter_value cpu {resetSlave} {mem.s1}

add_instance mem altera_avalon_onchip_memory2
set_instance_parameter_value mem {memorySize} {262144}
set_instance_parameter_value mem {initializationFileName} {hello.hex}
set_instance_parameter_value mem {useNonDefaultInitFile} {true}

add_instance jtag_uart_0 altera_avalon_jtag_uart

add_instance pio altera_avalon_pio

add_instance ltc2308 ltc2308

add_instance spi altera_avalon_spi
set_instance_parameter_value spi {targetClockRate} {6000000}

# Clock connections
add_connection clk_0.clk cpu.clk
add_connection clk_0.clk mem.clk1
add_connection clk_0.clk jtag_uart_0.clk
add_connection clk_0.clk pio.clk
add_connection clk_0.clk ltc2308.clock_sink
add_connection clk_0.clk spi.clk

add_connection clk_0.clk_reset cpu.reset
add_connection clk_0.clk_reset mem.reset1
add_connection clk_0.clk_reset jtag_uart_0.reset
add_connection clk_0.clk_reset pio.reset
add_connection clk_0.clk_reset ltc2308.reset_sink
add_connection clk_0.clk_reset spi.reset

# CPU output connections
add_connection cpu.instruction_manager cpu.dm_agent
set_connection_parameter_value cpu.instruction_manager/cpu.dm_agent baseAddress {0x00090000}
add_connection cpu.instruction_manager mem.s1
set_connection_parameter_value cpu.instruction_manager/mem.s1 baseAddress {0x00040000}
add_connection cpu.data_manager cpu.timer_sw_agent
set_connection_parameter_value cpu.data_manager/cpu.timer_sw_agent baseAddress {0x000a0000}
add_connection cpu.data_manager cpu.dm_agent
set_connection_parameter_value cpu.data_manager/cpu.dm_agent baseAddress {0x00090000}
add_connection cpu.data_manager mem.s1
set_connection_parameter_value cpu.data_manager/mem.s1 baseAddress {0x00040000}
add_connection cpu.data_manager jtag_uart_0.avalon_jtag_slave
set_connection_parameter_value cpu.data_manager/jtag_uart_0.avalon_jtag_slave baseAddress {0x000a0070}
add_connection cpu.data_manager pio.s1
set_connection_parameter_value cpu.data_manager/pio.s1 baseAddress {0x000a0060}
add_connection cpu.data_manager ltc2308.avalon_slave
set_connection_parameter_value cpu.data_manager/ltc2308.avalon_slave baseAddress {0x000a0078}
add_connection cpu.data_manager spi.spi_control_port
set_connection_parameter_value cpu.data_manager/spi.spi_control_port baseAddress {0x000a0040}
add_connection cpu.dbg_reset_out cpu.ndm_reset_in

# JTAG UART output connections
add_connection cpu.platform_irq_rx jtag_uart_0.irq
set_connection_parameter_value cpu.platform_irq_rx/jtag_uart_0.irq irqNumber {15}

# Export pins
add_interface clk50 clock sink
set_interface_property clk50 EXPORT_OF clk_0.clk_in
add_interface reset reset sink
set_interface_property reset EXPORT_OF clk_0.clk_in_reset
add_interface pio conduit end
set_interface_property pio EXPORT_OF pio.external_connection
add_interface adc conduit end
set_interface_property adc EXPORT_OF ltc2308.adc0
add_interface spi conduit end
set_interface_property spi EXPORT_OF spi.external

save_system {lab5.qsys}