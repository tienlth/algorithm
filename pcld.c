#include <stdio.h>

#define MAXROW 10
#define MAXCOLUM 10

void readFile(char path[20], int *n, int work[][MAXCOLUM]);
int greedywork(int work[][MAXCOLUM], int n, int workResult[]);
int main(){
    int i,j;
    int n;
    int work[MAXROW][MAXCOLUM];
    int workResult[MAXROW];

    readFile("PC lao dong.txt", &n, work);
    int totaltime = greedywork(work, n, workResult);

    for(i=0;i<n;i++){
        printf("cong nhan %d lam cong viec %d\n",i+1 , workResult[i]);
    }
    printf("Tong thoi gian la %d", totaltime);
    return 0;
}


void readFile(char path[20], int *n, int work[][MAXCOLUM]){
    FILE *f=fopen(path, "r");
    int i=0, j=0;
    if(f){
        fscanf(f, "%d", n);
        while(!feof(f)){
            fscanf(f, "%d", &work[i][j++]);
            if(j==*n){
                ++i;
                j=0;
            }
        }
    }
}

int greedywork(int work[][MAXCOLUM], int n, int workResult[]){
    int i,j,totalTime = 0;
    int k;
    int min, key=0, tmpj;
    int deleted=-1;
    for(i=0;i<n;i++){
        key=0;
        for(j=0;j<n;j++){
            if(work[i][j]!=deleted && !key){
                min=work[i][j];
                workResult[i]=j+1;
                key=1;
            }
            if(work[i][j]!=deleted && min >= work[i][j]){
                min = work[i][j];
                workResult[i]=j+1;
                tmpj=j;
            }
        }
        for(k=0;k<n;k++)
            work[k][tmpj]=deleted;
        totalTime += min;
    }

    return totalTime;
}