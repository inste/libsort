/*	------------------------------------------------
	
	msort.c - Merge sort
	
	(c) Ilya Ponetayev, 2010
	Published under BSD License

  --------------------------------------------------- */ 
 
 #include "libsort.h"
 
/*	-----------------------------------------------------------------------------

		Implementation of merge sorting, additional functions
		For inside-use only

	---------------------------------------------------------------------------- */

struct inode {
	void * item;
	struct inode * next;
};

/*	-----------------------------------------------------------------------------

		merge() - merging of two linked lists, designed for work without
		recursive calling for efficient stack usage

		Implementation of merge sorting, additional functions
		For inside-use only

	---------------------------------------------------------------------------- */

struct inode * merge(struct inode * l, struct inode * r, int (*pred)(const void*, const void*)) {
	struct inode * res = NULL, * head = NULL;
		
	while ((l != NULL) && (r != NULL)) {
		if ((head == NULL) && (res != NULL))
			head = res;
		if (pred(l->item, r->item) <= 0) {
			if (res == NULL)
				res = l;
			else 
				res = (res->next = l);
			l = l->next;
		} else {
			if (res == NULL)
				res = r;
			else
				res = (res->next = r);
			r = r->next;
		}
	}
	
	while (l != NULL) {
		if ((head == NULL) && (res != NULL))
			head = res;
		if (res == NULL)
			res = l;
		else 
			res = (res->next = l);
		l = l->next;
	}
	
	while (r != NULL) {
		if ((head == NULL) && (res != NULL))
			head = res;
		if (res == NULL)
			res = r;
		else
			res = (res->next = r);
		r = r->next;
	}
	return head;
}

/*	-----------------------------------------------------------------------------

		mergesort() - dividing and sorting linked lists

		Implementation of merge sorting, additional functions
		For inside-use only

	---------------------------------------------------------------------------- */

struct inode * mergesort(struct inode * a, int count, int (*pred)(const void*, const void*)) {
	struct inode *l = NULL, *r = NULL, *t;
	int m = count / 2, i;

	if ((a == NULL) || (a->next == NULL))
		return a;
	
	for (i = 1; i <= m; ++i) {
		t = a->next;
		if (l == NULL) {
			l = a;
			l->next = NULL;
		} else {
			a->next = l;
			l = a;
		}
		a = t;
	}

	for (i = m + 1; i <= count; ++i) {
		t = a->next;
		if (r == NULL) {
			r = a;
			r->next = NULL;
		} else {
			a->next = r;
			r = a;
		}
		a = t;
	}

	return merge(mergesort(l, m, pred), mergesort(r, count - m, pred), pred);
}

/*	-----------------------------------------------------------------------------

		msort() - Implementation of merge sort, high-level function
		Efficiency tends to gain efficiency of qsort() from stdlib

	---------------------------------------------------------------------------- */

void msort(void * base, size_t nmb, size_t size, int (*pred)(const void*, const void*)) {
	struct inode * list = NULL, * t;
	int i;
	void * buffer = malloc(size * nmb);
	
	for(i = 0; i < (int) nmb; ++i) {
		t = malloc(sizeof(struct inode));
		t->item = (char *)base + size * i;
		if (list == NULL) {
			list = t;
			list->next = NULL;
		} else {
			t->next = list;
			list = t;
		}
	}
	
	list = mergesort(list, nmb, pred);
	
	t = list;
	i = 0;
	while (t != NULL) {
		memcpy((char *)buffer + (i++) * size, (char *)t->item, size);
		t = t->next;
	}
	memcpy(base, buffer, size * nmb);
	free(buffer);
	
	while (list != NULL) {
		t = list->next;
		free(list);
		list = t;
	}
}
