#include <stdio.h>
#include <string.h>
int main(){
    char dataToRead[100];
    FILE *fileptr;
    FILE *fileptr1;
    fileptr=fopen("Variable.txt","r");
    fileptr1=fopen("Variable1.txt","w");
if(fileptr1!=NULL){
    while( fgets ( dataToRead, 100, fileptr ) != NULL ) {
        {
      	
            if ( strlen (  dataToRead  ) > 0 ) 
            {
				// writing in the file2 using fputs()
                fputs(dataToRead, fileptr1) ;
            }
        }
        // Closing the file using fclose()
        fclose(fileptr) ;
        printf("Data successfully read from variable text file.txt\n");
        fclose(fileptr1) ;
        printf("The Variable1 text file is now closed. \n") ;
        printf("Data is successfully written into Variable1.txt \n");
        printf("The file2 is now closed. \n") ;
        return 0;
    }

  }
}
