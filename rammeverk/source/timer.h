/**
*@file
*@brief Timer to use when the door is open
*/
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__
#include <time.h>

/**
*@brief Starts the timer, used when the door opens.
*
*@return Seconds since pre-defined value
*/

time_t start_time();

/**
*@brief Checks if the timer has expired
*
*@param[out] start_time When timer is started
*@param[out] end_time When timer is expired
*
*@return 1 when the timer is expired, 0 otherwise
*/
int timer_expired(time_t start_time);



#endif // #ifndef __INCLUDE_TIMER_H__