#include<iostream>
using namespace std;
#include<list>
int main(){
	list<int> l1;
	int a[5]={3,4,5,6,7};
	list<int> l2(a,a+5);
	cout<<"l1.size  "<<l1.size()<<endl;
	cout<<"l2.size  "<<l2.size()<<endl;
	list<int>::iterator it;//class name list<int>
	for(it=l2.begin();it!=l2.end();++it){
		cout<<*it<<' ';	//no < ooperator
	}
	cout<<endl;
	it=l2.begin();
	it++;
	l2.erase(it);
	l2.insert(l2.begin(),898);
	l2.insert(l2.end(),999);
	for(it=l2.begin();it!=l2.end();++it){
		cout<<*it<<' ';	//no < ooperator
	}
	cout<<endl;
	return 0;
}
