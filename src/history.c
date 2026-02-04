#include "../include/history.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *history[HIST_LEN][INPUT_LEN];
int total = 0;
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
      pos = head;
    } else {
      char num_s[4];
      strncpy(num_s, tokens[0] + 1, 3);
      int num = atoi(num_s);

      if (num < -total || num > total || num < -HIST_LEN || num > HIST_LEN ||
          num == 0) {
        printf("Invalid history number entered!"); // TODO: Improve this message
        return 1;
      }
      if (num > 0) {
        pos = (head + num - 1) % HIST_LEN;
      } else {
        pos = (HIST_LEN + head + num) % HIST_LEN;
      }
    }

    // Subsitute history element into tokens input
    for (int i = 0; history[pos][i]; i++) {
      tokens[i] = history[pos][i];
    }
    return 0;
  }

  add_hist(tokens);
  return 0;
}

void add_hist(char *input[INPUT_LEN]) {
  for (int i = 0; history[head][i]; i++) {
    free(history[head][i]);
    history[head][i] = NULL;
  }

  for (int i = 0; input[i]; i++) {
    history[head][i] = malloc((strlen(input[i]) + 1) * sizeof(char));
    strcpy(history[head][i], input[i]);
  }

  total++;
  head = (head + 1) % HIST_LEN;
}

void print_hist() {
  int count = 1;
  for (int i = 0; i < HIST_LEN; i++) {
    int pos = (head + i) % HIST_LEN;
    if (history[pos][0]) {
      printf("%2d: ", count);
      count++;

      for (int j = 0; history[pos][j]; j++) {
        printf("%s ", history[pos][j]);
      }
      printf("\n");
    }
  }
}

void free_hist() {
  for (int i = 0; i < HIST_LEN; i++) {
    for (int j = 0; history[i][j]; j++) {
      free(history[i][j]);
    }
  }
}
