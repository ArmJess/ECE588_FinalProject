#include <stdio.h>
#include <string.h>
#include "signal.h"
#include "cache.h"

void main(){

    //for loop to go around everything until we go through all the inputs until we hit length of input file
    //get time needs to be added
    //input file -> someone can make this argv, argc when they get a chance instead
    char *path;
    path = "input1.txt";
    int loop_length = inputLength(path); //use this as the number of times we need to run the full loop through all cores (this is the number of rows inside the input file)
    printf("number of input rows: %d\n", loop_length); //can take this out -> was just for double checking
    FILE *file = fopen(path, "r"); //opening the file to parse inputs below
    inputParse(&arr_input[0], file);
    //access the input information from arr_input[0], shown below

    signal_t signal;
    status_t current_status;
    inputSignals(&signal, &current_status,arr_input[0].processor, 0, &Cache0, arr_input[0].block_access, arr_input[0].access_type); //core0 example only shown here

    //MESI/MSI/MI protocol function and output status to be used below

    insert(&Cache0, arr_input[0].block_access, Modified); //example after getting MESI/MSI/MI protocol output (Modified is made up here and needs to be replaced by protocol)

    printf("Testing: cache contents for Core0:\n");
    printCacheContent(&Cache0); //just included for some verification debug
    //each core needs to be added
    //etc

    fclose(file);
    //end get time and report out time taken
    return;
}