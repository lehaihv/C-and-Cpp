#include <stdio.h>
//#include <cstdint.h>
#include <stdint.h>

//Data structure definition of the circular buffer
typedef struct {
    uint8_t * const buffer;
    int head;
    int tail;
    const int maxlen;
} circ_bbuf_t;

//Function to push data into the circular buffer
int circ_bbuf_push(circ_bbuf_t *c, uint8_t data)
{
    int next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->maxlen)
        next = 0;

    if (next == c->tail)  // if the head + 1 == tail, circular buffer is full
        return -1;

    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
    return 0;  // return success to indicate successful push.
}

//Function to pull data from the circular buffer
int circ_bbuf_pop(circ_bbuf_t *c, uint8_t *data)
{
    int next;

    if (c->head == c->tail)  // if the head == tail, we don't have any data
        return -1;

    next = c->tail + 1;  // next is where tail will point to after this read.
    if(next >= c->maxlen)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
    return 0;  // return success to indicate successful push.
}

//Define a circular buffer
#define CIRC_BBUF_DEF(x,y)                \
    uint8_t x##_data_space[y];            \
    circ_bbuf_t x = {                     \
        .buffer = x##_data_space,         \
        .head = 0,                        \
        .tail = 0,                        \
        .maxlen = y                       \
    }

/*Initialize an instance of circular buffer with the size of 6 bytes
 - 5 bytes for store data.
 - 1 byte use as a flag to differentiate between buffer empty and full cases. */
CIRC_BBUF_DEF(my_circ_buf, 6);

int main() {

  int i;
  uint8_t out_data[5], in_data[5] = {0x11, 0x22, 0x33, 0x44, 0x55};

  // Push array of 5 byte from in_data[5] into the circular buffer
  for (i = 0; i < 5; i++) {
	  if (circ_bbuf_push(&my_circ_buf, in_data[i])) {
	        printf("Out of space in CB\n");
	        return -1;
	    }
	  else printf("Push: 0x%x\n", in_data[i]);
  }

  // Pull out array of 5 byte from the circular buffer and store in in_data[5]
  for (i = 0; i < 5; i++) {
	  if (circ_bbuf_pop(&my_circ_buf, &out_data[i])) {
	        printf("CB is empty\n");
	        return -1;
	    }
	  else printf("Pop:  0x%x\n", out_data[i]);
    }

  double *p;

// Prints size of an 'int'
printf("%zu\n", sizeof(int));

// p is type 'int *', so prints size of 'int*'
printf("%zu\n", sizeof p);

// *p is type 'int', so prints size of 'int'
printf("%zu\n", sizeof *p);

int x[12]; // 12 ints

printf("%zu\n", sizeof(x)); // 48 total bytes
printf("%zu\n", sizeof(int)); // 4 bytes per int

printf("%zu\n", sizeof(x) / sizeof(int)); // 48/4 = 12 ints!

  return 0;
}

/***********************************************************************
 + Comment on design decisions
 1. Have you optimised for speed or space?
  - The design was optimsed for speed, because it is assumed that mostly
  "push data to circular buffer" will be called within an ISR so a push
  should be as (small)quick as possible.
 2. Are your items allocated statically?
  - No, the buffer has to be global or it has to be in stack so long as you
  need to use it.
 ***********************************************************************/


