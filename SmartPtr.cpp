// Универсальный класс интеллектуальных указателей

#include <iostream>
using namespace std;

template <class T> class SmartPtr {
	T* ptr; // Фактический указатель
public:
	// Конструктор
	explicit SmartPtr(T* p = NULL) { ptr = p; }

	// Деструктор
	~SmartPtr() { delete (ptr); }

	// Перегрузка оператора разыменования (разадресации)
	T& operator*() { return *ptr; }

	// Перегрузка оператора селектора выбора
	T* operator->() { return ptr; }
};

int main()
{
	SmartPtr<int> ptr(new int());
	*ptr = 20;
	cout << *ptr;
	return 0;
}
