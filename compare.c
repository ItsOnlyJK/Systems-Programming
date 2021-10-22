#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "duplicates.h"

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void update_duplicate(int size) {

    total_files_count++;
    total_bytes_count = total_bytes_count + size;
}

void update_unique(int size) {
    total_files_count++;
    total_bytes_count = total_bytes_count + size;
    unique_count++;
    unique_bytes_count = unique_bytes_count + size;
}

void stats(char filename[]) {
    // check for failure 
    files = realloc(files, (nfiles+1)*sizeof(FILES));
    //obtain hash to compare
    char *hash = strSHA2(filename);
    
    struct stat stat_info;
    stat(filename, &stat_info);
    
    check_hash = true;
    for (int i = 0; i < nfiles; i++) {
        if (strcmp(files[i].hash, hash) == 0) { 
            files[i].dup = true;
            files[nfiles].hash = hash;
            files[nfiles].size = stat_info.st_size;
            files[nfiles].name = strdup(filename);
            files[nfiles].dup = true;
            update_duplicate(stat_info.st_size);
            ++nfiles;
            i = nfiles;
            check_hash = false;
        } 
    }
    if (check_hash == true) {
       files[nfiles].hash = hash;
       files[nfiles].size = stat_info.st_size;
       files[nfiles].name = strdup(filename);
       files[nfiles].dup = false;
       update_unique(stat_info.st_size);
       ++nfiles;
    }
}