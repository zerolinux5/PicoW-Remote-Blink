#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdio.h>

const int BUTTON_PIN = 20;
const uint BUF_LEN = 1;

// Buffers for data transfer over SPI
static uint8_t out_buf[BUF_LEN], in_buf[BUF_LEN];

void init_spi()
{
    // Initialize the SPI with a transfer speed of 1 MHz
    spi_init(spi_default, 1000 * 1000);

    // Set the function of the pins for the SPI communication
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);
}

void init_button(int pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_down(pin);
}

void gpio_callback(uint gpio, uint32_t events)
{
    // If events is set to EDGE_FALL, the button was pressed
    if (events & GPIO_IRQ_EDGE_FALL)
    {
        out_buf[0] = 1;
        spi_write_read_blocking(spi_default, out_buf, in_buf, BUF_LEN);
    }
}

int main()
{
    stdio_init_all();
    // Check if the default SPI pins are defined
#if !defined(spi_default) || !defined(PICO_DEFAULT_SPI_SCK_PIN) || !defined(PICO_DEFAULT_SPI_TX_PIN) || !defined(PICO_DEFAULT_SPI_RX_PIN) || !defined(PICO_DEFAULT_SPI_CSN_PIN)
#warning spi/spi_master example requires a board with SPI pins
    puts("Default SPI pins were not defined");
#else
    init_spi();
    init_button(BUTTON_PIN);

    // Track the state of the LED on the other side.
    bool state = false;

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    while (true)
    {
    }
#endif
}
