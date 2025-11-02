#include <stdio.h>
#include <stdlib.h>



int main(int argc,char* argv[]){

	FILE* fp, *tmp;
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

//Add tasks to the file
	else if(strcmp(argv[1],"add") == 0){
		fp = fopen(".tasks","a");
		if(fp != NULL){
			printf("Enter new task: ");
			fgets(buff,sizeof(buff),stdin);
			//strcat(buff,"\n");
			fputs(buff, fp);
			printf("One task Added\n");
		}
		else{
			printf("Error: Can't add task\n");
			exit(1);
		}
		fclose(fp);
	}
//Delete tasks from the file
	else if(strcmp(argv[1],"delete") == 0){
		if(argc<3){
			printf("argument required <task>\n");
			exit(1);
		}

		int line = atoi(argv[2]);
		int count =0;

		if(line<=0 || line>100){
			printf("Error: Invalid task ID.\n");
			exit(1);
		}


		//open both files
		fp = fopen(".tasks", "r");
		tmp = fopen("tmp","w");

		if(fp == NULL || tmp == NULL){
			printf("couldn't delete task, Error occured\n");
			exit(1);
		}

		//read and write in files
		while(fgets(buff,100,fp) !=NULL){
			count++;
			if(count == line)
				continue;
			fputs(buff, tmp);
		}

		fclose(fp);
		fclose(tmp);

		// rename tmo file and remove original .takss file
		remove(".tasks");
		rename("tmp", ".tasks");

		if(count == 0)
		printf("No taks to delete!\n");
		else printf("One task deleted!\n");
	}

	return 0;
}
