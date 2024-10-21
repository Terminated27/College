/* switches2.c This code turns on LEDs when  momentary pushbutton  
switches are pressed. Input pins on PD3 and PD4. LEDS on PD6 on PD7
D. McLaughlin 2/21/22 
updated and repurposed with 
/*******************************************************************
 * blink.c   Blink an LED on Port B pin5 (PB5).  
 * This is the built-in LED (pin13) on the Arduino Uno dev board.
 * This is pin 19 of ATmega328P DIP
 * Version  Date         Author          Revision
 * 1.0      12/14/21     D. McLaughlin   initial code creation
 * 1.1      1/9/22       D. McLaughlin   tested on host MacOS Monterey, Apple M1 pro
 * 1.2      2/12/22      D. McLaughlin   cleaned up formatting, added comments
 * 1.3      2/21/23      D. McLaughlin   changed PB5 to DDB5 and PORTB5 in lines 17, 20, 22
 * 2.0      4/7/24       D. McLaughlin   operating only on PB5; using Elliot Williams style
 *                              (from https://github.com/hexagon5un/AVR-Programming)
 * *****************************************************************/
/*
buttons.c This code turns LEDs on when momentary pushbuttons are pressed, when 1 is pressed, it either blinks
1 led or both. if more than one is pressed, nothing happens
LEDS are on ports D3, D4, D5
Buttons are on D6, D7
Aidan Chin 33803321 ECE 231 4/13/2024
*/


#include <avr/io.h>
#include <util/delay.h>

#define MYDELAY 100  // set delay at half wanted Hz

int main(void) {
  DDRD |= (1 << DDD6) | (1 << DDD7);                       // Set D6, D7 as output
  PORTD |= (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5);  // Set pull-up on D3, D4, D5

  while (1) {
    int D3 = !(PIND & (1 << PIND3));  // Inverted logic since 0 means pressed
    int D4 = !(PIND & (1 << PIND4));
    int D5 = !(PIND & (1 << PIND5));
    int totButton = D3 + D4 + D5;

    if (totButton > 1 || totButton == 0) {
      PORTD &= ~(1 << PORTD6);  // Make P6 low; LED off
      PORTD &= ~(1 << PORTD7);  // Make P7 low; LED off
    } else {
      if (D3 == 1) {
        PORTD |= (1 << PORTD6);  // Make P6 high; LED ON
        _delay_ms(MYDELAY);
        PORTD &= ~(1 << PORTD6);  // Make P6 low; LED off
        _delay_ms(MYDELAY);
      }
      if (D4 == 1) {
        PORTD |= (1 << PORTD7);  // Make P7 high; LED ON
        _delay_ms(MYDELAY);
        PORTD &= ~(1 << PORTD7);  // Make P7 low; LED off
        _delay_ms(MYDELAY);
      }
      if (D5 == 1) {
        PORTD |= (1 << PORTD6) | (1 << PORTD7);  // Make P6 and P7 high; LEDs ON
        _delay_ms(MYDELAY);
        PORTD &= ~(1 << PORTD6) & ~(1 << PORTD7);  // Make P6 and P7 low; LEDs off
        _delay_ms(MYDELAY);
      }
    }
  }

  return 0;
}
