#include "systick.h"
#include "clock.h"

#define SYST_CSR (*(volatile uint32_t*)0xE000E010)//SysTick Control and Status Reg.
#define SYST_RVR (*(volatile uint32_t*)0xE000E014)//,, Reload Value Reg.
#define SYST_CVR (*(volatile uint32_t*)0xE000E018)//,, Current Value Reg.

volatile uint32_t ms_ticks=0;

void systick_init(void){
	clock_init_72mhz();//Initializing clock

	SYST_RVR=71999;//For 72MHz
	SYST_CVR=0;//Forcing restart of counter
	SYST_CSR |= (7<<0);//CLKSOURCE, TICKINT, ENABLE enabled
}

void SysTick_Handler(void){
	ms_ticks++;//SysTick_Handler executes as soon as SYST_CSRs COUNTFLAG sets to 1
}

void delay_ms(uint32_t delay){
	uint32_t start_time=ms_ticks;
	while((uint32_t)(ms_ticks-start_time)<delay){
		//Wait till user assigned delay time
	}
}
