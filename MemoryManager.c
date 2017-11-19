//Lisa Chen and Briar Harrison
//MHC CS 322 - Operating Systems
//2017

//MemoryManager simulates the way that an operating system might handle a process' memory heap. 
//It can allocate and free memory. It cannot currently support defragmentation.

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "mem.h"
#include <fcntl.h>

//Mem_Init 
void *Mem_Init (int sizeOfRegion){
	int numPages = ceil((double) sizeOfRegion / (double) getpagesize());
	int requestSize = numPages * getpagesize();

	// open the /dev/zero device
	int fd = open("/dev/zero", O_RDWR);

	// requestSize (in bytes) needs to be evenly divisible by the page size
	void *ptr = mmap(NULL, requestSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	close(fd);

	return ptr;
}

//main is just for testing purposes
int main (int argc, char **argv){
	printf("%p\n", Mem_Init(2000));

	return 0;
}
