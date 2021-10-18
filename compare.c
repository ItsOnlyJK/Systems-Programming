#include <stdio.h>
#include <stdlib.h>
#include "duplicates.h"

//  Compile with:  cc -std=c11 -Wall -Werror -o square square.c

char *convert_SHA2(char filename[]) {
    char *test = strSHA2(filename);
    return(test);
    
    //takes the file hash
    //checks if the hash is the the files array
    //if not in the array, add it, including hash and size
    //if already in the array, add size to total of duplicates and increase file count
    
    
    
    
    
    
}
