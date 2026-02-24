#include "../include/builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *save_path() {
  char *old_path = getenv("PATH");
  char *saved_path = malloc((strlen(old_path) + 1) * sizeof(char));
  strcpy(saved_path, old_path);
  return saved_path;
}

void set_home() {
  char *home = getenv("HOME");
  if (chdir(home) != 0) {
    perror("Error: ");
  };
}
