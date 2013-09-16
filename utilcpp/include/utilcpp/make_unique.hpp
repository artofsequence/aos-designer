#ifndef HGUARD_UTILCXX_MAKE_UNIQUE_HPP__
#define HGUARD_UTILCXX_MAKE_UNIQUE_HPP__

#include <memory>

namespace std
{

	// emulate variadics for 5 args
	template<class T >
	unique_ptr<T> make_unique(){
		return unique_ptr<T>(new T());
	}

	template<class T, class A0>
	unique_ptr<T> make_unique(A0&& a0){
		return unique_ptr<T>(new T(forward<A0>(a0)));
	}

	template<class T, class A0, class A1>
	unique_ptr<T> make_unique(A0&& a0, A1&& a1){
		return unique_ptr<T>(new T(forward<A0>(a0),
			forward<A1>(a1)));
	}

	template<class T, class A0, class A1, class A2>
	unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2){
		return unique_ptr<T>(new T(forward<A0>(a0),
			forward<A1>(a1), forward<A2>(a2)));
	}

	template<class T, class A0, class A1, class A2, class A3>
	unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3){
		return unique_ptr<T>(new T(forward<A0>(a0),
			forward<A1>(a1), forward<A2>(a2),
			forward<A3>(a3)));
	}

	template<class T, class A0, class A1, class A2, class A3, class A4>
	unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4){
		return unique_ptr<T>(new T(forward<A0>(a0),
			forward<A1>(a1), forward<A2>(a2),
			forward<A3>(a3), forward<A3>(a3)));
	}


}


#endif
