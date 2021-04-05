#include <stdio.h>

int main(){
    int items=15;
    int cols=3;
    int a=1;
    int i,j=1;

    for(i=1;j<=items+1;i++){
        if(i>10){
            i=1;
            a+=cols;
            if(j<items) printf("\n\n%");
        }
        for(j=a;j<a+cols && j<=items;j++){
            printf("%3d x%3d = %3d   ",j,i,i*j);

        }
        if(a<=items) printf("\n");
    }

    return 0;
}
