#include "../include/input.h"
#include <stdio.h>

#define HIST_LEN 20

int check_hist(char *input[INPUT_LEN]);
void add_hist(char *input[INPUT_LEN]);
void output_hist(FILE *stream);
void load_hist();
void save_hist();
void free_hist();
