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
    	    char *hash = convert_SHA2(path);
    	    printf("%s: %s\n", path, hash);
    	} else {
    	    //deal with directories over here 
    	}
    	//convert SHA2
    	//using structs to identify files, then compare after conversion
    	
    }
    closedir(dirp);
}

int main(int argcount, char *argv[])
{
    // Check the number of command-line arguments
    if(argcount < 2) {
        fprintf(stderr, "Usage: %s value1 [value2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);			// Exit indicating failure
    }
    else {
        scan_directory(argv[1]);
    }
    return EXIT_SUCCESS;
}