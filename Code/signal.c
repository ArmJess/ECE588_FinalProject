//Prototypes for the functions below are found in the signal.h header file
#include "signal.h"

//Can use this array to printf user-friendly naming
const char* signalNames[] = {"P_WR","P_RD","B_WR","B_RD","P_Writeback", "NA"};


//note below: processor_num is the processor number associated with the input request and current_processor is the current processor we are looking into
void inputSignals(signal_t *output_signal, status_t *previous_status, int processor_num, int current_processor,struct DLLNode **current_processor_cache, int location_mem, access_type_t input_access_type){
//output_signal and previous_status are outputs from this function
    if(DEBUG){printf("getting into the inputSignals function\n");}
    signal_t temp_signal;
    status_t temp_status = Uninit;
    if(current_processor == processor_num){
        if(DEBUG){printf("checked the processor num and it matched\n");}
        //all signals are processor signals according to current processor
        if(checkMemInCache(current_processor_cache, location_mem)){
            temp_status = checkStatus(current_processor_cache, location_mem);
            if(DEBUG){printf("checked the processor and found it in mem\n");}
        }
        if(input_access_type == Read){
            temp_signal = P_RD; 
        }else{
            temp_signal = P_WR;
        }
    }else{
        if(DEBUG){printf("got into the else so we know the processor doesn't match\n");}
        //all signals are bus signals according to current processor
        if(checkMemInCache(current_processor_cache, location_mem)){
            temp_status = checkStatus(current_processor_cache, location_mem);
            if(DEBUG){printf("checked the processor and found it in mem\n");}
        }
        if(input_access_type == Read){
            temp_signal = B_RD; 
        }else{
            temp_signal = B_WR;
        }
    }
    //Need to do: write logic for P_Writeback since I am not so sure about that one yet <---------------
    *output_signal = temp_signal;
    *previous_status= temp_status;
    return;
}

//note below: parses one line of the input file at a time
void inputParse(struct input_line_info *line_info, FILE *file){
    int buffer0;
    int buffer1;
    int buffer2;
    char buffer3;
    static int row;

    while(fscanf(file, "%d%*c %d%*c %d%*c %c%*c", &buffer0, &buffer1, &buffer2, &buffer3) != EOF){

    printf("for input file row %d, requesting processor: %d\n", row, buffer0);
    printf("for input file row %d, block access (memory location): %d\n", row, buffer1);
    printf("for input file row %d, access time: %d\n", row, buffer2);
    printf("for input file row %d, access type: %c\n", row, buffer3);

    line_info->processor = buffer0;
    line_info->block_access = buffer1;
    line_info->access_time = buffer2;
    line_info->access_type = buffer3;
    row++;
    return;
    }
}

int inputLength(char *filepath){
    int temp_row = 0;
    char temp_buff[20];
    int status = 0;

    FILE *file = fopen(filepath, "r");

    while(status != EOF){
        status = fscanf(file, "%20c", &temp_buff);
        temp_row++;
    }

    fclose(file);
    return (temp_row-1);
}

int maxFour(int a, int b, int c, int d){
    int temp =0;

    if(a>b){
        temp = a;
    }else{
        temp = b;
    }
    if(c>temp){
        temp = c;
    }
    if(d>temp){
        temp = d;
    }

    return temp;
}

int timetax(struct per_core_stats currentStats, int processor_num){
    int temp=0;

    if(processor_num==0){
        if(currentStats.core0.prev_status==Invalid & currentStats.core0.new_status==Modified){
            temp = 5;
        }else if(currentStats.core0.prev_status==Invalid & currentStats.core0.new_status==Exclusive){
            temp = 5;
        }else if(currentStats.core0.prev_status==Invalid & currentStats.core0.new_status==Shared){
            temp = 2;
        }else{
            temp = 1;
        }
    }
    if(processor_num==1){
        if(currentStats.core1.prev_status==Invalid & currentStats.core1.new_status==Modified){
            temp = 5;
        }else if(currentStats.core1.prev_status==Invalid & currentStats.core1.new_status==Exclusive){
            temp = 5;
        }else if(currentStats.core1.prev_status==Invalid & currentStats.core1.new_status==Shared){
            temp = 2;
        }else{
            temp = 1;
        }
    }
    if(processor_num==2){
        if(currentStats.core2.prev_status==Invalid & currentStats.core2.new_status==Modified){
            temp = 5;
        }else if(currentStats.core2.prev_status==Invalid & currentStats.core2.new_status==Exclusive){
            temp = 5;
        }else if(currentStats.core2.prev_status==Invalid & currentStats.core2.new_status==Shared){
            temp = 2;
        }else{
            temp = 1;
        }
    }
    if(processor_num==3){
        if(currentStats.core3.prev_status==Invalid & currentStats.core3.new_status==Modified){
            temp = 5;
        }else if(currentStats.core3.prev_status==Invalid & currentStats.core3.new_status==Exclusive){
            temp = 5;
        }else if(currentStats.core3.prev_status==Invalid & currentStats.core3.new_status==Shared){
            temp = 2;
        }else{
            temp = 1;
        }
    }
    return temp;
}
