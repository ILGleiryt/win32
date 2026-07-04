/* 
*  Created 04.07.2026 // dd mm yyyy
*  high-performancfe timer for windows platform using WIN API
* 
* using:
*
* timer_init();
* while(1)
* {
*	timer_update();
*	if needed: timer_get_totaltime();
* }
*/

#include "Timer.h"

static LARGE_INTEGER g_frequency;
static LARGE_INTEGER g_startTime;
static LARGE_INTEGER g_currentTime;
static LARGE_INTEGER g_previousTime;
static double g_deltaTime = 0.0;
static double g_totalTime = 0.0;

void timer_init()
{
	if (!QueryPerformanceFrequency(&g_frequency))
	{
		g_frequency.QuadPart = 10000000;
	}

	QueryPerformanceCounter(&g_startTime);
	g_currentTime = g_startTime;
	g_previousTime = g_startTime;
}

void timer_update()
{
	g_previousTime = g_currentTime;
	QueryPerformanceCounter(&g_currentTime);
	LONGLONG deltaTicks = g_currentTime.QuadPart - g_previousTime.QuadPart;
	g_deltaTime = (double)deltaTicks / (double)g_frequency.QuadPart;
	g_totalTime += g_deltaTime;
}

double timer_get_delta()
{
	return g_deltaTime;
}

double timer_get_totaltime()
{
	return g_totalTime;
}

double timer_get_frequency()
{
	return (double)g_frequency.QuadPart;
}