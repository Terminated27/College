#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    printf("\n LED Flash Start \n");
    FILE *LEDHandle = NULL;
    FILE *record = NULL;
    const char *LEDBrightness = "/sys/class/leds/beaglebone:green:usr3/brightness";
    const char *time_diff_file = "time_diff_file.txt";
    struct timespec stamp1, stamp2;

    if ((record = fopen(time_diff_file, "w")) != NULL) {
        for (int j = 0; j < 100; j++) {
            for (int i = 0; i < 5; i++) {
                if ((LEDHandle = fopen(LEDBrightness, "r+")) != NULL) {
                    fwrite("1", sizeof(char), 1, LEDHandle);
                    fclose(LEDHandle);
                }
    
                clock_gettime(CLOCK_MONOTONIC, &stamp1);
                usleep(500000);
                clock_gettime(CLOCK_MONOTONIC, &stamp2);
                fprintf(record, "%ld ", stamp2.tv_nsec - stamp1.tv_nsec);
                fflush(record); // Flush the buffer
    
                if ((LEDHandle = fopen(LEDBrightness, "r+")) != NULL) {
                    fwrite("0", sizeof(char), 1, LEDHandle);
                    fclose(LEDHandle);
                }
    
                clock_gettime(CLOCK_MONOTONIC, &stamp1);
                usleep(500000);
                clock_gettime(CLOCK_MONOTONIC, &stamp2);
                fprintf(record, "%ld ", stamp2.tv_nsec - stamp1.tv_nsec);
                fflush(record); // Flush the buffer
            }
            fprintf(record, "\n");
        }
        fclose(record);
        printf("\n LED Flash End\n");

    } else {
        printf("error opening file%s\n", time_diff_file);
    }
    return 0;
}

