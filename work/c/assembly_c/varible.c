#include<stdio.h>
const int A=10;
int a=20;
static int b=30;
int c;
int main(){
	static int a=40;
	char b[]="hello world";
	register int c=50;
	printf("Hello world %d\n",c);
	return 0;
}
