#include "../include/alias.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Alias *aliases[ALIAS_LEN];
int head_a = 0;

int check_alias(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) {
    return 0;
  }

  for (int tok_num = 0; tokens[tok_num]; tok_num++) {
    for (int ali_num = 0; ali_num < head_a; ali_num++) {
      if (!strcmp(tokens[tok_num], aliases[ali_num]->name)) {
        // If alias found then insert it
        int endpos = 0;
        for (; tokens[endpos]; endpos++) {
        } // Calculate position of last token in array
        endpos--;

        int comd_len = aliases[ali_num]->command_len;
        // Move elements out of the way
        for (int k = endpos; k > tok_num; k--) {
          tokens[k + comd_len - 1] = tokens[k];
        }
        // Insert new elements
        for (int k = 0; k < comd_len; k++) {
          tokens[tok_num + k] = aliases[ali_num]->command[k];
        }

        return 1;
      }
    }
  }
  return 0;
}

void add_alias(char *tokens[INPUT_LEN]) {
  if (!tokens[1] || !tokens[2]) {
    printf("Alias must have name and command!\n");
    return;
  }

  aliases[head_a] = malloc(sizeof(Alias));

  aliases[head_a]->command_len = 0;
  aliases[head_a]->name = malloc((strlen(tokens[1]) + 1) * sizeof(char));
  strcpy(aliases[head_a]->name, tokens[1]);

  for (int i = 0; tokens[i + 2]; i++) {
    printf("Saving: {%s}\n", tokens[i + 2]);
    aliases[head_a]->command_len++;
    aliases[head_a]->command[i] =
        malloc((strlen(tokens[i + 2]) + 1) * sizeof(char));
    strcpy(aliases[head_a]->command[i], tokens[i + 2]);
  }

  printf("Saved to: {%s}\n", aliases[head_a]->command[0]);
  head_a++;
}

void output_aliases() {
  for (int i = 0; i < head_a; i++) {
    printf("alias %s = ", aliases[i]->name);
    for (int j = 0; j < aliases[i]->command_len; j++) {
      printf("%s ", aliases[i]->command[j]);
    }
    printf("\n");
  }
}
