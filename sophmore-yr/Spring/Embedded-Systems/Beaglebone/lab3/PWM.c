#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// ===============================================================
// configure_gpio_input()
//    > Sets up GPIO pin as input
// ===============================================================
void configure_gpio_input(int gpio_number)
{
    //Attempt to open /sys/class/gpio/gpio67/direction
    // if(!fp): open /sys/class/gpio/export and add 67

    char gpio_num[10];
    sprintf(gpio_num, "%d", gpio_number);
    const char *GPIOExport = "/sys/class/gpio/export";

    // Exporting the GPIO to user space
    FILE *fp;

    // Setting GPIO direction as input
    char GPIODirection[40];
    sprintf(GPIODirection, "/sys/class/gpio/gpio%d/direction", gpio_number);
    fp = fopen(GPIODirection, "w");
    if (!fp)
    {
        printf("GPIODirection %s not found, exporting now...\n", GPIODirection);
        FILE *fpf = fopen(GPIOExport, "w");
        fwrite(gpio_num, sizeof(char), strlen(gpio_num), fpf);
        fclose(fpf);
        fp = fopen(GPIODirection, "w");
    }
    fwrite("in", sizeof(char), 2, fp);
    fclose(fp);
}
// sets up an interrupt on the given GPIO pin
void configure_interrupt(int gpio_number)
{
    // set gpio as input
    configure_gpio_input(gpio_number);
    // configure interrupts using edge file
    char InterruptEdge[40];
    sprintf(InterruptEdge, "/sys/class/gpio/gpio%d/edge", gpio_number);
    // configure interrupt on falling edge
    FILE *fp = fopen(InterruptEdge, "w");
    if (!fp)
    {
        printf("InterruptEdge not found\n");
        exit(EXIT_FAILURE);
    }
    fwrite("falling", sizeof(char), 7, fp);
    // configure interrupt on both edges
    // fwrite("both", sizeof(char), 4, fp);
    fclose(fp);
}
// ===============================================================
// config_pin()
//    > Setup input pin in given mode
// ===============================================================
void config_pin(char *pin_number, char *mode)
{
    // Creates environment to execute shell command
    if (!vfork())
    {
        // Execute shell command for pin configuration
        int ret = execl("/usr/bin/config-pin", "config-pin", pin_number, mode, NULL);
        if (ret < 0)
        {
            printf("Failed to configure pin in PWM mode.\n");
            exit(-1);
        }
    }
}

// ===============================================================
// set_pwm_duty_cycle()
//    > Set PWM duty cycle
// ===============================================================
void set_pwm_duty_cycle(char *pwmchip, char *channel, char *duty_cycle)
{
    // Export file path
    char PWMDutyCycle[60];
    sprintf(PWMDutyCycle, "/sys/class/pwm/%s/pwm-4:%s/duty_cycle", pwmchip, channel);

    // Configure PWM device
    FILE *fp = fopen(PWMDutyCycle, "w");
    if (!fp)
    {
        printf("PWMDutyCycle not found\n");
        exit(EXIT_FAILURE);
    }
    fwrite(duty_cycle, sizeof(char), strlen(duty_cycle), fp);
    fclose(fp);
}

