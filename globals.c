#include "duplicates.h"

//define the global variables to be used by duplicates
FILES		*files = NULL;
int		nfiles = 0;

int 		total_files_count = 0;
int 	   	total_bytes_count = 0;
int 	   	unique_count = 0;
int 	   	unique_bytes_count = 0;

bool		hidden_file_state = true;
bool		check_hash = true;
