#include "../include/history.h"
#include "../include/env.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 2D array of up to 20 previous inputs
char *history[HIST_LEN][INPUT_LEN];
int head = 0; // index of array that the next input will be written to

int check_hist(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) { // If input is empty
    return 1;
  }

  // If input is history invocation
  if (tokens[0][0] == '!') {
    if (tokens[1]) { // arguments to history invocation not allowed
      printf("History commands don't take arguments!\n");
      return 1;
    }

    // Determine index in array to load from based on input number
    int index;
    if (tokens[0][1] == '!') {                  // If !! entered
      index = (HIST_LEN + head - 1) % HIST_LEN; // Load most recent history item
    } else {
      char num_s[4];
      strncpy(num_s, tokens[0] + 1, 3); // get number after !
      int num = atoi(num_s);            // convert number to int

      if (num < -HIST_LEN || num > HIST_LEN) { // If number out of range
        printf("History index must be from -%d to %d!\n", HIST_LEN, HIST_LEN);
        return 1;
      }
      if (num > 0) { // If positive number entered
        if (history[head][0]) {
          index = (head + num - 1) % HIST_LEN; // if overflow has happened
        } else {
          index = num - 1; // if array not overflowed
        }
      } else if (num < 0) { // if negative number entered
        index = (HIST_LEN + head + num) % HIST_LEN; // for negative number
      } else {                                      // If 0 or nothing entered
        printf("0 is not a valid history index!\n");
        return 1;
      }
    }
    if (history[index][0] == NULL) { // check the history item exists
      printf("Invalid history entry!\n");
      return 1;
    }

    // Subsitute chosen history element into tokens input
    for (int i = 0; history[index][i]; i++) {
      tokens[i] = history[index][i];
    }
    return 0;
  }

  add_hist(tokens); // If command was not history invocation add it to history
  return 0;
}

void add_hist(char *input[INPUT_LEN]) {
  // Remove old history item if present
  for (int i = 0; history[head][i]; i++) {
    free(history[head][i]);
    history[head][i] = NULL;
  }
  // malloc space for each token in input, then copy it into history
  for (int i = 0; input[i]; i++) {
    history[head][i] = malloc((strlen(input[i]) + 1) * sizeof(char));
    strcpy(history[head][i], input[i]);
  }

  // Move head forwards
  head = (head + 1) % HIST_LEN;
}

void output_hist(FILE *stream) {
  int index = 1; // for printing the command number
  for (int i = 0; i < HIST_LEN; i++) {
    int pos = (head + i) % HIST_LEN;
    if (history[pos][0]) { // if not empty then it must be the first element
      fprintf(stream, "%2d: ", index);
      index++;

      for (int j = 0; history[pos][j];
           j++) { // print each word in history entry
        fprintf(stream, "%s ", history[pos][j]);
      }
      fprintf(stream, "\n");
    }
  }
}

void load_hist() {
  set_home();
  char buffer[INPUT_LEN];  // buffer for each line to be read to from file
  char *tokens[INPUT_LEN]; // pointers to each token in the buffer
  FILE *hist_file = fopen(".hist_list", "r");
  if (hist_file) { // check that .hist_list exists
    while (fgets(buffer, INPUT_LEN, hist_file)) {
      tokenize(buffer + 4, tokens); // +4 to skip the number
      add_hist(tokens);
      clear(tokens);
    }
    fclose(hist_file);
  }
}

void save_hist() {
  set_home();
  FILE *hist_file = fopen(".hist_list", "w");
  output_hist(hist_file); // print the list to the history file
  fclose(hist_file);
}

void free_hist() {
  for (int i = 0; i < HIST_LEN; i++) {
    for (int j = 0; history[i][j]; j++) {
      free(history[i][j]);
      history[i][j] = NULL;
    }
  }
}
