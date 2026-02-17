//history header file
//decleartion of all the methods


#define HIST_LEN 4

//Check if a history command prompt has been entered
int check_history(char* tokens[INPUT_LEN]);

//if not history, add current command to the history and then execute
void history_add(char* tokens[INPUT_LEN]);

//free the malloced memory at the end when exit character entered
void free_hist();



