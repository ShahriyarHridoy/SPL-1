#include<stdio.h>
int test(int i);

int main(){
    int i, j, k;
    printf("this is a test");
    i=0;
    
    for(i;i<20; i++){
        j=j+i*i;
       
        if(j>350){
            test(i);
            }
         else printf("ok\n");
     }
     return 0;
}

