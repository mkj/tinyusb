/*
 * Automatically generated by LUNA; edits will be discarded on rebuild.
 * (Most header files phrase this 'Do not edit.'; be warned accordingly.)
 *
 * Generated: 2021-06-22 15:55:37.475094.
 */


#ifndef __SOC_RESOURCES_H__
#define __SOC_RESOURCES_H__

#include <stdint.h>

#include <stdbool.h>

//
// Environment Information
//

#define PLATFORM_NAME "LUNA r0.4"

#ifndef read_csr
#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })
#endif

#ifndef write_csr
#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })
#endif

#ifndef set_csr
#define set_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })
#endif

#ifndef clear_csr
#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })
#endif

#ifndef MSTATUS_MIE
#define MSTATUS_MIE         0x00000008
#endif

//
// Minerva headers
//

static inline uint32_t irq_getie(void)
{
        return (read_csr(mstatus) & MSTATUS_MIE) != 0;
}

static inline void irq_setie(uint32_t ie)
{
        if (ie) {
                set_csr(mstatus, MSTATUS_MIE);
        } else {
                clear_csr(mstatus, MSTATUS_MIE);
        }
}

static inline uint32_t irq_getmask(void)
{
        return read_csr(0x330);
}

static inline void irq_setmask(uint32_t value)
{
        write_csr(0x330, value);
}

static inline uint32_t pending_irqs(void)
{
        return read_csr(0x360);
}

//
// Peripherals
//
#define TIMER_RELOAD_ADDRESS (0x00020000U)
#define TIMER_RELOAD_SIZE (4)
static inline uint32_t timer_reload_read(void) {
    volatile uint32_t *reg = (uint32_t *)TIMER_RELOAD_ADDRESS;
    return *reg;
}
static inline void timer_reload_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)TIMER_RELOAD_ADDRESS;
    *reg = value;
}

#define TIMER_EN_ADDRESS (0x00020004U)
#define TIMER_EN_SIZE (4)
static inline uint32_t timer_en_read(void) {
    volatile uint32_t *reg = (uint32_t *)TIMER_EN_ADDRESS;
    return *reg;
}
static inline void timer_en_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)TIMER_EN_ADDRESS;
    *reg = value;
}

#define TIMER_CTR_ADDRESS (0x00020008U)
#define TIMER_CTR_SIZE (4)
static inline uint32_t timer_ctr_read(void) {
    volatile uint32_t *reg = (uint32_t *)TIMER_CTR_ADDRESS;
    return *reg;
}
static inline void timer_ctr_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)TIMER_CTR_ADDRESS;
    *reg = value;
}

#define TIMER_EV_STATUS_ADDRESS (0x00020010U)
#define TIMER_EV_STATUS_SIZE (4)
static inline uint32_t timer_ev_status_read(void) {
    volatile uint32_t *reg = (uint32_t *)TIMER_EV_STATUS_ADDRESS;
    return *reg;
}

#define TIMER_EV_PENDING_ADDRESS (0x00020014U)
#define TIMER_EV_PENDING_SIZE (4)
static inline uint32_t timer_ev_pending_read(void) {
    volatile uint32_t *reg = (uint32_t *)TIMER_EV_PENDING_ADDRESS;
    return *reg;
}
static inline void timer_ev_pending_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)TIMER_EV_PENDING_ADDRESS;
    *reg = value;
}

#define TIMER_EV_ENABLE_ADDRESS (0x00020018U)
#define TIMER_EV_ENABLE_SIZE (4)
static inline uint32_t timer_ev_enable_read(void) {
    volatile uint32_t *reg = (uint32_t *)TIMER_EV_ENABLE_ADDRESS;
    return *reg;
}
static inline void timer_ev_enable_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)TIMER_EV_ENABLE_ADDRESS;
    *reg = value;
}

#define UART_DIVISOR_ADDRESS (0x00030000U)
#define UART_DIVISOR_SIZE (4)
static inline uint32_t uart_divisor_read(void) {
    volatile uint32_t *reg = (uint32_t *)UART_DIVISOR_ADDRESS;
    return *reg;
}
static inline void uart_divisor_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)UART_DIVISOR_ADDRESS;
    *reg = value;
}

