#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/input.h"
#include "../include/hist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



// GLOBAL
char* stor[1000]; // This is the queue
int f = 0; // front
int r = 0; // rear
int counter = 20; // Kepp track that queue contains 20 elements

int hisAcc(int n, char input_buffer[INPUT_LEN]){
  int i = n + (f - n) + n; 
  
  strcpy(input_buffer, stor[i-48]);

  printf("\nAccessed memory : %s\n", stor[i-48]); // DEBUG
  printf("Input Buffer : %s\n", input_buffer); // DEBUG
}
int hisStore(char input[INPUT_LEN]){
  
  // Check input is not empty
  if (!input) {
    return 1;
  }
  
  // Checks if the queue is full and ensures it still holding recent methods and getting rid of old ones
  if(r == counter){

    dequeue();
    enqueue(input);
  } else{

    enqueue(input);
  }


  show();
}

//Enqueue the store array
void dequeue(){
  
  if(!(f == -1 || f > r)){
    free(stor[f]);
    f++; // Increment front
    counter++; // Increment counter
  } else {
    // DEBUG
    printf("Error Dequeue");
    return;
  }
}

void enqueue(char input[INPUT_LEN]){
  
  if(!(r == -1 || f > r)){
    r++;

    printf("Input: %s \n", input); // DEBUG

    stor[r] = malloc(INPUT_LEN*sizeof(char));
    strcpy(stor[r], input);
  } else {
    // DEBUG
    printf("Error Enqueue");
    return;
  }
}

void show(){
  
  printf("front = %d, rear = %d, counter = %d", f, r, counter);
  for(int i = f; i < r; i++){
    
    printf("Element : %s\n", stor[i]);
  }
}

void putHist(char input_buffer[INPUT_LEN]){

  if(input_buffer[0] == '!'){
    int n = input_buffer[1];
    printf("\n%d\n", n); // DEBUG
// a[b] = (a+b)
    hisAcc(n, input_buffer);
  } else {

    hisStore(input_buffer);
  }
}
