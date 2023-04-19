/* 
 * File:   main.c
 * Author: saenz
 *
 * Created on November 25, 2019, 11:05 PM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "configuration.h"
#include "ControlZ.h"
#include "UART.h"
#include "motor.h"
#include "PWM.h"
#include "serial.h"
#include "Actuator.h"
#include "GPIOsparcA1.h"
#include "User_Interface.h"
#include "Interrupt.h"

void main(void) {
    OSCCON = 0x72;
    GPIO_init_PORTA();
    GPIO_init_PORTB();
   GPIO_init_PORTC();
   GPIO_init_PORTD();
    GPIO_init_PORTE();
    ENABLE_Z_SetLow();
    ENABLE_X = 1;
    ENABLE_Y = 1;
    USART_Init(9600);
    Int_Ext();
    USART_TxS("WELCOME TO SPARC\n", sizeof ("WELCOME TO SPARC\n") - 1);
   Usart_Interface_ON('A');
    USART_TxS("W\n", sizeof ("W\n") - 1);
   main_Home();
    Usart_Interface_OFF('A');
    USART_TxS("C\n", sizeof ("C\n") - 1);
     Usart_Interface_ON('V');
    Serial_Oupcode();
    USART_TxS("F", sizeof ("F") - 1);
    while(1);
}



void main_Home(void) {
    while (BanderaX == 0) {
        ENABLE_X = 0; //Habilita los drivers
        ENABLE_Y = 1;
        Motor_Home();
    }
    while (BanderaY == 0) {
        ENABLE_X = 1; //Habilita los drivers
        ENABLE_Y = 0;
        Motor_Home();
    }
    ENABLE_X = 1;
    ENABLE_Y = 1;
    T2CONbits.TMR2ON = 0;
    BanderaX = 0;
    BanderaY = 0;
    return;
}


/*
void Oneshot() {
    if (PORTBbits.RB2 == 0 & oneshot == 0) {
        cont++;
        oneshot = 1;
    }
}
 */