#define UART_RX_DATA_ADDRESS (0x00030004U)
#define UART_RX_DATA_SIZE (4)
static inline uint32_t uart_rx_data_read(void) {
    volatile uint32_t *reg = (uint32_t *)UART_RX_DATA_ADDRESS;
    return *reg;
}

#define UART_RX_RDY_ADDRESS (0x00030008U)
#define UART_RX_RDY_SIZE (4)
static inline uint32_t uart_rx_rdy_read(void) {
    volatile uint32_t *reg = (uint32_t *)UART_RX_RDY_ADDRESS;
    return *reg;
}

#define UART_RX_ERR_ADDRESS (0x0003000cU)
#define UART_RX_ERR_SIZE (4)
static inline uint32_t uart_rx_err_read(void) {
    volatile uint32_t *reg = (uint32_t *)UART_RX_ERR_ADDRESS;
    return *reg;
}

#define UART_TX_DATA_ADDRESS (0x00030010U)
#define UART_TX_DATA_SIZE (4)
static inline void uart_tx_data_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)UART_TX_DATA_ADDRESS;
    *reg = value;
}

#define UART_TX_RDY_ADDRESS (0x00030014U)
#define UART_TX_RDY_SIZE (4)
static inline uint32_t uart_tx_rdy_read(void) {
    volatile uint32_t *reg = (uint32_t *)UART_TX_RDY_ADDRESS;
    return *reg;
}

#define UART_EV_STATUS_ADDRESS (0x00030020U)
#define UART_EV_STATUS_SIZE (4)
static inline uint32_t uart_ev_status_read(void) {
    volatile uint32_t *reg = (uint32_t *)UART_EV_STATUS_ADDRESS;
    return *reg;
}

#define UART_EV_PENDING_ADDRESS (0x00030024U)
#define UART_EV_PENDING_SIZE (4)
static inline uint32_t uart_ev_pending_read(void) {
    volatile uint32_t *reg = (uint32_t *)UART_EV_PENDING_ADDRESS;
    return *reg;
}
static inline void uart_ev_pending_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)UART_EV_PENDING_ADDRESS;
    *reg = value;
}

#define UART_EV_ENABLE_ADDRESS (0x00030028U)
#define UART_EV_ENABLE_SIZE (4)
static inline uint32_t uart_ev_enable_read(void) {
    volatile uint32_t *reg = (uint32_t *)UART_EV_ENABLE_ADDRESS;
    return *reg;
}
static inline void uart_ev_enable_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)UART_EV_ENABLE_ADDRESS;
    *reg = value;
}

#define RAM_ADDRESS (0x00040000U)
#define RAM_SIZE (65536)

#define USB_DEVICE_CONTROLLER_CONNECT_ADDRESS (0x00050000U)
#define USB_DEVICE_CONTROLLER_CONNECT_SIZE (4)
static inline uint32_t usb_device_controller_connect_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_DEVICE_CONTROLLER_CONNECT_ADDRESS;
    return *reg;
}
static inline void usb_device_controller_connect_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_DEVICE_CONTROLLER_CONNECT_ADDRESS;
    *reg = value;
}

#define USB_DEVICE_CONTROLLER_EV_STATUS_ADDRESS (0x00050010U)
#define USB_DEVICE_CONTROLLER_EV_STATUS_SIZE (4)
static inline uint32_t usb_device_controller_ev_status_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_DEVICE_CONTROLLER_EV_STATUS_ADDRESS;
    return *reg;
}

#define USB_DEVICE_CONTROLLER_EV_PENDING_ADDRESS (0x00050014U)
#define USB_DEVICE_CONTROLLER_EV_PENDING_SIZE (4)
static inline uint32_t usb_device_controller_ev_pending_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_DEVICE_CONTROLLER_EV_PENDING_ADDRESS;
    return *reg;
}
static inline void usb_device_controller_ev_pending_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_DEVICE_CONTROLLER_EV_PENDING_ADDRESS;
    *reg = value;
}

