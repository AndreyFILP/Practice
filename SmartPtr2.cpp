// Класс со стратегией владения объектом на основе подсчета ссылок на объект.
//

#include <iostream>
using namespace std;

template <class T> 
class SmartPtr {
	T* ptr; 
	size_t* pCounter;

	void Attach(const SmartPtr& S)
	{
		pCounter = S.pCounter;
		(*pCounter)++;
		ptr = S.ptr;
	}

	void Detach()
	{
		if (ptr)
		{
			(*pCounter)--;
			if ((*pCounter) == 0)
			{
				delete ptr;
				delete pCounter;
			}
			ptr = 0;
			pCounter = 0;
		}
	}

public:
	explicit SmartPtr(T* p) { 
		ptr = p; 
		pCounter = new size_t();
		*pCounter = 1;
	}

	SmartPtr(const SmartPtr& S) { 
		Attach(S);
	}

	SmartPtr& operator=(const SmartPtr& S) {
		if (this == &S)
		{
			return *this;
		}
		Detach();
		Attach(S);
		return *this;
	}

	~SmartPtr() { 
		Detach();
	}

	size_t use_count() {
		return *pCounter;
	}

	T& operator*() { return *ptr; }

	T* operator->() { return ptr; }
};

int main()
{
	SmartPtr<int> ptr(new int());
	*ptr = 20;
	SmartPtr<int> ptr2(ptr);
	*ptr2 = 30;
	SmartPtr<int> ptr3 = ptr;
	//*ptr3 = 50;
	//ptr = ptr3;
	cout << *ptr << "  " << *ptr2 << "  " << *ptr3 << endl;
	cout << ptr.use_count() << "  " << ptr2.use_count() << "  " << ptr3.use_count();
	return 0;
}