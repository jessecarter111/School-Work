#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "xdev.h"

//Source of Queue Implementation :
//https://stackoverflow.com/questions/39047190/creating-a-queue-with-structs-in-c
typedef struct Queue{
        int capacity;
        int size;
        unsigned short  front;
        unsigned short  rear;
        unsigned short *elements;
} Queue;

typedef struct Port{
        Queue *input;
        pthread_mutex_t empty;//lock for Consumption
        pthread_mutex_t full;//lock for Producer
} Port;

Port * createPort(Queue *input, pthread_mutex_t empty, pthread_mutex_t full){
        Port *P;
        P = (Port *)malloc(sizeof(Port));
        P->input = input;
        P->empty = empty;
        P->full = full;
        return P;
}

Queue * createQueue(unsigned short  maxElements){
        /* Create a Queue */
        Queue *Q;
        Q = (Queue *)malloc(sizeof(Queue));
        /* Initialise its properties */
        Q->elements = (unsigned short  *)malloc(sizeof(unsigned short )*maxElements);
        Q->size = 0;
        Q->capacity = maxElements;
        Q->front = 0;
        Q->rear = -1;
        /* Return the pointer */
        return Q;
}
unsigned short Dequeue(Queue *Q){
        /* If Queue size is zero then it is empty. So we cannot pop */
        if(Q->size==0)
        {
                printf("Queue is Empty\n");
                return (int) NULL;
        }
        /* Removing an element is equivalent to incrementing index of front by one */
        else
        {
                unsigned short value = Q->elements[Q->front];
                Q->size--;
                Q->front++;
                /* As we fill elements in circular fashion */
                if(Q->front==Q->capacity)
                {
                        Q->front=0;
                }
                return value;
        }
        return (int) NULL;
}
unsigned short  front(Queue *Q){
        if(Q->size==0)
        {
                printf("Queue is Empty\n");
                exit(0);
        }
        /* Return the element which is at the front*/
        return Q->elements[Q->front];
}
void Enqueue(Queue *Q, unsigned short element){
        /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
        if(Q->size == Q->capacity)
        {
          printf("Queue is full\n");
        }
        else
        {
                Q->size++;
                Q->rear = Q->rear + 1;
                /* As we fill the queue in circular fashion */
                if(Q->rear == Q->capacity)
                {
                        Q->rear = 0;
                }
                /* Insert the element in its rear side */ 
                Q->elements[Q->rear] = element;
        }
        return;
}

Port *ports [3] = {NULL}; //Array of ports to access (With input/output queues)

int xdev_associate_port( unsigned short port ) {
  //if nothing at port create input/output queue and assign it
  if(ports[port - 1] == NULL){
    //Create input
    Queue *input = createQueue(1000);
    pthread_mutex_t empty = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t full = PTHREAD_MUTEX_INITIALIZER;
    Port *newPort = createPort(input, empty, full);
    pthread_mutex_lock(&newPort->full);
    ports[port - 1] = newPort;
    return 1;
  }
  return 0;
}

int xdev_dev_put( unsigned short data, unsigned short port ) {
  //WAITING FOR CPU TO MAKE INPUT REQUEST
  //TODO: Needs to be done synchronously, sends a word of data from the device to CPU.
  //check if port is associated with device
  Port *currentPort = ports[port - 1];
  if(currentPort != NULL){
    pthread_mutex_lock(&currentPort->empty); //if lock cant be obtained it means other method is accessing
    //Copy the data to reqeusting CPU, signal the CPU, and return
    //printf("------ xdev_dev_put\n");
    //printf("Enqueing Data: %d, on Port %d", data, port);
    Enqueue(currentPort->input, data);
    pthread_mutex_unlock(&currentPort->full);
    return 1;
  }
  return 0;
}

int xdev_inp_sync( unsigned short port, unsigned short *data ) {
  //WAITING FOR DEVICE TO CONSUME INPUT REQUEST.
  //This function synchronously receives a word of data for the CPU from the
  //device associated with the specified port.
  //associated with the specified port
  Port *currentPort = ports[port - 1];
  if(currentPort != NULL){
      pthread_mutex_lock(&currentPort->full);
      //we can acquire lock
      //function copies the word of data into location of *data
      //printf("------ xdev_inp_sync\n");
      unsigned short value = Dequeue(currentPort->input);
      *data = value;
      //printf("Dequeing Data: %d, on Port %d", value, port);
      //Signals device, and returns.
      pthread_mutex_unlock(&currentPort->empty);
      return 1;
  } 
  return 0; // replace with your code
}


int xdev_dev_get( unsigned short port, unsigned short *data ) {
  //WAITING FOR CPU TO MAKE OUTPUT REQUEST
  //TODO: Needs to be done synchronously, receives a word of data for the device.
  //check if port is associated with device
  Port *currentPort = ports[port - 1];
  if(currentPort != NULL){
    //check for request waiting in outpute queue
    pthread_mutex_lock(&currentPort->full);
    //something waiting in output queue.
    //copy data from the request queue to the location of *data.
    //printf("------ xdev_dev_get\n");
    unsigned short value = Dequeue(currentPort->input);
    *data = value;
    //signals CPU performing request
    pthread_mutex_unlock(&currentPort->empty);
    return 1;
    
  }
  return 0; // replace with your code
}


int xdev_outp_sync( unsigned short data, unsigned short port ) {
  //This function synchronously sends a word of data from the CPU to the device
  //associated with the specified port
  //check if device is associated with port.
  Port *currentPort = ports[port - 1];
  if(currentPort != NULL){
    pthread_mutex_lock(&currentPort->empty);
    //insert word into output queue.
    //printf("------ xdev_outp_sync\n");
    Enqueue(currentPort->input, data);
    //if device is ready to output the word, signal device and return
    //otherwise block until the device removes the word from output queue and signals CPU.
    //WAITING FOR DEVICE TO CONSUME OUTPUT REQUEST
    pthread_mutex_unlock(&currentPort->full);
    return 1;

  }
  return 0; // replace with your code
}


int xdev_outp_async( unsigned short data, unsigned short port ) {
  //This function asynchronously sends a word of data from the CPU to the device
  //associated with the specified port
  Port *currentPort = ports[port - 1];
  if(currentPort != NULL){
    //insert word into output queue.
    if(pthread_mutex_trylock(&currentPort->empty) == 0){
      //printf("------ xdev_outp_async\n");
      Enqueue(currentPort->input, data);
      pthread_mutex_unlock(&currentPort->full);
      return 1;
    }
  }
  return 0;
}

int xdev_inp_poll( unsigned short port, unsigned short *data ) {
  //check if device is associated with port.
  Port *currentPort = ports[port - 1];
  if(currentPort != NULL){
    //need to check if device is ready with a word of data.
    if(pthread_mutex_trylock(&currentPort->full) == 0){
      //printf("------ xdev_inp_poll\n");
      unsigned short value = Dequeue(currentPort->input);
      *data = value;
      //Signals device data has been dequeued.
      pthread_mutex_unlock(&currentPort->empty);
      return 1;
    }
  }
  return 0;
}


