#include <stdio.h>
#include <stdlib.h>



int main(int argc,char* argv[]){

	FILE* fp;
	char buff[100];
	int c;

// Check argument count if less than 2
	if(argc<2){
		printf("Error: argument required.\n");
		exit(1);
	}

/*
// Open .tasks file for operations
	fp = fopen(".tasks", "ar");
	if(fp == NULL){
		printf("can't access tasks\n");
		exit(1);
	}

*/

//show todo list, read from .tasks
	if(strcmp(argv[1], "show") == 0){
		fp = fopen(".tasks", "r");
		if(fp != NULL){
			while((c=fgetc(fp)) != EOF){
				printf("%c", c);
			}
		}
		else{
			printf("Error: Cant't access tasks\n");
			exit(1);
		}
		fclose(fp);
	}
	return 0;
}
