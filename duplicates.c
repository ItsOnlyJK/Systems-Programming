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
        scan_directory(argv[argcount - 1]);
            if(strcmp(argv[1], "-a") == 0) {
            }
            if(strcmp(argv[1], "-A") == 0) {
            }
            if(strcmp(argv[1], "-f") == 0) {
                char *hash = strSHA2(argv[2]);
                for (int i = 0; i < nfiles; i++) {
                    if (strcmp(hash, files[i].hash) == 0) {
                        printf("Match %s\n", files[i].name);
                    } else if (i == nfiles - 1) {
                        printf("No Duplicates\n");
                        exit(EXIT_SUCCESS);
                    }
                }
                exit(EXIT_SUCCESS);
            }
        }
        if(argcount < 2) {
            fprintf(stderr, "Usage: %s value1 [value2 ...]\n", argv[0]);
            exit(EXIT_FAILURE);	
        }		// Exit indicating failure
    }
    printf("Files Count: %i\n", total_files_count);
    printf("Bytes Count: %i\n", total_bytes_count);
    printf("Unique Files Count: %i\n", unique_count);
    printf("Unique Bytes Count: %i\n", unique_bytes_count);
    return EXIT_SUCCESS;
}
