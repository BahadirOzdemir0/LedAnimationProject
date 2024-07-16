/*
 * Led Project by Bahadır Özdemir
 */

#include <stdint.h>
#include <stdio.h>
#include <time.h>

// Function prototypes
void Transition();
void LedAnime1(uint32_t delay_ms);
void LedAnime2(uint32_t delay_ms);
void LedAnime3(uint32_t delay_ms);
void LedAnime4(uint32_t delay_ms);



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

void Transition(){
	*pPortDOutReg |= 0x1ff0;
	delay(100);
	*pPortDOutReg &= 0x00000000;
}
// Function to control LED light animation
void LedAnime1(uint32_t delay_ms) {
    // LED animation loop
    for(int8_t i = 0; i < 9; i++) {
        *pPortDOutReg &= 0x00000000;            // Clear PC bits
        *pPortDOutReg |= 0x1000 >> i;           // Set portD 12 to 4 bit for LED control
        delay(delay_ms);              // Delay for smooth animation
    }

    // LED animation in reverse
    for(int8_t i = 8; i >= 0; i--) {
        *pPortDOutReg &= 0x00000000;            // Clear PC bits
        *pPortDOutReg |= 0x1000 >> i;           // Set portD 12 to 4 bit for LED control
        delay(delay_ms);              // Delay for smooth animation
    }

    *pPortDOutReg &= 0x00000000;                // Turn off all LEDs
}
void LedAnime2(uint32_t delay_ms){
	for(int8_t i=0;i<5;i++){
		*pPortDOutReg &= 0x00000000;

		*pPortDOutReg |= 0x0100 <<i;
		*pPortDOutReg |= 0x0100 >>i;
		delay(delay_ms);

	}
	 *pPortDOutReg &= 0x00000000;
}
void LedAnime3(uint32_t delay_ms){
	for(int8_t i=4;i>=0;i--){
			*pPortDOutReg &= 0x00000000;

			*pPortDOutReg |= 0x0100 <<i;
			*pPortDOutReg |= 0x0100 >>i;
			delay(delay_ms);

		}
		 *pPortDOutReg &= 0x00000000;
}
void LedAnime4(uint32_t delay_ms){
	LedAnime2(20);
	LedAnime3(20);
}
int main(void) {
    *pClkReg |= 0x08;                      // Enable peripheral A
    *pPortDModeReg &= 0x00000000;                // Clear PB bits
    *pPortDModeReg |= 0x01555500;                // Set specific bits for PB configuration



    for(int8_t choice=1;choice <7;choice++){        // Infinite loop for continuous operation


    	//LedAnime1(10);      // Determine delay based on user


    	switch(choice){
    		case 1:
    			Transition();
    			LedAnime1(10);
    			LedAnime1(10);
    			LedAnime1(10);
    			break;
    		case 2:
    			Transition();
    			LedAnime2(20);
    			LedAnime2(20);
    			LedAnime2(20);
    			break;
    		case 3:
    			Transition();
    			LedAnime3(20);
    			LedAnime3(20);
    			LedAnime3(20);
    			break;
    		case 4:
    			Transition();
    			LedAnime4(20);
    			LedAnime4(20);
    			LedAnime4(20);
    			break;
    		default:
    			choice=0;

    	}

    }
}
