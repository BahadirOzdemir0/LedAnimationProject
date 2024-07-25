// Led Animation project on stm32f103c8t6   Bahadır Özdemir
// 7 animation 7 Led

#include <stdint.h>
#include <time.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

	uintptr_t volatile *pClockREG    = (uintptr_t*)0x40021018;  // RCC APB2ENR register address
	uintptr_t volatile *pModeREGA    = (uintptr_t*)0x40010800;  // GPIOA CRL register address
	uintptr_t volatile *pOutREGA     = (uintptr_t*)0x4001080c;  // GPIOA ODR register address
	uintptr_t volatile *pModeRegB    = (uintptr_t*)0x40010C00;  // GPIOB CRL register address
	uintptr_t volatile *pInREGB      = (uintptr_t*)0x40010c08;  // GPIOB IDR register address
	uint8_t choice = 0;  // Variable to store the current animation choice

void choicer();
void delay(uint32_t delay_ms);
void Transition(uint32_t Delay);
void LedAnime1(uint32_t Count, uint32_t Delay);
void LedAnime2(uint32_t Count, uint32_t Delay);
void LedAnime3(uint32_t Count, uint32_t Delay);
void LedAnime4(uint32_t Count, uint32_t Delay);
void LedAnime5(uint32_t Count, uint32_t Delay);
void LedAnime6(uint32_t Count, uint32_t Delay);
void LedAnime7(uint32_t Count, uint32_t Delay);

void choicer() {
	if ((*pInREGB & 0x1) == 1) {  // Check if button is pressed
		choice++;
		Transition(50);  // Apply transition effect
	}
}

// Function to create a delay using NOP (No Operation) instructions
void delay(uint32_t delay_ms) {
    uint32_t volatile count = delay_ms * 8000;  // Adjust this value based on your processor speed
    while (count--) {
        __asm("nop");  // No Operation (just waste time)
    }
}

void Transition(uint32_t Delay) {
		*pOutREGA |= 0xff;  // Turn on all LEDs
		delay(Delay);  // Wait for the specified delay
		*pOutREGA &= 0x0000;  // Turn off all LEDs
}

void LedAnime1(uint32_t Count, uint32_t Delay) {
	while (1) {
		// Animation loop
		for (int8_t i = 0; i <= 6; i++) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			*pOutREGA |= 0x1 << i;  // Turn on LED at position i
			delay(Delay);  // Wait for the specified delay
		}
		for (int8_t i = 5; i >= 0; i--) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			*pOutREGA |= 0x1 << i;  // Turn on LED at position i
			delay(Delay);  // Wait for the specified delay
		}
		if (Count == 1) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			break;  // Exit the loop if Count is 1
		}
		Count = Count == 0 ? 0 : Count - 1;  // Decrement Count if not zero
	}
}

void LedAnime2(uint32_t Count, uint32_t Delay) {
	while (1) {
		// Animation loop
		for (int8_t i = 0; i < 4; i++) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			*pOutREGA |= 0x8 << i;  // Turn on LEDs in a pattern
			*pOutREGA |= 0x8 >> i;  // Turn on LEDs in a pattern
			delay(Delay);  // Wait for the specified delay
		}
		for (int8_t i = 2; i >= 1; i--) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			*pOutREGA |= 0x8 << i;  // Turn on LEDs in a pattern
			*pOutREGA |= 0x8 >> i;  // Turn on LEDs in a pattern
			delay(Delay);  // Wait for the specified delay
		}
		if (Count == 1) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			break;  // Exit the loop if Count is 1
		}
		Count = Count == 0 ? -1 : Count - 1;  // Decrement Count if not zero
	}
}

void LedAnime3(uint32_t Count, uint32_t Delay) {
	while (1) {
		// Animation loop
		for (int8_t i = 0; i <= 6; i++) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			*pOutREGA |= 0x3 << i;  // Turn on two LEDs at a time
			delay(Delay);  // Wait for the specified delay
		}
		for (int8_t i = 5; i >= 0; i--) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			*pOutREGA |= 0x3 << i;  // Turn on two LEDs at a time
			delay(Delay);  // Wait for the specified delay
		}
		if (Count == 1) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			break;  // Exit the loop if Count is 1
		}
		Count = Count == 0 ? 0 : Count - 1;  // Decrement Count if not zero
	}
}

