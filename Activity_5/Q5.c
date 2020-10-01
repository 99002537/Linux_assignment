#include <stdio.h>
#include <unistd.h>
int main(){
    char chr;
    printf("Enter code:");
    scanf("%s",&chr);
    system("cc -o ./all.out chr");
    execl("./all.out","all.out",NULL);
    return 0;   
}
