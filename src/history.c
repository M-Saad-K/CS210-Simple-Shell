#include "../include/history.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *history[INPUT_LEN][20];
int total = 0;

// returns 1 if history error, else zero
int check_hist(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) {
    return 1;
  }

  if (tokens[0][0] == '!') {
    if (tokens[1]) {
      printf("History commands don't take arguments!\n");
      return 1;
    }

    char num_s[3];
    strncpy(num_s, tokens[0] + 1, 2);
    int num = atoi(num_s);
    if (num < 1 || num > 20) {
      printf("History goes from position 1 to position 20!\n");
      return 1;
    }
    int pos = num - 1;

    for (int i = 0; history[pos][i]; i++) {
      tokens[i] = history[pos][i];
    }

    return 0;
  }

  add_hist(tokens);
  return 0;
}

int add_hist(char *input[INPUT_LEN]) {
  for (int i = 0; input[i]; i++) {
    history[total][i] = malloc((strlen(input[i]) + 1) * sizeof(char));
    strcpy(history[total][i], input[i]);
  }
  total++;
  return 0;
}

void free_hist() {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; history[i][j]; j++) {
      free(history[i][j]);
    }
  }
}

void print_hist() {
  printf("hisory: \n");
  for (int i = 0; i < 20; i++) {
    printf("%2d: ", i + 1);
    for (int j = 0; history[i][j]; j++) {
      printf("%s ", history[i][j]);
    }
    printf("\n");
  }
}
