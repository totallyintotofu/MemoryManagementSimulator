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

void* head;


//each header should be 16 bytes.
//addresses require 6 bytes -> pad with 0s to make 8 each
//magic number requires 2 bytes -> 0x072D -> pad with 0s to make 8
//size require ? bytes


//Mem_Init 
void *Mem_Init (int sizeOfRegion){
	
	//calculate the request size from the sizeOfRegion, rounding up if needed to fit evenly on some number of pages.
	double numPages = ceil((double) sizeOfRegion / (double) getpagesize());
	int requestSize = numPages * getpagesize();
	printf("The requestSize is %d\n", requestSize);

	// open the /dev/zero device
	int fd = open("/dev/zero", O_RDWR);

	// requestSize (in bytes) needs to be evenly divisible by the page size
	void *ptr = mmap(NULL, requestSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	close(fd);

	head = ptr;

	//set memory header
		//track how large the maximum size is
	int headerSize = 8;

	//set header of current free chunk
	int size = requestSize - headerSize;
	head = &size;

	int next = 0;
	void* nextPtr = head + (headerSize/2);
	nextPtr = &next;

	return ptr;
}

//helper function iterates through the memory until it finds a chunk flagged as free
//i.e., the chunk's header does not contain the magic number 1837.
void* findFree(){
	//for now, max size is one page = 4096
	//int maxSize = getpagesize();
	//4096 = 0b1000000000000 = 0x1000
	int offset = 4;

	void* nextHeader = head;
	while ((*(int*)(nextHeader + offset)) == 1837){
		nextHeader = nextHeader + *(int*)nextHeader + (offset*2);
	}

	return nextHeader;
}

void Mem_Dump(){
	//find the first free chunk
	printf("First free chunk is at %p\n", findFree());
	printf("Size of first free chunk is %d\n", *(int*)head);
	printf("Next free chunk is %d\n", *(int*)(head+4));
	
	//loop until next is 0
}

//main is just for testing purposes
int main (int argc, char **argv){
	//printf("%p\n", Mem_Init(2000));
	Mem_Init(2000);
	Mem_Dump();

	return 0;
}
