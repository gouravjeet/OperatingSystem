#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void square(int x){
   		x=x*x;
   		printf("%d",x);
   	}
// char* getProcessPath(char * file->d_name){
// 	  pid_t pid;    
// 	  pid = fork();   
// 	  if ( pid < 0 )
// 	  {
// 	    perror( "fork() failed!" );
// 	    return EXIT_FAILURE;
// 	  }


// }   	
int main(){

   		char *choice;
   		char *path[100],*path_temp;
   		char *args[100], *args_temp;
   		char history[5][5];
   		char paths[100];
   		int history_len=0,history_index=0,numbering_index=0;

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
			if(history_len==5){									    //  ->  -> ->				  |   
				strcpy(history[history_index],choice);				//	^						  V
																	//  |<-<- <-<- <-<- <-<- <-<- V
		   		history_index++;
			}	
			else{
				strcpy(history[history_len],choice);	
		   		history_len++;
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
		   struct dirent * file;

		   // history 
		   if(strncmp(args[0],"history",7)==0){
		   		
			   		if(history_len>=5){
			   			numbering_index=0;
			   			for(int i=history_index+1;i<history_len;i++,numbering_index++){	
			   				printf( "%d\t",numbering_index);	
			   				printf( "%s\n", history[i] );	
			   			}
			   			for(int i=0;i<history_index;i++,numbering_index++){
			   				printf( "%d\t", numbering_index);	
			   				printf( "%s\n", history[i] );	
			   			}
			   		}
			   		else{
			   			for(int i=0;i<history_len;i++){	
			   				printf( "%d\t", i);	
			   				
			   				printf( "%s\n", history[i] );	
			   			}
			   		}	
		    }
		   // checking for paramater to verify the arguments
			   for(int i=0;i<path_len;i++){
			   		dir[i] = opendir( path[i] );
			   		while ( ( file = readdir( dir [i]) ) != NULL )
					 	{
						    if(strncmp(file->d_name,args[0],2)==0){

						    	printf( "found %s\n", file->d_name );
						    	strcpy(paths,path[0]);
						    	strcat(paths,"/");
						    	strcat(paths,file->d_name);
						    	printf( "%s\n", paths);	
						    	break;
						    } 
					 	}
				}	 	
				    pid_t pid;    
				    //pid = fork(); 
				    //printf( "%d\n", pid);	

						 //   if ( pid < 0 )
						 //   {
						 //   		perror( "fork() failed!" );
						 //    	return EXIT_FAILURE;
						 //   }
					  //      if ( pid == 0 )   /* child process */
						   // {
						   //  	printf( "CHILD: happy birthday!\n" );
						   //  	sleep( 5 );
						   //  	int rc=execlp(paths,args[0],args[1],NULL);

						   //  	perror( "execlp() failed!" );
	   					// 		return EXIT_FAILURE;

				 		  //  }
				 		   if(1){}
				 		   else{
				 		   																//pid>0 , so we are calling the parent process
				 		   		printf( "PARENT: my child's pid is %d\n", pid );
						  		printf( "PARENT: bye\n" );
						  		#if 1
								    														/* wait for the child to terminate */
								    int status;
								    int child_pid = wait( &status );

								    printf( "PARENT: child %d terminated...", child_pid );

								    if ( WIFSIGNALED( status ) ) 							 /* core dump or kill or kill -9 */
								    {
								      printf( "abnormally\n" );
								    }
								    else if ( WIFEXITED( status ) ) 						/* child called return or exit() */
								    {
								      int rc = WEXITSTATUS( status );
								      printf( "successfully with exit status %d\n", rc );
								    }
								#endif
	    							printf( "PARENT: bye\n" );
	  							
	  							return 0;
				 		   }
   }//while(1)
   
   
}// main 
