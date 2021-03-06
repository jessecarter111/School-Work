#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xis.h"
#include "xmem.h"

/* title: init memory with a specific size
 * param: size of physical memory (between 0 and 65536)
 * function: allocates and iniializes physical memory of specified size
 * returns: 1 if successful, 0 if not
 */

//Pointer to use for malloc, char used because we want to allocate memory in terms of bytes
static char* ptr;

extern int xmem_init(int size) {
  if (size >= 0 && size <= 65536){
    //Think of Pointers as Arrays
    ptr = malloc(size * sizeof(char));
    if (ptr != NULL){
      return 1;
    }
  }
  return 0;
}


/* title: store a word (2 bytes) of data at specified location in memory
 * param: pointer to data, location in memory
 * function: writes the two bytes at specific address in memory.  Address must
 *           be in logical range (0 ... 65536), and if no virtual mapping
 *           is used must be less than size of physical memory.
 *           this function aborts if an error occurs.
 * returns: void
 */
extern void xmem_store( unsigned char data[2], unsigned short addr ) {
  if (addr < 0 || addr > 65536){
    printf("Error: Memory Address out of range 0-65536");
    return;
  }
  else {
    ptr[addr] = data[0];
    ptr[addr+1] = data[1];
  }
}


/* title: load a word (2 bytes) of data from specified location in memory
 * param: location in memory, pointer to where data should be stored 
 * function: loads the 2 bytes stored at the specified address into the 
             location pointed to by data.  Address must be in logical 
             range (0 ... 65536), and if no virtual mapping is used must 
             be less than size of physical memory.
 * returns: void
 */
extern void xmem_load( unsigned short addr, unsigned char data[2] ) {
  if (addr < 0 || addr > 65536){
    printf("Error: Memory Address out of range 0-65536");
    return;
  }
  else{
    data[0] = ptr[addr];
    data[1] = ptr[addr+1];    
  }
}




