#ifndef VIGOR_H
#define VIGOR_H
#define SIZE 256


typedef struct {
	int pid;
	char comm[SIZE];
	char state;
	unsigned long utime;
	unsigned long stime;
} proc_stats_t;

int parse_proc_stat(int pid, proc_stats_t *stats);

#endif
