#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void square(int x){
   		x=x*x;
   		printf("%d",x);
   	}
int main(){

   
	   while(1){
		   getenv("MYPATH");
		   int s;
		   scanf("%d",&s);
		   
		   exit(1);
		   pid_t pid;
		   printf("%d\n",getpid());
		    
		   if(s==1){
		   	pid=fork();
		   }
		   if(pid<0){
		   	printf("Fork Failed");
		   	return -1;
		   }
		   else if(pid==0){
		   	printf("%s\n","I m the child");
		   	sleep(3000);
		   }
		   else if(pid>0) {
		   	
		   	printf("%s\n", "Im the parent");
		   	
		   	sleep(3000);
		   }
   }
   
   
   
}
