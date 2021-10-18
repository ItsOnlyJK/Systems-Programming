#include  <stdio.h>
#include  <stdbool.h>
#include  <math.h>

// DECLARE GLOBAL PREPROCESSOR CONSTANTS
#define	TEST	200

// DECLARE STRUCTURE
typedef struct {
    char	*hash;
    int	  	size;
    int		count;
} FILES;


// DECLARE GLOBAL FUNCTIONS
extern	char 	   *strSHA2(char *filename);
extern  char	   *convert_SHA2(char filename[]);
extern char* 	   strdup(const char*);

// DECLARE GLOBAL VARIABLES
extern FILES	   *files;
extern int	   nfiles;

