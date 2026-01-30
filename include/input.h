#define INPUT_LEN 512

#define BLINK "\x1b[5m"
#define RESET "\x1b[0m"

#define RED_FG "\x1b[31m"
#define GREEN_FG "\x1b[32m"
#define BLUE_FG "\x1b[34m"
#define MAGENTA_FG "\x1b[35m"
#define BLACK_FG "\x1b[30m"

#define RED_BG "\x1b[41m"
#define GREEN_BG "\x1b[42m"
#define BLUE_BG "\x1b[44m"
#define BLACK_BG "\x1b[40m"

// Read in input from stdin
int get_input(char *input_buffer, char *output[INPUT_LEN]);

// Turn input string into array of strings in output
int tokenize(char input[INPUT_LEN], char *output[INPUT_LEN]);

// Delete all words in array
int clear(char *array[INPUT_LEN]);

// Print all tokens in array
void print_tokens(char *array[INPUT_LEN]);

void stop_flashing_cursor(char *tokens[INPUT_LEN]);
