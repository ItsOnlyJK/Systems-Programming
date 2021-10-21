#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "duplicates.h"

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void stats(char filename[]) {
    files = realloc(files, (nfiles+1)*sizeof(FILES));
    // check for failure 

    
    //obtain hash to compare
    char *hash = strSHA2(filename);
    
    struct stat stat_info;
    stat(filename, &stat_info);
    
    bool check = true;
    for (int i = 0; i < nfiles; i++) {
        if (strcmp(files[i].hash, hash) == 0) { 
            files[nfiles].hash = hash;
            files[nfiles].size = stat_info.st_size;
            files[nfiles].name = strdup(filename);
            files[nfiles].dup = true;
            files[i].dup = true;
            //printf("Dup: %s\n", files[nfiles].name);
            
            total_files_count++;
            total_bytes_count = total_bytes_count + stat_info.st_size;
            ++nfiles;
            i = nfiles;
            check = false;
        } 
    }
    if (check == true) {
        files[nfiles].hash = hash;
        files[nfiles].size = stat_info.st_size;
        files[nfiles].name = strdup(filename);
        files[nfiles].dup = false;
        
        total_files_count++;
        total_bytes_count = total_bytes_count + files[nfiles].size;
        unique_count++;
        unique_bytes_count = unique_bytes_count + files[nfiles].size;
        ++nfiles;
    }
}