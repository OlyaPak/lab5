// LinkedList.h:
//    Определяет класс связанного списка LinkedList.
//    Требует небольших доработок в местах, отмеченных `// TODO'.

#pragma once

#include <cstddef>           // size_t
#include <initializer_list>  // std::initializer_list<T>
#include <iosfwd>            // std::ostream
using namespace std;

typedef double Data;

class LinkedList
{
	// Необязательно, нужно для "copy & swap", если вы помните, что это.
	friend void swap(LinkedList& left, LinkedList& right);

	// Полезно для отладки, обязательно.
	friend std::ostream& operator<<(std::ostream& output, const LinkedList& xs);

public:
	LinkedList();
	LinkedList(const std::initializer_list<Data> values);

	LinkedList(const LinkedList& source);
	LinkedList& operator=(LinkedList rhs);

	LinkedList(LinkedList&& source);
	LinkedList& operator=(LinkedList&& source);

	virtual ~LinkedList();

public:
	size_t size() const;

	void push_back(const Data& value);
	void push_front(const Data& value);
	void pop_back();
	void pop_front();

	void clear();

	// При некорректном индексе должны возбужадать std::out_of_range.
	void remove_at(size_t index);
	void insert_before(size_t index, const Data& value);
	void insert_after(size_t index, const Data& value);
	Data& value_at(size_t index);

	bool operator==(const LinkedList& other) const;
	bool operator!=(const LinkedList& other) const;

private:
	struct Node
	{
	double value ;// TODO: нужно самостоятельно определить структуру узла Node.
     Node* previous; //указатель  на следующий
     Node* next;     //указатель на предыдущий
	};

private:
	// Возвращает указатель на узел с заданным индексом.
	Node* node_at(size_t index);

	// Создают и добавляют в список узел до (после) указанного.
	// Если указанный --- nullptr, добавляют узел в начало (в конец).
	Node* insert_before(Node* before);
	Node* insert_after(Node* after);

	// Удаляет узел по указателю на него.
	void erase(const Node* node);

private:

     Node* first;
     Node* last;
     size_t size_;             // TODO: нужно объявить данные-члены (поля) LinkedList.
};
