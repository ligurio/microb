#include <string.h>
#include <stdio.h>

void malloc_perf() {

	void *p = NULL;
	int size = 1 * 1024 * 1024;

	p = malloc(size);
	if (!p)
		perror("malloc error");
	free(p);
}

size_t b_malloc_sparse()
{
	void *p[10000];
	size_t i;
	for (i=0; i<sizeof p/sizeof *p; i++) {
		p[i] = malloc(4000);
		memset(p[i], 0, 4000);
	}
	for (i=0; i<sizeof p/sizeof *p; i++)
		if (i%150) free(p[i]);
	return 0;
}

size_t b_malloc_bubble()
{
	void *p[10000];
	size_t i;
	for (i=0; i<sizeof p/sizeof *p; i++) {
		p[i] = malloc(4000);
		memset(p[i], 0, 4000);
	}
	for (i=0; i<sizeof p/sizeof *p-1; i++)
		free(p[i]);
	return 0;
}

size_t b_malloc_tiny1()
{
	void *p[10000];
	size_t i;
	for (i=0; i<sizeof p/sizeof *p; i++) {
		p[i] = malloc((i%4+1)*16);
	}
	for (i=0; i<sizeof p/sizeof *p; i++) {
		free(p[i]);
	}
	return 0;
}

size_t b_malloc_tiny2()
{
	void *p[10000];
	size_t i;
	for (i=0; i<sizeof p/sizeof *p; i++) {
		p[i] = malloc((i%4+1)*16);
	}
	for (i=1; i; i = (i+57)%(sizeof p/sizeof *p))
		free(p[i]);
	return 0;
}

size_t b_malloc_big1()
{
	void *p[2000];
	size_t i;
	for (i=0; i<sizeof p/sizeof *p; i++) {
		p[i] = malloc((i%4+1)*16384);
	}
	for (i=0; i<sizeof p/sizeof *p; i++) {
		free(p[i]);
	}
	return 0;
}

size_t b_malloc_big2()
{
	void *p[2000];
	size_t i;
	for (i=0; i<sizeof p/sizeof *p; i++) {
		p[i] = malloc((i%4+1)*16384);
	}
	for (i=1; i; i = (i+57)%(sizeof p/sizeof *p))
		free(p[i]);
	return 0;
}
