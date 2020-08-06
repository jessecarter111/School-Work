#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define X_INSTRUCTIONS_NEEDED

#include "xis.h"
#include "xcpu.h"
#include "xmem.h"

extern void xcpu_print( xcpu *c ) {
  int i;
  unsigned char data[2];
  unsigned int op1;
  int op2;

#ifdef PTHREAD_MUTEX_INITIALIZER
  static pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;

  if( pthread_mutex_lock( &lk ) ) {
    printf( "Failure to acquire lock!" );
    abort();
  }
#endif

  fprintf( stdout, "%2.2d> PC: %4.4x, State: %4.4x\n" , c->id, c->pc, c->state);
  fprintf( stdout, "%2.2d> Registers: ", c->id );
  for( i = 0; i < X_MAX_REGS; i++ ) {
    if( !( i % 8 ) ) {
      fprintf( stdout, "\n%2.2d>     ", c->id );
    }
    fprintf( stdout, " r%2.2d:%4.4x", i, c->regs[i] );
  }
  fprintf( stdout, "\n" );

  xmem_load( c->pc, data );
  op1 = data[0];
  op2 = data[1];
  for( i = 0; i < I_NUM; i++ ) {
    if( x_instructions[i].code == op1 ) {
      fprintf( stdout, "%2.2d> Next instruction: %s ", c->id, 
               x_instructions[i].inst );
      break;
    }
  }

  switch( XIS_NUM_OPS( op1 ) ) {
  case 1:
    if( op1 & XIS_1_IMED ) {
      fprintf( stdout, "%d", op2 );
    } else {
      fprintf( stdout, "r%d", XIS_REG1( op2 ) );
    }
    break;
  case 2:
    fprintf( stdout, "r%d, r%d", XIS_REG1( op2 ), XIS_REG2( op2 ) );
    break;
  case XIS_EXTENDED:
    xmem_load( c->pc + 2, data );
    fprintf( stdout, "%u", data[0] << 8 | data[1] );
    if( op1 & XIS_X_REG ) {
      fprintf( stdout, ", r%d", XIS_REG1( op2 ) );
    }
    break;
  }
  fprintf( stdout, "\n\n" );

#ifdef PTHREAD_MUTEX_INITIALIZER
  if( pthread_mutex_unlock( &lk ) ) {
    printf( "Failure to release lock!" );
    abort();
  }
#endif
}

