#include "pico/stdlib.h"
#include "hardware/spi.h"

const int LED_PIN = 21;
const uint BUF_LEN = 1;

void init_spi()
{
    spi_init(spi_default, 1000 * 1000);
    spi_set_slave(spi_default, true);
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);
}

void init_gpio_out(int pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

int main()
{
    stdio_init_all();
#if !defined(spi_default) || !defined(PICO_DEFAULT_SPI_SCK_PIN) || !defined(PICO_DEFAULT_SPI_TX_PIN) || !defined(PICO_DEFAULT_SPI_RX_PIN) || !defined(PICO_DEFAULT_SPI_CSN_PIN)
#warning spi/spi_master example requires a board with SPI pins
    puts("Default SPI pins were not defined");
#else
    init_spi();

    init_gpio_out(LED_PIN);

    bool state = false;

    uint8_t out_buf[BUF_LEN], in_buf[BUF_LEN];
    while (true)
    {
        spi_write_read_blocking(spi_default, out_buf, in_buf, BUF_LEN);
        if (in_buf[0] == 1 && state == false)
        {
            state = true;
            gpio_put(LED_PIN, 1);
            sleep_ms(1000);
        }
        else if (in_buf[0] == 1 && state == true)
        {
            state = false;
            gpio_put(LED_PIN, 0);
            sleep_ms(1000);
        }
    }
#endif
}
