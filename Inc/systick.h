#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

extern volatile uint32_t ms_ticks;
void systick_init(void);
void delay_ms(uint32_t delay);

#endif /* SYSTICK_H_ */
