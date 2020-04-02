#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <algorithm>
#define M 6
#define K 10

template<class T>
class List {
private:
	template<class T>
	class Node
	{
	public:
		Node<T>* next;
		T data;
		Node(T data = T(), Node* next = nullptr) {
			this->next = next;
			this->data = data;
		}
	};
	Node<T>* head;
	int size;

public:
	class iterator {
	private:
		Node<T>* elem;
	public:
		iterator() {
			elem = nullptr;
		}
		iterator(Node<T>* elem)
		{
				this->elem = elem;
		}
		void operator++(int) { elem = elem->next; }
		T& operator*() { return elem->data; }
		bool operator==(iterator it) {
			return (this->elem == it.elem);
		}
		bool operator!=(iterator it) { return !(this->operator==(it)); }
		iterator& operator=(iterator it) {
			elem = it.elem;
			return *this;
		}
		void swap( iterator& it2) {
			List<T>::iterator it;
			it = *this;
			*this = it2;
			it2 = it;
		}
		friend class List;
	};
	List();
	List(int n);
	void insert(iterator& it, T data) {
		Node<T>* a = new Node<T>;
		a = it.elem->next;
		Node<T>* tmp = new Node<T>(data, a);
		it.elem->next = tmp;
		size++;
	}
	void remove(iterator& it) {
		Node<T>* a = new Node<T>;
		a = it.elem->next->next;
		delete[] it.elem->next;
		it.elem->next = a;
		size--;
	}
	iterator begin() {
		auto it = iterator(head);
		return it;
	}
	iterator end() {
		auto it = List<T>::iterator(NULL);
		return it;
	}
	~List();
	void push_back( T);
	void push_begin(T);
	void delete_back();
	void delete_begin();
	int getsize() { return size; }
	bool operator==(List<T>&);
	List(List<T>&);
	List<T>& operator=(List<T>&);
};
template<class T>
List<T>::List() {
	head = nullptr;
	size = 0;
}
template<class T>
List<T>::List(int n) {
	size = n;
	head = new Node<T>;
	Node<T>* tmp = head;
	for (int i = 1; i < size; i++) {
		Node<T>* tmp2 = new Node<T>;
		tmp->next = tmp2;
		tmp = tmp2;
	}
	tmp->next = nullptr;

}
template<class T>
List<T>::~List() {
	if (head != nullptr) {
		Node<T>* a = head;
		if (a->next != nullptr) {
			Node<T>* b;
			while (a->next != nullptr) {
				b = a;
				a = a->next;
				delete[] b;
			}
			delete[] a;
		}
		else
			delete[] a;
	}
}
template<class T>
void List<T>::push_back(T data) {
	if (size == 0)
		head = new Node<T>(data);

	else {
		Node<T>* tmp = this->head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new Node<T>(data);
	}
	size++;
}
template<class T>
void List<T>::push_begin(T data) {
	if (size == 0) {
		head = new Node<T>(data);
	}
	else {
		Node<T>* tmp = new Node<T>(data, head);
		head = tmp;
	}
	size++;
}
template<class T>
void List<T>::delete_back() {
	if (size == 0) {
		std::exception ex("Empty list");
		throw ex;
	}
	else {
		Node<T>* tmp = head;
		if (tmp->next != nullptr) {
			tmp = tmp->next;
			Node<T>* tmp1 = head;
			while (tmp->next != nullptr) {
				tmp = tmp->next;
				tmp1 = tmp1->next;
			}
			delete[] tmp;
			tmp1->next = nullptr;
			size--;
		}
		else {
			delete[] tmp;
			size--;
			head = nullptr;
		}
	}
}
template<class T>
void List<T>::delete_begin() {
	if (size == 0) {
		std::exception ex("Empty list");
		throw ex;
	}
	else {
		head = head->next;
		size--;
	}
}
template<class T>
bool List<T>::operator==(List<T>& lst) {
	if (this == &lst)
		return true;
	else {
		bool a = false;
		if (size == lst.size) {
			if (size == 0)
				a = true;
			else {
				int sum = 0;
				List<T>::iterator it_this(begin());
				List<T>::iterator it_lst(lst.begin());
				while (it_this != end()) {
					if ((*it_this) == (*it_lst))
						sum++;
					it_this++;
					it_lst++;
				}
				if (size == sum)
					a = true;

			}
		}
		return a;
	}
}
template<class T>
List<T>::List(List<T>& lst) {
	if (lst.head == nullptr) {
		head == nullptr;
		size = 0;
	}
	else {
		size = lst.size;
		List<T>::iterator it = lst.begin();
		head = new Node<T>(*it);
		Node<T>* tmp = head;
		it++;
		while (it != lst.end()) {
			tmp->next = new Node<T>(*it);
			tmp = tmp->next;
			it++;
		}
		tmp->next = nullptr;
	}
}
template<class T>
List<T>& List<T>::operator=(List<T>& lst) {
	while (size != 0) {
		this->delete_back();
	}
	if(lst.size != 0) {
		size = lst.size;
		List<T>::iterator it = lst.begin();
		head = new Node<T>(*it);
		Node<T>* tmp = head;
		it++;
		while (it != lst.end()) {
			tmp->next = new Node<T>(*it);
			tmp = tmp->next;
			it++;
		}
		tmp->next = nullptr;
	}
	return *this;
}
template<class T>
class cell    {
private:
	T data;
	int key;
public:
	int getkey() {
		return key;
	}
	T& getdata() {
		return data;
	}
	cell(int key = 0, T data = T()) {
		this->key = key;
		this->data = data;
	}
	bool operator>(cell<T>& c)
	{
		return getkey() > c.getkey();
	}
};
template <class T>
class Table
{
protected:
	int size;
public:
	int getsize() {
		return size;
	}
	virtual int GetKey() = 0;
	virtual T GetData() = 0;
	virtual int Reset() = 0;
	virtual int GoNext() = 0;
	virtual int IsTabEnded() = 0;
	virtual T& getelem(int) = 0;
	
