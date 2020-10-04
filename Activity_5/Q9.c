#include <time.h>
 #include <unistd.h>
 #include<signal.h>
 
  void sig_handler(int signum){
 
  printf("Inside handler function\n");
 
  alarm(2); 
}
int main(){
  
  char cur_time[128];
  {
  time_t      t;
  struct tm*  ptm;
  
  t = time(NULL);
  ptm = localtime(&t);
    
  strftime(cur_time, 128, "%d-%b-%Y %H:%M:%S", ptm);
  
  printf("Current date and time: %s\n", cur_time);
  }
  
  
  signal(SIGALRM,sig_handler); 
 
  alarm(2); 
 
  for(int i=1;i<=2;i++){
 
    printf("%d : Inside main function\n",i);
    pause(); 
}
  return 0;
}
