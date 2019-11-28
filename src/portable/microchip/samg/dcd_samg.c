/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2018, hathach (tinyusb.org)
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

#include "tusb_option.h"

#if CFG_TUSB_MCU == OPT_MCU_SAMG

#include "sam.h"
#include "device/dcd.h"

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+

// Transfer descriptor
typedef struct
{
  uint8_t* buffer;
  uint16_t total_len;
  volatile uint16_t actual_len;
  uint16_t  epsize;
} xfer_desc_t;

// Endpoint 0-5 with OUT & IN
xfer_desc_t _dcd_xfer[6][2];

void xfer_begin(xfer_desc_t* xfer, uint8_t * buffer, uint16_t total_bytes)
{
  xfer->buffer     = buffer;
  xfer->total_len  = total_bytes;
  xfer->actual_len = 0;
}

uint16_t xfer_packet_len(xfer_desc_t* xfer)
{
  // also cover zero-length packet
  return tu_min16(xfer->total_len - xfer->actual_len, xfer->epsize);
}

void xfer_packet_done(xfer_desc_t* xfer)
{
  uint16_t const xact_len = xfer_packet_len(xfer);

  xfer->buffer += xact_len;
  xfer->actual_len += xact_len;
}

/*------------------------------------------------------------------*/
/* Device API
 *------------------------------------------------------------------*/

// Set up endpoint 0, clear all other endpoints
static void bus_reset(void)
{
  tu_memclr(_dcd_xfer, sizeof(_dcd_xfer));

  _dcd_xfer[0][0].epsize = _dcd_xfer[0][1].epsize = CFG_TUD_ENDPOINT0_SIZE;

  // Enable EP0 control
  UDP->UDP_CSR[0] = UDP_CSR_EPEDS_Msk;

  // Enable interrupt : EP0, Suspend, Resume, Wakeup
  UDP->UDP_IER = UDP_IER_EP0INT_Msk | UDP_IER_RXSUSP_Msk | UDP_IER_RXRSM_Msk | UDP_IER_WAKEUP_Msk;

  // Enable transceiver
  UDP->UDP_TXVC &= ~UDP_TXVC_TXVDIS_Msk;
}

// Initialize controller to device mode
void dcd_init (uint8_t rhport)
{
  (void) rhport;

  tu_memclr(_dcd_xfer, sizeof(_dcd_xfer));

  // Enable pull-up, disable transceiver
  UDP->UDP_TXVC = UDP_TXVC_PUON | UDP_TXVC_TXVDIS_Msk;
}

// Enable device interrupt
void dcd_int_enable (uint8_t rhport)
{
  (void) rhport;
  NVIC_EnableIRQ(UDP_IRQn);
}

// Disable device interrupt
void dcd_int_disable (uint8_t rhport)
{
  (void) rhport;
  NVIC_DisableIRQ(UDP_IRQn);
}

// Receive Set Address request, mcu port must also include status IN response
void dcd_set_address (uint8_t rhport, uint8_t dev_addr)
{
  (void) rhport;
  (void) dev_addr;

  // SAMG can only set address after status for this request is complete
  // do it at dcd_edpt0_status_complete()
}

// Receive Set Configure request
void dcd_set_config (uint8_t rhport, uint8_t config_num)
{
  (void) rhport;
  (void) config_num;
}

// Wake up host
void dcd_remote_wakeup (uint8_t rhport)
{
  (void) rhport;
}

//--------------------------------------------------------------------+
// Endpoint API
//--------------------------------------------------------------------+

// Invoked when a control transfer's status stage is complete.
// May help DCD to prepare for next control transfer, this API is optional.
void dcd_edpt0_status_complete(uint8_t rhport, tusb_control_request_t const * request)
{
  (void) rhport;

  if (request->bRequest == TUSB_REQ_SET_ADDRESS)
  {
    uint8_t const dev_addr = (uint8_t) request->wValue;
    TU_LOG2("dev address = %d", dev_addr);

    // Enable addressed state
    UDP->UDP_GLB_STAT |= UDP_GLB_STAT_FADDEN_Msk;

    // Set new address & Function enable bit
    UDP->UDP_FADDR |= UDP_FADDR_FADD(dev_addr);

    UDP->UDP_FADDR |= UDP_FADDR_FEN_Msk;
  }
}

// Configure endpoint's registers according to descriptor
bool dcd_edpt_open (uint8_t rhport, tusb_desc_endpoint_t const * ep_desc)
{
  (void) rhport;
  (void) ep_desc;
  return false;
}

