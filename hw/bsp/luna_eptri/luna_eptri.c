/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Ha Thach (tinyusb.org)
 * Copyright (c) 2021 Great Scott Gadgets <info@greatscottgadgets.com>
 * Copyright (c) 2021 Katherine J. Temkin <k@ktemk.in>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#include <stdint.h>
#include <stdbool.h>
#include "../board.h"
#include "resources.h"

// Current system tick timer.
volatile uint32_t system_ticks = 0;

//--------------------------------------------------------------------+
// Board porting API
//--------------------------------------------------------------------+

static void timer_init(void)
{
	// Set up our timer to generate an interrupt every millisecond.
	timer_reload_write(60 * 1000);
	timer_en_write(1);
	timer_ev_enable_write(1);

	// Enable our timer's interrupt.
	irq_setie(1);
	timer_interrupt_enable();
}

static void timer_isr(void)
{
	// Increment our total millisecond count.
	++system_ticks;
}


void isr(void)
{
	bool pending_usb_event = 
		usb_device_controller_interrupt_pending() ||
		usb_setup_interrupt_pending()             ||
		usb_in_ep_interrupt_pending()             ||
		usb_out_ep_interrupt_pending();

	// Dispatch USB events.
	if (pending_usb_event) {
		// ... and call the core TinyUSB interrupt handler.
		tud_int_handler(0);
	}

	// Dispatch timer events.
	if (timer_interrupt_pending()) {
		timer_ev_pending_write(timer_ev_pending_read());
		timer_isr();
	}


}

void board_init(void)
{
	timer_init();
	return;
}

void board_led_write(bool state)
{
	leds_output_write(state ? 1 : 0);
}

uint32_t board_button_read(void)
{
	return 0;
}


static void board_uart_write_char(char c)
{
	while(!uart_tx_rdy_read());
	uart_tx_data_write(c);
}

static uint8_t board_uart_read_char(void)
{
	while(!uart_rx_rdy_read());
	return uart_rx_data_read();
}


int board_uart_read(uint8_t* buf, int len)
{
	int i;

	for (i = 0; i < len; ++i) {
		buf[i] = board_uart_read_char();
	}

	return len;
}

int board_uart_write(void const * buf, int len)
{
	int i;
	const char *data = buf;

	for (i = 0; i < len; ++i) {
		board_uart_write_char(data[i]);
	}

	return len;
}

#if CFG_TUSB_OS == OPT_OS_NONE
uint32_t board_millis(void)
{
	return system_ticks;
}
#endif
