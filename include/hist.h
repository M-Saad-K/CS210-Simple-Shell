#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/input.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int hisAcc();
int hisStore(char input[INPUT_LEN]);
void dequeue();
void enqueue(char input[INPUT_LEN]);
void show();
void putHist(char input_buffer[INPUT_LEN]);



