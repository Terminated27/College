/*
Aidan Chin Lab 1 
find timestamp and mean of an array 2x
2/20/24
*/

#include <stdio.h>
#include <time.h>

void timestampmean(int *array, struct timespec *timestamp, int *mean){

    clock_gettime(CLOCK_MONOTONIC, timestamp);
    *mean = 0;
    for(int i = 0; i < 10; i++)
    {
        *mean = *mean + array[i];
    }
    *mean = *mean / 10;
}

int main(void){
    struct timespec timestamp;
    int mean = 0;
    int array[10];
    for (int j = 0; j < 2; j++)
    {
        printf("Run Number %d\n", j+1);
        for(int i = 0; i < 10; i++)
        {
            printf("Input digit in position %d between 0 and 9000\n", i+1);
            scanf("%d", &array[i]);
        }
        timestampmean(array, &timestamp, &mean);
        printf("Timestamp = %ld mean = %d\n", timestamp.tv_nsec, mean); 
    }
    return 0;
}
