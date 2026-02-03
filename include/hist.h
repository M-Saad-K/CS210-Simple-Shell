#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/input.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int hisAcc();
int hisStore(char input[INPUT_LEN]);
void dequeue(int f, int r);
void enqueue(char* stor[20+1], char input[INPUT_LEN], int f, int r);



