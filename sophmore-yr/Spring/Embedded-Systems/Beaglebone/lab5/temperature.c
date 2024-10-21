#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/epoll.h>
#include <pthread.h>

// ===============================================================
// configure_gpio_input()
//    > Sets up GPIO pin as input
// ===============================================================
void configure_gpio_input(int gpio_number)
{
    // Attempt to open /sys/class/gpio/gpio67/direction
    //  if(!fp): open /sys/class/gpio/export and add 67

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
//  CtoF()
//    > Celcius to Farenheit
// ===============================================================
// Read the digital value from the ADC interface.
const char AIN_DEV[] = "/sys/bus/iio/devices/iio:device0/in_voltage1_raw";
double CtoF(double c)
{
    return (c * 9.0 / 5.0) + 32.0;
}
// ===============================================================
// temperature()
//    > extract temperature from TMP36 data
// ===============================================================
double temperature(int value)
{
    // Convert the digital value to millivolts.
    double millivolts = (value / 4096.0) * 1800;
    // Convert the millivolts to Celsius temperature.
    // Celcius conversion from the TMP36 Datasheet
    double temperature = (millivolts - 500.0) / 10.0;
    return temperature;
}
// ===============================================================
// sensor_type
//    > struct that holds timestamp value and temp in celcius
// ===============================================================
struct sensor_type
{
    struct timespec timestamp;
    double celcius_temperature;
};
// ===============================================================
// outputThread()
//    > output information stored from buffer to text file
//     "Aidan_Chin_sensordata.txt”
// ===============================================================
void *outputThread(void *input)
{
    // Cast input to the appropriate type if needed
    struct sensor_type *input_array = (struct sensor_type *)input;

    // Declare buffer array and copy elements from input_array
    struct sensor_type buffer[10];
    for (int i = 0; i < 10; i++)
    {
        buffer[i] = input_array[i];
    }
    for (int j = 0; j < 10; j++)
    {
        FILE *fb = fopen("Aidan_Chin_sensordata.txt", "a");

        // Check if the file was opened successfully
        if (fb == NULL)
        {
            perror("Error Aidan_Chin_sensordata.txt file");
            exit(EXIT_FAILURE);
        }

        // Write data to the file using fprintf
        fprintf(fb, "%.9f, %f\n",
                buffer[j].timestamp.tv_sec + (((double)buffer[j].timestamp.tv_nsec) / 1000000000), buffer[j].celcius_temperature);
        // Mirror data in the terminal
        printf("Buffer content: Celcius = %f, timestamp = %.9f\n",
               buffer[j].celcius_temperature, buffer[j].timestamp.tv_sec + (((double)buffer[j].timestamp.tv_nsec) / 1000000000));
        // Close the file when done
        fclose(fb);
    }
}
// ===============================================================
// inputThread()
//    > record clock and temp data
// ===============================================================
void *inputThread()
{
    FILE *f;
    int a2dReading = 0;               // analog output from a2d pin
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
    struct sensor_type buffer[10];
    for (int i = 0; i < 10; i++)
    { // Capture interrupt ten times
        // (STEP 5) wait for epoll interface to signal the change
        capture_interrupt = epoll_wait(epfd, &ev_wait, 1, -1);
        f = fopen(AIN_DEV, "r");
        if (f == NULL)
        {
            printf("ERROR: Unable to open voltage input file.\n");
            exit(-1);
        }
        // Get analog to digital reading
        fscanf(f, "%d", &a2dReading);
        fclose(f);
        double celsius = temperature(a2dReading);
        // write sensor readings to buffer array
        buffer[i].celcius_temperature = celsius;
        clock_gettime(CLOCK_MONOTONIC, &buffer[i].timestamp);
    }
    // (STEP 6) close the epoll interface
    close(epfd);
    // throw into outputThread to print to text file
    // Create output thread
    pthread_t output_thread;
    if (pthread_create(&output_thread, NULL, outputThread, (void *)buffer) != 0)
    {
        perror("Error creating output thread");
    }

    // Wait for output thread to finish
    pthread_join(output_thread, NULL);

    pthread_exit(0);
}

// ===============================================================
// main()
//    > Program enters here
// ===============================================================
int main()
{
    // run 4 times to get 40 data points
    pthread_t thread_id;
    for (int i = 0; i < 4; i++)
    {
        if (pthread_create(&thread_id, NULL, inputThread, NULL) != 0)
        {
            perror("Error creating input thread");
            exit(EXIT_FAILURE);
        }
        pthread_join(thread_id, NULL);
    }
}
