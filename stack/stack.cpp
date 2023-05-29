#include <iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

template <typename T>
class List
{
public:
	List();
	~List();

	void push_back(T data);
	void push_front(T data);
	void pop_front();
	void pop_back();
	void insert(T data, int index);
	void removeAt(int index);

	void clear();
	int getSize() const { return size; }
	T getData(int index) const;
	void print() const;

	T& operator[](const int index);
	

private:
	template <typename T>
	class Node
	{
	public:
		T data;
		Node* next = nullptr;
		
		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->next = pNext;
		}
	};

	int size;
	Node<T>* head;

public:
	List<T>::Node<T> clone(const List<T>& obj);
};


//-----------------------------------------------------------------------------


int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int num, num2;
	List<int> lst;

	// ЗАПОЛНЕНИЕ СПИСКА И ВЫВОД НА ЭКРАН
	cout << "Введите количество элементов списка: ";
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		lst.push_back(rand() % 10);
	}
	lst.print();
	
	// УДАЛЕНИЕ ПЕРВОГО ЭЛЕМЕНТА
	cout << "Удаление первого элемента.\n";
	lst.pop_front();
	lst.print();

	// ДОБАВЛЕНИЕ ЭЛЕМЕНТА ПО ИНДЕКСУ
	cout << "Введите значение элемента: ";
	cin >> num;
	cout << "Введите индекс для нового элемента: ";
	cin >> num2;
	lst.insert(num, num2);
	lst.print();

	// УДАЛЕНИЕ ЭЛЕМЕНТА ПО ИНДЕКСУ
	cout << "Введите индекс элемента, который будет удален: ";
	cin >> num;
	lst.removeAt(num);
	lst.print();

	// ДОБАВЛЕНИЕ ПЕРВОГО ЭЛЕМЕНТА
	cout << "Введите значение элемента, который будет добавлен в начало списка: ";
	cin >> num;
	lst.push_front(num);
	lst.print();

	// УДАЛЕНИЕ ПОСЛЕДНЕГО ЭЛЕМЕНТА
	cout << "Удаление последнего элемента.\n";
	lst.pop_back();
	lst.print();

	// СОЗДАНИЕ И ВЫВОД КЛОНИРОВАННОГО СПИСКА
	List<int> lst2;
	cout << "Клонирование и показ нового списка.\n";
	lst2.clone(lst);
	lst2.print();

	// УДАЛЕНИЕ ВСЕГО СПИСКА
	cout << "Удаление всех элементов.\n";
	lst.clear();
	lst.print();
	lst2.clear();
	lst2.print();

}


//-----------------------------------------------------------------------------


template <typename T>
List<T>::List()
{
	size = 0;
	head = nullptr;
}


template <typename T>
List<T>::~List()
{
	clear();
}


template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* obj = this->head;

		while (obj->next != nullptr)
		{
			obj = obj->next;
		}
		obj->next = new Node<T>(data);
	}
	size++;
}

template<typename T>
void List<T>::push_front(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* obj = new Node<T>(data);
		obj->next = head;
		head = obj;
	}
	size++;

	/*head = new Node(data, head);			// другая реализация
	size++;*/
}


template<typename T>
void List<T>::pop_front()
{
	if (head != nullptr)
	{
		Node<T>* temp = head;
		head = head->next;
		delete temp;
		size--;
	}
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
		push_front(data);
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->next;
		}

		Node<T>* newNode = new Node<T>(data, previous->next);
		previous->next = newNode;
		size++;
	}

}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
		pop_front();
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->next;
		}

		Node<T>* toDelete = previous->next;
		previous->next = toDelete->next;

		delete toDelete;
		size--;
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(size - 1);
}


template<typename T>
void List<T>::clear()
{
	while (head != nullptr)
	{
		pop_front();
	}
}


template<typename T>
T List<T>::getData(int index) const
{
	if (head != nullptr)
	{
		Node<T>* temp = head;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		return temp->data;
	}
	else return 0;
}


template<typename T>
void List<T>::print() const
{
	cout << "Вывод элементов односвязного списка: ";
	Node<T>* obj = this->head;
	while (obj != nullptr)
	{
		cout << obj->data << " ";
		obj = obj->next;
	}
	cout << "\nЭлементов в списке: " << size << endl << endl;
}


template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* obj = this->head;

	while (obj != nullptr)
	{
		if (counter == index)
		{
			return obj->data;
		}
		obj = obj->next;
		counter++;
	}
}


template<typename T>
List<T>::Node<T> List<T>::clone(const List<T>& obj)
{
	for (int i = 0; i < obj.getSize(); i++)
	{
		push_back(obj.getData(i));
	}
	return *this->head;
}

