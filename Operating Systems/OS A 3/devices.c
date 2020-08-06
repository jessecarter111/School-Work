#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "xdev.h"
#include "devices.h"

#define DISP_PORT 1
#define KBD_PORT 2
#define RAND_PORT 3

/* title: display device
 * param: void *arg (ignored)
 * function: invoked on a separate thread and peforms the following operations:
 *           - associates device with port 1 
 *           - enters an infinite loop
 *           - the loop 
 *             - gets a charatcer (lower half of a word) from the port
 *             - outputs the character to stdout
 * returns: void *, never returns.
 */
extern void *device_display( void *arg ) {
  xdev_associate_port(DISP_PORT);
  while(1){
    unsigned short character = NULL;
    xdev_dev_get(DISP_PORT, &character);
    putchar(character);
    fflush(stdout);
  }
}

/* title: keyboard device
 * param: void *arg (ignored)
 * function: invoked on a separate thread and peforms the following operations:
 *           - associates device with port 2 
 *           - enters an infinite loop
 *           - the loop 
 *             - gets a character from stdin
 *             - puts the character (lower half of a word) to the port
 * returns: void *, never returns.
 */
extern void *device_keyboard( void *arg ) {
  xdev_associate_port(KBD_PORT);
  while(1){
    unsigned short character = getchar();
    xdev_dev_put(character, KBD_PORT); //puts character to port.
  }
}

/* title: random device
 * param: void *arg (ignored)
 * function: invoked on a separate thread and peforms the following operations:
 *           - associates device with port 3 
 *           - enters an infinite loop
 *           - the loop 
 *             - generates a random word using random()
 *             - puts the word to the port
 * returns: void *, never returns.
 */
extern void *device_random( void *arg ) {
  xdev_associate_port(RAND_PORT);
  srand(time(0)); //use current time as seed for random.
  while(1){
    int rando = rand();
    xdev_dev_put((unsigned short)rando, RAND_PORT); //puts character to port.
  }
}
