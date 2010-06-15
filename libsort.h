/*	------------------------------------------------
	
	libsort.h - Main system header
	
	(c) Ilya Ponetayev, 2010
	Published under BSD License

  --------------------------------------------------- */ 
  
  #ifndef LIBSORT_H
  #define LIBSORT_H
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "libtime.h"
  
  
  /*
		Insertion sorts
  */
  /*	-----------------------------------------------------------------------------

		isort() - Implementation of insertion sort with aggressive usage of memcpy()
		Inefficient, for testing purposes only

	---------------------------------------------------------------------------- */
  void isort(void * arr, size_t count, size_t sizeofelem, int (predicate)(const void*, const void*));
  /*	-----------------------------------------------------------------------------

		pisort() - Implementation of insertion sort with optimized memory usage
		Rather efficient for real work

	---------------------------------------------------------------------------- */
  void pisort(void * arr, size_t count, size_t sizeofelem, int (predicate)(const void*, const void*));
  
  /*
		Merge sorts
  */
  /*	-----------------------------------------------------------------------------

		msort() - Implementation of merge sort, high-level function
		Efficiency tends to gain efficiency of qsort() from stdlib

	---------------------------------------------------------------------------- */
  void msort(void * base, size_t nmb, size_t size, int (*pred)(const void*, const void*));
  
  #endif