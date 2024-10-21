/*****************************************************************
 * uart_string.c - This code sends strings to com port via uart.
 * Version     Date     Author          Revision
 * 1.0      12/16/21     D. McLaughlin   Initial writing of the code
 * 1.1      1/15/22     D. McLaughlin   Tested on Arduino Uno w/ Apple M1 pro
 *                          host running Monterey
 * 1.2      2/27/22     D. McLaughlin   tested on Windows 11 on Parallels VM
 * 1.3      4/21/22     D. McLaughlin   re-written using uart.c/uart.h API
 * 2.0      4/7/24      D. McL          improved formatting
 *****************************************************************/
/*****************************************************************
 * adc_oled_test.c  Program to test the SSD1306 OLED display
 * using ADC inputs.
 *
 * Date         Author              Revision
 * 4/16/24     D. McLaughlin       initial writing of this code
 *******************************************************************/
/*
temperaturescreen.c program that give a C or F temp on a screen and serial monitor
if button is pressed
Date         Author              Revision
4/22/24     Aidan Chin       morphed a bunch of things together
*/
// __________ preamble __________
#include <util/delay.h>
#include <my_uart_lib.h>
#include <i2c.h>
#include <SSD1306.h>
#include <my_adc_lib.h>
#include <avr/io.h>

void OLED_displayDecimal(double v_floatNum_f32)
{
    uint32_t v_temp_u32;
    /* Dirty hack to support the floating point by extracting the integer and fractional part.
    1.Type cast the number to int to get the integer part.
    2.Display the extracted integer part followed by a decimal point(.)
    3.Later the integer part is made zero by subtracting with the extracted integer value.
    4.Finally the fractional part is multiplied by 10^1 to support 1-digit precision */

    v_temp_u32 = (uint32_t)v_floatNum_f32;
    OLED_DisplayNumber(C_DECIMAL_U8, v_temp_u32, C_DisplayDefaultDigits_U8);

    OLED_DisplayChar('.');

    v_floatNum_f32 = v_floatNum_f32 - v_temp_u32;
    v_temp_u32 = v_floatNum_f32 * 10;
    if (v_temp_u32 == 0)
    {
        OLED_DisplayChar('0');
    }
    else
    {
        OLED_DisplayNumber(C_DECIMAL_U8, v_temp_u32, C_DisplayDefaultDigits_U8);
    }
}

void uart_float(double v_floatNum_f32)
{
    // modify OLED_displayDecimal to work for serial, 1 decimal place
    uint32_t v_temp_u32;
    char tempstr[32];
    v_temp_u32 = (uint32_t)v_floatNum_f32;
    sprintf(tempstr, "%lu", v_temp_u32);
    send_string(tempstr);

    uart_send('.');

    v_floatNum_f32 = v_floatNum_f32 - v_temp_u32;
    v_temp_u32 = v_floatNum_f32 * 10; // prints only 1 decimal place
    sprintf(tempstr, "%lu", v_temp_u32);
    send_string(tempstr);
}

int main(void)
{
    int Too_HOT = 80;
    int tempValue;
    float tempC;
    float tempF;
    OLED_Init(); // initialize the OLED display
    uart_init(); // initialize the USART
    adc_init(); // initialize the adc

    DDRD = 1 << DDD6; // Set D6 as output
    PORTC = 1 << PC1; // Set pull-up on C1
    while (1)
    {
        tempValue = get_adc();                    // get voltage value from TMP36
        tempC = 25 + ((tempValue - 750) / 100.0); // convert to Celcius, subtract 750 to get centered at 0, divide by 100 to get 10mV
        tempF = (tempC * 1.8) + 32; // convert C to F
        OLED_GoToLine(3);
        OLED_DisplayString("Temp is:");
        send_string("Temp is:");
        if (tempF >= Too_HOT)
        {
            PORTD |= (1 << PD6); // Turn on LED
        }
        else
        {
            PORTD &= ~(1 << PD6); // Turn off LED
        }
        OLED_GoToLine(5);
        if ((PINC & (1 << PC1))) // if button NOT pressed
        {
            OLED_displayDecimal(tempF);
            OLED_DisplayChar('F');
            uart_float(tempF);
            uart_send('F');
        }
        else // button pressed
        {
            OLED_displayDecimal(tempC);
            OLED_DisplayChar('C');
            uart_float(tempC);
            uart_send('C');
        }

        uart_send(13); // Carriage return (goto beginning of line)
        uart_send(10); // line feed (new line)
        _delay_ms(500); // half second delay
    }
}

/*** End of File***/