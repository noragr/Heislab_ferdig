/**
 * @file
 * @brief A set of logic operations on a matrix of the elevator-orders. 
 * Also a matrix that holds all of the matrix orders. 
 */

#ifndef __INCLUDE_LOGIC_H__
#define __INCLUDE_LOGIC_H__
//#include "statemachine.h"
#include "elev.h"


/**
 * @brief Initialize the elevator to a known floor. If it starts between floors, drive up until 
 * it reaches a floor. 
 *
 * @return floor    Returns the floor the elevator is at. 
 */
int initializer();



/**
 * @brief A two-dimensional matrix that holds all of the orders. 1 for order, 0 for no order. 
 * 
 */
int queue[3][N_FLOORS];



/**
 * @brief Takes in floor and button type, and checks in matrix 
 * if there is an order for that combination. 
 *
 * @param[in] floor   The floor we want to check
 * @param[in] button   The type of button we want to check
 *
 * @return 1 if there is an order, else 0. 
 */
int get_order(int floor, elev_button_type_t button);



/**
 * @brief Takes in the current motor-direction and checks with orders set in matrix
 * which direction to drive to next
 *
 * @param[in, out] dir   The current direction of the motor, may change during function 
 * @param[out] floor Sets the current floor if it is not between floors. 
 *
 * @return dir Returns the new direction of the motor. 
 */
elev_motor_direction_t get_direction(elev_motor_direction_t dir);


/**
 * @brief Uses a double-for-loop to check all the floors and all the button-types 
 * and uses elev_get_button_signal() to check if there is made an order for that 
 * floor with that button. It then sets the order in the matrix. 
 */
void set_order();  


/**
 * @brief Takes in floor and deletes all the orders for all the buttons
 * in the matrix at that floor
 *
 * @param[in] floor   The floor at which we want to delete orders. 
 */
void delete_order(int floor);


/**
 * @brief Uses for-loops to check all the floors and all the buttons
 * and summarizes all of the orders- 
 *
 * @return amount   The integer amount of all the orders set in the matrix. 
 */
int order_amount();


/**
 * @brief Takes in the current motor-direction and checks if the next order is 
 * in the current direction 
 *
 * @param[in] current_dir The current direction of the motor. 
 *
 * @return 1 if the next order is in the same direction, -1 if it is not. 
 */
int order_is_in_dir(elev_motor_direction_t current_dir);


 /**
 * @brief Takes in the current motor-direction and checks if the current order is complete
 *
 * @param[in] current_dir The current direction of the motor. 
 *
 * @return 1 if the order is complete, 0 if it is not.  
 */
int check_order_complete(elev_motor_direction_t dir); //return 1 if complete, 0 otherwise


/**
 * @brief Takes in the current motor-direction and checks if there is any more
 * orders in that same direction. 
 *
 * @param[in] current_dir The current direction of the motor. 
 *
 * @return 1 if there are more orders in same direction, 0 else. 
 */
int no_more_orders_dir(elev_motor_direction_t dir);


#endif // #ifndef __INCLUDE _LOGIC_H__