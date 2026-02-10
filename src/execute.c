#include "../include/input.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int run(char *input[INPUT_LEN]) {
  if (!*input) {
    return 1;
  }

  pid_t p = fork();
  if (p > 0) {
    // Parent proccess
    wait(NULL);

  } else if (!p) {
    // Child proccess
    if (execvp(input[0], input) == -1) {
      // If this point reached, an error occured in exec
      int n = errno; // get error number of exec function

      perror(input[0]);
      exit(1);
    }

  } else {
    printf("Forking failed\n");
    return 1;
  }

  return 0;
}
