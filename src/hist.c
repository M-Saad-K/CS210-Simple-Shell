#include "../include/hist.h"
#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_LEN 21

/*! CURRENT ISSUE WITH THE CODE IS THAT IS CAN'T TAKE IN !10-!20 FOR HISTORY
 * ACCESS
 *
 *  Reasons:
 *
 *  1. putHist only takes in the MSB digit of the integer
 *  2. Boundary Check only allowed for integers between 0-9
 *  3. There are no ASCII values for 10-20
 * */

// GLOBAL
char *stor[QUEUE_LEN]; // This is the queue
int f = 0;             // front
int r = 0;             // reari
int counter = 0;       // Keep track that queue contains 20 elements

int hisAcc(int n, char input_buffer[INPUT_LEN]) {
  // int i = n + (f - n) + n;

  printf("Int value: %d\n", n);

  if (n == 33 && counter != 0) {

    strcpy(input_buffer, stor[(r - 1) % QUEUE_LEN]); // When !!
  } else if (n >= 0 && n <= 20 && counter != 0) {
    strcpy(input_buffer, stor[(f + (n)) % QUEUE_LEN]); // When any random point
                                                       // between f -> r chosen
  } else {
    printf("Invalid!\n");
  }
  // printf("\nAccessed memory : %s\n", stor[n-48]); // DEBUG
  // printf("Input Buffer : %s\n", input_buffer); // DEBUG
  //
  return 0;
}
int hisStore(char input[INPUT_LEN]) {

  // Check input is not empty
  if (!input) {
    return -1;
  }

  enqueue_dequeue(input);

  show();
  return 0;
}

void enqueue_dequeue(char input[INPUT_LEN]) {

  // When f == r empty
  if (f == r && counter == 0) {

    // DEBUG
    printf("Counter: %d \n", counter);
    // DEBUG
    printf("The queue is empty \n");

    stor[r] = malloc(INPUT_LEN * sizeof(char));
    strcpy(stor[r], input);
    r = (r + 1) % QUEUE_LEN;

    counter++;
    // DEBUG
    printf("Should have now incremented! Counter: %d \n", counter);

  } else if (f == r && counter != 0) { // Else if the queue is now empty

    // DEBUG
    printf("Counter: %d \n", counter);

    // DEBUG
    printf("The queue is now full\n");

    // CHECK IF STOR[R] HAS ANY MALLOCED SPACE
    // When r + 0 == f
    // First increment f
    f = (f + 1) % QUEUE_LEN;
    strcpy(stor[r], input);
    // Then increment r
    r = (r + 1) % QUEUE_LEN;

  } else { // Else when f < r and still enqueue

    // DEBUG
    printf("Counter: %d \n", counter);
    // DEBUG
    printf("The queue is filling up\n");

    stor[r] = malloc(INPUT_LEN * sizeof(char));
    strcpy(stor[r], input);
    r = (r + 1) % QUEUE_LEN;
  }
}

void show() {

  // if filling up
  if (r > f) {

    for (int i = 0; i < QUEUE_LEN; i++) {

      printf("F: %d, R: %d \n\n", f, r);
      printf("Element (%d) : %s : %p \n\n", i, stor[i], (void *)&stor[i]);
    }
  }

  // If the queue is full
  if (f == r && counter == 1) {

    for (int i = f; i < QUEUE_LEN; i++) {

      printf("F: %d, R: %d \n\n", f, r);
      printf("Element (%d) : %s : %p \n\n", i, stor[i], (void *)&stor[i]);
    }
    for (int i = 0; i < r - 1; i++) {

      printf("F: %d, R: %d \n\n", f, r);
      printf("Element (%d) : %s : %p \n\n", i, stor[i], (void *)&stor[i]);
    }
  }
}

void putHist(char input_buffer[INPUT_LEN]) {

  if (input_buffer[0] == '!') {

    char trans[3];
    memcpy(trans, input_buffer, 3 * sizeof(char)); // !100
    int n = atoi(trans);
    printf("\n%d\n", n); // DEBUG
                         // a[b] = (a+b)
    hisAcc(n, input_buffer);
  } else {

    hisStore(input_buffer);
  }
}
