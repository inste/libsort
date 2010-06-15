/*	------------------------------------------------
	
	isort.c - Insertion sorts
	
	(c) Ilya Ponetayev, 2010
	Published under BSD License

  --------------------------------------------------- */ 

#include "libsort.h"

/*	-----------------------------------------------------------------------------

		isort() - Implementation of insertion sort with aggressive usage of memcpy()
		Inefficient, for testing purposes only

	---------------------------------------------------------------------------- */

void isort(void * arr, size_t count, size_t sizeofelem, int (predicate)(const void*, const void*)) {
	void * k = malloc(sizeofelem);
	int i, j;

	for(i = 0; i < (int) count; i++) {
		memcpy(k, (char *)arr + i * sizeofelem, sizeofelem);
		j = i;
		while ((j > 0) && (predicate(((char *)arr + (j - 1) * sizeofelem), k) >= 0)) {
			memcpy((char *)arr + j * sizeofelem, (char *)arr + (j - 1) * sizeofelem, sizeofelem);
			j--;
		}
		memcpy((char *)arr + j * sizeofelem, k, sizeofelem);
	}
	free(k);
}

/*	-----------------------------------------------------------------------------

		pisort() - Implementation of insertion sort with optimized memory usage
		Rather efficient for real work

	---------------------------------------------------------------------------- */

void pisort(void * arr, size_t count, size_t sizeofelem, int (predicate)(const void*, const void*)) {
	void * k;
	char * buffer = malloc(sizeofelem * count);
	void ** list = malloc(sizeof(void *) * count);
	int i, j;

	for(i = 0; i < (int) count; ++i)
		list[i] = (char *)arr + i * sizeofelem;

	for(i = 0; i < (int) count; i++) {
		k = list[j = i];
		while ((j > 0) && (predicate(list[j - 1], k) >= 0)) {
			list[j] = list[j - 1];
			j--;
		}
		list[j] = k;
	}

	for(i = 0; i < (int) count; ++i)
		memcpy(buffer + i * sizeofelem, list[i], sizeofelem);
	memcpy(arr, buffer, sizeofelem * count);
	free(buffer);
	free(list);
}

