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
    // Incrementing total files when duplicate is hit
    total_files_count++;
    total_bytes_count = total_bytes_count + size;
}

void update_unique(int size) {
    // Incrementing all values when unique file is hit
    total_files_count++;
    total_bytes_count = total_bytes_count + size;
    unique_count++;
    unique_bytes_count = unique_bytes_count + size;
}

void stats(char filename[]) {
    // Check for failure 
    files = realloc(files, (nfiles+1)*sizeof(FILES));
    
    // Obtain hash to compare
    char *hash = strSHA2(filename);
    
    // Using stat for size of files
    struct stat stat_info;
    stat(filename, &stat_info);
    
    // Using boolean to files arent counted twice
    check_hash = true;
    for (int i = 0; i < nfiles; i++) {
        // Checking if the file is a duplicate
        if (strcmp(files[i].hash, hash) == 0) { 
            // Changes original file to be marked as duplicate for -l command line option
            files[i].dup = true;
            
            // Adds duplicate file marked as a duplicate
            files[nfiles].hash = hash;
            files[nfiles].size = stat_info.st_size;
            files[nfiles].name = strdup(filename);
            files[nfiles].dup = true;
            
            // Updates statistics
            update_duplicate(stat_info.st_size);
            
            // Increments counters
            ++nfiles;
            i = nfiles;
            
            // Sets boolean to false to ensure that the file is not added as unique
            check_hash = false;
        } 
    }
    // Adding unique files
    if (check_hash == true) {
       // Adding unique file
       files[nfiles].hash = hash;
       files[nfiles].size = stat_info.st_size;
       files[nfiles].name = strdup(filename);
       files[nfiles].dup = false;
       
       // Updates statistics
       update_unique(stat_info.st_size);
       ++nfiles;
    }
}