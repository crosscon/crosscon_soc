set bitfile [lindex $argv 0]

if { [file exists $bitfile] != 1 } {

    puts "No bitfile $bitfile"

    quit

} else {

    puts "Using bitfile $bitfile"

}

load_features labtools

open_hw

connect_hw_server -url TCP:localhost:3121

set targu [get_hw_targets *]

current_hw_target $targu

open_hw_target

set first_hw_device [lindex [get_hw_devices] 0]

current_hw_device $first_hw_device

set_property PROGRAM.FILE $bitfile $first_hw_device

# if ila included: set_property PROBES.FILE {C:/design.ltx} $first_hw_device

program_hw_devices $first_hw_device

# in case of "ERROR: [Labtools 27-3165] End of startup status: LOW"
# check that bitstream file is for target FPGA

# if ila included: refresh_hw_device $first_hw_device

quit
