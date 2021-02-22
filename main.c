/*****************************************************************************
* Copyright (C) 2021 by Moanrk Patel
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Monark Patel and the University of Colorado are not liable for
* any misuse of this material.
*
*****************************************************************************/
 
/**
 * @file    main.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define RED_LED_PIN 18      // on port A
#define GREEN_LED_PIN 19    // on port A
#define BLUE_LED_PIN  1		// on port D

/* TODO: insert other function definitions and declarations here. */

void delay(int iterations)
{
	// TBD msec
	while(iterations--)
		;
}
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Welcome to LED World\n");

    // Enable clock to Port B and Port D TBD: Clock logic is not working.
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

    PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
    GPIOB->PDDR |= (1 << RED_LED_PIN);

    PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
    GPIOB->PDDR |= (1 << GREEN_LED_PIN);

	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1 << BLUE_LED_PIN);

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
 	for(int i=0; 1; i++){
        if(i & 0x1)
        {
        	PRINTF("RED LED ON FOR 100 msc\n");
            GPIOB-> PCOR |= (1 << RED_LED_PIN);
            delay(5);
        }
         else
         {
        	PRINTF("RED LED OFF FOR 100 msc\n");
        	GPIOB-> PSOR |= (1 << RED_LED_PIN);
        	delay(50);
         }
        if(i & 0x1)
        {
        	PRINTF("GREEN LED ON FOR 100 msc\n");
            GPIOB-> PCOR |= (1 << GREEN_LED_PIN);
            delay(500);
        }
         else
         {
        	PRINTF("GREEN LED OFF FOR 100 msc\n");
        	GPIOB-> PSOR |= (1 << GREEN_LED_PIN);
        	delay(5000);
         }
        if(i & 0x1)
        {
        	PRINTF("BLUE LED ON FOR 100 msc\n");
            GPIOD-> PCOR |= (1 << BLUE_LED_PIN);
            delay(50000);
        }
         else
         {
        	PRINTF("BLUE LED OFF FOR 100 msc\n");
        	GPIOD-> PSOR |= (1 << BLUE_LED_PIN);
        	delay(500000);
         }
    	}
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
