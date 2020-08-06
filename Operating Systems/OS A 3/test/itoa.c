#include <stdio.h>

int main() {
  int c;
  short i = 0;
  for( c = getchar(); c >= 0; c = getchar() ) {
    printf( "%d\n", c );
    i++;
    if( !( i % 1000 ) ) {
      fputc( '.', stderr );
    }
  }
  fputc( '\n', stderr );
  return 0;
}
