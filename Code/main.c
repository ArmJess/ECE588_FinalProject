#include <stdio.h>
#include <string.h>
#include "signal.h"
#include "cache.h"

void main(){

    //get time needs to be added
    //input file -> someone can make this argv, argc when they get a chance instead of hardcoding path below
    char *path;
    path = "input1.txt";
    int loop_length = inputLength(path); //use this as the number of times we need to run the full loop through all cores (this is the number of rows inside the input file)
    printf("number of input rows: %d\n", loop_length); //can take this out -> was just for double checking
    FILE *file = fopen(path, "r"); //opening the file to parse inputs below
    inputParse(&arr_input[0], file);
    //access the input information from arr_input[0] which represents the current line of input that we are working on



    //Starting loop for each input row (one mem location per row)
        //for loop to go around everything until we go through all the inputs until we hit length of input file (variable of length: loop_length)

    //structure called per_core_stats:
    //structure in which to save all the caches status of the current input mem location and current per core B/P signals (this structure is a nested structure and can be sent into and out of the protocol functions)
    //Core      previous status     signal      new status      memory location value
    //Core0         X                   Y            Z                      A
    //Core1         W                   P            Q                      A
    //Core2         B                   C            D                      A
    //Core3         O                   R            S                      A
    //the inputParse function will fill the memory location value, the inputSignals fuction will fill the previous status and signal columns, and the <protocol functions> will fill the new status column
    //new status column can be used to save the status to be inserted into the caches at the end of each loop
    //this structure is reset at the start of each loop
    struct per_core_stats currentStats= resetStruct;

    //reset statuses each loop
    status_t statusCore0 = Uninit;
    status_t statusCore1 = Uninit;
    status_t statusCore2 = Uninit;
    status_t statusCore3 = Uninit;

    //reset signals each loop
    signal_t signalCore0 = NA;
    signal_t signalCore1 = NA;
    signal_t signalCore2 = NA;
    signal_t signalCore3 = NA;

    //reset new status each loop, this is to be input to the cache after protocol function runs
    status_t newCore0 = Uninit;
    status_t newCore1 = Uninit;
    status_t newCore2 = Uninit;
    status_t newCore3 = Uninit;

    //1. Getting previous status of mem and B/P signal
    //Core0
    currentStats.core0.mem_location = arr_input[0].block_access; //get mem location
    inputSignals(&signalCore0, &statusCore0, arr_input[0].processor, 0, &Cache0, arr_input[0].block_access, arr_input[0].access_type); //get status and B/P signal
    currentStats.core0.prev_status = statusCore0;
    currentStats.core0.curr_signal = signalCore0;

    //Core1

    //Core2

    //Core3



    //2. Getting new status from protocol functions
    //Core0
        //call protocol function and send in &currentStats nested structure (pointer in function) so that the protocol can know the status of this one mem location in all caches
        //outputs of the protocol function can go into the currentStats structure new_status column
        //example here is just saying that the output of Core0 protocol function is Modified
        currentStats.core0.new_status = Modified;
        newCore0 = currentStats.core0.new_status;

    //Core1
    
    //Core2

    //Core3

    //3. Inserting new status into the caches
    //Core0
    insert(&Cache0, arr_input[0].block_access, newCore0);

    //Core1

    //Core2

    //Core3

    //Testing outputs
    
        printf("Testing: cache contents for Core0:\n");
        printCacheContent(&Cache0); //just included for some verification debug


    fclose(file);
    //end get time and report out time taken
    return;
}