	friend std::ostream& operator<<(std::ostream& ostr, Table<T>& t) {
		ostr << "Ключ" << '\t' << "Значение" << '\n' << '\n';
		for(t.Reset(); !t.IsTabEnded(); t.GoNext())
			ostr << t.GetKey() << '\t' << t.GetData() << '\n' << '\n';
		return ostr;
	}
	virtual int search(int, int, int) = 0;
	virtual void insert(int, T) = 0;
	virtual void remove(int) = 0;
};
template<class T>
class Unordered_table: public Table<T> {
private:
	int Msize;
	cell<T>* mas;
	int CurrPos;
public:
	Unordered_table() {
		CurrPos = 0;
		size = 0;
		Msize = M;
		cell<T>* mas1 = new cell<T>[M];
		mas = mas1;
	}
	virtual ~Unordered_table()
	{
		delete[] mas;
	}
	int GetKey()
	{
		return mas[CurrPos].getkey();
	}
	T GetData()
	{
		return mas[CurrPos].getdata();
	}
	int Reset()
	{
		if(!IsTabEnded())
		    CurrPos = 0;
		return IsTabEnded();
	}
	int GoNext()
	{
		if (!IsTabEnded())
			CurrPos++;
		return IsTabEnded();
	}
	int IsTabEnded()
	{
		return size == CurrPos;
	}
	int search(int key, int left_border, int right_border) override{
		for (int i = 0; i < size; i++) {
			if ( mas[i].getkey() == key )
				return i;
		}
		return -1;
	}
	
	void insert(int key, T data) override{
		if (search(key, 1, 1) != -1) {
			std::exception ex("Ключ не уникален");
			throw ex;
		}
		cell<T> c(key, data);
		mas[size] = c;
		size++;
		if(size == Msize)
		{
			Msize = Msize / 2 * 3;
			cell<T>* mas1 = new cell<T>[Msize];
				for (int i = 0; i < size; i++)
					mas1[i] = mas[i];
			mas1[size] = c;
			delete [] mas;
			mas = mas1;
		}

	}
	void remove(int key) override{
		int j = search(key, 1, 1);
		if (j == -1) {
			std::exception ex("Данного элемента нет в таблице");
			throw ex;
		}
		std::swap(mas[j], mas[size - 1]);
		size--;
		if (size == Msize / 2 && Msize > M) {
			Msize = size / 2 * 3;
			cell<T>* mas1 = new cell<T>[Msize];
			for (int i = 0; i < size; i++)
				mas1[i] = mas[i];
			delete[] mas;
			mas = mas1;
		}
	}
	T& getelem(int key)
	{
		int i = search(key, 1, 1);
		if (!i)
		{
			std::exception ex("В таблице нет элемента с таким ключем");
			throw ex;
		}
		return mas[i].getdata();


	}


};
template<class T>
class Ordered_table : public Table<T> {
private:
	int Msize;
	cell<T>* mas;
	int CurrPos;
public:
	Ordered_table()
	{
		CurrPos = 0;
		size = 0;
		Msize = M;
		cell<T>* mas1 = new cell<T>[M];
		mas = mas1;
	}
	~Ordered_table()
	{
		delete[] mas;
	}

	int search(int key, int left_border, int right_border)
	{
		if (left_border > right_border || size == 0)
		{
			return -1;
		} 
		int middle = (left_border + right_border) / 2;
		if (mas[middle].getkey() > key)
		{
			return search(key, left_border, middle - 1);
		}
		else
	        if (mas[middle].getkey() == key)
		    {
			return middle;
		    }
			else
			    {  
			    return search(key, middle + 1, right_border);
		        }
	}

