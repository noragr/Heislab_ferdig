/**
 * @file
 */

#include "elev.h"
#include "logic.h"
#include "timer.h"
#include "statemachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	printf("Press obstruction button to exit program\n");
    static state_machine_type_t current_state;
    static elev_motor_direction_t current_dir;


    current_dir = DIRN_STOP;
    elev_set_motor_direction(current_dir);
    current_state = INITIALIZED;

    while (current_state != FAILURE){
        
        //set_order();
        current_state = state_machine(current_state);

        if (elev_get_stop_signal()) {
            current_state = EMERGENCY;
        }
        
        if (current_state == FAILURE){ //blir dette riktig???
            printf("Unable to initialize elevator hardware!\n");
            current_state = INITIALIZED; //hmmm
        }

         if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
            current_dir = DIRN_DOWN;
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
            current_dir = DIRN_UP;
        }

        if (elev_get_obstruction_signal()){ //Obstruction signal
            current_dir = DIRN_STOP;
            elev_set_motor_direction(DIRN_STOP); //Stop elevator
            break; //Exit program
        } 
    }
    return 0;
}


