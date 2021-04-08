#include <stdio.h>
#include <malloc.h>

typedef struct {
	int CT;
	int curentSum;
	int row,col;
}Node;

int **readFromFile(char path[20], int *);
void triagle_branch(int **, int , Node, int *, int *);
int maxInRow(int *,int );
int main(){
	int n;
	int **triagleArr=readFromFile("tam_giac_so.txt", &n);
	int *result=(int *)malloc(sizeof(int)*n);
	
	int tmpsum=-1;
	int i,tmpCT=0;
	for(i=0;i<n;i++){
		tmpCT+=maxInRow(triagleArr[i],i+1);
	}
	Node triagleNode={tmpCT,0,0,0};

	triagle_branch(triagleArr, n, triagleNode, &tmpsum, result);
	
	for(i=0;i<n;i++){
		printf("dong %d chon %d\n",i+1,result[i]+1);
	}
	printf("tong do dai: %d",tmpsum);
	return 0;
}

int **readFromFile(char path[20], int *n){
	FILE *f=fopen(path, "r");
	if(f){
		int **triagleArr=(int **)malloc(sizeof(int *));
		triagleArr[0]=(int *)malloc(sizeof(int));
		int i=0, j=0;
		while(!feof(f)){
			fscanf(f,"%d",&triagleArr[i][j]);
			j++;
			if(j<=i)
				triagleArr[i]=(int *)realloc(triagleArr[i], sizeof(int)*(j+1));
			else{
				j=0;
				i++;
				triagleArr= (int **)realloc(triagleArr, sizeof(int *)*(i+1));
				triagleArr[i]=(int *)malloc(sizeof(int));
			}
			
		}
		*n=i;
		fclose(f);
		return triagleArr;
	}
	
}

int maxInRow(int *row,int n){
	int i;
	int max=row[0];
	for(i=1;i<n;i++){
		max=max>row[i]?max:row[i];
	}
	return max;
}

void triagle_branch(int **triagleArr, int n, Node triagleNode, int *tmpSum, int *result){
	if(triagleNode.row<n){
		int j,l,col;
		int maxCT=-1, tmpCT;
		int left=triagleNode.col-1; if(left<0) left=0;
		int right=triagleNode.col+1; if(right>triagleNode.row) right=0;
		for(j=left;j<=right;j++){
			tmpCT=triagleNode.curentSum+triagleArr[triagleNode.row][j];
			
			for(l=triagleNode.row+1;l<n;l++){
				tmpCT+=maxInRow(triagleArr[l],l+1);
			}
			if(maxCT<tmpCT){
				maxCT=tmpCT;
				col=j;
			}
			
		}
		
		Node childNode;
		childNode.CT=maxCT;
		childNode.curentSum=triagleNode.curentSum+triagleArr[triagleNode.row][col];
		childNode.row=triagleNode.row+1;
		childNode.col=col;
		
		result[triagleNode.row]=childNode.col;
		triagle_branch(triagleArr, n, childNode, tmpSum, result);
		
		Node childNode2;
		for(j=left;j<=right && j!=col;j++){
			tmpCT=triagleNode.curentSum+triagleArr[triagleNode.row][j];
			for(l=triagleNode.row+1;l<n;l++){
				tmpCT+=maxInRow(triagleArr[l],triagleNode.row+1);
			}
			
			childNode2.CT=tmpCT;
			childNode2.curentSum=triagleNode.curentSum+triagleArr[triagleNode.row][j];
			childNode2.row=triagleNode.row+1;
			childNode2.col=j;
			
			result[triagleNode.row]=childNode.col;
			triagle_branch(triagleArr, n, childNode2, tmpSum, result);
		}

	}
	else {
		if(*tmpSum<triagleNode.curentSum){
			*tmpSum=triagleNode.curentSum;
		}
	}
}
