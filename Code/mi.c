#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cache.h"
#include "signal.h"

status_t mi(struct per_core_stats currentStats, int processor_num){
	//MI for Cache0
	if(processor_num == 0){	
		if ((currentStats.core0.curr_signal == P_RD) || (currentStats.core0.curr_signal == P_WR)){
			currentStats.core0.new_status = Modified; //from any status to modified
		}
		else if ((currentStats.core0.curr_signal == B_RD) || (currentStats.core0.curr_signal == B_WR)){
			currentStats.core0.new_status = Invalid;
		}
		return currentStats.core0.new_status;
	}
	//MI for Cache1
	else if(processor_num == 1){	
		if ((currentStats.core1.curr_signal == P_RD) || (currentStats.core1.curr_signal == P_WR)){
			currentStats.core1.new_status = Modified; //from any status to modified
		}
		else if ((currentStats.core1.curr_signal == B_RD) || (currentStats.core1.curr_signal == B_WR)){
			currentStats.core1.new_status = Invalid;
		}
		return currentStats.core1.new_status;
	}
	//MI for Cache2
	else if(processor_num == 2){	
		if ((currentStats.core2.curr_signal == P_RD) || (currentStats.core2.curr_signal == P_WR)){
			currentStats.core2.new_status = Modified; //from any status to modified
		}
		else if ((currentStats.core2.curr_signal == B_RD) || (currentStats.core2.curr_signal == B_WR)){
			currentStats.core2.new_status = Invalid;
		}
		return currentStats.core2.new_status;
	}
	//MI for Cache3
	else if(processor_num == 3){	
		if ((currentStats.core3.curr_signal == P_RD) || (currentStats.core3.curr_signal == P_WR)){
			currentStats.core3.new_status = Modified; //from any status to modified
		}
		else if ((currentStats.core3.curr_signal == B_RD) || (currentStats.core3.curr_signal == B_WR)){
			currentStats.core3.new_status = Invalid;
		}
		return currentStats.core3.new_status;
	}
}