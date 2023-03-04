#include "elw_btn.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_port.h"

#define SW1_GPIO_PIN_MASK  (1 << BOARD_SW1_GPIO_PIN)
#define SW3_GPIO_PIN_MASK  (1 << BOARD_SW3_GPIO_PIN)

static elw_btn_isr_callback_t isr_callback = NULL;

uint8_t elw_btn_status_sw1(void)
{
    if (!GPIO_PinRead(BOARD_SW1_GPIO, BOARD_SW1_GPIO_PIN))
        return ELW_BTN_PRESSED;
    else
        return ELW_BTN_RELEASED;
}

uint8_t elw_btn_status_sw3(void)
{
    if (!GPIO_PinRead(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN))
        return ELW_BTN_PRESSED;
    else
        return ELW_BTN_RELEASED;
}

void elw_btn_irq_enable(elw_btn_isr_callback_t callback)
{
    isr_callback = callback;

    PORT_SetPinInterruptConfig(BOARD_SW1_PORT, BOARD_SW1_GPIO_PIN, kPORT_InterruptRisingEdge);
    PORT_SetPinInterruptConfig(BOARD_SW3_PORT, BOARD_SW3_GPIO_PIN, kPORT_InterruptRisingEdge);
    EnableIRQ(PORTC_PORTD_IRQn);
}

void elw_btn_irq_disable(void)
{
    DisableIRQ(PORTC_PORTD_IRQn);
    PORT_SetPinInterruptConfig(BOARD_SW1_PORT, BOARD_SW1_GPIO_PIN, kPORT_InterruptOrDMADisabled);
    PORT_SetPinInterruptConfig(BOARD_SW3_PORT, BOARD_SW3_GPIO_PIN, kPORT_InterruptOrDMADisabled);

    isr_callback = NULL;
}

void elw_btn_init(void)
{
    BOARD_InitButtons();
    elw_btn_irq_disable();
}

void PORTC_PORTD_IRQHandler(void)
{
    if (GPIO_PortGetInterruptFlags(BOARD_SW1_GPIO) & SW1_GPIO_PIN_MASK) {
        GPIO_PortClearInterruptFlags(BOARD_SW1_GPIO, SW1_GPIO_PIN_MASK);
        if (isr_callback != NULL)
            isr_callback(ELW_BTN_SW1);
    }

    if (GPIO_PortGetInterruptFlags(BOARD_SW3_GPIO) & SW3_GPIO_PIN_MASK) {
        GPIO_PortClearInterruptFlags(BOARD_SW3_GPIO, SW3_GPIO_PIN_MASK);
        if (isr_callback != NULL)
            isr_callback(ELW_BTN_SW3);
    }
}
