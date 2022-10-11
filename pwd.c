#include "stdio.h"
#include <unistd.h>


#define MAX_PARAMETER 100
int main(int argc, int *argv[])
{

    char buff[MAX_PARAMETER];
    if (argc != 1) {
	printf("MultiPle Argument, No Arguments are needed");
    } else {
	char *state = getcwd(buff, MAX_PARAMETER);
	if (state != NULL) {
	    printf("%s\n", buff);
	} else {
	    printf("NULL POINTER\n");
	}

    }


    return 0;
}
