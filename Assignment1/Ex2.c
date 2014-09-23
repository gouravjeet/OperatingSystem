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
#include <fcntl.h>

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



// this method is for the checking the paramntere defined and if the command is ther , it will return the path of the file to be exected
// otherwise return something to distinguish that it is an error.
char* checkingParamter(char *args[100],char paths[100],int args_len,char *path[100],DIR * dir[100],int path_len, struct dirent * file,char *newpath){
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
	    	printf("ERROR: command %s not found\n", args[0]);
	    	newpath=NULL;  	
		}
		else{
			//checking various commands in /bin folder
			printf( "found %s\n", file->d_name );
			strcpy(paths,path[0]);
			strcat(paths,"/");
			strcat(paths,file->d_name);
			//printf( "%s", paths);	
			newpath="/bin";
		}
	} 
	
	return newpath;
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
	//printf("%s\n", args[1]);
	char *directory = args[1];
	int ret;
	ret = chdir (directory);
	if (ret ==0) 										// to check that chdir() is working or not//
		printf("Your current directory is %s\n",args[1] );
	else
		printf("%s Directory doesnot exists\n",args[1]);
}

void historyChecking(char history[1000][1000], int *history_index,char *choice,bool historyflag){
	
	// History is calculated here, so at each step, cmd are added to the history array so that we can get that later on
			//===========================================================================================================
	if(*history_index==1000){									     
				historyflag=true;
				*history_index=0;									
				strcpy(history[*history_index],choice);	
				*history_index=*history_index+1;
			}	
	else{
		strcpy(history[*history_index],choice);	
		*history_index=*history_index+1;
	}   

}
void PreArgsProcessing(char *args[100],char paths[100],int *args_len,char *choice,char *args_temp){
			//printf("%d\n", *args_len);
			*args_len = 0;
			//printf("Here is CHoice :    \n\n\n\n Choice %s", choice);
			args_temp=strtok(choice," ");
			while(args_temp != NULL){
				args[*args_len] = args_temp;		
				*args_len=*args_len+1;
				args_temp=strtok(NULL," ");		
			}
			//args[*args_len-1] = trimwhitespace(args[*args_len-1]);
			args[*args_len] = NULL;
			*args_len=*args_len+1;
			//printf("Length of all the args :  ------------------>>>     %d\n", *args_len);
			for(int i=0; i<*args_len; i++){
				printf("These are args: %d %s\n", i, args[i]);
			}
}
void runExclamationCommand(char *args[100],char paths[100],int args_len,char history[1000][1000],char *choice,char *args_temp){
	// run the command with ! followed either by the name of command or by the number of the command
	char temp4[1000];
	memset(temp4, ' ', 1000);
	printf("%s\n","run exclamation" );
	char command[100];
	char cmd[100];
	sscanf(args[0] ,"!%s ", command);
	printf("%s\n", command);
	if(isdigit(command[0])){								// integer
		int num = atoi(command);
		printf("%d\n", num);
		//args[0]=historyChecking(history);
		
		forkMethod(args,paths,args_len);
	}
	else if(isalpha(command[0])){								//string
		//printf("%s\n", command);
		args[0]=command;
		//printf("%s\n",args[0]);
		strcpy(temp4,args[0]);
		printf("%d\n", args_len);
		for(int o=0;0<args_len-2;o++){
			strcat(temp4,args[o]);
			strcat(temp4," ");
		}
		strcpy(choice,temp4);
		choice=trimwhitespace(choice);
		PreArgsProcessing(args,paths,&args_len,choice,args_temp);
		//forkMethod(args,paths,args_len);
	}	
}
void BackgroundProcesses(char *args[100],char paths[100],int args_len){
	printf("background process");
	// user should execute a process in the background if user enters & at the end of the command
}
void Redirection(char *args[100],char paths[100],int args_len,char *choice,char *args_temp, int *flag_to){
	// Redirect the stdin and stdout to a file
	// case 1: cmd1 < stdout.text  stdout is input to cmd1 
	     // redirects data from stdout to stdin for cmd1
		 // closes fd-0
		 // open a file with fd 0
		 // child process and by default it reads from stdin ie fd-0
	char temp2[1000];
	char temp3[1000];
	char *pn;
	memset(temp2, ' ', 1000);
	memset(temp3, ' ', 1000);
	char temp_buffer[100];
	printf("%d\n", args_len);
	printf("dara" );
	for(int i=0;i<args_len-1;i++){
		if(strncmp(args[i],"<",1)==0){
			printf("Redirect from file.\n");
			//int fd_stored=dup(0);
			//close(0);
			int fname;
			args[i+1] = trimwhitespace(args[i+1]);
			fname=open(args[i+1],O_RDONLY,0660); 					//filename
			char temp_buffer[1000];
			int fileSize=read(fname,temp_buffer,100);
			temp_buffer[fileSize] = '\0';
			memcpy ( temp_buffer, temp_buffer, fileSize );
			char* temp[100];
			// create a copy of args and then update it with the new value --> cmd1 args and then run it using execv
			//strcpy(args[0],temp);
			strcpy(temp2, args[0]);
			printf("%d\n", i);
			for(int j=1;j<i;j++){
				strcat(temp2," ");
				strcat(temp2,args[j]);
			}
			strcat(temp2,temp_buffer);
			strcpy(choice,temp2);
			char * a = trimwhitespace(temp_buffer);
			choice = trimwhitespace(choice);

			
			PreArgsProcessing(args,paths,&args_len,choice,args_temp);
			//printf(" temp2 :: %s  a value %s choice : %s", temp2, a, choice);
			//pn=checkingParamter(args,paths,args_len,path,dir,path_len,file,pn);
			// if(newpath==NULL){
			// 	}
			// 	else {
			// 		forkMethod(args,paths,args_len);
			// 	}	
			// if(fork()==0){
			// 	//execv(paths,args);
			// }
			// for(int k=i;k<args_len-2;k++){   //set arguments after < equal to null
			// 	args[k]=NULL;
			// }
			//strncmp(args[i],">>",2);
			printf("breaking\n");
			return;
		}
		//printf("ss\n");
			// case 2: cmd1 >> stdout.txt  append the response of the command 1 to teh text file
		else if(strncmp(args[i],">>",2)==0){
			printf("Append to file");
			*flag_to=1;
			int dv=dup(1);
			char * b;
			
			//close(1);
			open(args[i+1],O_RDWR | O_CREAT, 0660);
			pid_t pid;  
			//printf( "abc");
			// strcpy(temp3, args[0]);
			// strcat(temp3, " ");
			for(int m=0;m<i-1;m++){
				printf("argument are %s\n",args[m] ); 
				strcat(temp3, args[m]);
				strcat(temp3, " ");
			}
			strcat(temp3, args[i-1]);
			strcpy(choice,temp3);
			choice = trimwhitespace(choice);
			printf("%s\n", choice);
			PreArgsProcessing(args,paths,&args_len,choice,args_temp);	  
			pid = fork(); 																	//forking a process
			if(pid<0){
				printf("error !!");
			}	
			if(pid == 0){
				printf("HCild\n");
				for(int i=0; i<args_len; i++){
					if(args[i]!=NULL){
						args[i] = trimwhitespace(args[i]);
					}
				}
				execv(paths, args);
			}
			else{
				printf("parent\n");
				int status;
				int termChild = wait(&status);
				//printf("terminated");
				dup2(dv,1);
			}
			return;								
		}
			// case 3 : cmd2 > stdout.text  override the response of the command 1 to the text file
			// paths[0] paths[1] paths[2]
			     // first release fd 1 and then open a file with fd 1 and then open a child process and 
			     // then the program writes to stdout ie fd 1 and hence in this case it is file 
		else if(strncmp(args[i],">",1)==0){						
			*flag_to=1;
	 		printf("Redirect to file");
			int dv=dup(1);
			char * b;
			
			//close(1);
			open(args[i+1],O_RDWR | O_CREAT, 0660);
			pid_t pid;  
			strcpy(temp3, args[0]);
			strcat(temp3, " ");
			for(int m=1;m<i;m++){
				printf("argument are %s\n",args[m] ); 
				strcat(temp3, args[m]);
				strcat(temp3, " ");
			}
			strcpy(choice,temp3);
			choice = trimwhitespace(choice);
			printf("%s\n", choice);
			PreArgsProcessing(args,paths,&args_len,choice,args_temp);	  
			pid = fork(); 																	
			if(pid<0){
				printf("error !!");
			}	
			if(pid == 0){
				printf("HCild\n");
				for(int i=0; i<args_len; i++){
					if(args[i]!=NULL){
						args[i] = trimwhitespace(args[i]);
					}
				}
				execv(paths, args);
			}
			else{
				printf("parent\n");
				int status;
				int termChild = wait(&status);
				//printf("terminated");
				dup2(dv,1);
			}
		return;								
		}
		printf("Hereend" );	
	}
	printf("Hereend" );	
}
// this method will calculated output according to pipes
void IPCPipes(char *args[100],char paths[100],int args_len){
	// output from a process A  is the input to process B
	// ls -la | ps
	// 
	printf("%s\n", "we are in pipes");
}

