#include "../include/input.h"

#define ALIAS_LEN 10

typedef struct {
  char *name;
  char *command[INPUT_LEN];
  int command_len;
} Alias;

int check_alias(char *tokens[INPUT_LEN]);
void add_alias(char *tokens[INPUT_LEN]);
void output_aliases();
