#include <stdio.h>
#include "C:\Users\ASUS\Desktop\algorihsm\sortlib.c"

int main(){
    int arr[]={13,456,234,45,22,23,345,3423,46,67,34,346,112,66,32,1145,78,93,89,72,483,58,29,19,234,89,134,348,99,873};
    // int arr[]={5,6,2,2,10,12,9,10,8,3};
    print(arr, 30);
    // int tmp[30];
    // mergeSort(arr,30,0,tmp, great);
    heapSort(arr,30,least);
    print(arr, 30);

    return 0;
}




