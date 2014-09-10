import java.util.Scanner;
import java.io.*;


public class CacheProgram{


	public static void main(String arg[]) throws IOException{
		int size=11;
		int [] CacheKey= new int[size];
		int [] CacheValues= new int[size];
		int num;
		while(true){
			System.out.println("Enter a number between 1 and 100");
			Scanner sc=new Scanner(System.in);
			num=sc.nextInt();
			ABC abc= new ABC();
			
			int result=abc.calculateCache(num,CacheKey,CacheValues,size);
			System.out.println("Result is "+result);
			
		}
		

	}
}
 class ABC{
	
	
	int calculateAnswer(int num,int size){
		int sum=0;
		try{
			System.out.println("Cache created ");
			for(int i=1;i<=num;i++){
				sum=sum+num;
			}
			Thread.sleep(3000);
			
			
		}
		catch(Exception e){
			System.out.println("Exception");
		}
		return sum;
	}


	int calculateCache(int num,int [] CacheKey,int [] CacheValues,int size){
		
		int location=num%size;
		if(CacheKey[location]==num){
			return CacheValues[location];
		//cache hit	
		}
		else{
			//cache miss
			CacheKey[location]=num;
			CacheValues[location]=calculateAnswer(num,size);
			return CacheValues[location];
		}
	}
	
	
}
	

