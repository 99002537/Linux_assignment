#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
void parent(char *a, char **arg)
{
    while(*a!='\0'){
        while (*a == ' ' || *a == '\t' || *a == '\n'){
               *a++ = '\0';  }  
          *arg++ = a;        
          while (*a != '\0' && *a != ' ' && *a != '\t' && *a != '\n'){
               a++;            
     }
    }
     *arg = '\0';                
}   
void  execute(char **arg)
{
     pid_t  pid;
     int    status;
    
     if ((pid = fork()) < 0) {    
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {         
          if (execvp(*arg, arg) < 0) {   
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                
          while (wait(&status) != pid);
     }
}
void  main(void)
{
     char  a[1024];            
     char  *arg[64];             
    
     while (1) {                  
          printf("Shell -> ");   
          gets(a);             
          printf("\n");
          parent(a,arg);     
          if (strcmp(arg[0], "exit") == 0){
               exit(0);  }       
          execute(arg);          
     }
}