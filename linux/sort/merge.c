#include<stdio.h>
#define N 1000
int mid[N+1];
void merge(int src[],int des[],int i,int m,int n){
	//i...m...n
	int k,j;
	for(k=i,j=m;i<=m&&j<=n;++k){
		if(src[i]<src[j]){
			des[k]=src[i++];
		}else{
			des[k]=src[j++];
		}
	}
		while(k<=n){
			des[k++]=src[j++];
		}

		while(k<=n&&i<=m){
			des[k++]=src[i++];
		}
}
void sort(int* src,int* des,int* mid,int s,int t){
	int m;
	if(s=t){
		mid[s]=src[s];
	}else{
		m=(s+t)/2;
		sort(src,des,mid,s,m);
		sort(src,des,mid,m+1,t);
		merge(mid,des,s,m,t);
	}
}
void show(int* arr,int len){
	int i=0;
	for(;i<len;++i){
		printf("%d ",arr[i]);
	}
	printf("\n");
}
void init(int arr[],int* len){
	int i=0;
	scanf("%d",len);
	while(scanf("%d",arr+i),++i<*len);
}
int main(){
	int src[9]={3,6,3,7,1,6,47,87,43};
	int des[9]={0};
	sort(src,des,mid,0,9);
	show(des,9);
	return 0;
}
