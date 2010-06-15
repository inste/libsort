/*	------------------------------------------------
	
	main.c - test program
	
	(c) Ilya Ponetayev, 2010
	Published under BSD License

  --------------------------------------------------- */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libsort.h"
#include "libtime.h"

int pred(const void * p1, const void * p2) {
	return *((int *)p1) - *((int *)p2);
}

int main(void) {
	
	int * a = malloc(1024 * 8 * sizeof(int));
	int * b = malloc(1024 * 8 * sizeof(int));
	int * c = malloc(1024 * 8 * sizeof(int));
	int i;
	long long int start, Sq, Si, Sp, freq;
	
	
	srand(time(NULL));
	
	for(i = 0; i < 1024 * 8; ++i)
		a[i] = rand();
	
	memcpy(b, a, 1024 * 8);
	memcpy(c, a, 1024 * 8);
	
	start = getcount();
	
	qsort(a, 1024 *  8, sizeof(int), pred);
	
	Sq = getcount() - start;
	
	start = getcount();
	isort(b, 1024 * 8, sizeof(int), pred);
	
	Si = getcount() - start;
	
	start = getcount();
	pisort(c, 1024 * 8, sizeof(int), pred);
	
	Sp = getcount() - start;
	
	
	free(a);
	free(b);
	free(c);
	
	freq = getfreq();
	
	printf("\n\t qsort(): %.3f", Sq * 1000 / (float)freq);
	printf("\n\t isort(): %.3f", Si * 1000 / (float)freq);
	printf("\n\t pisort(): %.3f", Sp * 1000 / (float)freq);
	puts("");
	
	return 0;
}
