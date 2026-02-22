#include<stdio.h>
#include<string.h>
#include "vigor.h"

int check_stale_libs(int pid) {
    char path[40], line[1024];
    sprintf(path, "/proc/%d/maps", pid);
    
    FILE *f = fopen(path, "r");
    if (!f) return 0; // If we can't open it, assume it's fine

    int stale = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "(deleted)") && strchr(line, '/')) {
    		// 1. Ignore the common "noise" paths
    		if (strstr(line, "/run/user/") || strstr(line, "/dev/shm")) {
        		continue;
		}

    		// 2. Only care if it's a library, a binary, or in /tmp (our test area)
    		if (strstr(line, ".so") || strstr(line, "/bin/") || strstr(line, "/tmp/")) {
        		stale = 1;
        		break;
		}
	}

} 
    fclose(f);
    return stale;
}

int parse_proc_stat(int pid, proc_stats_t *stats) {
    char path[40], buffer[1024];
    sprintf(path, "/proc/%d/stat", pid);
    
    FILE *f = fopen(path, "r");
    if (!f) return -1;

    if (fgets(buffer, sizeof(buffer), f)) {
        // Find the boundaries of the process name
        char *first_paren = strchr(buffer, '(');
        char *last_paren = strrchr(buffer, ')');

        if (first_paren && last_paren && last_paren > first_paren) {
            stats->pid = pid;

            // 1. Extract the name (comm)
            size_t len = last_paren - first_paren - 1;
            // Ensure we don't exceed the 256-byte limit in the struct
            if (len > sizeof(stats->comm) - 1) len = sizeof(stats->comm) - 1;
            
            strncpy(stats->comm, first_paren + 1, len);
            stats->comm[len] = '\0'; // Always null-terminate

            // 2. Extract the state
            // The state is exactly 2 characters after the last ')'
            stats->state = *(last_paren + 2);

            // 3. Extract the ticks
            // We start parsing 4 characters after the last ')' to skip the state and its space
            sscanf(last_paren + 4, "%*d %*d %*d %*d %*d %*d %*u %*u %*u %*u %lu %lu", 
                   &stats->utime, &stats->stime);
        }
    }
    
    fclose(f);
    return 0;
}
