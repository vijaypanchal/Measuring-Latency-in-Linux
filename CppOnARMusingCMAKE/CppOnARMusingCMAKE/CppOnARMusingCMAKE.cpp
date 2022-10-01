// CppOnARMusingCMAKE.cpp : Defines the entry point for the application.
//


#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "CppOnARMusingCMAKE.h"
#include <cstdio>
#include <locale.h>

using namespace std;
#if 0
// http://c-faq.com/stdio/commaprint.html
#include <locale.h>
char* commaprint(unsigned long n)
{
	static int comma = '\0';
	static char retbuf[30];
	char* p = &retbuf[sizeof(retbuf) - 1];
	int i = 0;

	if (comma == '\0') {
		struct lconv* lcp = localeconv();
		if (lcp != NULL) {
			if (lcp->thousands_sep != NULL &&
				*lcp->thousands_sep != '\0')
				comma = *lcp->thousands_sep;
			else	comma = ',';
		}
	}

	*p = '\0';

	do {
		if (i % 3 == 0 && i != 0)
			*--p = comma;
		*--p = '0' + n % 10;
		n /= 10;
		i++;
	} while (n != 0);

	return p;
}
#endif

#define USE_CLOCK	CLOCK_REALTIME 
/* Other Options to use as clock
CLOCK_REALTIME   
CLOCK_REALTIME_COARSE  
CLOCK_REALTIME_HR
CLOCK_MONOTONIC
CLOCK_MONOTONIC_RAW
CLOCK_MONOTONIC_COARSE
*/

#define create_clock(VAR,CLOCK_TYPE)	\
struct timespec	start_##VAR##CLOCK_TYPE, stop_##VAR##CLOCK_TYPE, diff_##VAR##CLOCK_TYPE;

#define start_clock(VAR,CLOCK_TYPE)		\
clock_getres(CLOCK_TYPE, &start_##VAR##CLOCK_TYPE); clock_gettime(CLOCK_TYPE, &start_##VAR##CLOCK_TYPE);

#define stop_clock(VAR,CLOCK_TYPE)		\
clock_getres(CLOCK_TYPE, &stop_##VAR##CLOCK_TYPE);  clock_gettime(CLOCK_TYPE, &stop_##VAR##CLOCK_TYPE);

#define taken_clock(VAR,CLOCK_TYPE)		\
do { \
	clock_getres(CLOCK_TYPE, &diff_##VAR##CLOCK_TYPE);\
	diff_##VAR##CLOCK_TYPE.tv_sec = stop_##VAR##CLOCK_TYPE.tv_sec - start_##VAR##CLOCK_TYPE.tv_sec; \
	diff_##VAR##CLOCK_TYPE.tv_nsec = stop_##VAR##CLOCK_TYPE.tv_nsec - start_##VAR##CLOCK_TYPE.tv_nsec; \
} while (0);

#ifdef __cplusplus	
#define print_clock(VAR,CLOCK_TYPE)		\
std::cout << "Started Time at " << #VAR << " is sec " << start_##VAR##CLOCK_TYPE.tv_sec << " and nsec " << start_##VAR##CLOCK_TYPE.tv_nsec << std::endl;\
std::cout << "Stopped Time at " << #VAR << " is sec " << stop_##VAR##CLOCK_TYPE.tv_sec << " and nsec " << stop_##VAR##CLOCK_TYPE.tv_nsec << std::endl;\
std::cout << "Taken Time By " << #VAR << " is sec " << diff_##VAR##CLOCK_TYPE.tv_sec << " and nsec " << diff_##VAR##CLOCK_TYPE.tv_nsec << std::endl; 

#else	
#define print_clock(VAR,CLOCK_TYPE)		\
printf("aken Time By %15s is sec %15ld and nsec %15ld \n",#VAR,diff_##VAR##CLOCK_TYPE.tv_sec, diff_##VAR##CLOCK_TYPE.tv_nsec);
#endif	

#if 0
// macro to call clock_gettime w / different values for CLOCK
#define do_clock(CLOCK) \
do { \
   struct timespec x; \
   clock_getres(CLOCK, &x); \
   printf("%25s\t%15ld", #CLOCK, commaprint(x.tv_nsec)); \
   clock_gettime(CLOCK, &x); \
   printf("\t%15ld", commaprint(x.tv_sec)); \
   printf("\t%15ld\n", /*commaprint*/(x.tv_nsec)); \
} while(0)


int test()
{
	printf("%25s\t%15s\t%15s\t%15s\n", "clock", "res (ns)", "secs", "nsecs");

	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%25s\t%15s\t%15s\t", "gettimeofday", "1,000", commaprint(tv.tv_sec));
	printf("%15s\n", commaprint(tv.tv_usec * 1000));

#if _POSIX_TIMERS > 0   

#ifdef CLOCK_REALTIME
	do_clock(CLOCK_REALTIME);
#endif

#ifdef CLOCK_REALTIME_COARSE
	do_clock(CLOCK_REALTIME_COARSE);
#endif

#ifdef CLOCK_REALTIME_HR
	do_clock(CLOCK_REALTIME_HR);
#endif

#ifdef CLOCK_MONOTONIC
	do_clock(CLOCK_MONOTONIC);
#endif

#ifdef CLOCK_MONOTONIC_RAW
	do_clock(CLOCK_MONOTONIC_RAW);
#endif

#ifdef CLOCK_MONOTONIC_COARSE
	do_clock(CLOCK_MONOTONIC_COARSE);
#endif

#endif

	return 0;
}
#endif

#define TEST

create_clock(TEST, USE_CLOCK)

int main()
{
	start_clock(TEST, USE_CLOCK);
	cout << "Hello CMake." << endl;	
	stop_clock(TEST, USE_CLOCK);

	taken_clock(TEST, USE_CLOCK);

	print_clock(TEST, USE_CLOCK);

	return 0;
}
