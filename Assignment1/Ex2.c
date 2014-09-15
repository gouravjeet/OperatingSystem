#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>

void square(int x){
   		x=x*x;
   		printf("%d",x);
   	}
char *trimwhitespace(char *str)															//trim whitespace function
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}
void forkMethod(char *args[100],char paths[100],int args_len){
	pid_t pid;  
		// printf( "abc");	  
		pid = fork(); 																	//forking a process
		if(pid<0){
			printf("error !!");
		}	
		if(pid == 0){
			//printf("HCild\n");
			for(int i=0; i<args_len; i++){
				if(args[i]!=NULL){
					args[i] = trimwhitespace(args[i]);
				}
			}
			execv(paths, args);
		}
		else{
			//printf("parent\n");
			int status;
			int termChild = wait(&status);
			//printf("terminated");
		}		 		 
}
void cdProcessing(char *args[100],char paths[100],int args_len){
														// change the directory  we need to provide it with a new path
	
	printf("%s\n", args[1]);
	char *directory = args[1];
	int ret;
	ret = chdir (directory);
	if (ret ==0) 										// to check that chdir() is working or not//
		printf("Your current directory is %s\n",args[1] );
	else
		printf("%s\n","Directory doesnot exists");
}
void runExclamationCommand(char *args[100],char paths[100],int args_len){
	// run the command with ! followed either by the name of command or by the number of the command
	printf("%s\n","run exclamation" );
	char command[100];
	char cmd[100];
	sscanf(args[0] ,"!%s ", command);

	printf("%s\n", command);
	
	if(isdigit(command[0])){								// integer
		int num = atoi(command);
		printf("%d\n", num);
		args[0]=command;
	}
	else if(isalpha(command[0])){								//string
		//printf("%s\n", command);
		args[0]=command;
		printf("%s\n",args[0]);
		printf("%d\n", args_len);
		
		forkMethod(args,paths,args_len);
	}
	
}
void BackgroundProcesses(char *args[100],char paths[100],int args_len){
	// user should execute a process in the background if user enters & at the end of the command
}
void Redirection(char *args[100],char paths[100],int args_len){
	// Redirect the stdin and stdout to a file
}
void IPCPipes(char *args[100],char paths[100],int args_len){
	// output from a process A  is the input to process B
}


void historyPrinting(char history[1000][1000],int history_index, int numbering_index,bool historyflag){
	numbering_index=0;	
	   		if(historyflag==true){
	   			for(int i=history_index;i<1000;i++,numbering_index++){	
	   				if(numbering_index>=0 && numbering_index<10){
	   					printf( "00%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
	   				}
		   			else if(numbering_index>=10 && numbering_index<100)
		   			{
		   				printf( "0%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
		   				
		   			}
		   			else
		   			{
		   				printf( "%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
		   			}
	   				
	   			}
	   			for(int i=0;i<history_index;i++,numbering_index++){
	   				if(numbering_index>=0 && numbering_index<10){
	   					printf( "00%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
	   				}
		   			else if(numbering_index>=10 && numbering_index<100)
		   			{
		   				printf( "0%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
		   				
		   			}
		   			else
		   			{
		   				printf( "%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
		   			}
	   			}
	   		}
	   		else{
	   			for(int i=0;i<history_index;i++,numbering_index++){	
	   				if(numbering_index>=0 && numbering_index<10){
	   					printf( "00%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
	   				}
		   			else if(numbering_index>=10 && numbering_index<100)
		   			{
		   				printf( "0%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
		   				
		   			}
		   			else
		   			{
		   				printf( "%d\t",numbering_index);	
	   					printf( "%s\n", history[i] );	
		   			}
	   			}
	   		}
	   		

}
// void historyComRun(){

// }
int main(){
   		char *choice;
   		char *path[100],*path_temp;
   		char *args[100], *args_temp;
   		char history[1000][1000];
   		bool historyflag=false;
   		char paths[100];
   		int history_index=0,numbering_index=0;
   		DIR * dir[100];
   		int args_len =0, path_len=0;
	    while(1){																		//infinite while loop starting
			args_len = 0;
			path_len=0;
			printf("sardarKaShell-1.0-$ ");
			path_temp=getenv("MYPATH");
			path_temp=strtok(path_temp,":");

			while(path_temp!=NULL)
			{
			   	path[path_len]=path_temp;
			   	path_len++;
			   	path_temp = strtok(NULL,":");
			}
			int s;													
			fgets(choice,1000,stdin);												//history command implementation								
			if(history_index==1000){									     
				historyflag=true;
				history_index=0;									
				strcpy(history[history_index],choice);	
				history_index++;
			}	
			else{
				strcpy(history[history_index],choice);	
				history_index++;
			}   

			if(strncmp(choice,"exit",4)==0 || strncmp(choice,"quit",4)==0){
			printf("bye\n");
			exit(1);
			}
			args_temp=strtok(choice," ");
			while(args_temp != NULL){
				args[args_len] = args_temp;		
				args_len++;
				args_temp=strtok(NULL," ");		
			}
			args[args_len] = NULL;
			args_len ++;
			struct dirent * file;
			
																				
			if(strncmp(args[0],"history",7)==0){										// history printing 
				historyPrinting(history,history_index, numbering_index,historyflag);
				continue;	
			}
		   																// checking for paramater to verify the arguments                     
			for(int i=0;i<path_len;i++){
				dir[i] = opendir( path[i] );
				while ( ( file = readdir( dir [i]) ) != NULL )
				{
				    if(strncmp(file->d_name,args[0],args_len)==0){	
				    	break;
			   		} 
				}
				if(file==NULL){
			    	for(int i=0; i<args_len; i++){
							if(args[i]!=NULL){
								args[i] = trimwhitespace(args[i]);
							}
						} 
			    	if(strncmp(args[0],"cd",2)==0){		
		    			//printf( "found %s\n", args[1] );									// cd command 
						cdProcessing(args,paths,args_len);
						continue;	
					}
					if(strncmp(args[0],"!",1)==0){		
		    			printf( "found %s\n", args[0] );									// Exclamation command 
						runExclamationCommand(args,paths,args_len);
						continue;	
					}	

			    	printf("ERROR: command %s not found\n", args[0]);
			    	
				}
				else{
						

																			//checking various commands in /bin folder
					printf( "found %s\n", file->d_name );
					strcpy(paths,path[0]);
					strcat(paths,"/");
					strcat(paths,file->d_name);
					//printf( "%s", paths);	

					forkMethod(args,paths,args_len);

				}


			}	//for 

		
			
   }//while(1)
}// main 
