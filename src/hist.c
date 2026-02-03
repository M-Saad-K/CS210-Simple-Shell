#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/input.h"
#include "../include/hist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



// GLOBAL
char* stor[20+1]; // This is the queue


//void dequeue(int f, int r);
//void enqueue(char* stor[20+1], char* input[INPUT_LEN], int f, int r);
//Storing previous inputs

int hisAcc(int n, char input_buffer[INPUT_LEN]){

  input_buffer = stor[20-n];
}
int hisStore(char input[INPUT_LEN]){
  
  int f = -1; //Front
  int r = -1; //Rear

  // Check input is not empty
  if (!input) {
    return 1;
  }
  
  
  // Length of queue
  //int length = sizeof(stor) / sizeof(stor[0]);
  
  // Checks if the queue is full and ensures it still holding recent methods and getting rid of old ones
  if(r == 20){

    dequeue(f, r);
    enqueue(stor, input, f, r);
  } else{

    enqueue(stor, input, f, r);
  }
}

//Enqueue the store array
void dequeue(int f, int r){
  int front = f;
  int rear = r;
  
  if(!(front == -1 || front > rear)){
    front = front+1;
  } else {
    // DEBUG
    printf("Error Dequeue");
    return;
  }
}

void enqueue(char* stor[20+1], char input[INPUT_LEN], int f, int r){
  int front = f;
  int rear = r;
  
  if(!(rear == -1 || front > rear)){
    rear = rear+1;
    stor[rear] = &input[INPUT_LEN];
  } else {
    // DEBUG
    printf("Error Enqueue");
    return;
  }
}

