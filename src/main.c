/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Peter Lawrence
 *
 * influenced by lrndis https://github.com/fetisov/lrndis
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
 */

/*
this appears as either a RNDIS or CDC-ECM USB virtual network adapter; the OS
picks its preference

RNDIS should be valid on Linux and Windows hosts, and CDC-ECM should be valid on
Linux and macOS hosts

The MCU appears to the host as IP address 192.168.7.1, and provides a DHCP
server, DNS server, and web server.
*/
/*
Some smartphones *may* work with this implementation as well, but likely have
limited (broken) drivers, and likely their manufacturer has not tested such
functionality.  Some code workarounds could be tried:

The smartphone may only have an ECM driver, but refuse to automatically pick ECM
(unlike the OSes above); try modifying
./examples/devices/net_lwip_webserver/usb_descriptors.c so that CONFIG_ID_ECM is
default.

The smartphone may be artificially picky about which Ethernet MAC address to
recognize; if this happens, try changing the first byte of
tud_network_mac_address[] below from 0x02 to 0x00 (clearing bit 1).
*/

#include "tusb.h"

#include "dhserver.h"
#include "dnserver.h"
#include "httpd.h"
#include "lwip/ethip6.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"

#include "systick.h"
#include "usb.h"
#include "led.h"

void board_init(void);
int main(void) {
    /* initialize TinyUSB */
    board_init();

    // init device stack on configured roothub port
    tud_init(0);

    while (1) {
        tud_task();
        led_blinking_task();
    }

    return 0;
}

/* lwip needs a millisecond time source, and the TinyUSB board support code has
 * one available */
uint32_t sys_now(void) { return board_millis(); }

void board_init(void) {
    systick_init();
    usb_init();
    led_init();
}