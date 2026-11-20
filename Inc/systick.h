#ifndef SYSTICK_H_
#define SYSTICK_H_

volatile uint32_t ms_ticks=0;
void systick_init(void);
void delay_ms(uint32_t delay);

#endif /* SYSTICK_H_ */
