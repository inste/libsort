/*	------------------------------------------------
	
	libtime.h - cross-platform timecounters
	
	(c) Ilya Ponetayev, 2010
	Published under BSD License

  --------------------------------------------------- */ 

#ifndef LIBTIME_H
#define LIBTIME_H

/*
	Getting current state of the system counter
*/

long long int getcount(void);

/*
	Getting frequency of the system counter
*/
long long int getfreq(void);

/*
	All results will be in int64 on all platforms
*/

#endif