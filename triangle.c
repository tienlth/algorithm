#include <stdio.h>
#include <malloc.h>


int **readFile(char path[20], int *n);
int **triangle_greedy(int **arr ,int n, int *sum);

int main(){
    int n,i,j;
    int sum;
    int **a=readFile("tam_giac_so.txt", &n);
    int **result=triangle_greedy(a,n,&sum);

    for(i=0;i<n;i++){
        if(i==n-1) printf("(%d %d)",result[i][0],result[i][1]);
        else printf("(%d %d)->",result[i][0],result[i][1]);
    }
    printf("\ntotal: %d",sum);

    return 0;
}


int **readFile(char path[20], int *n){
    FILE *f=fopen(path, "r");

    int i=0, j=0;

    int **work=(int **)malloc(sizeof(int*));
    work[0] = (int *)malloc(sizeof(int));
        
    if(f){
        
        while(!feof(f)){

            

            fscanf(f, "%d", &work[i][j++]);

            if(j>i){
                ++i;
                j=0;
                work = (int **)realloc(work,sizeof(int *)*(i+1));
                work[i] = (int *)malloc(sizeof(int));
            }
            else work[i] = (int *)realloc(work[i], sizeof(int)*(j+1));
        }
        *n=i;
        fclose(f);
    }
    return work;
}
int **triangle_greedy(int **arr ,int n, int *sum){
    *sum=arr[0][0];
    int **result=(int **)malloc(sizeof(int*));
    result[0]=(int *)malloc(sizeof(int)*2);

    result[0][0]=1;
    result[0][1]=1;

    int i=0,j=0;
    while(i<n){
        if(j==0){
            ++i;
            j=arr[i][0]>arr[i][1]?0:1;
        }
        else{
            ++i;
            if(arr[i][j]>=arr[i][j-1]){
                j=arr[i][j]>arr[i][j+1]?j:j+1;
            }
            else if(arr[i][j]<arr[i][j-1]){
                j=arr[i][j-1]>arr[i][j+1]?j-1:j+1;
            }
        }

        if(i<n){
            (*sum)+=arr[i][j];
            result = (int **)realloc(result, sizeof(int *)*(i+1));
            result[i]=(int *)malloc(sizeof(int)*2);
            result[i][0]=i+1;
            result[i][1]=j+1;
        }
    }
    return result;
}