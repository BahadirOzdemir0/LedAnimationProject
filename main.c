/*
 * Led Project by Bahadır Özdemir
 */

#include <stdint.h>
#include <stdio.h>
#include <time.h>

// Function prototypes
void ledlight(uint32_t delay_ms);
void delay(uint32_t delay_ms);

// Function to create a delay using NOP (No Operation) instructions
void delay(uint32_t delay_ms) {
    uint32_t count = delay_ms * 8000; // Adjust this value based on your processor speed
    while(count--) {
        __asm("nop"); // No Operation (just waste time)
    }
}

// Pointers to control registers for peripherals
uintptr_t *pClkReg = (uintptr_t*)0x40023830;
uintptr_t *pPortDModeReg = (uintptr_t*)0x40020c00;
uintptr_t *pPortDOutReg = (uintptr_t*)0x40020c14;

// Function to control LED light animation
void ledlight(uint32_t delay_ms) {
    // LED animation loop
    for(int i = 0; i < 9; i++) {
        *pPortDOutReg &= 0x00000000;            // Clear PC bits
        *pPortDOutReg |= 0x1000 >> i;           // Set portD 12 to 4 bit for LED control
        delay(delay_ms);              // Delay for smooth animation
    }

    // LED animation in reverse
    for(int i = 8; i >= 0; i--) {
        *pPortDOutReg &= 0x00000000;            // Clear PC bits
        *pPortDOutReg |= 0x1000 >> i;           // Set portD 12 to 4 bit for LED control
        delay(delay_ms);              // Delay for smooth animation
    }

    *pPortDOutReg &= 0x00000000;                // Turn off all LEDs
}

int main(void) {
    *pClkReg |= 0x08;                      // Enable peripheral A
    *pPortDModeReg &= 0x00000000;                // Clear PB bits
    *pPortDModeReg |= 0x01555500;                // Set specific bits for PB configuration



    for(;;){        // Infinite loop for continuous operation


        ledlight(10);           // Determine delay based on user
    }
}
