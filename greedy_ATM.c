#include <stdio.h>
#include <string.h>

typedef struct{
    int number;
    char string[40];
}price;

void readFile(char path[20], price pricearr[4]);
void bubleSort(price pricearr[], int n);
void swap(price *a, price *b){
    price t=*a;
    *a=*b;
    *b=t;
}
void greedATM(price pircearr[], int atmResult[], int money);
int main(){
    int i;
    int n;
    int money=1290000;
    int atmResut[4];
    price pricearr[4];
    readFile("ATM.txt", pricearr);
    bubleSort(pricearr, 4);
    greedATM(pricearr, atmResut, money);
    for(i=0;i<4;i++){
        printf("%-3d to%s\n",atmResut[i], pricearr[i].string);
    }
    return 0;
}

void readFile(char path[20], price pricearr[4]){
    FILE *f=fopen(path, "r");
    int i=0;
    if(f){
        while(!feof(f)){
            fscanf(f,"%d",&pricearr[i].number);
            fgets(pricearr[i].string, 40, f);
            if(pricearr[i].string[strlen(pricearr[i].string)-1]=='\n')
                pricearr[i].string[strlen(pricearr[i].string)-1]='\0';
            ++i;
        }
    }
}

void bubleSort(price pricearr[], int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=n-1;j>i;j--){
            if(pricearr[j].number>pricearr[j-1].number)
                swap(&pricearr[j], &pricearr[j-1]);
        }
    }
}

void greedATM(price pircearr[], int atmResult[], int money){
    int i;
    for(i=0;i<4;i++){
        atmResult[i]=0;
    }

    i=0;
    while(money>0){
        if(money/pircearr[i].number > 0){
            atmResult[i]=money/pircearr[i].number;
            money-=(money/pircearr[i].number)*pircearr[i].number;
        }
        else ++i;
    }
}