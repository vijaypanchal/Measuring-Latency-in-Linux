// Measuring-Latency.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#ifdef __cplusplus
#include <iostream>
#endif
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <cstdio>
#include <locale.h>


#define USE_CLOCK       CLOCK_REALTIME
/* Other Options to use as clock
CLOCK_REALTIME
CLOCK_REALTIME_COARSE
CLOCK_REALTIME_HR
CLOCK_MONOTONIC
CLOCK_MONOTONIC_RAW
CLOCK_MONOTONIC_COARSE
*/


#define create_clock(VAR,CLOCK_TYPE)    \
struct timespec start_##VAR##CLOCK_TYPE, stop_##VAR##CLOCK_TYPE, diff_##VAR##CLOCK_TYPE;

#define start_clock(VAR,CLOCK_TYPE)             \
clock_getres(CLOCK_TYPE, &start_##VAR##CLOCK_TYPE); clock_gettime(CLOCK_TYPE, &start_##VAR##CLOCK_TYPE);

#define stop_clock(VAR,CLOCK_TYPE)              \
clock_getres(CLOCK_TYPE, &stop_##VAR##CLOCK_TYPE);  clock_gettime(CLOCK_TYPE, &stop_##VAR##CLOCK_TYPE);

#define taken_clock(VAR,CLOCK_TYPE)             \
do { \
        clock_getres(CLOCK_TYPE, &diff_##VAR##CLOCK_TYPE);\
        diff_##VAR##CLOCK_TYPE.tv_sec = stop_##VAR##CLOCK_TYPE.tv_sec - start_##VAR##CLOCK_TYPE.tv_sec; \
        diff_##VAR##CLOCK_TYPE.tv_nsec = stop_##VAR##CLOCK_TYPE.tv_nsec - start_##VAR##CLOCK_TYPE.tv_nsec; \
} while (0);

#ifdef __cplusplus
#define print_clock(VAR,CLOCK_TYPE)             \
	std::cout << "Started Time at " << #VAR << " is sec " << start_##VAR##CLOCK_TYPE.tv_sec << " and nsec " << start_##VAR##CLOCK_TYPE.tv_nsec << std::endl;\
	std::cout << "Stopped Time at " << #VAR << " is sec " << stop_##VAR##CLOCK_TYPE.tv_sec << " and nsec " << stop_##VAR##CLOCK_TYPE.tv_nsec << std::endl;\
	std::cout << "Total Time By " << #VAR << " is sec " << diff_##VAR##CLOCK_TYPE.tv_sec << " and nsec " << diff_##VAR##CLOCK_TYPE.tv_nsec << std::endl;

#else
#define print_clock(VAR,CLOCK_TYPE)             \
	printf("Start Time at %15s is sec %15ld and nsec %15ld \n",#VAR, start_##VAR##CLOCK_TYPE.tv_sec, start_##VAR##CLOCK_TYPE.tv_nsec); \
	printf("Stop Time at %15s is sec %15ld and nsec %15ld \n",#VAR, stop_##VAR##CLOCK_TYPE.tv_sec, stop_##VAR##CLOCK_TYPE.tv_nsec); \
	printf("Total Time By %15s is sec %15ld and nsec %15ld \n",#VAR, diff_##VAR##CLOCK_TYPE.tv_sec, diff_##VAR##CLOCK_TYPE.tv_nsec);
#endif


