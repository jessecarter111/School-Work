#include <stdio.h>
#include <stdlib.h>
#include "xis.h"
#include "xcpu.h"
#include "xmem.h"

int main( int argc, char **argv ) {
  //Read in a value
  int maxCycle = atoi(argv[1]);
  //  sscanf(argv[1], "%d", &maxCycle);
  FILE *fp;
  
  //Open the file
  fp = fopen(argv[2], "r");

  //Initialize the memory space
  xmem_init(65536);

  //Initialize the CPU struct and 0 all values 
  xcpu cpu = {
  .regs = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  .pc = 0,
  .state = 0,
  .itr = 0,
  .id = 0,
  .num = 0
  };

  
  unsigned char data[2];
  unsigned short addr = 0;

  //Store the file name in memory. First value stored in memory 
  xmem_store(argv[2], 0);

  //Read the contents of the file into memory 
  while(fread(data, sizeof(unsigned char), 2, fp) == 2){
    xmem_store(data, addr);
    addr += 2;
  }

  int run = 1;
  int cycles = 0;
  int outcome;

  //Main loop
  while (run == 1){ 
    outcome = xcpu_execute(&cpu);
    cycles++;
    if(cycles > maxCycle && maxCycle != 0){
      run = 0;
    }
    else if(outcome == 0){
      run = 0;
    }
  }
  return 0;
}


