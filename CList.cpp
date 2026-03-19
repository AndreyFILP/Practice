#include <iostream>
using namespace std;

template <class T>
class CList
{
private:
	struct CItem
	{
		T value;
		CItem* next;
	};
	CItem* head;    // Корень списка
public:
	CList(): head(nullptr) {} // Инициализация списка
	CList(T* t, int n)  // Инициализация списка по n элементам массива 
	{
		// добавить проверку n 
		CItem* p = new(CItem);
		head = p;
		p->value = t[0];
		for(int i=1; i<n; i++)
		{
			p->next = new(CItem);
			p = p->next; 
			p->value = t[i];
		}
		p->next = nullptr;
	}

	~CList() 
	{
		CItem* p;
		while (head)
		{
			p = head;
			head = head->next;
			delete p;
		}
	}

	void insFirst(T t)  // Вставка элемента в начало списка
	{
		CItem* p = new(CItem);
		p->value = t;
		p->next = head;
		head = p;
	}

	void print()
	{
		CItem* p = head;
		if (!p)
		{
			cout << "Список пуст!\n";
			return;
		}
		while(p)
		{
			cout << p->value << '\t';
			p = p->next;
		}
	}
};

int main()
{
	system("chcp 1251");
	int a[] = {9,7,6,4,3,2,1,20};
	CList<int> L1;
	CList<int> L2(a,5);
	L1.print();
	L1.insFirst(5);
	L1.insFirst(8);
	L1.insFirst(7);
	L1.print();
	cout << "\n";
	L2.print();
}