#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cache.h"
#include "signal.h"

status_t mesi(struct per_core_stats currentStats, int processor_num){
	//MESI for Cache0
	if(processor_num == 0){	
		if (currentStats.core0.curr_signal == P_RD){
			if ((currentStats.core0.prev_status == Modified) || (currentStats.core0.prev_status == Exclusive) || (currentStats.core0.prev_status == Shared)){
				currentStats.core0.new_status = currentStats.core0.prev_status;
			}
			else if ((currentStats.core0.prev_status == Invalid) || (currentStats.core0.prev_status == Uninit)){
				if ((currentStats.core1.prev_status == Modified) || (currentStats.core1.prev_status == Exclusive) || (currentStats.core1.prev_status == Shared)||
					(currentStats.core2.prev_status == Modified) || (currentStats.core2.prev_status == Exclusive) || (currentStats.core2.prev_status == Shared)||
					(currentStats.core3.prev_status == Modified) || (currentStats.core3.prev_status == Exclusive) || (currentStats.core3.prev_status == Shared)){
					currentStats.core0.new_status = Shared;
					}
				else {
					currentStats.core0.new_status = Exclusive;
				}
			}
		}
		else if (currentStats.core0.curr_signal == P_WR){
			currentStats.core0.new_status = Modified; //from any status to modified
		}
		else if (currentStats.core0.curr_signal == B_RD){
			if ((currentStats.core0.prev_status == Modified) || (currentStats.core0.prev_status == Exclusive) || (currentStats.core0.prev_status == Shared)){
				currentStats.core0.new_status = Shared;
			}
			else if ((currentStats.core0.prev_status == Invalid) || (currentStats.core0.prev_status == Uninit)){
				currentStats.core0.new_status = currentStats.core0.prev_status;
			}
		}
		else if (currentStats.core0.curr_signal == B_WR){
			if ((currentStats.core0.prev_status == Modified) || (currentStats.core0.prev_status == Exclusive) || (currentStats.core0.prev_status == Shared)){
				currentStats.core0.new_status = Invalid;
			}
			else if ((currentStats.core0.prev_status == Invalid) || (currentStats.core0.prev_status == Uninit)){
				currentStats.core0.new_status = currentStats.core0.prev_status;
			}
		}
		return currentStats.core0.new_status;
	}	
		
		
		
		//MESI for Cache1
	else if (processor_num == 1){	
		if (currentStats.core1.curr_signal == P_RD){
			if ((currentStats.core1.prev_status == Modified) || (currentStats.core1.prev_status == Exclusive) || (currentStats.core1.prev_status == Shared)){
				currentStats.core1.new_status = currentStats.core1.prev_status;
			}
			else if ((currentStats.core1.prev_status == Invalid) || (currentStats.core1.prev_status == Uninit)){
				if ((currentStats.core0.prev_status == Modified) || (currentStats.core0.prev_status == Exclusive) || (currentStats.core0.prev_status == Shared)||
					(currentStats.core2.prev_status == Modified) || (currentStats.core2.prev_status == Exclusive) || (currentStats.core2.prev_status == Shared)||
					(currentStats.core3.prev_status == Modified) || (currentStats.core3.prev_status == Exclusive) || (currentStats.core3.prev_status == Shared)){
					currentStats.core1.new_status = Shared;
					}
				else {
					currentStats.core1.new_status = Exclusive;
				}
			}
		}
		else if (currentStats.core1.curr_signal == P_WR){
			currentStats.core1.new_status = Modified; //from any status to modified
		}
		else if (currentStats.core1.curr_signal == B_RD){
			if ((currentStats.core1.prev_status == Modified) || (currentStats.core1.prev_status == Exclusive) || (currentStats.core1.prev_status == Shared)){
				currentStats.core1.new_status = Shared;
			}
			else if ((currentStats.core1.prev_status == Invalid) || (currentStats.core1.prev_status == Uninit)){
				currentStats.core1.new_status = currentStats.core1.prev_status;
			}
		}
		else if (currentStats.core1.curr_signal == B_WR){
			if ((currentStats.core1.prev_status == Modified) || (currentStats.core1.prev_status == Exclusive) || (currentStats.core1.prev_status == Shared)){
				currentStats.core1.new_status = Invalid;
			}
			else if ((currentStats.core1.prev_status == Invalid) || (currentStats.core1.prev_status == Uninit)){
				currentStats.core1.new_status = currentStats.core1.prev_status;
			}
		}
		return currentStats.core1.new_status;
	}	
		
		
		
		//MESI for Cache2
	else if (processor_num == 2){	
		if (currentStats.core2.curr_signal == P_RD){
			if ((currentStats.core2.prev_status == Modified) || (currentStats.core2.prev_status == Exclusive) || (currentStats.core2.prev_status == Shared)){
				currentStats.core2.new_status = currentStats.core2.prev_status;
			}
			else if ((currentStats.core2.prev_status == Invalid) || (currentStats.core2.prev_status == Uninit)){
				if ((currentStats.core1.prev_status == Modified) || (currentStats.core1.prev_status == Exclusive) || (currentStats.core1.prev_status == Shared)||
					(currentStats.core0.prev_status == Modified) || (currentStats.core0.prev_status == Exclusive) || (currentStats.core0.prev_status == Shared)||
					(currentStats.core3.prev_status == Modified) || (currentStats.core3.prev_status == Exclusive) || (currentStats.core3.prev_status == Shared)){
					currentStats.core2.new_status = Shared;
					}
				else {
					currentStats.core2.new_status = Exclusive;
				}
			}
		}
		else if (currentStats.core2.curr_signal == P_WR){
			currentStats.core2.new_status = Modified; //from any status to modified
		}
		else if (currentStats.core2.curr_signal == B_RD){
			if ((currentStats.core2.prev_status == Modified) || (currentStats.core2.prev_status == Exclusive) || (currentStats.core2.prev_status == Shared)){
				currentStats.core2.new_status = Shared;
			}
			else if ((currentStats.core2.prev_status == Invalid) || (currentStats.core2.prev_status == Uninit)){
				currentStats.core2.new_status = currentStats.core2.prev_status;
			}
		}
		else if (currentStats.core2.curr_signal == B_WR){
			if ((currentStats.core2.prev_status == Modified) || (currentStats.core2.prev_status == Exclusive) || (currentStats.core2.prev_status == Shared)){
				currentStats.core2.new_status = Invalid;
			}
			else if ((currentStats.core2.prev_status == Invalid) || (currentStats.core2.prev_status == Uninit)){
				currentStats.core2.new_status = currentStats.core2.prev_status;
			}
		}
		return currentStats.core2.new_status;
	}	
		
		
		
		//MESI for Cache3
	else if (processor_num == 3){	
		if (currentStats.core3.curr_signal == P_RD){
			if ((currentStats.core3.prev_status == Modified) || (currentStats.core3.prev_status == Exclusive) || (currentStats.core3.prev_status == Shared)){
				currentStats.core3.new_status = currentStats.core3.prev_status;
			}
			else if ((currentStats.core3.prev_status == Invalid) || (currentStats.core3.prev_status == Uninit)){
				if ((currentStats.core1.prev_status == Modified) || (currentStats.core1.prev_status == Exclusive) || (currentStats.core1.prev_status == Shared)||
					(currentStats.core2.prev_status == Modified) || (currentStats.core2.prev_status == Exclusive) || (currentStats.core2.prev_status == Shared)||
					(currentStats.core0.prev_status == Modified) || (currentStats.core0.prev_status == Exclusive) || (currentStats.core0.prev_status == Shared)){
					currentStats.core3.new_status = Shared;
					}
				else {
					currentStats.core3.new_status = Exclusive;
				}
			}
		}
		else if (currentStats.core3.curr_signal == P_WR){
			currentStats.core3.new_status = Modified; //from any status to modified
		}
		else if (currentStats.core3.curr_signal == B_RD){
			if ((currentStats.core3.prev_status == Modified) || (currentStats.core3.prev_status == Exclusive) || (currentStats.core3.prev_status == Shared)){
				currentStats.core3.new_status = Shared;
			}
			else if ((currentStats.core3.prev_status == Invalid) || (currentStats.core3.prev_status == Uninit)){
				currentStats.core3.new_status = currentStats.core3.prev_status;
			}
		}
		else if (currentStats.core3.curr_signal == B_WR){
			if ((currentStats.core3.prev_status == Modified) || (currentStats.core3.prev_status == Exclusive) || (currentStats.core3.prev_status == Shared)){
				currentStats.core3.new_status = Invalid;
			}
			else if ((currentStats.core3.prev_status == Invalid) || (currentStats.core3.prev_status == Uninit)){
				currentStats.core3.new_status = currentStats.core3.prev_status;
			}
		}
		return currentStats.core3.new_status;
	}
}