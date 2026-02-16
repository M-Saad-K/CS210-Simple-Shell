#include "../include/input.h"
#include "../include/history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

//declaring a struct called history
//contains an integer for the number in history.. confused if this is the array accessor
//contains pointer to strings- which is the tokenized input (need to malloc and then point seperatley)
struct history {
	int commandNo;			//the command number to be referenced (like an identity) (starts from 1)
	char *commands[INPUT_LEN]; 	//the command line, each part of this array points to a string (token)  
};

//history commandNo start at 1 and continue indefinetly until the death of the program
//this is the integer that the user refers to when calling their command?
//is this what the user calls as the command number
int globalCommand = 1;

//the current head of the struct... ie like an index counter
int head = 0;				//for circular array implementation
int total = 0; 

//need to declare an array of structs, intially empty and of 20 poisitons
//history is an array of tokens, however these are stored locally
//each position in this array is it's own struct which relates to a command
struct history arrHistory[HIST_LEN];


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
		//Finaly code extraction-from github
		//check maths working with all conditions
    		int pos;	
		if (tokens[0][1] == '!') { // If !! entered
      			pos = head;
    		} else {

			//this code below generates either a positive integer or a negative, deependent on call
      			char num_s[4];
      			strncpy(num_s, tokens[0] + 1, 3);
      			int num = atoi(num_s);
			

			//checks id the integer entered is valid
			//boundary checking
      			if (num < -total|| num > total || num < -HIST_LEN || num > HIST_LEN ||
          		    num == 0) {
        		printf("Invalid history number entered!"); // TODO: Improve this message
        		return 1;
      			}
	
			
			//implementation...not circular yet
			//need to make this implementation circular
			//this maths isn't working for my array implementation
			//boundary condition not working
      			if (num > 0) {
        			pos =(num - 1) % HIST_LEN; 
      			} else {
        			pos = (HIST_LEN + head + num) % HIST_LEN;
      			}
		}

		printf("pos check: %d\n", pos);
		//at this point, if the command isn't a history prompt then it will have returned to main
		//if it is a history prompt, then the maths above has worked out the value to call
		//this can be placed into tokens and then passed back to main

		//at this point, we are ready to interpret the command after Finlay's mathematical expertise
		// Subsitute history element into tokens input
		//need to modify this for the tokens and struct
		//this is making tokens[i] point the malloced strings in the corrosponding array

		//array is index 0, pos however starts from 1, so have to less one when accessing the array
    		for (int i = 0; arrHistory[pos].commands[i]; i++) {
			tokens[i] = arrHistory[pos].commands[i];
    		
		}
		
		//at this point now, tokens conatins the executeable history command
		//it will either contain the 
    		return 0;

	}
	//if we get here, the command line should be added to the array
	history_add(tokens);
	return 0;  
}

//This method is called when no history call has been made from the command line
void history_add(char* tokens[INPUT_LEN]) {

	//reset command number for current head
	arrHistory[head].commandNo = 0;

	//if circular occurs then have to free the element leaving the array of structs	
	for (int i; arrHistory[head].commands[i]; i++) {
		free(arrHistory[head].commands[i]);
		arrHistory[head].commands[i] = NULL;
	}


	//need to create a strcut then add it to the correct position in the struct array
	//returns a new struct which can then be added to the head of the array
	//overwrites memory address of old struct with new struct
	arrHistory[head] = create_struct(tokens);
	
	//current number- test
	printf("Struct number: %d\n", arrHistory[head].commandNo);

	//incrementation- does the maths deal with total... ask Finaly
	total++; 

	//head- next available position... circular implementation
	head = (head + 1) % HIST_LEN;
	
}

/**
//This method will execute if a ! has been entered as the first token
int history_exe(char* tokens[INPUT_LEN]) {

	//this method will create a struct, which can then be added to the array of history
	struct create_struct(tokens);

	//need to copy local tokens as they are just pointers and will change
	//repeat for all tokens, token pointer = 1

	//want to create a new position in the struct array
	//declare new struct, fill it, add it to the history array
	//how to know what commandNumber this struct will get
	struct history currentLine;
	int pos = 0;

	//after this, we need to add the current command line to the array of struct
	while (token) {
		//while you have a token, save it locallay
		//want to malloc space for the current token
		commands[0] = malloc(str_copy)
	}
	
	
}
**/

//this method will create a struct which will then be returned to be added to the array of structs
struct history create_struct(char* tokens[INPUT_LEN]) {
 //want to create a new position in the struct array
          //declare new struct, fill it, add it to the history array
          //how to know what commandNumber this struct will get
	  //globalCommand is what the user will type in... it is incremented by 1 each time...
	  //it is what the user will type in to the command line
          struct history currentLine;
	  currentLine.commandNo  = globalCommand;
	  globalCommand++;


	//after this, we need to add the current command line to the array of struct
	//current format- array of pointers to strings
	//malloc new space
	//repeat until tokens hit null
	for (int i = 0; tokens[i]; i++) {
		//here, you will have a current token
		currentLine.commands[i] = malloc((strlen(tokens[i]) + 1) * sizeof(char));
		strcpy(currentLine.commands[i], tokens[i]);
	}

	//at this point we have a new struct, it has the correct global command number 
	//it has the correct array of string pointers as it's variable
	return currentLine;
	}

//frees history when an exit command has been entered to the terminal
//gets access to the array as it's a global variable
void free_hist() {
	for (int i = 0; i< HIST_LEN; i++) {
		for (int j= 0; arrHistory[i].commands[j]; j++) {
			free(arrHistory[i].commands[j]);
		}
	}
}







