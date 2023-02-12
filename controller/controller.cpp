#include "pico/stdlib.h"
#include "hardware/spi.h"

const int BUTTON_PIN = 20;
const uint BUF_LEN = 1;

void init_spi()
{
    spi_init(spi_default, 1000 * 1000);
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);
}

int main()
{
    stdio_init_all();
#if !defined(spi_default) || !defined(PICO_DEFAULT_SPI_SCK_PIN) || !defined(PICO_DEFAULT_SPI_TX_PIN) || !defined(PICO_DEFAULT_SPI_RX_PIN) || !defined(PICO_DEFAULT_SPI_CSN_PIN)
#warning spi/spi_master example requires a board with SPI pins
    puts("Default SPI pins were not defined");
#else
    init_spi();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);
    bool state = false;

    uint8_t out_buf[BUF_LEN], in_buf[BUF_LEN];
    while (true)
    {
        int value = gpio_get(BUTTON_PIN);
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
