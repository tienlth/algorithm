#include <stdio.h>
#include <string.h>

#define Max 100

typedef struct{
    int weight;
    int value;
    float avgValue;
    char name[40];
}item;

void readFile(char path[20], item itemarr[], int *totalWeight, int *n);
void bubleSort(item itemarr[], int n);
void swap(item *a, item *b){
    item t=*a;
    *a=*b;
    *b=t;
}
void greedpacked(item itemarr[], int packedResult[], int totalWeight, int n);
int main(){
    int i;
    int n;
    int totalWeight;
    int packedResut[Max];
    item itemarr[Max];
    readFile("CaiTui1.txt", itemarr, &totalWeight, &n);
    bubleSort(itemarr, n);
    greedpacked(itemarr, packedResut, totalWeight, n);
    for(i=0;i<n;i++){
        printf("%5d ki%s\n",packedResut[i], itemarr[i].name);
    }
    return 0;
}

void readFile(char path[20], item itemarr[], int *totalWeight, int *n){
    FILE *f=fopen(path, "r");
    int i=0;
    if(f){
        fscanf(f, "%d", totalWeight);
        while(!feof(f)){
            fscanf(f,"%d",&itemarr[i].weight);
            fscanf(f,"%d",&itemarr[i].value);
            itemarr[i].avgValue=(float)itemarr[i].value/itemarr[i].weight;
            fgets(itemarr[i].name, 40, f);
            if(itemarr[i].name[strlen(itemarr[i].name)-1]=='\n')
                itemarr[i].name[strlen(itemarr[i].name)-1]='\0';
            ++i;
            *n=i;
        }
    }
}

void bubleSort(item itemarr[], int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=n-1;j>i;j--){
            if(itemarr[j].avgValue>itemarr[j-1].avgValue)
                swap(&itemarr[j], &itemarr[j-1]);
        }
    }
}

void greedpacked(item itemarr[], int packedResult[], int totalWeight, int n){
    int i, numOfItem;
    for(i=0;i<n;i++){
        packedResult[i]=0;
    }

    i=0;
    while(totalWeight>0 && i<n){
        numOfItem=totalWeight/itemarr[i].weight;

        if(numOfItem>0){
            packedResult[i]=numOfItem;
            totalWeight-=(numOfItem)*itemarr[i].weight;    
        }
        else ++i;
    }
}