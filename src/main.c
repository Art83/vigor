#include<stdio.h>
#include<ctype.h>
#include<dirent.h>
#include "vigor.h"


int main(){
	DIR *dir;
	dir = opendir("/proc");
	if(!dir){
		perror("Cannot open /proc\n");
		return 1;
	}
	struct dirent *dp;
	int pid;
	proc_stats_t st = {0};
	int num = 0;
	int num_zombies = 0;
	while( (dp = readdir(dir)) != NULL){
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
	}
	printf("Currently detected %d processes: %d zombies\n", num, num_zombies);
	
	return 0;
}
