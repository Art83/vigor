#include<dirent.h>
#include<stdio.h>
#include<ctype.h>
#include "vigor.h"

int collect_stats(proc_stats_t *stats_array, int max_limit) {
    DIR *dir = opendir("/proc");
    if (!dir) {
        perror("Cannot open /proc");
        return -1; // Standard C practice: -1 for error
    }

    struct dirent *dp;
    int pid;
    int count = 0;

    while ((dp = readdir(dir)) != NULL) {
        // Check if we are out of space BEFORE we try to add
        if (count >= max_limit) {
            fprintf(stderr, "Warning: More than %d processes, skipping rest.\n", max_limit);
            break;
        }

        if (isdigit(dp->d_name[0])) {
            if (sscanf(dp->d_name, "%d", &pid) == 1) {
                if (parse_proc_stat(pid, &stats_array[count]) == 0) {
                    count++;
                }
            }
        }
    }
    
    closedir(dir);
    return count; // Return the total number of processes captured
}
