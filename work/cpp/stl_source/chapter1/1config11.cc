/*
 *	file:1config11.cc
 *	test class template can have non-type template argument
 *	test __STL_NON_TYPE_TMPL_PARAM_BUG in <stl_config.h>
 *	ref. C++ Primer 3/e, p.825
 * */
#include<iostream>
#include<cstddef>	/* for size_t */
using namespace std;
class alloc{

};
inline size_t __deque_buf_size(size_t n,size_t sz){
	return  n!=0?n:(sz<512?size_t(512/sz):size_t(1));
}
template<typename T,typename Ref,typename Ptr,size_t  BufSiz>
struct __deque_iterator{
	typedef __deque_iterator<T,T&,T*,BufSiz> iterator;
	typedef __deque_iterator<T,const T&,const T*,BufSiz> const_iterator;
	static size_t buffer_size(){
		return __deque_buf_size	(BufSiz,sizeof(T));
	}
};
template<typename T,class Alloc=alloc,size_t BufSiz=0>
class deque{
	public:
		deque(){
			cout<<"deque"<<endl;
		}
		typedef __deque_iterator<T,T&,T*,BufSiz> iterator;
};
int main(){
	cout<<deque<int>::iterator::buffer_size()<<endl;
	cout<<deque<int,alloc,64>::iterator::buffer_size()<<endl;
	return 0;
}
