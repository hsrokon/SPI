#include "clock.h"

void clock_init_72mhz(void){
	RCC->CFGR &= ~((0xF<<18)|(3<<16)|(3<<2)|(3<<0));//Reset
	RCC->CR |= (1<<16);//HSE on

	FLASH->ACR |= (1<<4);//Prefetch buffer enabled
	FLASH->ACR &= ~(7<<0);
	FLASH->ACR |= (2<<0);//Latency two wait states

	RCC->CFGR |= ((7<<18)|(1<<16));//PLLMULx9 & HSE as PLL input

	while(!(RCC->CR & (1<<17)));//Wait for HSERDY flag
	RCC->CR |= (1<<24);//PLL ON

	while(!(RCC->CR & (1<<25)));//Waiting for PLL to lock
	RCC->CFGR |= (2<<0);//PLL selected as system clock

	while(!(RCC->CFGR & (1<<2)));//Checking if HSE used for System clock
}
