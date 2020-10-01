#include <stdio.h>
#include <string.h>
int main(){
    char ch;
    int num_of_lines,num_of_word,num_of_character,word=0;
    FILE *fileptr;
    fileptr=fopen("Variable.txt","r");
     if(fileptr == NULL) 
  {
    printf("Could not open the file %s\n");
    return 1;
  }
 
  while ((ch = fgetc(fileptr)) != EOF) 
  {
     num_of_character++;
 
    if(ch == ' ' || ch == '\t' || ch == '\0' || ch == '\n') 
    {
      if (word) 
      {
        word = 0;
        num_of_word++;
      }
 
      if(ch = '\0' || ch == '\n')num_of_lines++;
 
    } 
    else 
    {
      word = 1;
    }
  }
   printf(" %d  %d %d\n",num_of_lines,num_of_word,num_of_character);
   return 0;
}