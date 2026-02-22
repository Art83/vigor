#ifndef VIGOR_H
#define VIGOR_H
#define SIZE 256
#define MAX_PROC 1024


typedef struct {
	int pid;
	char comm[SIZE];
	char state;
	unsigned long utime;
	unsigned long stime;
	double cpu_usage;
	int is_stale;
} proc_stats_t;

int parse_proc_stat(int pid, proc_stats_t *stats);
int collect_stats(proc_stats_t *stats_array, int max_limit);
int check_stale_libs(int pid);

#endif
