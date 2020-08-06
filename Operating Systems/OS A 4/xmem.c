#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "xis.h"
#include "xmem.h"
#include "block.h"

#define LAST8(X) (X & 0x00ff) 
#define FIRST8(X) ((X >> 8) & 0x00ff)

static unsigned char *memory;
static int phys_size;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

extern int xmem_init( int size ) {
  if( size <= XIS_MEM_SIZE ) {
    phys_size = size;
    memory = calloc( 1, size );
    return memory != NULL;
  }
  return 0;
}

void swapFrames(unsigned short location){
  //Only swapping pages in/out of first frame
  //Frames 0 and 1 store the pagetable so always use frame 2
  unsigned short previousFrame = pageTableLookup(2); 
  //Load the previous frame into logical mem
  block_store(memory + 512, previousFrame);

  if(block_load(location, memory + 512)){
    //load succesfull, nothing to do
  } 
  else {
    //Block not found, so need to allocate something to the 
    //block and repeat
  	unsigned char emptyMemory[256] = {0};
    block_store(emptyMemory, location);
    block_load(location, memory + 512);
  }
}

unsigned short pageTableLookup(unsigned char frameAddress){
  //Iterate over the page table entries
  //Page table is 512 bytes, each entry is 2 bytes 
  //8 for page#, 8 for frame#
  int temp = 0;
  while (temp < 512){
    if(memory[temp + 1] != 0){ //check that something is stored at that frame#
      if(frameAddress == memory[temp + 1]){ //check if the frame number == frameAddr
        memory[temp + 1] = 0; //If yes set it to 0 as we are swapping it out
        return memory[temp]; //return the page#
      }
    }
    temp += 2;
  }
  return 0;
}
 
unsigned short updatePage(unsigned short addr, unsigned short location, unsigned short fn){
  //Page exists in page table
  if(fn == 0){
    //Block doesn't exist on a frame
    swapFrames(location/2);
    memory[location + 1] = 2;
    return LAST8(addr) + 512;
    } 
  else {
    //Block exists on frame
    return LAST8(addr) + 512;
  }
}

unsigned short addNewPage(unsigned short addr, unsigned short location){
  swapFrames(location); //replace the first frame with new data
  memory[location] = location/2;
  memory[location + 1] = 2; //replace frame number of the entry with the new frame number
  return LAST8(addr) + 512; //Return it's new address (First frame + OFFSET into it)
}

unsigned short getAddr(unsigned short addr){
    pthread_mutex_lock( &lock );
    unsigned short physicalAddress;
    unsigned short location = FIRST8(addr)*2; //Multiply the first 8 bits to get page#

    if(memory[location] != location/2){ //If the location in pagetable != location passed in
    	physicalAddress = addNewPage(addr, location); //Need to add a new page
    } 
   	else { //Has entry in the table
   		physicalAddress = updatePage(addr, location, memory[location + 1]); //Update the corresponding entry
    }
    pthread_mutex_unlock( &lock );

    return physicalAddress;
}

extern void xmem_store( unsigned char data[2], unsigned short addr ) {
  if( memory && ( addr <= 65536) ) {
    unsigned short temp= getAddr(addr);
    memcpy( memory + temp, data, 1);

    temp = getAddr(addr + 1);
    memcpy( memory + temp, data + 1, 1);
  } else {
    printf( "Memory store error at %d\n", addr );
    exit( 1 );
  }
}

extern void xmem_load( unsigned short addr, unsigned char data[2] ) {
  if( memory && ( addr <= 65536) ) {
    unsigned short temp = getAddr(addr);
    memcpy( data, memory + temp, 1 );

    temp = getAddr(addr+1);
    memcpy( data + 1, memory + temp, 1 );
  } else {
    printf( "Memory load error at %d\n", addr );
    exit( 1 );
  }
}