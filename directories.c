#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <sys/param.h> // for MAXPATHLEN

#include "duplicates.h"

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void scan_directories(char *dirname) { //ty daddy chris
    DIR *dirp = opendir(dirname);
    
    if (dirp == NULL) {
    	perror(dirname);
    	exit(EXIT_FAILURE);
    }
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
    	char path[MAXPATHLEN];
    	
    	sprintf(path, "%s/%s", dirname, dp->d_name);
    	
    	struct stat stat_info;
    	if(stat(path, &stat_info) != 0) {
    	    perror(path);
    	    exit(EXIT_FAILURE);
    	}
    	if (S_ISREG(stat_info.st_mode) == 1) {
    	    if (dp->d_name[0] == '.') {
    	        if (hidden_file_state == false) {
    	            stats(path);
    	        }
            } else {
                stats(path);
            }
    	} else {
    	    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
                continue;
            } else {
                scan_directories(path);
            }
    	}
    }
    closedir(dirp);
}
