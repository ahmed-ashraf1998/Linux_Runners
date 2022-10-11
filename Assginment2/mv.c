#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "string.h"
#include <unistd.h>
#include <stdio.h>



#define MAX_SIZE_BUFF  100
int main(int argc, char *argv[])
{

    if (argc != 3) {
	printf("Need to mention the soruce file and its destination");
	return -1;
    }
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
	printf("File that need to be moved is not existed");
	return -1;
    }

    strcat(argv[2], argv[1]);
    int fd2 =
	open(argv[2], O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd2 == -1) {
	printf
	    ("Invaild Path, YOu should provide destination with \\ at the end");
	return -1;
    }

    int count;
    char buff[MAX_SIZE_BUFF];
    while ((count = read(fd1, buff, MAX_SIZE_BUFF)) != 0) {
	int write_erro = write(fd2, buff, count);
	if (write_erro == -1) {
	    printf("Error in writing\n");
	}
    }

}

close(fd1);
remove(argv[1]);
close(fd2);

return 0;
}