	void insert(int key, T data) 
	{
		if (search(key, 0, size - 1) != -1) {
			std::exception ex("Ключ не уникален");
			throw ex;
		}
		cell<T> c(key, data);
		mas[size] = c;
		size++;
		if(size == Msize)
		{
			Msize = Msize / 2 * 3;
			cell<T>* mas1 = new cell<T>[Msize];
			for (int i = 0; i < size; i++)
				mas1[i] = mas[i];
			mas1[size] = c;
			delete[] mas;
			mas = mas1;
		}
		int k = size - 1;
		while (k && mas[k - 1] > mas[k] )
		{
			std::swap(mas[k - 1], mas[k]);
			k--;
		}
	}
	void remove(int key) override
	{
		int j = search(key, 0, size - 1);
		if (j == -1) {
			std::exception ex("Данного элемента нет в таблице");
			throw ex;
		}
		while (j != size - 1)
		{
			std::swap(mas[j], mas[j + 1]);
			j++;
		}
		size--;
		if (size == Msize / 2 && Msize > M) {
			Msize = size / 2 * 3;
			cell<T>* mas1 = new cell<T>[Msize];
			for (int i = 0; i < size; i++)
				mas1[i] = mas[i];
			delete[] mas;
			mas = mas1;
		}
	}
	T& getelem(int key)
	{
		int i = search(key, 1, 1);
		if (!i)
		{
			std::exception ex("В таблице нет элемента с таким ключем");
			throw ex;
		}
		return mas[i].getdata();


	}
	int GetKey()
	{
		return mas[CurrPos].getkey();
	}
	T GetData()
	{
		return mas[CurrPos].getdata();
	}
	int Reset()
	{
		if (!IsTabEnded())
			CurrPos = 0;
		return IsTabEnded();
	}
	int GoNext()
	{
		if (!IsTabEnded())
			CurrPos++;
		return IsTabEnded();
	}
	int IsTabEnded()
	{
		return size == CurrPos;
	}
};
template<class T>
class HashTable: public Table<T> {
private:
	List<cell<T>>* mas;
	typename List<cell<T>>::iterator It;
	int CurrPos;
	int CurrListPos;
public:
	HashTable()
	{
		mas = new List<cell<T>>[K];
		It = mas[0].begin();
		CurrPos = 0;
		size = 0;
		CurrListPos = 0;
	}
	int HashFunk(int key)
	{
		return key % K;
	}
	int search(int key, int left_border, int right_border) override
	{
		int m = HashFunk(key);
		List<cell<T>>::iterator it = mas[m].begin();
		while (it != mas[m].end())
		{
			if ((*it).getkey() == key)
				return true;
			it++;
		}
		return false;
	}
	void insert(int key, T data) override
	{
		int m = HashFunk(key);
		if (search(key, 1, 1)) 
		{
			std::exception ex("Элемент с таким ключем уже есть в таблице");
			throw ex; 
		}
		cell<T> a(key, data);
		mas[m].push_back(a);
		size++;
	}
	void remove(int key) override
	{
		int m = HashFunk(key);
		if (!search(key, 1, 1))
		{
			std::exception ex("Нет элемента с таким ключем");
			throw ex;
		}
		List<cell<T>>::iterator it = mas[m].begin();
		while (it != mas[m].end())
		{
			if ((*it).getkey() == key)
			{
				List<cell<T>>::iterator it1 = mas[m].begin();
				(*it) = (*it1);
				mas[m].delete_begin();
				break;
			}
			it++;
		}
		size--;
	}
	int Reset() override
	{
		CurrListPos = 0;
		CurrPos = 0;
		if (size)
		{
			for (int i = 0; i < K; i++)
			{
				if (mas[i].getsize() != 0)
				{
					CurrListPos = i;
					It = mas[i].begin();
					break;
				}
			}
		}
		return IsTabEnded();
	}
	int GoNext() override
	{
		CurrPos++;
		if (!IsTabEnded()) {
			It++;
			if (It == mas[CurrListPos].end())
			{
				for (int i = CurrListPos + 1; i < K; i++)
				{
					if (mas[i].getsize() != 0)
					{
						CurrListPos = i;
						It = mas[CurrListPos].begin();
						break;
					}
				}
			}
				
		}
		return IsTabEnded();
	}
	int IsTabEnded() override
	{
		return size == CurrPos;
	}
	int GetKey() override
	{
		return (*It).getkey();
	}
	T GetData() override
	{
		return (*It).getdata();
	}
	T& getelem(int key)
	{
		int i = search(key, 1, 1);
		if (!i)
		{
			std::exception ex("В таблице нет элемента с таким ключем");
			throw ex;
		}
		for (Reset(); !IsTabEnded(); GoNext())
		{
			if ((*It).getkey() == key)
			{
				return (*It).getdata();
			}
		}
	}

};