//history header file
//decleartion of all the methods

#include "../include/input.h"
#define HIST_LEN 20

// Checks if the input was a history invocation, and insert appropriate item.
//Check if a history command prompt has been entered
int check_history(char* tokens[INPUT_LEN]);

//if not history, add current command to the history and then execute
void history_add(char* tokens[INPUT_LEN]);

//free the malloced memory at the end when exit character entered
void free_hist();

// Print the history in order from oldest to newest to specified stream
void output_hist(FILE *stream);

// Load the history file
void load_hist();

// Save the history to the history file
void save_hist();