#define USB_DEVICE_CONTROLLER_EV_ENABLE_ADDRESS (0x00050018U)
#define USB_DEVICE_CONTROLLER_EV_ENABLE_SIZE (4)
static inline uint32_t usb_device_controller_ev_enable_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_DEVICE_CONTROLLER_EV_ENABLE_ADDRESS;
    return *reg;
}
static inline void usb_device_controller_ev_enable_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_DEVICE_CONTROLLER_EV_ENABLE_ADDRESS;
    *reg = value;
}

#define USB_SETUP_DATA_ADDRESS (0x00060000U)
#define USB_SETUP_DATA_SIZE (4)
static inline uint32_t usb_setup_data_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_DATA_ADDRESS;
    return *reg;
}

#define USB_SETUP_RESET_ADDRESS (0x00060004U)
#define USB_SETUP_RESET_SIZE (4)
static inline void usb_setup_reset_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_RESET_ADDRESS;
    *reg = value;
}

#define USB_SETUP_EPNO_ADDRESS (0x00060008U)
#define USB_SETUP_EPNO_SIZE (4)
static inline uint32_t usb_setup_epno_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_EPNO_ADDRESS;
    return *reg;
}

#define USB_SETUP_HAVE_ADDRESS (0x0006000cU)
#define USB_SETUP_HAVE_SIZE (4)
static inline uint32_t usb_setup_have_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_HAVE_ADDRESS;
    return *reg;
}

#define USB_SETUP_PEND_ADDRESS (0x00060010U)
#define USB_SETUP_PEND_SIZE (4)
static inline uint32_t usb_setup_pend_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_PEND_ADDRESS;
    return *reg;
}

#define USB_SETUP_ADDRESS_ADDRESS (0x00060014U)
#define USB_SETUP_ADDRESS_SIZE (4)
static inline uint32_t usb_setup_address_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_ADDRESS_ADDRESS;
    return *reg;
}
static inline void usb_setup_address_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_ADDRESS_ADDRESS;
    *reg = value;
}

#define USB_SETUP_EV_STATUS_ADDRESS (0x00060020U)
#define USB_SETUP_EV_STATUS_SIZE (4)
static inline uint32_t usb_setup_ev_status_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_EV_STATUS_ADDRESS;
    return *reg;
}

#define USB_SETUP_EV_PENDING_ADDRESS (0x00060024U)
#define USB_SETUP_EV_PENDING_SIZE (4)
static inline uint32_t usb_setup_ev_pending_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_EV_PENDING_ADDRESS;
    return *reg;
}
static inline void usb_setup_ev_pending_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_EV_PENDING_ADDRESS;
    *reg = value;
}

#define USB_SETUP_EV_ENABLE_ADDRESS (0x00060028U)
#define USB_SETUP_EV_ENABLE_SIZE (4)
static inline uint32_t usb_setup_ev_enable_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_EV_ENABLE_ADDRESS;
    return *reg;
}
static inline void usb_setup_ev_enable_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_SETUP_EV_ENABLE_ADDRESS;
    *reg = value;
}

#define USB_IN_EP_DATA_ADDRESS (0x00070000U)
#define USB_IN_EP_DATA_SIZE (4)
static inline void usb_in_ep_data_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_DATA_ADDRESS;
    *reg = value;
}

#define USB_IN_EP_EPNO_ADDRESS (0x00070004U)
#define USB_IN_EP_EPNO_SIZE (4)
static inline uint32_t usb_in_ep_epno_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_EPNO_ADDRESS;
    return *reg;
}
static inline void usb_in_ep_epno_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_EPNO_ADDRESS;
    *reg = value;
}

#define USB_IN_EP_RESET_ADDRESS (0x00070008U)
#define USB_IN_EP_RESET_SIZE (4)
static inline void usb_in_ep_reset_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_RESET_ADDRESS;
    *reg = value;
}

#define USB_IN_EP_STALL_ADDRESS (0x0007000cU)
#define USB_IN_EP_STALL_SIZE (4)
static inline uint32_t usb_in_ep_stall_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_STALL_ADDRESS;
    return *reg;
}
static inline void usb_in_ep_stall_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_STALL_ADDRESS;
    *reg = value;
}

#define USB_IN_EP_IDLE_ADDRESS (0x00070010U)
#define USB_IN_EP_IDLE_SIZE (4)
static inline uint32_t usb_in_ep_idle_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_IDLE_ADDRESS;
    return *reg;
}

