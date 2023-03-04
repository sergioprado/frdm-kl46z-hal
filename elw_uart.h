#ifndef ELW_UART_H_
#define ELW_UART_H_

#include <stdint.h>

/**
 * ISR callback
 *
 * @param  data  Byte received from the UART interface
 *
 * @return none
 */
typedef void (*elw_uart_isr_callback_t)(uint8_t data);

/**
 * Initialize UART
 *
 * @param  none
 *
 * @return none
 */
void elw_uart_init(void);

/**
 * Send a byte to the UART interface
 *
 * @param  data  byte to be sent
 *
 * @return none
 */
void elw_uart_tx_byte(uint8_t data);

/**
 * Send a buffer to the UART interface
 *
 * @param  buf  buffer to be sent
 * @param  size size of the buffer to be sent
 *
 * @return none
 */
void elw_uart_tx_buffer(uint8_t *buf, int size);

/**
 * Send a string to the UART interface
 *
 * @param  str  string to be sent
 *
 * @return none
 */
void elw_uart_tx_string(char *str);

/**
 * Receive a byte from the UART interface (polling mode).
 *
 * @param  data  address to save the byte received
 *
 * @return 0 on success or -1 on error
 */
int elw_uart_rx_byte(uint8_t *data);

/**
 * Receive a buffer from the UART interface (pooling mode).
 *
 * @param  buf  buffer to save received data
 * @param  qtd  number of bytes to wait for
 *
 * @return 0 on success or -1 on error
 */
int elw_uart_rx_buffer(uint8_t *buf, int qtd);

/**
 * Enable UART RX interrupt
 *
 * @param  callback  Function to be called to handle the interrupt
 *
 * @return none
 */
void elw_uart_rx_irq_enable(elw_uart_isr_callback_t callback);

/**
 * Disable UART RX interrupt
 *
 * @param  none
 *
 * @return none
 */
void elw_uart_rx_irq_disable(void);

#endif /* ELW_UART_H_ */
