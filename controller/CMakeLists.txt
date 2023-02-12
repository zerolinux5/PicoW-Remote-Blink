add_executable(controller
        controller.cpp
        )

# Pull in basic dependencies
target_link_libraries(controller pico_stdlib hardware_spi)

# create map/bin/hex file etc.
pico_add_extra_outputs(controller)