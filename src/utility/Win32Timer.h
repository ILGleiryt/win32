/* Created 04.07.2026
*  Firstly we need to call timer_init(), before using get methods we need to use timer_update() to gather information
*  Timer for windows platform
*/

#ifndef WIN32TIMER_H
#define WIN32TIMER_H

#include <windows.h>
// neew to call this before any other function
void timer_init();

// call this function 1 time per frame to calculates delta time
void timer_update();

//return delta time elapsed between two time_update() methods
double timer_get_delta();

// returns total time in seconds from initialithation
double timer_get_totaltime();

// return tick per second for this CPU
double timer_get_frequency();

#endif // WIN32TIMER_H