void LedAnime4(uint32_t Count, uint32_t Delay) {
	while (1) {
		// Animation loop
		for (int8_t i = 0; i <= 6; i++) {
			*pOutREGA |= 0x1 << i;  // Turn on LEDs one by one
			delay(Delay);  // Wait for the specified delay
		}
		for (int8_t i = 6; i >= 1; i--) {
			*pOutREGA &= ~(0x01 << i);  // Turn off LEDs one by one
			delay(Delay);  // Wait for the specified delay
		}
		if (Count == 1) {
			break;  // Exit the loop if Count is 1
		}
		Count = Count == 0 ? 0 : Count - 1;  // Decrement Count if not zero
	}
}

void LedAnime5(uint32_t Count, uint32_t Delay) {
	while (1) {
		// Animation loop
		for (int8_t i = 6; i >= 0; i--) {
			*pOutREGA |= 0x1 << i;  // Turn on LEDs one by one in reverse
			delay(Delay);  // Wait for the specified delay
		}
		for (int8_t i = 0; i <= 5; i++) {
			*pOutREGA &= ~(0x01 << i);  // Turn off LEDs one by one in reverse
			delay(Delay);  // Wait for the specified delay
		}
		if (Count == 1) {
			break;  // Exit the loop if Count is 1
		}
		Count = Count == 0 ? 0 : Count - 1;  // Decrement Count if not zero
	}
}

void LedAnime6(uint32_t Count, uint32_t Delay) {
	while (1) {
		uint8_t step = 0;
		// Animation loop
		for (uint8_t i = 0; i < 7; i++) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			step++;
			*pOutREGA |= 0x1 << i;  // Turn on LEDs in steps
			if (step == 3) {
				step = 0;
				i -= 2;  // Move back to create a step effect
			}
			delay(Delay);  // Wait for the specified delay
		}
		if (Count == 1) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			break;  // Exit the loop if Count is 1
		}
		Count = Count == 0 ? 0 : Count - 1;  // Decrement Count if not zero
	}
}

void LedAnime7(uint32_t Count, uint32_t Delay) {
	while (1) {
		// Animation loop
		*pOutREGA &=

 0x0000;  // Turn off all LEDs
		*pOutREGA |= 0x7;  // Turn on first three LEDs
		delay(50);  // Wait for the specified delay
		*pOutREGA &= 0x0000;  // Turn off all LEDs
		*pOutREGA |= 0xf0;  // Turn on last four LEDs
		delay(50);  // Wait for the specified delay
		*pOutREGA &= 0x0000;  // Turn off all LEDs
		if (Count == 1) {
			*pOutREGA &= 0x0000;  // Turn off all LEDs
			break;  // Exit the loop if Count is 1
		}
		Count = Count == 0 ? 0 : Count - 1;  // Decrement Count if not zero
	}
}

int main(void) {
	*pClockREG |= 0x0c;  // Enable clock for GPIOA and GPIOB
	*pModeREGA &= 0x00000000;  // Clear GPIOA CRL
	*pModeREGA |= 0x22222222;  // Set GPIOA pins to output mode
	*pModeRegB &= ~(0xf);  // Clear GPIOB CRL for pin 0
	*pModeRegB |= 0x8;  // Set GPIOB pin 0 to input mode with pull-down

	for (;;) {  // Loop forever
		choicer();  // Check for button press and update choice
		switch (choice) {
		case 1:
			LedAnime1(1, 10);  // Execute animation 1
			break;
		case 2:
			LedAnime2(1, 10);  // Execute animation 2
			break;
		case 3:
			LedAnime3(1, 10);  // Execute animation 3
			break;
		case 4:
			LedAnime4(1, 10);  // Execute animation 4
			break;
		case 5:
			LedAnime5(1, 10);  // Execute animation 5
			break;
		case 6:
			LedAnime6(1, 25);  // Execute animation 6
			break;
		case 7:
			LedAnime7(1, 25);  // Execute animation 7
			break;
		default:
			choice = 0;  // Reset choice if no valid choice is made
		}
	}
}