// Submit a transfer, When complete dcd_event_xfer_complete() is invoked to notify the stack
bool dcd_edpt_xfer (uint8_t rhport, uint8_t ep_addr, uint8_t * buffer, uint16_t total_bytes)
{
  (void) rhport;

  uint8_t const epnum = tu_edpt_number(ep_addr);
  uint8_t const dir   = tu_edpt_dir(ep_addr);

  xfer_desc_t* xfer = &_dcd_xfer[epnum][dir];
  xfer_begin(xfer, buffer, total_bytes);

  uint16_t const xact_len = xfer_packet_len(xfer);

  // control endpoint
  if ( epnum == 0 )
  {
    if (dir == TUSB_DIR_OUT)
    {
      // Clear DIR bit
      UDP->UDP_CSR[0] &= ~UDP_CSR_DIR_Msk;

    }else
    {
      // Set DIR bit if needed
      UDP->UDP_CSR[0] |= UDP_CSR_DIR_Msk;

      // Write data to fifo
      for(uint16_t i=0; i<xact_len; i++) UDP->UDP_FDR[0] = (uint32_t) buffer[i];

      // TX ready for transfer
      UDP->UDP_CSR[0] |= UDP_CSR_TXPKTRDY_Msk;
    }

  }else
  {
    return false;
  }

  return true;
}

// Stall endpoint
void dcd_edpt_stall (uint8_t rhport, uint8_t ep_addr)
{
  (void) rhport;
  (void) ep_addr;
}

// clear stall, data toggle is also reset to DATA0
void dcd_edpt_clear_stall (uint8_t rhport, uint8_t ep_addr)
{
  (void) rhport;
  (void) ep_addr;
}

//--------------------------------------------------------------------+
// ISR
//--------------------------------------------------------------------+
void dcd_isr(uint8_t rhport)
{
  uint32_t const intr_mask   = UDP->UDP_IMR;
  uint32_t const intr_status = UDP->UDP_ISR & intr_mask;

  // clear interrupt
  UDP->UDP_ICR = intr_status;

  // Bus reset
  if (intr_status & UDP_ISR_ENDBUSRES_Msk)
  {
    bus_reset();
    dcd_event_bus_signal(rhport, DCD_EVENT_BUS_RESET, true);
  }

  // SOF
//  if (intr_status & UDP_ISR_SOFINT_Msk) dcd_event_bus_signal(rhport, DCD_EVENT_SOF, true);

  // Suspend
//  if (intr_status & UDP_ISR_RXSUSP_Msk) dcd_event_bus_signal(rhport, DCD_EVENT_SUSPEND, true);

  // Resume
//  if (intr_status & UDP_ISR_RXRSM_Msk)  dcd_event_bus_signal(rhport, DCD_EVENT_RESUME, true);

  // Wakeup
//  if (intr_status & UDP_ISR_WAKEUP_Msk)  dcd_event_bus_signal(rhport, DCD_EVENT_RESUME, true);

  //------------- Endpoints -------------//

  if ( intr_status & TU_BIT(0) )
  {
    // setup packet
    if (UDP->UDP_CSR[0] & UDP_CSR_RXSETUP)
    {
      // get setup from FIFO
      uint8_t setup[8];
      for(uint8_t i=0; i<sizeof(setup); i++)
      {
        setup[i] = (uint8_t) UDP->UDP_FDR[0];
      }

      // notify usbd
      dcd_event_setup_received(rhport, setup, true);

      // Clear Setup bit
      UDP->UDP_CSR[0] &= ~UDP_CSR_RXSETUP_Msk;
    }
  }

  for(uint8_t epnum = 0; epnum < 6; epnum++)
  {
    // Endpoint IN
    if (UDP->UDP_CSR[epnum] & UDP_CSR_TXCOMP_Msk)
    {
      xfer_desc_t* xfer = &_dcd_xfer[epnum][1];
      uint16_t xact_len = xfer_packet_len(xfer);
      xfer_packet_done(xfer);

      dcd_event_xfer_complete(rhport, epnum | TUSB_DIR_IN_MASK, xact_len, XFER_RESULT_SUCCESS, true);

      // Clear TX Complete bit
      UDP->UDP_CSR[0] &= ~UDP_CSR_TXCOMP_Msk;
    }

    // Endpoint OUT
    if (UDP->UDP_CSR[epnum] & UDP_CSR_RX_DATA_BK0_Msk)
    {
      uint16_t const xact_len = (uint16_t) ((UDP->UDP_CSR[0] & UDP_CSR_RXBYTECNT_Msk) >> UDP_CSR_RXBYTECNT_Pos);

      dcd_event_xfer_complete(rhport, epnum, xact_len, XFER_RESULT_SUCCESS, true);

      // Clear DATA Bank0 bit
      UDP->UDP_CSR[0] &= ~UDP_CSR_RX_DATA_BK0_Msk;
    }
  }
}

#endif