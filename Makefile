duplicates: compare.o duplicates.o globals.o strSHA2.o 
	cc compare.o duplicates.o globals.o strSHA2.o -std=c11 -Wall -Werror -pedantic -o duplicates

compare.o: compare.c duplicates.h
	cc -c compare.c

duplicates.o: duplicates.c duplicates.h
	cc -c duplicates.c

globals.o: globals.c duplicates.h
	cc -c globals.c

strSHA2.o: strSHA2.c
	cc -c strSHA2.c

clean:
	rm *.o duplicates