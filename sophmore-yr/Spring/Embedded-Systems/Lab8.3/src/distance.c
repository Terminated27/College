
/* ultrasound.c This code operates the HC-SR04 ultrasound sensor
and displays measured range on a serial monitor via UART.

Operation: code provides a 10us trigger pulse on PB1 then
waits for an echo pulse on PB0. Duration of echo pulse is
the round-trip time delay to the target. With Fcpu=16 MHz
and 1024 divider, Fclock = 16 MHz/1024 = 15.625 KHz. Each
clock pulse is therefore 1/15,625 = 64 us.
Speed of sound is 343 m/s or 34300 cm/s so each clock pulse
is 34300 cm/s x 64e-6 s = 2.195 cm round trip or 1.098 cm one way
8 bit counter with 256 states can measure distances 0 to 255*1.098
= 2.80 m or 9.2 feet with 1.1 cm resolution.
Timer0 will be set free-running, 0-255 then repeating
Note: objects >2.80m will have round-trip delay longer
than the clock count-up time; such echos are not printed to UART.
D. McLaughlin 4/14/22 Initial Code Writing for ECE--231 Spring 2022 */

// Combined with:

/* seven_uart_main.c This code demonstrates the use of a 4 digit
7 segment LED. This version counts 0-1000 repeatedly and uses
persistence to create an always-on effect in the digits. Digits
are also sent via UART. This code has D1 contention between UART &
the display. D. McLaughlin 3/20/22 ECE-231 Demo */

// By Aidan Chin 5/12/2024 Lab8.3

#define TRIG PB5 // PB5 = pin 19
#define ECHO PB0 // PB0 = pin 14
#define RANGE_PER_CLOCK 1.098
#define PERSISTENCE 5 // Retinal Persistance
#define COUNTTIME 50  // #ms between counters

#include <avr/io.h>
#include <util/delay.h>
#include <my_uart_lib.h>

void timer0_init(void);

int main(void)
{

    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
                                 0x07, 0x7F, 0x67}; // 7 segment numbers
    unsigned char DIG1, DIG2, DIG3, DIG4;

    DDRC = 0x0F;                                                           // segments a-d use PC0-PC3
    DDRD = 0xF0;                                                           // segments e-g & dp use PD4-PD7
    DDRB |= 1 << TRIG | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4); // Digit enable pins

    unsigned char rising_edge_clocks, falling_edge_clocks,
        echo_width_clocks;
    float target_range;
    int range_int;
    PORTB &= ~(1 << TRIG); // Set the TRIG pin low
    uart_init();
    timer0_init(); // Initialize timer0

    while (1)
    {
        TCNT0 = 0;             // Load counter with 0
        PORTB |= 1 << TRIG;    // These three lines of code
        _delay_us(10);         // Put a 10 usec pulse on the
        PORTB &= ~(1 << TRIG); // TRIG pin.

        // Wait till the ECHO pulse goes high
        while ((PINB & (1 << ECHO)) == 0)
            ;
        rising_edge_clocks = TCNT0; // Note the time
        // Now wait till the ECHO pulse goes low
        while (!(PINB & (1 << ECHO)) == 0)
            ;
        falling_edge_clocks = TCNT0;

        if (falling_edge_clocks > rising_edge_clocks)
        {
            // Compute target range and send it to the serial monitor
            echo_width_clocks = falling_edge_clocks - rising_edge_clocks;
            target_range = echo_width_clocks * RANGE_PER_CLOCK;
            range_int = (int)target_range;
            // send_to_monitor(rising_edge_clocks, falling_edge_clocks, target_range);
        }

        DIG4 = range_int % 10;         // Compute 1's digit (Least sig digit)
        DIG3 = (range_int / 10) % 10;  // Compute 10's digit
        DIG2 = (range_int / 100) % 10; // Compute 100's digit
        DIG1 = (range_int / 1000);     // Compute 1000's digit (Most sig digit)

        for (int j = 0; j < COUNTTIME / PERSISTENCE / 4; j++)
        {
            PORTB = 0x0F;

            // Show 1000's digit
            PORTC = ledDigits[DIG1];
            PORTD = ledDigits[DIG1];
            uart_send(DIG1 + '0'); // Tx 1000's digit
            PORTB = ~(1 << 4);     // Enable DIG1
            _delay_ms(PERSISTENCE);

            // Show 100's digit
            PORTC = ledDigits[DIG2];
            PORTD = ledDigits[DIG2];
            uart_send(DIG2 + '0'); // Tx 100's digit
            PORTB = ~(1 << 3);     // Enable DIG2
            _delay_ms(PERSISTENCE);

            // Show 10's digit
            PORTC = ledDigits[DIG3];
            PORTD = ledDigits[DIG3];
            uart_send(DIG3 + '0'); // Tx 10's digit
            PORTB = ~(1 << 2);     // Enable DIG3
            _delay_ms(PERSISTENCE);

            // Show 1's digit
            PORTC = ledDigits[DIG4];
            PORTD = ledDigits[DIG4];
            uart_send(DIG4 + '0'); // Tx 10's digit
            PORTB = ~(1 << 1);     // Enable DIG4
            _delay_ms(PERSISTENCE);

            PORTB = 0xFF;  // Disable all digits
            uart_send(13); // Tx carriage return
            uart_send(10); // Tx line feed
        }
    }
}

// Initialize timer0: normal mode (count up), divide clock by 1024
void timer0_init()
{
    TCCR0A = 0; // Timer 1 Normal mode (count up)
    TCCR0B = 5; // Divide clock by 1024
    TCNT0 = 0;  // Start the timer at 0
}
