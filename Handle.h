#pragma once
// Handle.h
#ifndef GUARD_Handle_h
#define GUARD_Handle_h

template <class T> class Handle {
public:
	// 생성자
	Handle() : p(0) { }
	Handle(T* t) : p(t) { }
	Handle(const Handle& s) : p(0) { if (s.p) p = s.p->clone(); }
	// 할당 연산자
	Handle& operator=(const Handle&);
	// 소멸자
	~Handle() { delete p; }

	// 존재한지 연산자
	operator bool() const { return p; }
	// 포인터 연산자
	T& operator*() const;
	T* operator->() const;
private:
	T* p;
};

#include <stdexcept>

using namespace std; // std::runtime_error;

template <class T> // 할당 연산자 = rhs (right-hand side)
Handle<T>& Handle<T>::operator=(const Handle& rhs) {
	if (&rhs != this) {
		delete p;
		p = rhs.p ? rhs.p->clone() : 0;
	}
	return *this;
}

template <class T>
T& Handle<T>::operator*() const {
	if (p)
		return *p;
	throw runtime_error("unbound Handle!");
}

template <class T>
T* Handle<T>::operator->() const {
	if (p)
		return p;
	throw runtime_error("unbound Handle!");
}

#endif
