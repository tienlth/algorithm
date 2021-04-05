#include <malloc.h>
#include <stdio.h>

enum type{
    least, great
};
//
void print(int a[], int n){
   int i;
   for(i=0;i<n;i++){
       printf("%d ", a[i]);
   }
   printf("\n");
}

void swap(int *a, int *b){
   int tmp=*a;
   *a=*b;
   *b=tmp;
}

void selectSort(int a[], int n, enum type sortType){
   int i,j;
   for(i=0;i<n-1;i++){
       for(j=i+1;j<n;j++){
           switch (sortType)
           {
               case least: {
                   if(a[i]<a[j]) swap(a+i, a+j);
                   break;
                   }

               case great: {
                   if(a[i]<a[j]) swap(a+i, a+j);
                   break;
               }
           }
       }
   }
}

void insertSort(int a[], int n, enum type sortType){
   int i, j;
   for(i=1;i<n;i++){
       j=i;
       switch (sortType)
       {
           case least: {
               while(a[j]<a[j-1] && j>0){
                   swap(a+j, a+j-1);
                   --j;
               }
               break;
               }

           case great: {
               while(a[j]<a[j-1] && j>0){
                   swap(a+j, a+j-1);
                   --j;
               }
               break;
           }

       }
   }
}

void bubbleSort(int a[], int n, enum type sortType){
   int i, j;
   for(i=0;i<n-1;i++){
       for(j=n-1;j>i;j--){
            switch (sortType)
           {
               case least: {
                   if(a[j]<a[j-1]) swap(a+j, a+j-1);
                   break;
                   }

               case great: {
                   if(a[j]<a[j-1]) swap(a+j, a+j-1);
                   break;
               }

           }
       }
   }
}

int getPivot(int a[], int l, int r){
   int i;
   int flag=0;
   int result=-1;
   for(i=l;i<r && !flag;i++){
       if(a[i]!=a[i+1]) {
           flag=1;
           result=a[i]<a[i+1]?i:i+1;
       }
   }
   return result;
}

int partition(int a[], int l, int r, int pivotIndex, enum type sortType){
   int pivot=a[pivotIndex];
   while(r>=l){
       switch (sortType)
       {
           case great: {
               if(a[l]<pivot){
                   if(a[r]<=pivot) swap(a+r, a+l);
                   else --r;
               }
               else ++l;
               break;
           }

           case least: {
               if(a[l]<=pivot){
                   if(a[r]<pivot) swap(a+r, a+l);
                   else --r;
               }
               else ++l;
               break;
           }
       }
   }
   return l;
}

void quickSort(int a[], int l, int r, enum type sortType){
   if(getPivot(a,l,r)>=0){
      int parpoin=partition(a,l,r,getPivot(a,l,r),sortType);
      quickSort(a,l,parpoin-1,sortType);
      quickSort(a,parpoin,r,sortType);

   }
}

// pivot nho , pivot lon -> min max of arr => bug:
// arr ko chia nho -> de quy ko stop






void mergeSort(int a[], int n, int l,int tmp[], enum type sortType){
    if(n>1){
        mergeSort(a, (n+1)/2, l,tmp, sortType);
        mergeSort(a, n/2, l+(n+1)/2,tmp, sortType);
        int i=l, j=l+(n+1)/2;
        int index=l;

        while(index<=(l+(2*n-1)/2)){
            if(i>(l+(n-1)/2)){
                tmp[index++]=a[j];
                j++;
            }
            else if(j>l+(2*n-1)/2){
                tmp[index++]=a[i];
                i++;
            }
            else{
                 switch (sortType){
                    case great: {
                        if(a[i]<a[j]){
                            tmp[index++]=a[j];
                            j++;
                        }
                        else {
                            tmp[index++]=a[i];
                            i++;
                        }
                        break;
                    }

                    case least: {
                        if(a[i]<a[j]){
                            tmp[index++]=a[j];
                            j++;
                        }
                        else {
                            tmp[index++]=a[i];
                            i++;
                        }
                        break;
                    }
                }
            }
        }

        for(i=l;i<index;i++){
            a[i]=tmp[i];
        }
    }
}

void putDownByLoop(int a[], int n, enum type sortType){
    int i;
    for(i=(n-2)/2;i>=0;i--){
        switch (sortType){
            case great:{
                    if(n%2==0 && i==(n-2)/2){
                    if(a[i]<a[2*i+1]){
                        swap(a+i, a+2*i+1);
                    }
                }
                else if(a[i]<a[2*i+1] || a[i]<a[2*i+2]){ 
                    if(a[2*i+1]<a[2*i+2]) {
                        swap(a+i,a+2*i+2);
                        if(2*i+2<=(n-2)/2) i=2*i+3;
                    }
                    else {
                        swap(a+i, a+2*i+1);
                        if(2*i+1<=(n-2)/2) i=2*i+2;
                    }
                }
                break;
            }
            case least:{
                    if(n%2==0 && i==(n-2)/2){
                    if(a[i]>a[2*i+1]){
                        swap(a+i, a+2*i+1);
                    }
                }
                else if(a[i]>a[2*i+1] || a[i]>a[2*i+2]){ 
                    if(a[2*i+1]>a[2*i+2]) {
                        swap(a+i,a+2*i+2);
                        if(2*i+2<=(n-2)/2) i=2*i+3;
                    }
                    else {
                        swap(a+i, a+2*i+1);
                        if(2*i+1<=(n-2)/2) i=2*i+2;
                    }
                }
                break;
            }
            
        }
    }
}

void putDownByRecusion(int a[], int index, int n, enum type sortType){
    if(index<=(n-2)/2){
        putDownByRecusion(a, 2*index+1, n, sortType);
        putDownByRecusion(a, 2*index+2, n, sortType);

        switch(sortType){
            case great:{
                if(n%2==0 && index==(n-2)/2){
                    if(a[index]<a[2*index+1]) swap(a+index, a+2*index+1);
                }
                else if(a[index]<a[2*index+1] || a[index]<a[2*index+2]){ 
                    if(a[2*index+1]<a[2*index+2]) {
                        swap(a+index,a+2*index+2);
                        putDownByRecusion(a, 2*index+2, n, sortType);
                    }
                    else {
                        swap(a+index, a+2*index+1);
                        putDownByRecusion(a, 2*index+1, n, sortType);
                    }
                }
                break;
            }
            case least:{
                if(n%2==0 && index==(n-2)/2){
                    if(a[index]>a[2*index+1]) swap(a+index, a+2*index+1);
                }
                else if(a[index]>a[2*index+1] || a[index]>a[2*index+2]){ 
                    if(a[2*index+1]>a[2*index+2]) {
                        swap(a+index,a+2*index+2);
                        putDownByRecusion(a, 2*index+2, n, sortType);
                    }
                    else {
                        swap(a+index, a+2*index+1);
                        putDownByRecusion(a, 2*index+1, n, sortType);
                    }
                }
                break;
            }

        }
        
    }
}

void heapSort(int a[], int n, enum type sortType){
    putDownByRecusion(a, 0, n, sortType);
    // putDownByLoop(a,n,sortType);
    while(n>2){
        swap(a, a+n-1);
        --n;
        putDownByRecusion(a, 0, n, sortType);
        // putDownByLoop(a,n,sortType);
    }
    swap(a,a+1);
}
