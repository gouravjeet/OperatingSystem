#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>

void square(int x){
   		x=x*x;
   		printf("%d",x);
   	}

char *trimwhitespace(char *str)
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


int main(){

   		char *choice;
   		char *path[100],*path_temp;
   		char *args[100], *args_temp;
   		char history[10][10];
   		bool historyflag=false;
   		char paths[100];
   		int history_index=0,numbering_index=0;

   		DIR * dir[100];
   		int args_len =0, path_len=0;
	    while(1){
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
			int s;													//		   ||->->->-> ->->->->|
			fgets(choice,1000,stdin);								//  |2| 3| 4| 5| 6| 7| 8| 9|  v
			if(history_index==10){									    //  ->  -> ->				  |   
														//	^						  V
				historyflag=true;
				history_index=0;									//  |<-<- <-<- <-<- <-<- <-<- V
				strcpy(history[history_index],choice);	
				history_index++;
			}	
			else{
				strcpy(history[history_index],choice);	
				history_index++;
			}   
			// exit and quit functionality
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

			// history 
			if(strncmp(args[0],"history",7)==0){
				
		   		if(historyflag==true){
		   			numbering_index=0;
		   			for(int i=history_index;i<10;i++,numbering_index++){	
		   				printf( "%d\t",numbering_index);	
		   				printf( "%s\n", history[i] );	
		   			}
		   			for(int i=0;i<history_index;i++,numbering_index++){
		   				printf( "%d\t", numbering_index);	
		   				printf( "%s\n", history[i] );	
		   			}
		   		}
		   		else{
		   			for(int i=0;i<history_index;i++){	
		   				printf( "%d\t", i);	
		   				printf( "%s\n", history[i] );	
		   			}
		   		}
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
			    	
				}
				else{
					printf( "found %s\n", file->d_name );
					strcpy(paths,path[0]);
					strcat(paths,"/");
					strcat(paths,file->d_name);
					//printf( "%s", paths);	
				}

			}	//for 	
			pid_t pid;  
			// printf( "abc");	  
			pid = fork(); 
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
   }//while(1)
}// main 
