#include <stdio.h>
#include <string.h>
#include "signal.h"
#include "cache.h"

void main(){

    //for loop to go around everything until we go through all the inputs until we hit length of input file (Jess working on that function to give us X [number of input rows]) 
    //get time to be added
    //input file -> someone can make this argv, argc when they get a chance instead
    char *path;
    path = "input1.txt";
    FILE *file = fopen(path, "r");
    inputParse(&arr_input[0], file);
    //access the input information from arr_input[0]

    signal_t signal;
    status_t current_status;
    inputSignals(&signal, &current_status,arr_input[0].processor, 0, &Cache0, arr_input[0].block_access, arr_input[0].access_type); //core0 example only shown here

    //MESI/MSI/MI protocol function and output status to be used below

    insert(&Cache0, arr_input[0].block_access, Modified); //example after getting MESI/MSI/MI protocol output

    printf("Testing: cache contents for Core0");
    printCacheContent(&Cache0); //just included for some verification debug
    //each core to be added
    //etc

    return;
}