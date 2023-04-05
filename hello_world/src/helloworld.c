/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
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
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "pwm_ctl.h"

XGpio LedGpio;
XGpio BtnSwGpio;

#define BTN_CHANNEL 1
#define BTN_MASK 0xFu
#define SW_CHANNEL 2
#define SW_MASK 0xFu
#define LED_CHANNEL 1
#define LED_MASK 0xFu

int main()
{
	XStatus Status;
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");

    *(uint32_t*)0x41200000 = 0x0u;

    Status = XGpio_Initialize(&LedGpio, 1);
    if(Status != XST_SUCCESS){
    	xil_printf("Gpio initialization failed.\r\n");
    	return XST_FAILURE;
    }
    XGpio_SetDataDirection(&LedGpio, LED_CHANNEL, ~LED_MASK);

    Status = XGpio_Initialize(&BtnSwGpio, 0);
    if(Status != XST_SUCCESS){
    	xil_printf("Gpio initialization failed.\r\n");
    	return XST_FAILURE;
    }
    XGpio_SetDataDirection(&BtnSwGpio, BTN_CHANNEL, BTN_MASK);
    XGpio_SetDataDirection(&LedGpio, SW_CHANNEL, SW_MASK);
    Pwm_SetDivider(0x43C00000, 128);
    Pwm_SetDivider(0x43C10000, 128);
    Pwm_SetDivider(0x43C20000, 128);
    while(1){
    	u32 btn = XGpio_DiscreteRead(&BtnSwGpio, BTN_CHANNEL) & BTN_MASK;
    	u32 sw = XGpio_DiscreteRead(&BtnSwGpio, SW_CHANNEL) & SW_MASK;
    	u32 led = (btn ? ~sw : sw) & LED_MASK;
    	XGpio_DiscreteWrite(&LedGpio, LED_CHANNEL, led);
    	Pwm_SetDuty(0x43C00000, sw<<4);
    	Pwm_SetDuty(0x43C10000, sw<<4);
    	Pwm_SetDuty(0x43C20000, sw<<4);
    }

    cleanup_platform();
    return 0;
}