// ===============================================================
// set_pwm_period()
//    > Set PWM period
// ===============================================================
void set_pwm_period(char *pwmchip, char *channel, char *period)
{
    long duty_cycle_int, period_int;
    char PWMDutyCycle[60], duty_cycle_str[20];

    // Before setting up the period, read old duty cycle
    sprintf(PWMDutyCycle, "/sys/class/pwm/%s/pwm-4:%s/duty_cycle", pwmchip, channel);
    FILE *fp = fopen(PWMDutyCycle, "r");
    if (!fp)
    {
        printf("PWMDutyCycle not found\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%ld", &duty_cycle_int);
    fclose(fp);
    period_int = atol(period);

    // If the old duty_cycle value is greater than the new period, update the dummy_duty_cycle
    // first to avoid errors with setting up the period
    if (duty_cycle_int >= period_int)
    {

        duty_cycle_int = period_int / 2;
        sprintf(duty_cycle_str, "%ld", duty_cycle_int);       // Convert long to char data type
        set_pwm_duty_cycle(pwmchip, channel, duty_cycle_str); // Setup dummy duty cycle
    }

    // Export file path
    char PWMPeriod[60];
    sprintf(PWMPeriod, "/sys/class/pwm/%s/pwm-4:%s/period", pwmchip, channel);
    fp = fopen(PWMPeriod, "w");
    if (!fp)
    {
        printf("PWMPeriod not found\n");
        exit(EXIT_FAILURE);
    }
    fwrite(period, sizeof(char), strlen(period), fp);
}

// ===============================================================
// start_pwm()
//    > Starts a PWM
// ===============================================================
void start_pwm(char *pin_number, char *pwmchip, char *channel, char *period, char *duty_cycle)
{
    // Configure the pin in PWM mode
    config_pin(pin_number, "pwm");

    // Export PWM device
    FILE *fp;
    char PWMExport[40];
    sprintf(PWMExport, "/sys/class/pwm/%s/export", pwmchip);
    fp = fopen(PWMExport, "w");
    if (!fp)
    {
        printf("PWMExport not found\n");
        exit(EXIT_FAILURE);
    }
    fwrite(channel, sizeof(char), strlen(channel), fp);
    fclose(fp);

    set_pwm_period(pwmchip, channel, period);         // Configure PWM Period
    set_pwm_duty_cycle(pwmchip, channel, duty_cycle); // Configure PWM Duty Cycle

    // Enable PWM
    char PWMEnable[40];
    sprintf(PWMEnable, "/sys/class/pwm/%s/pwm-4:%s/enable", pwmchip, channel);
    fp = fopen(PWMEnable, "w");
    fwrite("1", sizeof(char), 1, fp); // Configure generating PWM
    if (!fp)
    {
        printf("PWMEnable not found\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

// ===============================================================
// stop_pwm()
//    > Stops a PWM
// ===============================================================
void stop_pwm(char *pin_number, char *pwmchip, char *channel)
{
    char PWMDisable[40];

    // Stop generating PWM
    sprintf(PWMDisable, "/sys/class/pwm/%s/pwm-4:%s/enable", pwmchip, channel);
    FILE *fp = fopen(PWMDisable, "w");
    if (!fp)
    {
        printf("PWMDisablenot found\n");
        exit(EXIT_FAILURE);
    }
    fwrite("0", sizeof(char), 1, fp);
    fclose(fp);
}

// ===============================================================
// main()
//    > Program enters here
// ===============================================================
int main(int argc, const char *argv[])
{
    // Configure pin P8_6 and P8_9 as inputs
    int gpio_number1 = 67;
    int gpio_number2 = 69;
    configure_gpio_input(gpio_number1);
    configure_gpio_input(gpio_number2);
    // File path to read button status
    char valuePath1[40];
    char valuePath2[40];
    sprintf(valuePath1, "/sys/class/gpio/gpio%d/value", gpio_number1);
    sprintf(valuePath2, "/sys/class/gpio/gpio%d/value", gpio_number2);

    // Make sure the PWM pin and channel are cleared first
    char pin_number[32] = "P9_16";
    char pwmchip[32] = "pwmchip4";
    char channel[32] = "1";
    stop_pwm(pin_number, pwmchip, channel);

    // Wait before first readings to avoid faulty readings
    sleep(1);

    int state1, state2;
    FILE *fp1, *fp2;

    // Loop to monitor events
    while (1)
    {
        // Default state is 1 since buttons are configured with internal
        // pull-up //resistors. So, reading 0 means button is pressed
        fp1 = fopen(valuePath1, "r");
        if (!fp1)
        {
            printf("fp1 not found\n");
            exit(EXIT_FAILURE);
        }
        fscanf(fp1, "%d", &state1);
        fclose(fp1);

        // Event detected
        if (state1 == 0)
        {
            char period[32] = "1000000000";
            char duty_cycle[32] = "500000000";

            stop_pwm(pin_number, pwmchip, channel);                      // Make sure the PWM pin and channel are cleared first
            start_pwm(pin_number, pwmchip, channel, period, duty_cycle); // Start PWM
        }

        fp2 = fopen(valuePath2, "r");
        if (!fp2)
        {
            printf("fp2not found\n");
            exit(EXIT_FAILURE);
        }
        fscanf(fp2, "%d", &state2);
        fclose(fp2);

        if (state2 == 0)
        {
            char period[32] = "1000000";
            char duty_cycle[32] = "500000";

            stop_pwm(pin_number, pwmchip, channel);                      // pin and channel are cleared first
            start_pwm(pin_number, pwmchip, channel, period, duty_cycle); // Start PWM
        }
    }

    return 0;
}
