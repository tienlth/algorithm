#include <stdio.h>

int binarySearch(int a[], int ,int , int);

int main(){
    int a[]={1,2,3,4,5,6,7,8,9,199};
    printf("%d", binarySearch(a,10,0,199));
    return 0;
}

//by recursion

// int binarySearch(int a[], int n,int L, int x){
//     if(x>a[L+n-1] || x<a[L]) return -1;
//     else {
//         if(n==1) return L;
//         else {
//             if(x>a[L+(n-1)/2]) binarySearch(a, n/2, L+(n+1)/2, x);
//             else binarySearch(a, (n+1)/2, L, x);
//         }
//     }
// }

//by loop

int binarySearch(int a[], int n,int L, int x){
    if(x>a[n-1] || x<a[L]) return -1;
    else {
        while(n>1) {
            if(x>a[L+(n-1)/2]) {
                L+=(n+1)/2;
                n/=2;
            }
            else {
                n=(n+1)/2;
            }
        }
        return L;
    }
}

//both O(logn)