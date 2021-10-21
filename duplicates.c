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

//  Compile with:  cc -std=c11 -Wall -Werror -o square square.c

void scan_directory (char *dirname) { //ty daddy chris
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
    	    stats(path);
    	} else {
    	    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
    	        continue;
    	    } else {
    	        scan_directory(path);
    	    }
    	}
    }
    printf("Files Count: %i\n", total_files_count);
    printf("Bytes Count: %i\n", total_bytes_count);
    printf("Unique Files Count: %i\n", unique_count);
    printf("Unique Bytes Count: %i\n", unique_bytes_count);
    closedir(dirp);
}

int main(int argcount, char *argv[])
{
    // Check the number of command-line arguments
    if (argcount == 2) {
            scan_directory(argv[1]);
    }
    else {
        if (argcount > 2) {
            if(strcmp(argv[1], '-f') {
                   
            }
        }
        if(argcount < 2) {
            fprintf(stderr, "Usage: %s value1 [value2 ...]\n", argv[0]);
            exit(EXIT_FAILURE);			// Exit indicating failure
    }
    return EXIT_SUCCESS;
}
