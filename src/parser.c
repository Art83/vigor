#include<stdio.h>
#include<string.h>
#include "vigor.h"


int parse_proc_stat(int pid, proc_stats_t *stats){
	char path[40], buffer[1024];
	sprintf(path, "/proc/%d/stat", pid);
	FILE *f = fopen(path, "r");
	if(!f) return -1;

	if (fgets(buffer, sizeof(buffer), f)){
		char *last_paren = strrchr(buffer, ')');
		if (last_paren){
			stats->pid = pid;
			stats->state = *(last_paren+2);
		sscanf(last_paren + 4, "%*d %*d %*d %*d %*d %*d %*u %*u %*u %*u %lu %lu", &stats->utime, &stats->stime);
		}
	}
	fclose(f);
	return 0;
}
