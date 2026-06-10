#pragma once
// Ref_handle.h
#ifndef GUARD_Ref_handle_h
#define GUARD_Ref_handle_h

#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T> class Ref_handle {
public:
	// 참조 카운트를 포인터처럼 관리
	Ref_handle() : p(0), refptr(new size_t(1)) { }
	Ref_handle(T* t) : p(t), refptr(new size_t(1)) { }
	Ref_handle(const Ref_handle& h) : p(h.p), refptr(h.refptr) {
		++*refptr;
	}
	// 할당 연산자
	Ref_handle& operator=(const Ref_handle&);
	~Ref_handle(); // 소멸자

	// 이전과 같음 (Handle 클래스)
	operator bool() const { return p; }
	T& operator*() const {
		if (p) return *p;
		throw runtime_error("unbound Ref_handle!");
	}
	T* operator->() const {
		if (p) return p;
		throw runtime_error("unbound Ref_handle!");
	}
private:
	T* p;
	size_t* refptr;
};

template <class T>
Ref_handle<T>& Ref_handle<T>::operator=(const Ref_handle& rhs) {
	++*rhs.refptr; // 참조 포인터 이동

	// 상황에 따라 좌별을 할당 해제하고 포인터 소멸
	if (--*refptr = 0) {
		delete refptr;
		delete p;
	}

	// 우변 값들을 복사
	refptr = rhs.refptr;
	p = rhs.p;

	return *this;
}

template <class T>
Ref_handle<T>::~Ref_handle() {
	if (--*refptr = 0) {
		delete refptr;
		delete p;
	}
}
#endif