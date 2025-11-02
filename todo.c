#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 100
#define TOTAL_TASK 200


void showtask(FILE *fp, char buff[]);
void addtask(FILE *fp, char buff[]);

int main(int argc,char* argv[]){

	FILE* fp, *tmp;
	char buff[BUFF_SIZE];
	int c;

// Check argument count if less than 2
	if(argc<2){
		printf("Error: argument required.\n");
		exit(1);
	}

//show todo list, read from .tasks
	if(strcmp(argv[1], "show") == 0){
		showtask(fp, buff);
	}

//Add tasks to the file
	else if(strcmp(argv[1],"add") == 0){
		addtask(fp, buff);
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
		while(fgets(buff,BUFF_SIZE,fp) !=NULL){
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

void showtask(FILE * fp, char buff[]){

	fp = fopen(".tasks", "r");
	if(fp == NULL){
		printf("Can't Access Tasks!");
		exit(1);
	}

	printf("---------------  YOUR TO-DO  APP --------------\n\n");
	printf("TASKS :\n");

	int i=1;
	while(fgets(buff, BUFF_SIZE, fp) != NULL){
		printf("%d. %s",i, buff);
		i++;
	}
	fclose(fp);
}

void addtask(FILE *fp, char buff[]){
	fp = fopen(".tasks", "a");
	if(fp == NULL){
		printf("Can't add task!\n");
		exit(1);
	}

	printf("	ENTER NEW TASK : ");
	fgets(buff, BUFF_SIZE, stdin);

	fputs(buff, fp);

	printf("•••••••••• New Task Added ••••••••••\n");
	fclose(fp);
}
