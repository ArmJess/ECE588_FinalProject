#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cache.h"

#ifndef SIGNAL_H
#define SIGNAL_H

/*MSI and MESI Signals:
P_WR: Processor Write
P_RD: Processor Read
B_WR: Bus Write
B_RD: Bus Read

Additional MESI Signals:
P_Writeback:= Processor Write Back to Memory

MSI Diagram directions:
I (P_WR) -> M
I (P_RD) -> S
M (P_RD or P_WR) -> M
M (B_WR) -> I
M (B_RD) -> S
S (P_RD) -> S
S (P_WR) -> M
S (B_RD) -> S
S (B_WR) -> I

MESI Diagram directions:
I (P_WR) -> M
I (P_RD) -> S
I (P_RD) -> E
M (P_RD or P_WR) -> M
M (P_Writeback or B_WR) -> I
M (B_RD) -> S
S (P_RD) -> S
S (P_WR) -> M
S (B_WR) -> I
S (B_RD) -> S
E (P_RD) -> E
E (P_WR) -> M
E (B_WR) -> I
E (B_RD) -> S*/

typedef enum {P_WR = 0, P_RD = 1, B_WR = 2, B_RD = 3, P_Writeback = 4, NA = 5} signal_t;

extern const char* signalNames[];

typedef enum {Read = 0, Write = 1} access_type_t;

struct input_line_info
{
    int processor;
    int block_access;
    int access_time;
    char access_type;
};

//keeping an array of parsed input data, arbitrary array size of 16 chosen, fill one array slot by calling the inputParse function
struct input_line_info arr_input[16];

//Use this function in each core in order to get the signals generated by each input for each cache
//outputs: *output signal -> this is the bus or processor read or write signal generated for each core
//outputs: *previous signal -> this is the location mem MESI/MSI/MI status before current time
//outputs from this function pass to a MESI/MSI/MI function in order to figure out the next status of this locatiom mem in each cache
void inputSignals(signal_t *output_signal, status_t *previous_status, int processor_num, int current_processor,struct DLLNode **current_processor_cache, int location_mem, access_type_t input_access_type);

//Use this function in order to pull in data from the input file -> one row at a time with current implementation
void inputParse(struct input_line_info *line_info, FILE *file);

#endif