#define USB_IN_EP_HAVE_ADDRESS (0x00070014U)
#define USB_IN_EP_HAVE_SIZE (4)
static inline uint32_t usb_in_ep_have_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_HAVE_ADDRESS;
    return *reg;
}

#define USB_IN_EP_PEND_ADDRESS (0x00070018U)
#define USB_IN_EP_PEND_SIZE (4)
static inline uint32_t usb_in_ep_pend_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_PEND_ADDRESS;
    return *reg;
}

#define USB_IN_EP_PID_ADDRESS (0x0007001cU)
#define USB_IN_EP_PID_SIZE (4)
static inline uint32_t usb_in_ep_pid_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_PID_ADDRESS;
    return *reg;
}
static inline void usb_in_ep_pid_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_PID_ADDRESS;
    *reg = value;
}

#define USB_IN_EP_EV_STATUS_ADDRESS (0x00070020U)
#define USB_IN_EP_EV_STATUS_SIZE (4)
static inline uint32_t usb_in_ep_ev_status_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_EV_STATUS_ADDRESS;
    return *reg;
}

#define USB_IN_EP_EV_PENDING_ADDRESS (0x00070024U)
#define USB_IN_EP_EV_PENDING_SIZE (4)
static inline uint32_t usb_in_ep_ev_pending_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_EV_PENDING_ADDRESS;
    return *reg;
}
static inline void usb_in_ep_ev_pending_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_EV_PENDING_ADDRESS;
    *reg = value;
}

#define USB_IN_EP_EV_ENABLE_ADDRESS (0x00070028U)
#define USB_IN_EP_EV_ENABLE_SIZE (4)
static inline uint32_t usb_in_ep_ev_enable_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_EV_ENABLE_ADDRESS;
    return *reg;
}
static inline void usb_in_ep_ev_enable_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_IN_EP_EV_ENABLE_ADDRESS;
    *reg = value;
}

#define USB_OUT_EP_DATA_ADDRESS (0x00080000U)
#define USB_OUT_EP_DATA_SIZE (4)
static inline uint32_t usb_out_ep_data_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_DATA_ADDRESS;
    return *reg;
}

#define USB_OUT_EP_RESET_ADDRESS (0x00080004U)
#define USB_OUT_EP_RESET_SIZE (4)
static inline void usb_out_ep_reset_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_RESET_ADDRESS;
    *reg = value;
}

#define USB_OUT_EP_EPNO_ADDRESS (0x00080008U)
#define USB_OUT_EP_EPNO_SIZE (4)
static inline uint32_t usb_out_ep_epno_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_EPNO_ADDRESS;
    return *reg;
}
static inline void usb_out_ep_epno_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_EPNO_ADDRESS;
    *reg = value;
}

#define USB_OUT_EP_ENABLE_ADDRESS (0x0008000cU)
#define USB_OUT_EP_ENABLE_SIZE (4)
static inline uint32_t usb_out_ep_enable_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_ENABLE_ADDRESS;
    return *reg;
}
static inline void usb_out_ep_enable_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_ENABLE_ADDRESS;
    *reg = value;
}

#define USB_OUT_EP_STALL_ADDRESS (0x00080010U)
#define USB_OUT_EP_STALL_SIZE (4)
static inline uint32_t usb_out_ep_stall_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_STALL_ADDRESS;
    return *reg;
}
static inline void usb_out_ep_stall_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_STALL_ADDRESS;
    *reg = value;
}

#define USB_OUT_EP_HAVE_ADDRESS (0x00080014U)
#define USB_OUT_EP_HAVE_SIZE (4)
static inline uint32_t usb_out_ep_have_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_HAVE_ADDRESS;
    return *reg;
}

#define USB_OUT_EP_PEND_ADDRESS (0x00080018U)
#define USB_OUT_EP_PEND_SIZE (4)
static inline uint32_t usb_out_ep_pend_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_PEND_ADDRESS;
    return *reg;
}

