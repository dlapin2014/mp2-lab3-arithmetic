// объ€вление и реализаци€ шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удалени€)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыдел€тьс€ пам€ть

#pragma once
#include<iostream>

template <class TElement>
struct Node {
	TElement data;
	struct Node* next;
	Node(TElement Data, Node* Next) : data(Data), next(Next) {
	}
};


template <class TElement>
class TStack
{
private:
	unsigned int sizeOfStack;
	Node <TElement>* currentTop;

public:


	TStack() :sizeOfStack(0), currentTop(0) {
	}


	TStack(TStack const& a) {
		sizeOfStack = 0;
		if (a.sizeOfStack != 0) {
			sizeOfStack = a.sizeOfStack;
			Node <TElement>* temp = a.currentTop;
			Node <TElement>* t = new Node<TElement>(temp->data, 0);
			currentTop = t;
			temp = temp->next;
			while (temp != 0) {

				t->next = new Node<TElement>(temp->data, 0);
				t = t->next;
				temp = temp->next;
			}
		}
	}



	~TStack() {
		clear();
	}



	void push(const TElement element) {
		Node<TElement>* node = new Node <TElement>(element, currentTop);
		sizeOfStack++;
		currentTop = node;

	}

	void clear() {
		while (sizeOfStack)
			pop();
	}


	TElement top() {
		return currentTop->data;
	}

	void pop() {
		if (sizeOfStack == 0) throw std::invalid_argument("pop out of empty stack");
		sizeOfStack--;
		Node<TElement>* temp = currentTop;
		currentTop = currentTop->next;
		delete temp;
	}


	int GetSize() {
		return sizeOfStack;
	}


	bool empty() {
		return sizeOfStack == 0;
	}


	friend std::ostream& operator<<(std::ostream& ostr, const TStack& s) // вывод
	{

		Node<TElement>* t = s.currentTop;

		while (t != 0) {
			ostr << t->data << " ";
			t = t->next;
		}

		return ostr;
	}


};
