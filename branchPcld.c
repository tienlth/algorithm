#include <stdio.h>
#include <malloc.h>

typedef struct {
    int CT;
    int totalTime;
    int work,worker;
}Node;

int **readFile(char path[20], int *n);
void branchWork(int **work, int n, Node workNode,int *tmpTotalTime, int *lockbuffer, int *result);
int* setLock(int );
int main(){
    int i,j;
    int n;
    int **work = readFile("PC lao dong.txt", &n);
    int tmpTotalTime=-1;
    

    int CT=0, minTime=-1;
    for(i=0;i<n;i++){
        minTime=-1;
        for(j=0;j<n;j++){
            if(minTime==-1) minTime=work[i][j];
            else if(minTime>work[i][j]) minTime=work[i][j];
        }
        CT+=minTime;
    }

    Node workNode;
    workNode.totalTime=0;
    workNode.work=0;
    workNode.worker=0;
    workNode.CT=CT;

    int *lockbuffer=setLock(n);

    int *result=(int *)malloc(sizeof(int)*n);
    branchWork(work, n, workNode, &tmpTotalTime, lockbuffer, result);


    for(i=0;i<n;i++){
      printf("cong nhan %d lam cong viec: %d\n",i+1,result[i]+1);
    }
    printf("TONG THOI GIAN: %d ",tmpTotalTime);

    return 0;
}


int ** readFile(char path[20], int *n){
    FILE *f=fopen(path, "r");
    int i=0, j=0;
    if(f){
        fscanf(f, "%d", n);
        int **work=(int **)malloc(sizeof(int *)*(*n));
        int k;
        for(k=0;k<(*n);k++){
            work[k]=(int *)malloc(sizeof(int)*(*n));
        }

        while(!feof(f)){
            fscanf(f, "%d", &work[i][j++]);
            if(j==*n){
                ++i;
                j=0;
            }
        }

        return work;
    }
}

int* setLock(int n){
    int i;
    int *lockbuffer=(int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++){
        lockbuffer[i]=0;
    }
    return lockbuffer;
}

void branchWork(int **work, int n, Node workNode,int *tmpTotalTime, int *lockbuffer,int *result){
    int i,j,l,col;
    int *tmplockbuffer=(int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++) tmplockbuffer[i]=lockbuffer[i];

    if(workNode.worker<n-1){
        Node childNode1;
        int minCT=-1,tmpCT;

        for(i=0;i<n;i++){
            if(!tmplockbuffer[i]){

                tmpCT=workNode.totalTime+work[workNode.worker][i];

                for(j=workNode.worker+1;j<n;j++){
                    int minTime=-1;
                    for(l=0;l<n;l++){
                        if(!tmplockbuffer[l] && l!=i){
                            if(minTime==-1) minTime=work[j][l];
                            else if(minTime>work[j][l]) minTime=work[j][l];
                        }
                    }
                    tmpCT+=minTime;
                   
                }
              
                if(minCT==-1){
                    minCT=tmpCT;
                    col=i;
                }
                else if(minCT>tmpCT){
                    minCT=tmpCT;
                    col=i;
                }
            }
        }
        tmplockbuffer[col]=1;
        childNode1.totalTime=workNode.totalTime+work[workNode.worker][col];
        childNode1.worker=workNode.worker+1;
        childNode1.work=col;
        childNode1.CT=minCT;
        result[workNode.worker]=col;
        branchWork(work,n,childNode1,tmpTotalTime,tmplockbuffer, result);

        Node childNode2;
        for(i=0;i<n;i++){
            if(!lockbuffer[i] && i!=col){

                tmpCT=workNode.totalTime+work[workNode.worker][i];

                for(j=workNode.worker+1;j<n;j++){
                    int minTime=-1;
                    for(l=0;l<n;l++){
                        if(!lockbuffer[l] && l!=i){
                            if(minTime==-1) minTime=work[j][l];
                            else if(minTime>work[j][l]) minTime=work[j][l];
                        }
                    }
                    tmpCT+=minTime;
                }
                childNode2.CT=tmpCT;
                int *tmplockbuffer2=(int *)malloc(sizeof(int)*n);
                for(j=0;j<n;j++) tmplockbuffer2[j]=lockbuffer[j];

                if(childNode2.CT<*tmpTotalTime){
                    tmplockbuffer2[i]=1;
                    childNode2.totalTime=workNode.totalTime+work[workNode.worker][i];
                    childNode2.worker=workNode.worker+1;
                    childNode2.work=i;
                    result[workNode.worker]=i;
                    branchWork(work, n, childNode2, tmpTotalTime, tmplockbuffer2, result);

                }

            }
        }
       

    }
    else {
        if(*tmpTotalTime==-1){
            for(i=0;i<n;i++){
                if(!tmplockbuffer[i]) {
                    workNode.totalTime+=work[n-1][i];
                    result[n-1]=i;
                }
            }
            *tmpTotalTime=workNode.totalTime;
        }
        else{
            for(i=0;i<n;i++){
                if(!tmplockbuffer[i]){
                    workNode.totalTime+=work[n-1][i];
                    result[n-1]=i;
                }
            }
            if(*tmpTotalTime>workNode.totalTime){
                *tmpTotalTime=workNode.totalTime;
            }
        }
        
    }
}