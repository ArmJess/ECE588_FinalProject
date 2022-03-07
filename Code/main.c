#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "signal.h"
#include "cache.h"
#include "signal.c"
#include "cache.c"
#include "coherenceprotocol.h"
#include "mi.c"
#include "msi.c"
#include "mesi.c"
#include <sys/stat.h>

//For execution times
struct timespec   StartTime;
struct timespec   EndTime;  

/*/////////////////////////////////////////
This is the main function.
1st) It takes in the input trace file and coherence protocol (MESI, MSI)
2nd) It reads in the trace file. Trace file contains 
*//////////////////////////////////////////
void main(int argc, char *argv[]){

    //get time needs to be added
    
	char *path, *coherenceProtocol;
    path = argv[1];
	coherenceProtocol = argv[2];
	
	//user enters less/more than expected input arguments
	if (argc != 3 ){
		printf ("Please check your command_format: \n <EXECUTABLE_FILE> <INPUT_REQUEST_FILE> <COHERENCE PROTOCOL:(MESI or MSI or MI)>");
		return;
	}
	
   //If user doesn't enter a valid cache coherence protocol
    for(int i=0; i<=1; i++){
        
        if (strcmp(coherenceProtocol,"MESI") ==0 || strcmp(coherenceProtocol,"MSI") ==0 || strcmp(coherenceProtocol,"msi") ==0 || strcmp(coherenceProtocol,"mesi") ==0 || strcmp(coherenceProtocol,"MI") ==0 || strcmp(coherenceProtocol,"mi") ==0){
            printf("I made it in");            
            break;
        }

        printf("Please choose a valid cache coherence protocol.(MESI or MSI): ");
        gets(coherenceProtocol);    //Takes in user input
        printf("\nYou chose %s\n", coherenceProtocol);
        i=0;
    }

    //Get clock start time
    clock_t tStart = clock();
    //clock_gettime(CLOCK_REALTIME, &StartTime);

    int loop_length = inputLength(path); //use this as the number of times we need to run the full loop through all cores (this is the number of rows inside the input file)
    printf("number of input rows: %d\n", loop_length); //can take this out -> was just for double checking
    FILE *file = fopen(path, "r"); //opening the file to parse inputs below
    
    
    int i;
    //struct stat sb;
    //stat(file, &sb);

    //char *file_contents = malloc(sb.st_size);

    while (!feof(file)) {
        
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
        //printf("before_sending: req type: %c \n", arr_input[0].access_type);
        inputSignals(&signalCore0, &statusCore0, arr_input[0].processor, 0, &Cache0, arr_input[0].block_access, arr_input[0].access_type); //get status and B/P signal
        //printf("signal after input fn: %d \n", signalCore0);
        currentStats.core0.prev_status = statusCore0;
        currentStats.core0.curr_signal = signalCore0;
        //printf("signal after assigning: %d \n", currentStats.core0.curr_signal);

        //Core1
        currentStats.core1.mem_location = arr_input[0].block_access; //get mem location
        inputSignals(&signalCore1, &statusCore1, arr_input[0].processor, 1, &Cache1, arr_input[0].block_access, arr_input[0].access_type); //get status and B/P signal
        currentStats.core1.prev_status = statusCore1;
        currentStats.core1.curr_signal = signalCore1;
        
        //Core2
        currentStats.core2.mem_location = arr_input[0].block_access; //get mem location
        inputSignals(&signalCore1, &statusCore1, arr_input[0].processor, 2, &Cache2, arr_input[0].block_access, arr_input[0].access_type); //get status and B/P signal
        currentStats.core2.prev_status = statusCore2;
        currentStats.core2.curr_signal = signalCore2;
    
        //Core3
        currentStats.core3.mem_location = arr_input[0].block_access; //get mem location
        inputSignals(&signalCore1, &statusCore1, arr_input[0].processor, 3, &Cache3, arr_input[0].block_access, arr_input[0].access_type); //get status and B/P signal
        currentStats.core3.prev_status = statusCore3;
        currentStats.core3.curr_signal = signalCore3;


        //2. Getting new status from protocol functions
        //Core0
            //call protocol function and send in &currentStats nested structure (pointer in function) so that the protocol can know the status of this one mem location in all caches
            //outputs of the protocol function can go into the currentStats structure new_status column
            //example here is just saying that the output of Core0 protocol function is Modified
        if ((coherenceProtocol == "msi") || (coherenceProtocol == "MSI"))
            currentStats.core0.new_status = msi(currentStats, 0);
        else if ((coherenceProtocol == "mesi") || (coherenceProtocol == "MESI"))
            currentStats.core0.new_status = mesi(currentStats, 0);
        else if ((coherenceProtocol == "mi") || (coherenceProtocol == "MI"))
            currentStats.core0.new_status = mi(currentStats, 0);

        newCore0 = currentStats.core0.new_status;

        //Core1
        if ((coherenceProtocol == "msi") || (coherenceProtocol == "MSI"))
            currentStats.core1.new_status =  msi(currentStats, 1);
        else if ((coherenceProtocol == "mesi") || (coherenceProtocol == "MESI"))
            currentStats.core1.new_status = mesi(currentStats, 1);
        else if ((coherenceProtocol == "mi") || (coherenceProtocol == "MI"))
            currentStats.core1.new_status = mi(currentStats, 1);

        newCore1 = currentStats.core1.new_status; 
        
        //Core2
        if ((coherenceProtocol == "msi") || (coherenceProtocol == "MSI"))
            currentStats.core2.new_status =  msi(currentStats, 2);
        else if ((coherenceProtocol == "mesi") || (coherenceProtocol == "MESI"))
            currentStats.core2.new_status = mesi(currentStats, 2);
        else if ((coherenceProtocol == "mi") || (coherenceProtocol == "MI"))
            currentStats.core2.new_status = mi(currentStats, 2);
        
        newCore2 = currentStats.core2.new_status;
        
        //Core3
        if ((coherenceProtocol == "msi") || (coherenceProtocol == "MSI"))
            currentStats.core3.new_status =  msi(currentStats, 3);
        else if ((coherenceProtocol == "mesi") || (coherenceProtocol == "MESI"))
            currentStats.core3.new_status = mesi(currentStats, 3);
        else if ((coherenceProtocol == "mi") || (coherenceProtocol == "MI"))
            currentStats.core3.new_status = mi(currentStats, 3);
        
        newCore3 = currentStats.core3.new_status;

        //3. Inserting new status into the caches
        //Core0
        insert(&Cache0, arr_input[0].block_access, newCore0);

        //Core1
        insert(&Cache1, arr_input[0].block_access, newCore1);
        
        //Core2
        insert(&Cache2, arr_input[0].block_access, newCore2);
        
        //Core3
        insert(&Cache3, arr_input[0].block_access, newCore3);

        //Testing outputs
        //Core 0 debug
        printf("Testing: cache contents for Core0:\n");
        printCacheContent(&Cache0); //just included for some verification debug
        
        //Core 1 debug
        printf("Testing: cache contents for Core1:\n");
        printCacheContent(&Cache1); //just included for some verification debug
        
        //Core 2 debug
        printf("Testing: cache contents for Core2:\n");
        printCacheContent(&Cache2); //just included for some verification debug
        
        //Core 3 debug
        printf("Testing: cache contents for Core3:\n");
        printCacheContent(&Cache3); //just included for some verification debug
    }
   
    fclose(file);
    //end get time and report out time taken
    //clock_gettime(CLOCK_REALTIME, &EndTime);
 
    printf("Time taken: %.12fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    //unsigned long long int runtime = 1000000000 * (EndTime.tv_sec - StartTime.tv_sec) + EndTime.tv_nsec - StartTime.tv_nsec;
    //printf("Time = %lld nanoseconds\t(%d.%09lld sec)\n", runtime, runtime / 1000000000, runtime % 1000000000);
    return;
}
