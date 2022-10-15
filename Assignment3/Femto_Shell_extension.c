#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


#define MAX_INPUT 150
#define MAX_COMMANDS 100
#define MAX_NO_VARAIBLES 150

typedef struct {
    char command[MAX_INPUT];
} History;

typedef struct {
    char name_of_varaible[100];
    char value[100];
} LOCAL_VARIABLES;

int main(int argc, char *argv[])
{
    int status;
    int Enter_Pressed = 0;
    History A[MAX_COMMANDS];
    LOCAL_VARIABLES B[MAX_NO_VARAIBLES];
    int i = 0, max_count = 0;
    int NO_OF_LOCAL_VARIABLE = 0;
    while (1) {
	/*Printing, Get string from User */
	printf("Ana Gahez ya basha: ");
	char str[MAX_INPUT];
	gets(str);
		/********************************/
	/*Handling the pressing Enter */
	if (str[0] == '\0') {
	    Enter_Pressed = 1;
	}
		/****************************/
	/*Storing Commands <Furure Feature of up-arrow> */
	if (str[0] != '\0') {

	    strcpy(A[i].command, str);
	    i++;
	    max_count++;
	}
		/*******************************/
	/*Checking the the command need to set */
	int ret_pid = fork();
	if (ret_pid < 0) {
	    printf("Fork Failed\n");
	} else if (ret_pid > 0) {
	    wait(&status);
	    if (status == -1) {
		printf("Error in child process %d\n", ret_pid);
	    }
	} else if (ret_pid == 0) {
	    int return_execv;
	    if (Enter_Pressed == 1) {
		Enter_Pressed = 0;
	    } else if (Enter_Pressed == 0) {
		/*Token the string */
		char *newargv[10];
		char *token;
		int counter_of_char_for_string = 0;
		int n = 0;
		int SET_OPERATION = 0;
		/*Check this command for setting a local variables or not*/
		while (str[counter_of_char_for_string++] != '\0') {
		    if (str[counter_of_char_for_string] == '=') {
			SET_OPERATION = 1;
		    }
		}
		/***********************************************************/
		/*IF THIS IS FOR SET A LOCAL VARIABLE, STORE TO STRUCT */
		if (SET_OPERATION == 1) {
		    token = strtok(str, "=");
		    strcpy(B[NO_OF_LOCAL_VARIABLE].name_of_varaible, token);
		    token = strtok(NULL, "=");
		    strcpy(B[NO_OF_LOCAL_VARIABLE].value, token);
		    NO_OF_LOCAL_VARIABLE++;
		/********************************************************/
		} else {
		    token = strtok(str, " ");
		    newargv[n++] = token;
		    /*Built-In-Command <SET>*/
		    if (!strcmp(token, "set")) {
			if (NO_OF_LOCAL_VARIABLE == 0) {
			    printf(" \n");
			} else {
			    for (int i = 0; i < NO_OF_LOCAL_VARIABLE; i++) {
				printf("local_vars[%d]: %s = %s\n", i,
				       B[i].name_of_varaible, B[i].value);
			    }
			}
		     /*Built In-Command <EXPORT>*/
		    } else if (!strcmp(token, "export")) {
			int STATE_OF_SEARCHING_IN_LOCAL_VARAIBLE = 0;
			int i;
			token = strtok(NULL, " ");

			for (i = 0; i < NO_OF_LOCAL_VARIABLE; i++) {
			    if (strcmp(B[i].name_of_varaible, token) == 0) {
				STATE_OF_SEARCHING_IN_LOCAL_VARAIBLE = 1;
				break;

			    }
			}
			if (STATE_OF_SEARCHING_IN_LOCAL_VARAIBLE == 1) {
			    int ret_setenv =
				setenv(B[i].name_of_varaible, B[i].value,
				       1);
			    if (ret_setenv == -1) {
				printf
				    ("Error on exporting the variable\n");
			    }
			    STATE_OF_SEARCHING_IN_LOCAL_VARAIBLE = 0;
			} else if (STATE_OF_SEARCHING_IN_LOCAL_VARAIBLE ==
				   0) {
			    printf
				("Could not export [%s],varaible does not exist\n",
				 token);
			}
		    } 
		    /*External Commands*/
		    else {
			while (token != NULL) {
			    token = strtok(NULL, " ");
			    newargv[n++] = token;
			}
			newargv[n] = token;

			return_execv = execvp(str, newargv);
			if (return_execv == -1)
			    printf("This Command is not Found\n");
		    }
		}
	    }
	}
    }
}
