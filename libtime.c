/*	------------------------------------------------
	
	libtime.c - cross-platform timecounters

	(c) Ilya Ponetayev, 2010
	Published under GNU GPL v2 License

  --------------------------------------------------- */ 
  
#include <stdio.h>
#ifndef __GNUC__
	#include <windows.h>
#else
	#include <sys/time.h>
	#define SYSFREQ 1E6
#endif


/*
	Getting current state of the system counter
*/

long long int getcount(void) {
#ifdef __GNUC__
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * SYSFREQ + t.tv_usec;
#else
	long long int ticks;
	QueryPerformanceCounter(&ticks);
	return ticks;
#endif
}

/*
	Getting frequency of the system counter
*/

long long int getfreq(void) {
#ifdef __GNUC__
	return SYSFREQ;
#else
	long long int freq;
	QueryPerformanceFrequency(&freq);
	return freq;
#endif
}

