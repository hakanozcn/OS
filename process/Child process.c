#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<wait.h>
int Reverse(int  data)
{
if(data<0)
return -1;
else
{
int output=0;
int remainder;
  while(data != 0)
                                                 {
                                                        remainder = data%10;
                                                        output = output*10 + remainder;
                                                        data /= 10;
                                                 }

return output;
}

}
int main(void)
 {      
        char buf[1024] = {} ;
        char input[50] = {};
        
        int output = 0;
        pid_t pid;
        int i =0;
        int data;
        int Rp[2];
        int Wp[2];
       
        
       

        if (pipe(Rp) == -1) { fprintf(stderr, "Pipe Failed" );
        return 1;}
        if (pipe(Wp) == -1) { fprintf(stderr, "Pipe Failed" );
        return 1; }

        pid=fork();
        if(pid==-1)
        {
                fprintf(stderr, "fork Failed" );
                 return 1;   
        }
        while(i<1)
        {
                i = i+1;
                
    
                if(pid==0)
                { 
       

                        close(Rp[1]);
                        close(Wp[0]);
                        if(read(Rp[0],buf,sizeof(buf)) < 0)
                        {
                            break;
                        }
                        printf("Child Process is Talking >> Data Received from Parent Process %s\n",buf);
                        
                        int data = atoi(buf);

                                


                        output=Reverse(data);    
                        printf("Child Process  >> The data was reversed %d\n",output);
                        sprintf(buf,"%d",output);
                        
                        
                        printf("Child Process  >> Data Sent to the Parent Process %s\n",buf);
                        if(write(Wp[1],buf,strlen(buf)+1) < 0)
                        {
                            break;
                        }
                    

                }
                else
                {
                        close(Rp[0]);
                        close(Wp[1]);
                        printf("Parent Process >> Data entry from the user:");
                        fgets(input, 50, stdin);
                        printf("Parent Process >> Data Sent to the Child Process  %s\n",input);
                        if(write(Rp[1],input,strlen(input)+1) < 0)
                        {
                            break;
                        }        

                        if(read(Wp[0],buf,sizeof(buf)) < 0)
                        {
                            break;
                        }
                        printf("Parent Process >> Result is  %s\n",buf);
                        
                                             
                        fflush(stdin);
                            
                        
                        
                }

        }
        close(Rp[1]);
        close(Wp[0]);
        close(Rp[0]);
        close(Wp[1]);
        return 0;
}
