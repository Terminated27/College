#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// Sets up GPIO pin as input
void configure_gpio_input(int gpio_number){
    char gpio_num[10];
    sprintf(gpio_num, "%d", gpio_number);
    const char* GPIOExport = "/sys/class/gpio/export";
    
    // Exporting the GPIO to user space
    FILE* fp = fopen(GPIOExport, "w");
    fwrite(gpio_num, sizeof(char), strlen(gpio_num), fp);
    fclose(fp);
    
    // Setting GPIO direction as input
    char GPIODirection[40];
    sprintf(GPIODirection, "/sys/class/gpio/gpio%d/direction", gpio_number);
    
    // Setting GPIO as input
    fp = fopen(GPIODirection, "w");
    fwrite("in", sizeof(char), 2, fp);
    fclose(fp);
}

// Setup input pin in given mode
void config_pin(char* pin_number, char* mode){
    // Creates environment to execute shell command
    if(!vfork()){
        // Execute shell command for pin configuration
        int ret = execl("/usr/bin/config-pin", "config-pin", pin_number, mode, NULL);
        if (ret < 0){
            printf("Failed to configure pin in PWM mode.\n");
            exit(-1);
        }
    }
}

// Set PWM duty cycle
void set_pwm_duty_cycle(char* pwmchip, char* channel, char* duty_cycle){
    // Export file path
    char PWMDutyCycle[60];
    sprintf(PWMDutyCycle, "/sys/class/pwm/%s/pwm-4:%s/duty_cycle", pwmchip, channel);
    
    // Configure PWM device
    FILE* fp = fopen(PWMDutyCycle, "w");
    fwrite(duty_cycle, sizeof(char), strlen(duty_cycle), fp);
    fclose(fp);
}

// Set PWM period
void set_pwm_period(char* pwmchip, char* channel, char* period){
    long duty_cycle_int, period_int;
    
    // Before setting up the period, read old duty cycle
    char PWMDutyCycle[60], duty_cycle_str[20];
    sprintf(PWMDutyCycle, "/sys/class/pwm/%s/pwm-4:%s/duty_cycle", pwmchip, channel);
    FILE* fp = fopen(PWMDutyCycle, "r");
    fscanf(fp, "%ld", &duty_cycle_int);
    fclose(fp);
    
    period_int = atol(period);
    
    // If the old duty_cycle value is greater than the new period,
    // update the dummy_duty_cycle first to avoid errors with setting up
    // the period
    if (duty_cycle_int >= period_int){
        duty_cycle_int = period_int / 2;
        // Convert long to char data type
        sprintf(duty_cycle_str, "%ld", duty_cycle_int);
        // Setup dummy duty cycle
        set_pwm_duty_cycle(pwmchip, channel, duty_cycle_str);
    }
    
    // Export file path
    char PWMPeriod[60];
    sprintf(PWMPeriod, "/sys/class/pwm/%s/pwm-4:%s/period", pwmchip, channel);
    fp = fopen(PWMPeriod, "w");
    fwrite(period, sizeof(char), strlen(period), fp);
}

// Starts a PWM
void start_pwm(char* pin_number, char* pwmchip, char* channel, char* period, char* duty_cycle){
    /* Input:
    pin_number: pin_number to generate PWM on
    pwmchip: the device folder to generate PWM
    channel: pwm device channel
    period: pwm period
    duty_cycle: pwm duty cycle */
    
    // Configure the pin in PWM mode
    config_pin(pin_number, "pwm");
    
    // Export PWM device
    FILE* fp;
    char PWMExport[40];
    sprintf(PWMExport, "/sys/class/pwm/%s/export", pwmchip);
    fp = fopen(PWMExport, "w");
    fwrite(channel, sizeof(char), strlen(channel), fp);
    fclose(fp);
    
    // Configure PWM Period
    set_pwm_period(pwmchip, channel, period);
    
    // Configure PWM Duty Cycle
    set_pwm_duty_cycle(pwmchip, channel, duty_cycle);
    
    // Enable PWM
    char PWMEnable[40];
    sprintf(PWMEnable, "/sys/class/pwm/%s/pwm-4:%s/enable", pwmchip, channel);
    // Configure generating PWM
    fp = fopen(PWMEnable, "w");
    fwrite("1", sizeof(char), 1, fp);
    fclose(fp);
}

void stop_pwm(char* pin_number, char* pwmchip, char* channel){
    char PWMDisable[40];
    sprintf(PWMDisable, "/sys/class/pwm/%s/pwm-4:%s/enable", pwmchip, channel);
    // Stop generating PWM
    FILE* fp = fopen(PWMDisable, "w");
    fwrite("0", sizeof(char), 1, fp);
    fclose(fp);
}

int main(){
    // Configure pin P8_8 and P8_9 as inputs
    int gpio_number1 = 67;
    int gpio_number2 = 68;
    configure_gpio_input(gpio_number1);
    configure_gpio_input(gpio_number2);
    
    // File path to read button status
    char valuePath1[40];
    char valuePath2[40];
    sprintf(valuePath1, "/sys/class/gpio/gpio%d/value", gpio_number1);
    sprintf(valuePath2, "/sys/class/gpio/gpio%d/value", gpio_number2);
    
    char pin_number[32] = "P9_16";
    char pwmchip[32] = "pwmchip4";
    char channel[32] = "1";
    char period[32] = "1000000";
    char duty_cycle[32] = "500000";
    
    stop_pwm(pin_number, pwmchip, channel); // Make sure the PWM pin and channel are cleared first
    start_pwm(pin_number, pwmchip, channel, period, duty_cycle); // Start PWM
    
    // Wait before first readings to avoid faulty readings
    sleep(1);
    
    int state1;
    int state2;
    FILE *fp
    
    // Loop to monitor events
    while(1){
        fp = fopen(valuePath1, "r");

        
        // Default state is 1 since buttons are configured with internal pull-up //resistors.
        // So, reading 0 means button is pressed
        fscanf(fp, "%d", &state1);
        fclose(fp);

        
        // Event detected
        if (state1 == 0){
            char period[32] = "1000000000";
            char duty_cycle[32] = "500000000";
            stop_pwm(pin_number, pwmchip, channel); // Make sure the PWM pin and //channel are cleared first
            start_pwm(pin_number, pwmchip, channel, period, duty_cycle); // Start PWM
        }
        fp = fopen(valuePath2, "r");
        fscanf(fp, "%d", &state2);
        fclose(fp);
        if (state2 == 0){
            char period[32] = "1000000";
            char duty_cycle[32] = "500000";
            stop_pwm(pin_number, pwmchip, channel); // Make sure the PWM pin and
//channel are cleared first
            start_pwm(pin_number, pwmchip, channel, period, duty_cycle); // Start PWM
        }
    }
    return 0;
}
