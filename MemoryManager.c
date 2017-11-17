//MemoryManager simulates the way that an operating system might handle a process' memory heap. 
//It can allocate and free memory. It cannot currently support defragmentation.

//Lisa Chen and Briar Harrison
//MHC CS 322 - Operating Systems
//2017

#include <unistd.h>
#include <stdio.h>

//main is just for testing purposes
int main (int argc, char **argv){
	printf("%d\n", getpagesize());

	return 0;
}
