#include "../include/input.h"
#include "../include/history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

//array that stores all our history
//2D array, each row represents a hist_len
char *history[HIST_LEN][INPUT_LEN]; 	//the command line, each part of this array points to a string (token)  

//the current head of the struct... ie like an index counter
int head = 0;				

//This method will be called when the input has been tokenised
//it's goal is to check that a history prompt has been entered and then execute the command
int check_history(char* tokens[INPUT_LEN]){

	//if no commands, then just return
	//if they have entered an empty input, no need to check as invalid
	if (!tokens[0]) {
		return 1;
	}

	//check the first token is !- first sign of a valid history command
	if (tokens[0][0] == '!') {
		//history doesn't take parameters- invalid history prompt
		if (tokens[1]) {
			printf("History doesn't take parameters!\n");
			return 1; 
		}
		
		//at this point, the command is at least valid whether history prompt or normal command line
    		int pos;	
		if (tokens[0][1] == '!') { // If !! entered
      			pos = (HIST_LEN + head -1) % HIST_LEN; 
    		} else {

			//this code below generates either a positive integer or a negative, deependent on call
      			char num_s[4];
      			strncpy(num_s, tokens[0] + 1, 3);
      			int num = atoi(num_s);
			

			//boundary checking
			//need to include boundary checking for negative num as can't access negative index
      			if (num <= -HIST_LEN || num > HIST_LEN ||num == 0) {
        		printf("You can only call to the last 20 commands!\n"); // TODO: Improve this message
        		return 1;
      			}

			//calculate the correct position
			//issue with this maths need to fix it to work circular

			//positie case
      			if (num > 0) {
        			pos =(num - 1) % HIST_LEN;
      			} 
			//negative case
			else {
        			pos = (HIST_LEN + head + num-1) % HIST_LEN;
      			}	
		}

			  printf("pos check: %d\n", pos);
		          //ensure that this position exists in the array
                          //this would cause an error
                          if (!(history[pos][0])) {
                                  printf("History call does not exits!\n");
                                  return 1;
                          }


		//at this point, if the command isn't a history prompt then it will have returned to main
		//if it is a history prompt, then the maths above has worked out the value to call

		//at this point, we are ready to interpret the command after Finlay's mathematical expertise
		// Subsitute history element into tokens input
		//this is making tokens[i] point the malloced strings in the corrosponding array
    		for (int i = 0; history[pos][i]; i++) {
			tokens[i] = history[pos][i];
		}
		
		//at this point now, tokens conatins the executeable history command
    		return 0;

	}
	//if we get here, the command line should be added to the array
	history_add(tokens);
	return 0;  
}

//This method is called when no history call has been made from the command line
void history_add(char* tokens[INPUT_LEN]) {

	//if circular occurs then have to free the element leaving the array of structs	
	for (int i; history[head][i]; i++) {
		free(history[head][i]);
		history[head][i] = NULL;
	}

	//now we have freed position, need to add the current token input to history
         //current format- array of pointers to strings
         //malloc new space
         //repeat until tokens hit null
         for (int i = 0; tokens[i]; i++) {
                 //here, you will have a current token
                 history[head][i] = malloc((strlen(tokens[i]) + 1) * sizeof(char));
                 strcpy(history[head][i], tokens[i]);
         }

	//head- next available position... circular implementation
	head = (head + 1) % HIST_LEN;
	
}

//frees history when an exit command has been entered to the terminal
//gets access to the array as it's a global variable
void free_hist() {
	for (int i = 0; i< HIST_LEN; i++) {
		for (int j= 0; history[i][j]; j++) {
			free(history[i][j]);
		}
	}
}







