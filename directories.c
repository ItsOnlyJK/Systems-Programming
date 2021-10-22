#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "duplicates.h"

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void scan_directories(char *dirname) {
    // Open directory
    DIR *dirp = opendir(dirname);
    
    // Check if the opening of the directory was succesful
    if (dirp == NULL) {
    	perror(dirname);
    	exit(EXIT_FAILURE);
    }
    
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
    	char *path = malloc(sizeof(dp->d_name)); // Intiailising path pointer to store full pathnames
    	
    	sprintf(path, "%s/%s", dirname, dp->d_name);
    	
    	struct stat stat_info;
    	if(stat(path, &stat_info) != 0) {
    	    perror(path);
    	    exit(EXIT_FAILURE);
    	}
    	// Checking if the path is to a directory or file
    	if (S_ISREG(stat_info.st_mode) == 1) {
    	    if (dp->d_name[0] == '.') {
    	        // Removing hidden files from normal execution
    	        if (hidden_file_state == false) {
    	            // Sends file to compare.c and includes hidden files
    	            stats(path);
    	        }
            } else {
                // Sends file to compare.c
                stats(path);
            }
    	} else {
    	    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
                continue;
            } else {
                // For scanning subdirectories
                scan_directories(path);
            }
    	}
    }
    closedir(dirp);
}
