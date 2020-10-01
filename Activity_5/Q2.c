#include <stdio.h>
#include <string.h>
int main(){
    char chr[100];
    FILE *fileptr;
    fileptr=fopen("Variable.txt","r");
    if(fileptr==NULL)
    {
        printf("File failed to open");
    }
    else
    {
         while( fgets ( chr, 100, fileptr ) != NULL ) 
        {
        	printf( "%s", chr ) ;
        }
    }
}
