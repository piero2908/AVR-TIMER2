/*
 * Uso_timer2.c
 *
 * Created: 04/10/2018 03:55:52 p.m.
 * Author : Laptop
 */ 

//USO DEL TIMER 2 CON INTERRUPCION
#define F_CPU 16000000 //CRYSTAL = 16Mhz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t tmr2_count_overflow;

ISR(TIMER2_OVF_vect){
	tmr2_count_overflow++;
}

void tmr2_config(){
	TCCR2B |= (1<<CS22)|(1<<CS21)|(0<<CS20); //Prescaler de 256
	
	TIMSK2 |= (1<<TOIE2);
	
	//TIFR2 |= (X<<TOV2); ->Overflow flag
	
	sei();
	
	tmr2_count_overflow = 0;
	
	TCNT2 = 0;	
}

void pin_config(){
	DDRD = (0xFF<<DDRD);
}


int main(void)
{
    pin_config();
	tmr2_config();
	
    while (1) 
    {
			if(tmr2_count_overflow >= 12){
				if(TCNT2 >= 53){
					PORTD ^= 0xFF;
					tmr2_count_overflow = 0;
					TCNT2 = 0;
					
				}
			}
		
    }
}

