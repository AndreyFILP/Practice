// Простой интеллектуальный указатель с конструктором копирования и перегрузкой оператора присваивания

#include <iostream>
using namespace std;

template <class T> class SmartPtr {
	T* ptr; // Фактический указатель
public:
	explicit SmartPtr(T* p = NULL) {
		ptr = p;
	}
	SmartPtr(const SmartPtr& S) {
		ptr = new T(*S.ptr); 
	}
	SmartPtr& operator=(const SmartPtr& S) {
		*ptr = *S.ptr; 
		return *this;
	}
	~SmartPtr() {
		delete ptr;
	}

	// Перегрузка оператора разыменования (разадресации)
	T& operator*() { return *ptr; }

	// Перегрузка оператора селектора выбора
	T* operator->() { return ptr; }
};

int main()
{
	SmartPtr<int> ptr(new int());
	*ptr = 20;
	SmartPtr<int> ptr2(ptr);
	*ptr2 = 30;
	SmartPtr<int> ptr3 = ptr;
	*ptr3 = 50;
	//ptr = ptr3;
	cout << *ptr << "  " << *ptr2 << "  " << *ptr3;
	//cout << *ptr << "  " << *ptr3;
	//cout << *ptr;
	return 0;
}