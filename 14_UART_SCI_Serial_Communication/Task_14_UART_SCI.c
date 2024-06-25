
                           Task-14
 *********************************************************************
 UART (SCI) Serial Communication Interface   between two devices
 *********************************************************************
 */

// Header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "F28x_Project.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#include "device.h"
#include "driverlib.h"

void UART_GPIO_init();
void SCI_A_init();
char data='A';
int i=0;

void main(void)
{
    Device_init();
    Device_initGPIO();
    UART_GPIO_init();
    SCI_A_init();

    //////////////////////////////// Vande  /////////////////////////////////////////////

    char message[8] = {'1', '2', '3', '4', '5', '6', '\n', '\r'};
    while(1)
    {
        while (SciaRegs.SCICTL2.bit.TXRDY == 0)
        {
            // Wait for TXRDY bit to be set (transmit buffer empty)
        }
        // Store Data in Buffer
        SciaRegs.SCITXBUF.bit.TXDT = message[i];
        i++;
        if(i==8)
        {
            i=0;
        }
        DEVICE_DELAY_US(10000);
    }
}

void UART_GPIO_init(){

    //////////////////////////////// Vande  /////////////////////////////////////////////

    // for serial terminal use GPIO42 and 43
    EALLOW;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO42=3;
    GpioCtrlRegs.GPBMUX1.bit.GPIO42=3;
    GpioCtrlRegs.GPBPUD.bit.GPIO42=1;
    GpioCtrlRegs.GPBDIR.bit.GPIO42=1;
    GpioCtrlRegs.GPBCSEL2.bit.GPIO42=GPIO_MUX_CPU1;

    GpioCtrlRegs.GPBGMUX1.bit.GPIO43=3;
    GpioCtrlRegs.GPBMUX1.bit.GPIO43=3;
    GpioCtrlRegs.GPBPUD.bit.GPIO43=0;
    GpioCtrlRegs.GPBDIR.bit.GPIO43=0;
    GpioCtrlRegs.GPBCSEL2.bit.GPIO43=GPIO_MUX_CPU1;
    GpioCtrlRegs.GPBCSEL2.bit.GPIO43=3;
    EDIS;
    /////////////////////////////////////  END  ////////////////////////////////////////////////

    // For external output use gpios other than gpios 42  & 43
    /* EALLOW;
    // GPIO to UART-B
     GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 0;
     GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;
     GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;
     GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;
     //GpioCtrlRegs.GPACSEL3.bit.GPIO18 = GPIO_MUX_CPU2;

     GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 0;
     GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;
     GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;
     GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;
     //GpioCtrlRegs.GPACSEL3.bit.GPIO19 = GPIO_MUX_CPU2;
     GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;           // Asynch input
    EDIS;*/

}

void SCI_A_init(){

    EALLOW;
    //  CpuSysRegs.PCLKCR7.bit.SCI_B = 1;  // Enable peripheral clock for SCI module B (SCIB)
    EDIS;

    ///////////////////////////////////////  Vande ///////////////////////////////////////////

    // Set SWRESET bit to 1
    SciaRegs.SCICTL1.bit.SWRESET = 1;

    // Configure SCIA
    // Disable software reset
    SciaRegs.SCICTL1.bit.SWRESET = 0;
    // Disable sleep mode
    SciaRegs.SCICTL1.bit.SLEEP = 0;
    // 1 stop bit
    SciaRegs.SCICCR.bit.STOPBITS = 0;
    // No parity
    SciaRegs.SCICCR.bit.PARITY = 0;
    // 8 data bits
    SciaRegs.SCICCR.bit.SCICHAR = 7;

    // Set Baud Rate
    SciaRegs.SCIHBAUD.all = 0x0002;
    SciaRegs.SCILBAUD.all = 0x008B;
    SciaRegs.SCICTL1.all = 0x0023;
}



