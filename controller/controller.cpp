#include "pico/stdlib.h"
#include "hardware/spi.h"

const int BUTTON_PIN = 20;
const uint BUF_LEN = 1;

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

    // Buffers for data transfer over SPI
    uint8_t out_buf[BUF_LEN], in_buf[BUF_LEN];

    while (true)
    {
        int value = gpio_get(BUTTON_PIN);
        // If the button is pressed and the state change is correct, send a 1 over SPI
        if (value == 1 && state == false)
        {
            state = true;
            out_buf[0] = 1;
            spi_write_read_blocking(spi_default, out_buf, in_buf, BUF_LEN);
            sleep_ms(1000);
        }
        else if (value == 1 && state == true)
        {
            state = false;
            out_buf[0] = 1;
            spi_write_read_blocking(spi_default, out_buf, in_buf, BUF_LEN);
            sleep_ms(1000);
        }
    }
#endif
}
