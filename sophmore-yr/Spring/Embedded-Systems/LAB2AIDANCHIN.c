#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
 printf("\n LED Flash Start \n");
 FILE *LEDHandle = NULL;
 FILE *record = NULL;
 // directory path to the 4th led's brighness file
 const char *LEDBrightness="/sys/class/leds/beaglebone:green:usr3/brightness";
 const char *time_diff_file="time_diff_file.txt";
 struct timespec stamp1, stamp2;
 // make record file “time_diff_file.txt"
 if ((record = fopen(time_diff_file, "w")) != NULL){
//
 // flash the led 1000 times
 for(int i=0; i<10; i++){
 // Open the file
 // Read/Write only if the file pointer is not NULL
 // Always check for this condition to avoid Segmentation fault
 if((LEDHandle = fopen(LEDBrightness, "r+")) != NULL){
 // Turn the led on
 fwrite("1", sizeof(char), 1, LEDHandle);
 // Close the led file
 fclose(LEDHandle);
 }
 
 // sleep for 5^5 microsecond or .5 second
 clock_gettime(CLOCK_MONOTONIC, &stamp1);
 usleep(500000);
 clock_gettime(CLOCK_MONOTONIC, &stamp2);
 fprintf(record,"%ld ",stamp2.tv_nsec - stamp1.tv_nsec);
 // Open the file and check for the same condition as above
 if((LEDHandle = fopen(LEDBrightness, "r+")) != NULL){
 // Turn the led off
 fwrite("0", sizeof(char), 1, LEDHandle);
 // Close the led file
 fclose(LEDHandle);
 }
 // sleep again for 5^5 microsecond or .5 second
 
 clock_gettime(CLOCK_MONOTONIC, &stamp1);
 usleep(500000);
 clock_gettime(CLOCK_MONOTONIC, &stamp2);
 fprintf(record,"%ld ",stamp2.tv_nsec - stamp1.tv_nsec);
 }
 fclose(record);
 printf("\n LED Flash End");
} else {
    printf("error opening file%s\n", time_diff_file);
}
}