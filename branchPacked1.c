#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
    int weight, value;
    float price;
    char name[40];
    int selection;
}item;

typedef struct {
    int remainWeight;
    float totalValue;
    item curentItem;
    int numOfCurentItem;
    float topValue;
}PackedNode;

item *readFromFile(char path[20], int *totalWeight, int *n);
void bubbleSort(item *items, int n);
void swap(item *a, item *b){
    item tmp=*a;
    *a=*b;
    *b=tmp;
}
void  branchPacked(item *items,int itemIndex, int n, PackedNode Node, float *key, item *answer);

int main(){
    int i;
    int n, totalWeight;
    float key=-1;
    item *items=readFromFile("CaiTui1.txt", &totalWeight, &n);
    item *answer =(item*)malloc(sizeof(item)*n);
    // for(i=0;i<n;i++) answer[i]=items[i];

    bubbleSort(items, n);

    PackedNode Node={totalWeight,0, items[0],0,totalWeight*items[0].price};

    branchPacked(items, 0, n, Node, &key, answer);

    printf("Trong Tai :%5d\n",totalWeight);
    printf("|%15s|%15s|%15s|%25s|%15s|\n","khoi luong   ","gia tri   ", "Don gia   ", "ten   ", "so luong   ");
    for(i=0;i<n;i++){
        printf("|%15d|%15d|%15.1f|%25s|%15d|\n",answer[i].weight, answer[i].value,answer[i].price, answer[i].name,answer[i].selection);
    }
    printf("Tong Gia Tri :%15.2f",key);


    return 0;
}

item *readFromFile(char path[20], int *totalWeight, int *n){
    FILE *f = fopen(path, "r");
    if(f){
        fscanf(f,"%d ", totalWeight);
        item *itemarr=(item *)malloc(sizeof(item));
        int i=0;
        while(!feof(f)){
            fscanf(f,"%d%d",&itemarr[i].weight, &itemarr[i].value);
            itemarr[i].price=(float)itemarr[i].value/itemarr[i].weight;
            fgets(itemarr[i].name, 40, f);
            if(itemarr[i].name[strlen(itemarr[i].name)-1] =='\n') 
                itemarr[i].name[strlen(itemarr[i].name)-1] = '\0';
            i++;
            itemarr=(item *)realloc(itemarr, sizeof(item)*(i+1));
        }
        fclose(f);
        *n=i;
        return itemarr;
    }
}

void bubbleSort(item *items, int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=n-1;j>i;j--){
            if(items[j].price>items[j-1].price)
                swap(items+i, items+j);
        }
    }
}

void  branchPacked(item *items,int itemIndex, int n, PackedNode Node, float *key, item *answer){
    if(itemIndex<n){
        int itemsnum;
        if(Node.topValue>*key){
            PackedNode childNode1;
            childNode1.numOfCurentItem=Node.remainWeight/Node.curentItem.weight;
            childNode1.totalValue=childNode1.numOfCurentItem*Node.curentItem.value+Node.totalValue;
            childNode1.remainWeight=Node.remainWeight - Node.curentItem.weight*childNode1.numOfCurentItem;
            
            items[itemIndex].selection=childNode1.numOfCurentItem;

            childNode1.curentItem=items[itemIndex+1];
            childNode1.topValue=childNode1.remainWeight*childNode1.curentItem.price+childNode1.totalValue;
            itemsnum=childNode1.numOfCurentItem;
            branchPacked(items, itemIndex+1, n, childNode1, key, answer);
        }
            int k=itemsnum-1;
            int j;
            PackedNode childNode2;
            for(j=k;j>=0;j--){
                childNode2.numOfCurentItem=j;

                items[itemIndex].selection=childNode2.numOfCurentItem;

                childNode2.totalValue=childNode2.numOfCurentItem*Node.curentItem.value+Node.totalValue;
                childNode2.remainWeight=Node.remainWeight - Node.curentItem.weight*childNode2.numOfCurentItem;

                childNode2.curentItem=items[itemIndex+1];
                childNode2.topValue=childNode2.remainWeight*childNode2.curentItem.price+childNode2.totalValue;

                if(childNode2.topValue>*key){
                    branchPacked(items, itemIndex+1, n, childNode2, key, answer);
                }
            }
    }
    else {
        if(Node.totalValue>*key){
            *key=Node.totalValue;
            int i=0;
            for(i=0;i<n;i++)
                answer[i]=items[i];
        }
    }
}