#include <stdio.h>
#include <string.h>
#include "signal.h"
#include "cache.h"

void main(){

    int a = 58;
    int b = 360;
    int c = 4556;

    insert(&Cache0, c, Modified);
    insert(&Cache0, c, Exclusive);
    insert(&Cache0, a, Modified);
    insert(&Cache0, b, Shared);
    insert(&Cache0, b, Invalid);

    printCacheContent(&Cache0);

    signal_t signal;
    status_t current_status;
    access_type_t r = Read;

    inputSignals(&signal, &current_status, 0, 0, &Cache0, a, Read); //Expect: P_RD and Modified
    printf("What is the output from the inputSignals function? signal %s and previous status %s\n", signalNames[signal], statusNames[current_status]);
    inputSignals(&signal, &current_status, 0, 0, &Cache0, b, Read); //Expect: P_RD and Invalid
    printf("What is the output from the inputSignals function? signal %s and previous status %s\n", signalNames[signal], statusNames[current_status]);
    inputSignals(&signal, &current_status, 0, 0, &Cache0, c, Write); //Expect: P_WR and Exclusive
    printf("What is the output from the inputSignals function? signal %s and previous status %s\n", signalNames[signal], statusNames[current_status]);
    inputSignals(&signal, &current_status, 0, 2, &Cache2, c, Read); //Expect: B_RD and Uninit
    printf("What is the output from the inputSignals function? signal %s and previous status %s\n", signalNames[signal], statusNames[current_status]);

    struct input_line_info info;
    char *path;

    path = "input1.txt";
    FILE *file = fopen(path, "r");
    inputParse(&arr_input[0], file);
    inputParse(&info, file);
    inputParse(&info, file);

    printf("array form of the file outputs parsed into an array of structures: %d, %d, %d, %c", arr_input[0].processor, arr_input[0].block_access, arr_input[0].access_time, arr_input[0].access_type);

    fclose(file);
  
    return;
}