// Measuring-Latency.cpp : Defines the entry point for the application.
//


#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "Measuring-Latency.h"
#include <cstdio>
#include <locale.h>

using namespace std;
#ifndef USE_CLOCK
#define USE_CLOCK	CLOCK_REALTIME 
#endif

/* Other Options to use as clock
CLOCK_REALTIME   
CLOCK_REALTIME_COARSE  
CLOCK_REALTIME_HR
CLOCK_MONOTONIC
CLOCK_MONOTONIC_RAW
CLOCK_MONOTONIC_COARSE
*/


#define TEST

create_clock(TEST, USE_CLOCK)

int main()
{
	start_clock(TEST, USE_CLOCK);
	sleep(1);
	stop_clock(TEST, USE_CLOCK);

	taken_clock(TEST, USE_CLOCK);

	print_clock(TEST, USE_CLOCK);

	return 0;
}