#define USB_OUT_EP_ADDRESS_ADDRESS (0x0008001cU)
#define USB_OUT_EP_ADDRESS_SIZE (4)
static inline uint32_t usb_out_ep_address_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_ADDRESS_ADDRESS;
    return *reg;
}
static inline void usb_out_ep_address_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_ADDRESS_ADDRESS;
    *reg = value;
}

#define USB_OUT_EP_PID_ADDRESS (0x00080020U)
#define USB_OUT_EP_PID_SIZE (4)
static inline uint32_t usb_out_ep_pid_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_PID_ADDRESS;
    return *reg;
}
static inline void usb_out_ep_pid_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_PID_ADDRESS;
    *reg = value;
}

#define USB_OUT_EP_EV_STATUS_ADDRESS (0x00080040U)
#define USB_OUT_EP_EV_STATUS_SIZE (4)
static inline uint32_t usb_out_ep_ev_status_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_EV_STATUS_ADDRESS;
    return *reg;
}

#define USB_OUT_EP_EV_PENDING_ADDRESS (0x00080044U)
#define USB_OUT_EP_EV_PENDING_SIZE (4)
static inline uint32_t usb_out_ep_ev_pending_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_EV_PENDING_ADDRESS;
    return *reg;
}
static inline void usb_out_ep_ev_pending_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_EV_PENDING_ADDRESS;
    *reg = value;
}

#define USB_OUT_EP_EV_ENABLE_ADDRESS (0x00080048U)
#define USB_OUT_EP_EV_ENABLE_SIZE (4)
static inline uint32_t usb_out_ep_ev_enable_read(void) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_EV_ENABLE_ADDRESS;
    return *reg;
}
static inline void usb_out_ep_ev_enable_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)USB_OUT_EP_EV_ENABLE_ADDRESS;
    *reg = value;
}

#define LEDS_OUTPUT_ADDRESS (0x00090000U)
#define LEDS_OUTPUT_SIZE (4)
static inline void leds_output_write(uint32_t value) {
    volatile uint32_t *reg = (uint32_t *)LEDS_OUTPUT_ADDRESS;
    *reg = value;
}

//
// Interrupts
//
static inline bool timer_interrupt_pending(void) {
    return pending_irqs() & (1 << 0);
}
static inline void timer_interrupt_enable(void) {
    irq_setmask(irq_getmask() | (1 << 0));
}
static inline void timer_interrupt_disable(void) {
    irq_setmask(irq_getmask() & ~(1 << 0));
}
static inline bool uart_interrupt_pending(void) {
    return pending_irqs() & (1 << 1);
}
static inline void uart_interrupt_enable(void) {
    irq_setmask(irq_getmask() | (1 << 1));
}
static inline void uart_interrupt_disable(void) {
    irq_setmask(irq_getmask() & ~(1 << 1));
}
static inline bool usb_device_controller_interrupt_pending(void) {
    return pending_irqs() & (1 << 2);
}
static inline void usb_device_controller_interrupt_enable(void) {
    irq_setmask(irq_getmask() | (1 << 2));
}
static inline void usb_device_controller_interrupt_disable(void) {
    irq_setmask(irq_getmask() & ~(1 << 2));
}
static inline bool usb_setup_interrupt_pending(void) {
    return pending_irqs() & (1 << 3);
}
static inline void usb_setup_interrupt_enable(void) {
    irq_setmask(irq_getmask() | (1 << 3));
}
static inline void usb_setup_interrupt_disable(void) {
    irq_setmask(irq_getmask() & ~(1 << 3));
}
static inline bool usb_in_ep_interrupt_pending(void) {
    return pending_irqs() & (1 << 4);
}
static inline void usb_in_ep_interrupt_enable(void) {
    irq_setmask(irq_getmask() | (1 << 4));
}
static inline void usb_in_ep_interrupt_disable(void) {
    irq_setmask(irq_getmask() & ~(1 << 4));
}
static inline bool usb_out_ep_interrupt_pending(void) {
    return pending_irqs() & (1 << 5);
}
static inline void usb_out_ep_interrupt_enable(void) {
    irq_setmask(irq_getmask() | (1 << 5));
}
static inline void usb_out_ep_interrupt_disable(void) {
    irq_setmask(irq_getmask() & ~(1 << 5));
}
#endif

