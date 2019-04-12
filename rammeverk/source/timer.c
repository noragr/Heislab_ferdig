/**
 * @file
 */

#include "timer.h"
#include "elev.h"
#include <time.h>
#include <stdio.h>


time_t start_time(){
	return time(NULL); 
}

int timer_expired(time_t start_time){
	time_t end_time = time(NULL);
	if (end_time - start_time >= 3){ 
		return 1; 
	}
	return 0;
}