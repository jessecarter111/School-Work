#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

#include "xis.h"
#include "xcpu.h"
#include "xmem.h"

#define TICK_ARG 1
#define IMAGE_ARG 2

//Structure to hold the cpuContext and # of cycles to be passed into runme
//A basic work around for using the assignment implementation in a new method
//to be used with Pthread_create
struct args {
  xcpu cpuContext;
  int cycles;
};

//Max # of threads is 32 as outline in assignment
pthread_t threadID[32];

void *runme(void *arguments){
  //Takes in a void pointer which is used to grab the args struct
  struct args *args = arguments;
  //Set the values
  xcpu cpu = (xcpu)args -> cpuContext;
  int i;
  int ticks = (int)args -> cycles;
  //Same as assignment implementation
  for(i = 0; ( ticks < 1 ) || ( i < ticks ); i++ ) {
    if( !xcpu_execute( &cpu ) ) {
      break;
    }
  }
  //Call pthread_exit
  pthread_exit(NULL);
  return 0;
}

int main( int argc, char **argv ) {

  FILE *fp;
  struct stat fs;
  unsigned char data[2];
  int ticks;
  unsigned int i;

  if( ( argc < 3 ) || ( sscanf( argv[TICK_ARG], "%d", &ticks ) != 1 ) || 
      ( ticks < 0 ) ) {
    printf( "usage: xsim <ticks> <obj file>\n" );
    printf( "      <ticks> is number instructions to execute (0 = forever)\n" );
    printf( "      <image file> xis object file created by or xasxld\n" );
    return 1;
  } 

  if( !xmem_init( XIS_MEM_SIZE ) ) {
    printf( "error: memory allocation (%d) failed\n", XIS_MEM_SIZE );
    exit( 1 );
  } else if( stat( argv[IMAGE_ARG], &fs ) ) {
    printf( "error: could not stat image file %s\n", argv[IMAGE_ARG] );
    return 1;
  } else if( fs.st_size > XIS_MEM_SIZE ) {
    printf( "Not enough memory to run all the programs." );
    return 1;
  }

  fp = fopen( argv[IMAGE_ARG], "rb" );
  if( !fp ) {
    printf( "error: could not open image file %s\n", argv[IMAGE_ARG] );
    return 1;
  } 
 
  for( i = 0; i < fs.st_size; i += 2 ) {
    if( fread( data, 1, 2, fp ) < 1 ) {
      printf( "error: could not read file %s\n", argv[IMAGE_ARG] );
      return 1;
    }
    xmem_store( data, i );
  }
  fclose( fp );
  
  //Get total number of cpus
  int totalCPU = atoi(argv[3]);
  //Initialize an array to hold the CPU contexts
  xcpu contexts[totalCPU];
  
  //For loop used initialize all the CPU contexts and store in contexts[]
  for (i = 0; i < totalCPU; i++){
    xcpu x = {
      .regs = {0,0,0,0,0,0,0,0,0,0,0,0},
      .pc = 0,
      .state = 0,
      .itr = 0,
      .id = i,
      .num = totalCPU
    };
    contexts[i] = x;
  }
  
  //A pthread_t to be used with pthread_create
  pthread_t thread;
 
  for(i = 0; i < totalCPU; i++){
    //Malloc used to allocate the struct in the heap
    //This way we don't have to worry out it being overwritten
    //as we create more cpus
    struct args *args = malloc(sizeof(struct args));
    //Initialize the values in the struct
    args->cpuContext = contexts[i];
    args->cycles = ticks;
    //Pthread_create as outline in the notes, lecture 6 example 1
    thread = pthread_create(&threadID[i],
           NULL,
           &runme,
           (void *)args);
  }

  //pthread_join as outlined in the notes, lecture 6  example 1
  for (i = 0; i < totalCPU; i++){
    thread = pthread_join(threadID[i], 
         NULL);
  }

  return 0; 
}
 