// this method will print the history 
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
int main(){
             			// choice is the first argument
   		char *path[100],*path_temp;
   		char *args_temp;
   		char history[1000][1000];
   		char *newpath;
   		bool historyflag=false;
   		char paths[100];
   	 	
   	 	int ttoo = 1;
   		int history_index=0,numbering_index=0;
   		DIR * dir[100];
   		int f=0;
   		int args_len =0, path_len=0;
	    while(1){
	  //   	while(args[f]!=NULL){   // Setting the default value after each iteration as null
			// 	args[f]=NULL;
			// 	printf("%s\n", args[f]);
			// 	f++;
			// }
			char *choice=malloc(1000);
			char *args[100];
	    	int flag = 0;
   	 		int flag_to=0;																		//infinite while loop starting
			args_len = 0;
			path_len=0;

			printf(">>>>>>>");
			path_temp=getenv("MYPATH");
			path_temp=strtok(path_temp,":");
			
			while(path_temp!=NULL)  									// tokenizing paths ie different paths separated by : 
			{
			   	path[path_len]=path_temp;
			   	path_len++;
			   	path_temp = strtok(NULL,":");
			}
			int s;
			//printf("%s before\n",choice);
			fgets(choice,1000,stdin);
			choice=trimwhitespace(choice);
			// if(choice==){
			// 	continue;
			// }
			//printf("%s\n",choice);
			PreArgsProcessing(args,paths,&args_len,choice,args_temp);
			historyChecking(history,&history_index,choice, historyflag);
			struct dirent * file;
			//================================================================================================================
																				
			if(strncmp(args[0],"history",7)==0){										// history printing 
				historyPrinting(history,history_index, numbering_index,historyflag); // when you want to print history
				continue;	
			}
			//===============================================================================================================
			if(strncmp(args[0],"exit",4)==0 || strncmp(args[0],"quit",4)==0){    // exit or bye
				printf("bye\n");
				exit(0);
			}
			// if(strncmp(args[args_len-2],"&",1)==0){		
   //  			printf( "found %s\n", args[args_len-2] );									//Background command 
			// 	BackgroundProcesses(args,paths,args_len);
			// 	flag=1;
			// 	break;	
			// }
			// 												// checking for paramater to verify the arguments                     
		 // 	else if(strncmp(args[0],"cd",2)==0){		
	  //   			//printf( "found %s\n", args[1] );									// cd command 
			// 		cdProcessing(args,paths,args_len);
			// 		break;	
			// }
			// checking for various commands
			for(int i=0;i<args_len-1;i++){
				if(strncmp(args[i],"!",1)==0){		
	    			printf( "found %s\n", args[0] );									// Exclamation command 
					runExclamationCommand(args,paths,args_len,history,choice,args_temp);
					flag=1;
					break;	
				}
				if(strncmp(args[i],"<",1)==0 || strncmp(args[i],">",1)==0 || strncmp(args[i],">>",2)==0){  // redirection
					Redirection(args,paths,args_len,choice,args_temp,&flag_to);
					flag=1;
					break;
				}
				
				if(strncmp(args[i],"|",1)==0){		
					//printf( "found %s\n", args[1] );									// pipe command 
					IPCPipes(args,paths,args_len);
					flag=1;
					break;
				}
			//printf("%d\n",i);
			}
			
			if(flag & !flag_to){
				// the commands left at the end will be executed
				//printf("%d\n",flag );
				newpath=checkingParamter(args,paths,args_len,path,dir,path_len,file,newpath);
				//printf("%s\n", newpath);
				if(newpath==NULL){
				}
				else {
					forkMethod(args,paths,args_len);
				}	
			}
			if(!flag & !flag_to){
				// the commands left at the end will be executed
				//printf("%d\n",flag );
				newpath=checkingParamter(args,paths,args_len,path,dir,path_len,file,newpath);
				//printf("%s\n", newpath);
				if(newpath==NULL){
				}
				else {
					forkMethod(args,paths,args_len);
				}	
			}		
			free(choice);
			// for(int i=0;args_len-2;i++){   // Setting the default value after each iteration as null
			// 	args[i]=NULL;
			// }	 
   }//while(1)
}// main 
