#include "../include/alias.h"
#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/execute.h"
#include "../include/history.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *wel =
    "This is the SUSHI Shell - Strathclyde Unix-type SHell Implementation \n"
    "⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣤⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⣠⣴⣾⣿⡿⠿⠛⠛⠛⠛⠛⠛⠛⠻⠿⢿⣿⣶⣤⣄⠀⠀\n"
    "⢠⣾⡿⠛⠉⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠉⠛⢿⣷⡀\n"
    "⣿⣿⠀⠀⠀⠀⠀⢶⣿⣿⣿⣿⣿⣿⣿⣿⡶⠀⠀⠀⠀⠈⣿⣷\n"
    "⣿⣿⣷⣄⡀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⢀⣠⣾⣿⣿\n"
    "⣿⣿⣿⣿⣿⣿⣶⣦⣤⣤⣤⣄⣠⣤⣤⣤⣴⣶⣿⣿⣿⣿⣿⣿\n"
    "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
    "⣿⣿⣿⣿⣿⣿⣿⡿⠛⢿⣿⣿⣿⣿⡿⠛⢿⣿⣿⣿⣿⣿⣿⣿\n"
    "⣿⣿⣿⣿⣿⣿⣿⣿⣦⣾⣿⣿⣿⣿⣷⣴⣿⣿⣿⣿⣿⣿⣿⣿\n"
    "⢻⣿⣿⣿⣿⣿⣿⣏⠀⠉⠛⠛⠛⠛⠉⠀⣹⣿⣿⣿⣿⣿⣿⡟\n"
    "⠀⠻⣿⣿⣿⣿⣿⣿⣿⣶⣦⣤⣤⣴⣶⣿⣿⣿⣿⣿⣿⣿⠟⠀\n"
    "⠀⠀⠈⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠁⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠉⠉⠙⠛⠛⠛⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀\n"
    "\n";

const char *exi = "                                88          88   \n"
                  "                                88               \n"
                  "                                88               \n"
                  ",adPPYba, 88       88 ,adPPYba, 88,dPPYba,  88   \n"
                  "I8[     I 88       88 I8[    !! 88P'     8a 88   \n"
                  "  £Y8ba,  88       88  llY8ba,  88       88 88   \n"
                  "aa    ]8I 8a,    ,a88 aa    ]8I 88       88 88   \n"
                  "` YbbdP'    YbbdP 'Y8 `mYbbdP   88       88 88   \n"
                  "⠀⠀⠀⢸⣦⡀⠀⠀⠀⠀⢀⡄             \n"
                  "⠀⠀⠀⢸⣏⠻⣶⣤⡶⢾⡿⠁             \n"
                  "⠀⠀⣀⣼⠷⠀⠀⠁ 𝑺𝑬𝑬 𝒀𝑶𝑼 𝑺𝑷𝑨𝑪𝑬   \n"
                  "⠴⣾⣯⣅⣀⠀⠀⠀⠈⢻⣦⡀𝑪𝑶𝑾𝑩𝑶𝒀 . . . \n"
                  "⠀⠀⠀⠉⢻⡇⣤⣾⣿⣷⣿⠏⠉            \n"
                  "⠀⠀⠀⠀⠸⣿⡿⠏⠀⠀⠀⠀             \n"
                  "⠀⠀⠀⠀⠀⠟⠁⠀⠀⠀⠀ ⠀⠀           \n"
                  "\n";

int main(void) {
  printf("%s", wel);

  char *saved_path[2] = {NULL, save_path()}; // stored in form of input
  printf("Saved path: %s\n", saved_path[1]);

  char cwd[100];
  getcwd(cwd, 100);
  printf("Old HOME: %s\n", cwd);
  set_home();
  getcwd(cwd, 100);
  printf("New HOME: %s\n", cwd);

  load_hist();
  load_aliases();

  char input_buffer[INPUT_LEN]; // Buffer for user input
  char *tokens[INPUT_LEN];      // Pointers to each token in buffer
  clear(tokens); // Clears data left over from previous run which causes errors

  while (get_input(input_buffer, tokens)) {
    while (check_alias(tokens)) { // insert all aliases
    }

    if (!check_history(tokens)) {
      if (!check_builtin(tokens)) {
        print_tokens(tokens);
        run(tokens);
      }
    }

    clear(tokens);
  }
  printf("%s", exi);

  // Cleaning up
  setpath(saved_path);
  free(saved_path[1]);
  printf("Restored path: %s\n", getenv("PATH"));

  save_hist();
  save_aliases();
  free_hist();
}
