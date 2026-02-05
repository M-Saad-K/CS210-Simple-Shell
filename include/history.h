#include "../include/input.h"
#include <stdio.h>

#define HIST_LEN 20

// Checks if the input was a history invocation, and insert appropriate item.
// Returns 1 if error in parsing history command, else zero to continue
int check_hist(char *input[INPUT_LEN]);

// Add a input line to the history
void add_hist(char *input[INPUT_LEN]);

// Print the history in order from oldest to newest to specified stream
void output_hist(FILE *stream);

// Load the history file
void load_hist();

// Save the history to the history file
void save_hist();

// Free all the tokens in history
void free_hist();
