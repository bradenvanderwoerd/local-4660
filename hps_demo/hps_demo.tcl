package require -exact qsys 14.0

create_system {hps_demo}
set_project_property DEVICE_FAMILY {Cyclone V}
set_project_property DEVICE {5CSEMA4U23C6}

# Add all modules to the system
add_instance clk_0 clock_source
set_instance_parameter_value clk_0 {clockFrequency} {50000000}
set_instance_parameter_value clk_0 {clockFrequencyKnown} {true}

add_instance hps_0 altera_hps

# Clock connections
add_connection clk_0.clk hps_0.f2h_axi_clock
add_connection clk_0.clk hps_0.f2h_sdram0_clock
add_connection clk_0.clk hps_0.h2f_axi_clock
add_connection clk_0.clk hps_0.h2f_lw_axi_clock
add_connection hps_0.h2f_reset clk_0.clk_in_reset

# Export pins
add_interface clk50 clock sink
set_interface_property clk50 EXPORT_OF clk_0.clk_in
add_interface reset reset sink
set_interface_property clk_reset EXPORT_OF clk_0.clk_in_reset

add_interface f2h altera_axi slave
set_interface_property f2h EXPORT_OF hps_0.f2h_axi_slave

add_interface f2h_sdram altera_axi slave
set_interface_property f2h_sdram EXPORT_OF hps_0.f2h_sdram0_data

add_interface h2f altera_axi master
set_interface_property h2f EXPORT_OF hps_0.h2f_axi_master

add_interface h2f_lw altera_axi master
set_interface_property h2f_lw EXPORT_OF hps_0.h2f_lw_axi_master

add_interface memory conduit end
set_interface_property memory EXPORT_OF hps_0.memory

save_system {hps_demo.qsys}