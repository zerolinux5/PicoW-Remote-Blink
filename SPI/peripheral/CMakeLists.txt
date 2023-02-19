add_executable(peripheral
        peripheral.cpp
        )

# Pull in basic dependencies
target_link_libraries(peripheral pico_stdlib hardware_spi)

# create map/bin/hex file etc.
pico_add_extra_outputs(peripheral)