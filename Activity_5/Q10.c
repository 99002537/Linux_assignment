#include<stdio.h> 
#include<wait.h> 
#include<signal.h> 
int main() 
{ 
    int pid;
    printf("Enter PID: ");
    scanf("%d",&pid);
    kill(pid, SIGKILL);

 

} 
