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

int main(int argcount, char *argv[])
{
    // Check the number of command-line arguments
    if (argcount == 2) {
         //If no command line options were given
         scan_directories(argv[1]);
         printf("Files Count: %i\n", total_files_count);
         printf("Bytes Count: %i\n", total_bytes_count);
         printf("Unique Files Count: %i\n", unique_count);
         printf("Unique Bytes Count: %i\n", unique_bytes_count);
    }
    else {
        if (argcount > 2) { //For command line optioons - Assumption that the command line options will be first 
            if(strcmp(argv[1], "-a") == 0) {
                //Revealing hidden files
            	hidden_file_state = false;
            	scan_directories(argv[argcount - 1]);
            }
            
            if(strcmp(argv[1], "-A") == 0) {
                //we are cringe and did the basic version :(
            	exit(EXIT_FAILURE);
            }
            
            if(strcmp(argv[1], "-f") == 0 && argcount == 4) { //-f command option can only take 4 arguemnts 
                scan_directories(argv[argcount - 1]);
                char *hash = strSHA2(argv[2]); //grab hash of given file
                bool check = false;
                for (int i = 0; i < nfiles; ++i) { // loop to check 
                    if (strcmp(hash, files[i].hash) == 0) {
                        printf("Match %s\n", files[i].name);
                        check = true;
                    } else if (i == nfiles - 1 && check == false) {
                        exit(EXIT_FAILURE);
                    }
                }
                exit(EXIT_SUCCESS);
            } else if (strcmp(argv[1], "-f") == 0) {
                fprintf(stderr, "Usage: %s value1 [value2 ...]\n", argv[0]);
                exit(EXIT_FAILURE);	
            }
            
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
            } else if (strcmp(argv[1], "-h") == 0) {
                fprintf(stderr, "Usage: %s -h <hash>\n", argv[0]);
                exit(EXIT_FAILURE);	
            }
            if(strcmp(argv[1], "-l") == 0) {
            	scan_directories(argv[argcount - 1]);
            	//JAKE MY KING CAN YOU PLEASE LOOK INTO POSSIBLY USING MALLOC OR SOME OTHER WAY TO DYNAMICALLY ALLOCATE MEMORY FOR THIS ARRAY
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
            }
            if(strcmp(argv[1], "-q") == 0) {
            	scan_directories(argv[argcount - 1]);
            	for (int i = 0; i < nfiles; i++) {
            	    if (files[i].dup == true) {
            	    	exit(EXIT_FAILURE);
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
    return EXIT_SUCCESS;
}
