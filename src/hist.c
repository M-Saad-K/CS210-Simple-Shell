#include "../include/hist.h"
#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_LEN 4

// GLOBAL
char *stor[QUEUE_LEN]; // This is the queue
int f = 0;             // front
int r = 0;             // reari
int counter = 0;       // Keep tiack that queue contains 20 elements

int hisAcc(int n, char input_buffer[INPUT_LEN]) {
  // int i = n + (f - n) + n;

  printf("Int value: %d\n", n);

  if (n == 32767 && counter != 0) {

    strcpy(input_buffer, stor[(r - 1) % QUEUE_LEN]); // When !!
  } else if (n >= 0 && n <= QUEUE_LEN && counter != 0 && stor[n] != NULL) {
    strcpy(input_buffer, stor[(f + (n)) % QUEUE_LEN]); // When any random point
                                                       // between f -> r chosen
  } else if (n <= -1 && n >= -QUEUE_LEN && counter != 0) {

    strcpy(input_buffer, stor[(r + n) % QUEUE_LEN]);
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

  // show();
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
      printf("%d : %s \n\n", i, stor[i]);
    }
  }

  // If the queue is full
  if (f == r && counter == 1) {

    int x = 1;

    for (int i = f; i < QUEUE_LEN; i++) {

      // printf("F: %d, R: %d \n\n", f, r);
      printf("%d : %s \n\n", x, stor[i]);
      x++;
    }
    for (int i = 0; i < r; i++) {

      // printf("F: %d, R: %d \n\n", f, r);
      printf("%d : %s \n\n", x, stor[i]);
      x++;
    }
  }
}

void putHist(char input_buffer[INPUT_LEN]) {

  if (input_buffer[0] == '!') {

    printf("1\n");
    int n;
    char mark;
    char other;

    sscanf(input_buffer, "%c%d%c\n", &mark, &n, &other);
    printf("2\n");
    printf("mark: {%s}\n", &mark);
    printf("n: {%d}\n", n);
    printf("other: {%s}\n", &other);
    // return;
    printf("3\n");
    hisAcc(n, input_buffer);
    printf("4\n`");

  } else {

    hisStore(input_buffer);
    if (!strcmp(input_buffer, "history\n")) {
      show();
    } else {
      ; // Do Nothing
    }
  }
}
