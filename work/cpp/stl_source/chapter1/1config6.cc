/*
 *	file:1config6.cc
 *	test __STL_FUNCTION_TMPL_PARTIAL_ORDER in stl_config.h
 *
 */
#include<iostream>
using namespace std;
class alloc{};
template <class T,class Alloc=alloc>
class vector{
	public:
		void swap(vector<T,Alloc>&){
			cout<<"swap()"<<endl;
		}
};
#ifdef __STL_FUnCTION_TMPL_PARTIALORDER
template <class T,class Alloc>
inline void swap(vector<T,Alloc>& x,vector<T,Alloc>& y){
	x.swap(y);
}
#endif
int main(){
	vector<int>x,y;
	swap(x,y);
	return 0;
}
