/**
* @file
* @brief This is where the elevator chooses which state to go to next
* based on its current state and the next happening.
*/
#ifndef __INCLUDE_STATEMACHINE_H__
#define __INCLUDE_STATEMACHINE_H__


/**
 * @brief Open door
 */
void open_door();

/**
 * @brief Close door
 */
void close_door();

/**
 * @brief Stop the elevator
 */
void stop_elev();


/**
 * @brief When the stop button is pushed the elevator stops immediately,
 * deletes all orders and ignores new ones. If it is in a floor the door opens.
 *
 * @param[in] start When the timer is started.
 */
void emergency_stop();


/**
 * @brief Algorithm for choosing direction when the elevator 
 * is stopped between two floors. 
 *
 */
void emergency_between();
/**
 * @brief Different states that is used in the statemachine.
 */
typedef enum /*state_machine_type*/ {
	MOVING,
	INITIALIZED,
	IDLE,
	STOPPED,
	EMERGENCY,
	FAILURE
} state_machine_type_t;

/**
 * @brief OStatemachine uses the current state and eventual events
 * to decide the next state of the elevator.
 */
state_machine_type_t state_machine(state_machine_type_t current_state);

#endif // #ifndef __INCLUDE_STATEMACHINE_H__