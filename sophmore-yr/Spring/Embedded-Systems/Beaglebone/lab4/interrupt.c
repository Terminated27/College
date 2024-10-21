#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/epoll.h>

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
int main()
{
    int gpio_number = 67;             // P8_8 gpio pin
    configure_interrupt(gpio_number); // enable interrupt
    // the following code can be used to receive interrupts on the registered pin
    char InterruptPath[40];
    sprintf(InterruptPath, "/sys/class/gpio/gpio%d/value", gpio_number);
    int epfd;
    struct epoll_event ev;
    // (STEP 1) open the interrupt file
    // file pointer (C abstraction to manipulate files)
    FILE *fp = fopen(InterruptPath, "r");
    // file descriptor (Unix Linux file identifier used by system calls)
    int fd = fileno(fp);
    // (STEP 2) create epoll instance to monitor I/O events on interrupt file
    epfd = epoll_create(1);
    // (STEP 3) register events that will be monitored
    // detects whenever a new data is available for read (EPOLLIN)
    // signals the read events when the available read value has changed (EPOLLET)
    ev.events = EPOLLIN | EPOLLET;
    // (STEP 4) register interrupt file with epoll interface for monitoring
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    int capture_interrupt;
    struct epoll_event ev_wait;
    struct timespec tm;
    char buffer[10][40];    
    for (int i = 0; i < 10; i++)
    { // Capture interrupt ten times
        // (STEP 5) wait for epoll interface to signal the change
        capture_interrupt = epoll_wait(epfd, &ev_wait, 1, -1);
        clock_gettime(CLOCK_MONOTONIC_RAW, &tm);
        sprintf(buffer[i],"Interrupt received: %d at %ld\n", capture_interrupt, tm.tv_sec);
    }
    for (int j = 0; j < 10; j++){
        printf("Buffer content: %s\n", buffer[j]); 
    }

    // (STEP 6) close the epoll interface
    close(epfd);
    return 0;
}
