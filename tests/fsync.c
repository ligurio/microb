/*
 *
 *  gcc -static -o fsync_test fsync_test.c -lrt -lm
 *
 */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define B_SIZE    1024
#define B_NUM     10
#define MAX_FILES 100

extern int errno ;

unsigned long long rms(unsigned long long *v, int n)
{
    int i;
    double sum = 0.0;

    for(i = 0; i < n; i++)
        sum += v[i] * v[i];

    return sqrt(sum / n);
}

int main(int argc, char *argv[])
{
    int fdo, i, j;
    ssize_t len;
    struct timespec start, stop;
    unsigned long long min_time, max_time, total_time;
    unsigned long long total = 0;

    char buffer[B_SIZE];
    unsigned long long times[MAX_FILES];

    srand(time(NULL));

    for(i = 0; i < MAX_FILES; i++) {

        for(j = 0; j < B_SIZE; j++) {
            buffer[j] = (char)(rand() & 0xFF);
        }

        char filename[] = "fsync-bench-XXXXXX";

        if ((fdo = mkstemp(filename)) == -1) {
            perror("mkstemp");
            exit(errno);
        }

        clock_gettime(CLOCK_MONOTONIC, &start);

        for (j = 0; j < B_NUM; j++) {
            if (write(fdo, buffer, sizeof(buffer)) == -1) {
                perror("write");
                exit(errno);
            }
        }

        if (fsync(fdo) == -1) {
            perror("fsync");
            exit(errno);
        }

        clock_gettime(CLOCK_MONOTONIC, &stop);

        unsigned long long time_start = start.tv_sec * 1000 + start.tv_nsec / 1000000;
        unsigned long long time_stop  = stop.tv_sec  * 1000 + stop.tv_nsec  / 1000000;
        unsigned long long elapsed = time_stop - time_start; // Time diff in milieconds

        if ( i == 0 )
            max_time = elapsed;
        else
            max_time = fmaxl( max_time, elapsed);

        min_time = fminl( min_time, elapsed);

        total += elapsed;
        times[i] = elapsed;

        if (close(fdo) == -1) {
            perror("close");
            exit(errno);
        }
        unlink(filename);
    }

    unsigned long long av = rms(times, sizeof(times)/sizeof(unsigned long long));

    printf("Done %d rounds, Total time: %llu , Min time: %llu, Max time: %llu, Average: %llu, RMS time: %llu\n",
            MAX_FILES, total, min_time, max_time, total/MAX_FILES, av);

    /* if it survived to here, all worked. */
    exit(0);
}
