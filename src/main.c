/**
This is the SUSHI Shell - Strathclyde Unix-type SHell Implementation

⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣤⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⣠⣴⣾⣿⡿⠿⠛⠛⠛⠛⠛⠛⠛⠻⠿⢿⣿⣶⣤⣄⠀⠀
⢠⣾⡿⠛⠉⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠉⠛⢿⣷⡀
⣿⣿⠀⠀⠀⠀⠀⢶⣿⣿⣿⣿⣿⣿⣿⣿⡶⠀⠀⠀⠀⠈⣿⣷
⣿⣿⣷⣄⡀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⢀⣠⣾⣿⣿
⣿⣿⣿⣿⣿⣿⣶⣦⣤⣤⣤⣄⣠⣤⣤⣤⣴⣶⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⡿⠛⢿⣿⣿⣿⣿⡿⠛⢿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣦⣾⣿⣿⣿⣿⣷⣴⣿⣿⣿⣿⣿⣿⣿⣿
⢻⣿⣿⣿⣿⣿⣿⣏⠀⠉⠛⠛⠛⠛⠉⠀⣹⣿⣿⣿⣿⣿⣿⡟
⠀⠻⣿⣿⣿⣿⣿⣿⣿⣶⣦⣤⣤⣴⣶⣿⣿⣿⣿⣿⣿⣿⠟⠀
⠀⠀⠈⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠁⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠉⠉⠙⠛⠛⠛⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀
**/

#include "../include/externelRunner.h"
#include "../include/input.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  char input_buffer[512]; // This is for holding the user input
  char *tmp =
      "t"; // This is a temp variable, used for detecting ctrl+D when entered

  while (!((strcmp(input_buffer, "exit\n") == 0 || (tmp == NULL)))) {
    printf("--> ");
    tmp = fgets(input_buffer, sizeof(input_buffer),
                stdin); // TODO: Check if n correct

    printf("strcmp %d\n", strcmp(input_buffer, "exit\n"));
    printf("ASCII %d\n", *input_buffer);
    printf("tmp: %d\n", tmp == NULL);
    tokenize(input_buffer);
    char input_buffer[512];
  }
}
