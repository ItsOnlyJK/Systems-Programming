//  CITS2002 Project 2 2021
//  Name(s):             William Brown , Jake Scott-Hill
//  Student number(s):   23114092 , 23124504

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

// Check the number of command-line arguments
int main(int argcount, char *argv[])
{
    // If no command line options were given
    if (argcount == 2 && strcmp(argv[1], "-A") != 0) {
         scan_directories(argv[1]);
         printf("Files Count: %i\n", total_files_count);
         printf("Bytes Count: %i\n", total_bytes_count);
         printf("Unique Files Count: %i\n", unique_count);
         printf("Unique Bytes Count: %i\n", unique_bytes_count);
    }
    // we are cringe and did the basic version :(
    if(strcmp(argv[1], "-A") == 0) {
    	exit(EXIT_FAILURE);
    }
    else {
        
        // For command line optioons - Assumption that the command line option(s) will be first followed by directory
        if (argcount > 2) { 
            
            // Revealing hidden files using the -a command line option
            if(strcmp(argv[1], "-a") == 0 && argcount == 3) {
            	hidden_file_state = false;
                // Refer to directories.c where hidden_file_state == false
            	scan_directories(argv[argcount - 1]);
                printf("Files Count: %i\n", total_files_count);
                printf("Bytes Count: %i\n", total_bytes_count);
                printf("Unique Files Count: %i\n", unique_count);
                printf("Unique Bytes Count: %i\n", unique_bytes_count);
            } else if (strcmp(argv[1], "-a") == 0) { // If command-line inputs were incorrect for -a
                fprintf(stderr, "Usage: %s -l <directory>\n", argv[0]);
                exit(EXIT_FAILURE);	
            }
            
            // Lists the pathnames of matching files using -f
            if(strcmp(argv[1], "-f") == 0 && argcount == 4) { 
                scan_directories(argv[argcount - 1]);
                char *hash = strSHA2(argv[2]); // Grab hash of given file
                bool check = false;
                for (int i = 0; i < nfiles; ++i) { // Loop to check for matching hash
                    if (strcmp(hash, files[i].hash) == 0) {
                        printf("Match %s\n", files[i].name);
                        check = true;
                    } else if (i == nfiles - 1 && check == false) { // If no matches
                        exit(EXIT_FAILURE);
                    }
                }
                exit(EXIT_SUCCESS);
            } else if (strcmp(argv[1], "-f") == 0) { // If command-line inputs were incorrect for -f
                fprintf(stderr, "Usage: %s -h <file> <directory>\n", argv[0]);
                exit(EXIT_FAILURE);	
            }
            
            // Lists the pathnames of the files with matching hashes using -h
            if (strcmp(argv[1], "-h") == 0 && argcount == 4) {
                scan_directories(argv[argcount - 1]);
                bool check = false;
                for (int i = 0; i < nfiles; ++i) {
                    if (strcmp(argv[2], files[i].hash) == 0) {
                        printf("Match %s\n", files[i].name);
                        check = true;
                    } else if (i == nfiles - 1 && check == false) {
                        exit(EXIT_FAILURE);
                    }
                }
            } else if (strcmp(argv[1], "-h") == 0) { // If command-line inputs were incorrect for -h
                fprintf(stderr, "Usage: %s -h <hash> <directory>\n", argv[0]);
                exit(EXIT_FAILURE);	
            }
            
            // Lists the pathnames of all duplicate files using -l
            if(strcmp(argv[1], "-l") == 0 && argcount == 3) {
            	scan_directories(argv[argcount - 1]);
            	char *repeated_hash[1000];
            	int array_count = 0;
            	bool check = false;
            	for (int i = 0; i < nfiles; i++) {
            	    if (files[i].dup == true) {
            	        check = false;
            	        for (int x = 0; x < array_count; x++) {
            	            if (strcmp(files[i].hash, repeated_hash[x]) == 0) {
            	                check = true;
            	            }
            	        }
            	        if (check == false) {
            	            for (int j = 0; j < nfiles; j++) {
            	                if(strcmp(files[i].hash, files[j].hash) == 0) {
            	                    printf("%s\t", files[j].name);
            	                }
            	            }
            	            repeated_hash[array_count] = files[i].hash;
            	            array_count++;
            	            printf("\n");
            	        }
            	    }
            	}
            } else if (strcmp(argv[1], "-l") == 0) { // If command-line inputs were incorrect for -l
                fprintf(stderr, "Usage: %s -l <directory>\n", argv[0]);
                exit(EXIT_FAILURE);	
            }
            
            // Tests if given directory contains duplicate files using -q
            if(strcmp(argv[1], "-q") == 0 && argcount == 3) {
            	scan_directories(argv[argcount - 1]);
            	for (int i = 0; i < nfiles; i++) {
            	    if (files[i].dup == true) {
            	    	exit(EXIT_FAILURE);
            	    }
            	}
            	exit(EXIT_SUCCESS);
            } else if (strcmp(argv[1], "-q") == 0) { // If command-line inputs were incorrect for -q
                fprintf(stderr, "Usage: %s -q <directory>\n", argv[0]);
                exit(EXIT_FAILURE);	
        	}
        }
        
        // Invalid number of arguments error
        if(argcount < 2) { 
            fprintf(stderr, "Usage: %s <arg> <directory>\n", argv[0]);
            exit(EXIT_FAILURE);	
        }	
    }
    return EXIT_SUCCESS;
}
