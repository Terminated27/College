#include <stdio.h>
#include <string.h>

// processes a student ID to obtain individual sum

int sum_id( char* user_input){
    int sum = 0;
    for(int i = 0;i < strlen(user_input); i++){
        sum += user_input[i]-'0';
    }
    return sum;
}

int main()
{
    // store student ID
    char student_id_1[9]; // student id 1
    char student_id_2[9]; // student id 2
    int sum = 0;

    printf("[BEFORE] sum: address %p with value of %s\n",sum, sum);

    printf("Enter Student ID 1:\n");
    scanf("%s",student_id_1);
    //gets(student_id_1);

    printf("[BEFORE] student_id_1: address %p with value of %s\n",student_id_1, student_id_1);

    printf("Enter Student ID 2:\n");
    scanf("%s",student_id_2);
    //gets(student_id_2);

    printf("[BEFORE] student_id_2: address %p with value of %s\n\n",student_id_2, student_id_2);

    // Do calculation here
    sum += sum_id(student_id_1);
    sum += sum_id(student_id_2);

    printf("[AFTER] student_id_1: address %p with value of %s\n",student_id_1, student_id_1);
    printf("[AFTER] student_id_2: address %p with value of %s\n",student_id_2, student_id_2);
    printf("[SUM] sum: address %p with value of %i\n",sum,sum);

    return 0;
}
