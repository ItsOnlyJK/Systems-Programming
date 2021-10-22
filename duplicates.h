#include  <stdio.h>
#include  <stdbool.h>
#include  <math.h>

// DECLARE GLOBAL PREPROCESSOR CONSTANTS
#define	TEST	200

// DECLARE STRUCTURE
typedef struct {
    char	*hash;
    char	*name;
    int	  	size;
    bool	dup;
} FILES;

// DECLARE GLOBAL FUNCTIONS
extern	char 	   *strSHA2(char *filename);
extern  void	   stats(char filename[]);
extern  char* 	   strdup(const char*);
extern  void       scan_directories(char *dirname);

// DECLARE GLOBAL VARIABLES
extern FILES	   *files;
extern int	   nfiles;

extern int 	   total_files_count;
extern int 	   total_bytes_count;
extern int 	   unique_count;
extern int 	   unique_bytes_count;

extern bool	   hidden_file_state;
extern bool	   check_hash;