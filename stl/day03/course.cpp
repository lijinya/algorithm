#include<iostream>
using namespace std;
#include<list>
int main(){
	int cpp[5]={3,6,1,7,5};
	int java[8]={6,4,7,8,15,2,3,9};
	int _unix[4]={5,2,6,9};
	list<int> li;
	li.insert(li.begin(),cpp,cpp+5);
	li.insert(li.begin(),java,java+8);
	li.insert(li.begin(),_unix,_unix+4);
	li.sort();
	li.unique();
	list<int>::iterator it=li.begin();
	while(it!=li.end()){
		cout<<*it++<<' ';
	}
	cout<<endl;
	return 0;
}
