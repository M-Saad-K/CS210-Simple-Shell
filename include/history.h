//history header file
//decleartion of all the methods


#define HIST_LEN 20

//Check if a history command prompt has been entered
int check_history(char* tokens[INPUT_LEN]);

//if not history, add current command to the history and then execute
void history_add(char* tokens[INPUT_LEN]);

//creates a new struct token
struct history create_struct(char* tokens[INPUT_LEN]);

//free the malloced memory at the end when exit character entered
void free_hist();

/**
//this will check and run the various variations of the history command 
//int return for error handling
int history_exe(char* tokens[INPUT_LEN]);
**/


