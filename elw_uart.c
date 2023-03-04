#include "elw_uart.h"
#include "pin_mux.h"
#include "fsl_lpsci.h"
#include "board.h"
#include "peripherals.h"

#define UART_BASE_ADDR  BOARD_LPSCI_1_PERIPHERAL

const lpsci_config_t uart_config = {
        .baudRate_Bps = 115200U,
        .parityMode = kLPSCI_ParityDisabled,
        .stopBitCount = kLPSCI_OneStopBit,
        .enableTx = true,
        .enableRx = true
};

static elw_uart_isr_callback_t isr_callback = NULL;

void elw_uart_init(void)
{
    BOARD_InitDEBUG_UART();
    LPSCI_Init(UART_BASE_ADDR, &uart_config, BOARD_DEBUG_UART_CLK_FREQ);
}

void elw_uart_tx_byte(uint8_t data)
{
    LPSCI_WriteBlocking(UART_BASE_ADDR, &data, 1);
}

void elw_uart_tx_buffer(uint8_t *buf, int size)
{
    LPSCI_WriteBlocking(UART_BASE_ADDR, buf, size);
}

void elw_uart_tx_string(char *str)
{
    LPSCI_WriteBlocking(UART_BASE_ADDR, (const uint8_t *) str, strlen(str));
}

int elw_uart_rx_byte(uint8_t *data)
{
    status_t ret;

    ret = LPSCI_ReadBlocking(UART_BASE_ADDR, data, 1);
    if (ret == kStatus_Success)
        return 0;
    else
        return -1;
}

int elw_uart_rx_buffer(uint8_t *buf, int qtd)
{
    status_t ret;

    ret = LPSCI_ReadBlocking(UART_BASE_ADDR, buf, qtd);
    if (ret == kStatus_Success)
        return 0;
    else
        return -1;
}

void elw_uart_rx_irq_enable(elw_uart_isr_callback_t callback)
{
    isr_callback = callback;

    LPSCI_EnableInterrupts(UART_BASE_ADDR, kLPSCI_RxDataRegFullInterruptEnable);
    EnableIRQ(BOARD_UART_IRQ);
}

void elw_uart_rx_irq_disable(void)
{
    DisableIRQ(BOARD_UART_IRQ);
    LPSCI_DisableInterrupts(UART_BASE_ADDR, kLPSCI_RxDataRegFullInterruptEnable);

    isr_callback = NULL;
}

void UART0_IRQHandler(void)
{
    uint8_t data;

    if (LPSCI_GetStatusFlags(UART_BASE_ADDR) & kLPSCI_RxDataRegFullFlag) {
        data = LPSCI_ReadByte(UART_BASE_ADDR);
        if (isr_callback != NULL)
            isr_callback(data);
    }
}
