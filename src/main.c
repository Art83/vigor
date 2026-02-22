#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include "vigor.h"

int main(){
	int time = 1000000; // <- later an argument in CLI
	proc_stats_t prev[MAX_PROC];
	proc_stats_t curr[MAX_PROC];

	int n_prev = collect_stats(prev, MAX_PROC);
	usleep(time);
	int n_curr = collect_stats(curr, MAX_PROC);
	printf("\033[H\033[J");
	printf("%-8s %-20s %-8s %-10s\n", "PID", "NAME", "STATE", "CPU %");
        printf("----------------------------------------------------------\n");
	for (int i = 0; i < n_curr; i++) {
        	for (int j = 0; j < n_prev; j++) {
            		if (curr[i].pid == prev[j].pid) {
                		unsigned long total_ticks = (curr[i].utime + curr[i].stime) - 
                                            (prev[j].utime + prev[j].stime);
                
                               
                		double usage = (double)total_ticks * 200.0 / sysconf(_SC_CLK_TCK);
				curr[i].cpu_usage = usage;
                
                	if (curr[i].state == 'Z' || curr[i].state == 'D' || curr[i].cpu_usage > 50.0){
				printf("%-8d %-20s [%c] %10.2f%%\n",curr[i].pid, curr[i].comm, curr[i].state, curr[i].cpu_usage);				                }
            }
        }
    }
	
	/*while( (dp = readdir(dir)) != NULL){
		if(isdigit(dp->d_name[0])){
			if(sscanf(dp->d_name,"%d",&pid)==1){
				parse_proc_stat(pid, &st);
				num++;
				if(st.state == 'Z' || st.state == 'D'){
					num_zombies++;
					printf("pid:%d status: %c\n", st.pid, st.state);
				}
			}
		}
	}*/
	
	return 0;
}
