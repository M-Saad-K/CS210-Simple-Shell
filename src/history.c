#include "../include/history.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *history[HIST_LEN][INPUT_LEN];
int head = 0;

// returns 1 if error in parsing history command, else zero
int check_hist(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) {
    return 1;
  }

  if (tokens[0][0] == '!') {
    if (tokens[1]) {
      printf("History commands don't take arguments!\n");
      return 1;
    }

    // Determint history number entered
    int pos;
    if (tokens[0][1] == '!') { // If !! entered
      pos = (HIST_LEN + head - 1) % HIST_LEN;
    } else {
      char num_s[4];
      strncpy(num_s, tokens[0] + 1, 3);
      int num = atoi(num_s);

      if (num < -HIST_LEN || num > HIST_LEN) {
        printf("History index must be from -%d to %d!\n", HIST_LEN, HIST_LEN);
        return 1;
      }
      if (num > 0) {
        if (history[head][0]) {
          pos = (head + num - 1) % HIST_LEN; // formula if overflow has happened
        } else {
          pos = num - 1; // formula if array not overflowed
        }
      } else if (num < 0) {
        pos = (HIST_LEN + head + num) % HIST_LEN; // formula for negative index
      } else {
        printf("0 is not a valid history index!\n");
        return 1;
      }
    }
    if (history[pos][0] == NULL) { // check the history item is not empty
      printf("Invalid history entry!\n");
      return 1;
    }

    // Subsitute history element into tokens input
    for (int i = 0; history[pos][i]; i++) {
      tokens[i] = history[pos][i];
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

  for (int i = 0; input[i]; i++) {
    history[head][i] = malloc((strlen(input[i]) + 1) * sizeof(char));
    strcpy(history[head][i], input[i]);
  }

  head = (head + 1) % HIST_LEN;
}

void output_hist(FILE *stream) {
  int index = 1;
  for (int i = 0; i < HIST_LEN; i++) {
    int pos = (head + i) % HIST_LEN;
    if (history[pos][0]) {
      fprintf(stream, "%2d: ", index);
      index++;

      for (int j = 0; history[pos][j]; j++) {
        fprintf(stream, "%s ", history[pos][j]);
      }
      fprintf(stream, "\n");
    }
  }
}

void load_hist() {
  char buffer[INPUT_LEN];
  FILE *hist_file = fopen(".hist_list", "r");
  while (fgets(buffer, INPUT_LEN, hist_file)) {
    char *tokens[INPUT_LEN];
    tokenize(buffer + 4, tokens); // +4 to skip the number
    add_hist(tokens);
  }
  fclose(hist_file);
}

void save_hist() {
  FILE *hist_file = fopen(".hist_list", "w");
  output_hist(hist_file);
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
