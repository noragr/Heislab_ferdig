/**
 * @file
 */

#include "statemachine.h"
#include "channels.h"
#include "elev.h"
#include "io.h"
#include "logic.h"
#include "timer.h"

#include <stdio.h>
#include <time.h>


static int current_floor;
static elev_motor_direction_t current_dir;
static int EM_between;

//Open door
void open_door(){
	elev_set_door_open_lamp(1);
}

//Close door
void close_door(){
	elev_set_door_open_lamp(0);
}

//Stop elevator
void stop_elev(){
	elev_set_motor_direction(DIRN_STOP);
}

//Emergency button
void emergency_stop(){
	stop_elev();
	elev_set_stop_lamp(1);
	for (int floor = 0; floor < N_FLOORS; floor++){
		delete_order(floor); //delete all orders
	}
	if (elev_get_floor_sensor_signal() !=-1){ //at a floor
		while(elev_get_stop_signal()){
			open_door();
		}
		elev_set_stop_lamp(0);
		time_t start = start_time();
    	while (!(timer_expired(start))) {
        	open_door();
    	}
    	close_door();
    	}
	else{   // not at a floor
		while (elev_get_stop_signal()){
			;
		}

		elev_set_stop_lamp(0);
	}
}

void emergency_between() {
	if (order_amount()) {
		if (current_dir == DIRN_UP) {
			for (int button = 0; button < 3; button++) {
				if (get_order(current_floor, button)) {
					current_floor++;
					current_dir = DIRN_DOWN;
				}
			}
		}else if (current_dir == DIRN_DOWN) {
			for (int button = 0; button < 3; button++) {
				if (get_order(current_floor, button)) {
					current_floor--;
					current_dir = DIRN_UP;
				}
			}
		}
	}
}


state_machine_type_t state_machine(state_machine_type_t current_state){

	state_machine_type_t next_state = current_state;
	switch (current_state){
		case INITIALIZED:
			EM_between = 0;
		    if (!elev_init()) {
       			printf("Unable to initialize elevator hardware!\n");
       			next_state = INITIALIZED;
       			break;
    		}

			current_floor = initializer();
			current_dir = DIRN_STOP;
			next_state = IDLE; 
			break;

		case MOVING:
			set_order();
			if (EM_between) {	
				emergency_between();
				EM_between = 0;
			}

			// sjekk om den er fremme
			if (check_order_complete(current_dir)) {
				next_state = STOPPED;
				break;
			} else if (no_more_orders_dir(current_dir)) {
				current_dir = -1*current_dir;
				next_state = MOVING;
				break;
			}else{
			
				if(elev_get_stop_signal()){
					next_state = EMERGENCY;
					break;
				}else {
					// Change direction at top and bottom
					if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
	            		elev_set_motor_direction(DIRN_DOWN);
	            		current_dir = DIRN_DOWN;
	            		next_state = MOVING;
	            		break;
	        		} else if (elev_get_floor_sensor_signal() == 0) {
	           			elev_set_motor_direction(DIRN_UP);
	            		current_dir = DIRN_UP;
	            		next_state = MOVING;
	            		break;
	        		}
	        		if (!check_order_complete(current_dir)) {
						current_dir = get_direction(current_dir);
						elev_set_motor_direction(current_dir);  
						if (elev_get_floor_sensor_signal() != -1) { //in a floor
							current_floor = elev_get_floor_sensor_signal();
							printf("%d\n", current_floor);
							if (current_floor != -1) {
								elev_set_floor_indicator(current_floor);
							}
							
							next_state = MOVING;
						}
						else{
							next_state = MOVING;
						}
					}
				}
			}
			break;

		case IDLE:
			elev_set_motor_direction(DIRN_STOP);
			set_order();

			if (elev_get_floor_sensor_signal() != -1) {
				current_floor = elev_get_floor_sensor_signal();
			}

			if(elev_get_stop_signal()){
				next_state = EMERGENCY;
				break;
			}
			if (order_amount() != 0) {
				next_state = MOVING;
				break;
				
			}else {
				next_state = IDLE;
				break;
				
			}

		case STOPPED:  // I en etasje!! 
			stop_elev();
			current_floor = elev_get_floor_sensor_signal();

			if(current_floor != -1){ 
				time_t start = start_time();
				open_door();
    			while (!(timer_expired(start))) {
    				set_order();
    			}
				close_door();
				delete_order(current_floor);
			}
			next_state = IDLE;

			if(elev_get_stop_signal()){
				next_state = EMERGENCY;
			}
			break;

		case EMERGENCY:
			emergency_stop();
			if (elev_get_floor_sensor_signal() == -1) {
				EM_between = 1;
			}
			next_state = IDLE;
			break;

		case FAILURE:
			current_dir = DIRN_STOP;
			elev_set_motor_direction(current_dir);
			next_state = FAILURE;
			break;

		default:
			next_state = INITIALIZED;
			break;
	}
	return next_state;
}