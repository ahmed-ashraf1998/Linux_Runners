 #include <stdio.h>
 #include<string.h>

int main()
{       
        char str [100];
        while (1)
        {
                printf("Ana Gahez ya basha > ");
                fgets(str,100,stdin);
		if (! strcmp(str,"exit\n"))
		{
			printf("Good Bye :)\n");
			break;
		}
		else
		{
                	printf("You said: %s",str);
		}
        }

        return 0;
} 


