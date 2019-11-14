#ifndef STACK_H
#define STACK_H

#include <iostream>

template<class Type>
class Stack {
public:
	Stack();
	bool empty();
	void push(Type val);
	void pop();
	Type top();
	size_t size();
	Stack<Type>& operator= (const Stack<Type>&);
	~Stack();
private:
	struct Item {
		Type value;
		Item* next;
	} *last;
	size_t stackSize;
};

void emptyStackError(const char*);

template<typename Type>
Stack<Type>::Stack() : last(nullptr), stackSize(0) {}

template<typename Type>
bool Stack<Type>::empty() {
	return (last == nullptr);
}

template<typename Type>
void Stack<Type>::push(Type val) {
	Item* newTop = new Item;
	newTop->value = val;
	newTop->next = last;
	last = newTop;
	++stackSize;
}

template<typename Type>
void Stack<Type>::pop() {
	if (empty()) {
		emptyStackError("Item can't be pop.");
	}
	Item* nextItem = last->next;
	delete last;
	last = nextItem;
	--stackSize;
}

template<typename Type>
Type Stack<Type>::top() {
	if (empty()) {
		emptyStackError("Can't be take top element.");
	}
	return last->value;
}

template<typename Type>
size_t Stack<Type>::size() {
	return stackSize;
}

template<typename Type>
Stack<Type>& Stack<Type>::operator= (const Stack<Type>& stack) {
	this->~Stack();
	Item* prevItem = nullptr;
	Item* nextStack = stack.last;
	while (nextStack != nullptr) {
		Item* nextItem = new Item;
		nextItem->value = nextStack->value;
		nextItem->next = nullptr;

		if (prevItem != nullptr)
			prevItem->next = nextItem;
		else
			last = nextItem;
		prevItem = nextItem;
		nextStack = nextStack->next;
	}
	stackSize = stack.stackSize;
	return *this;
}

template<typename Type>
Stack<Type>::~Stack() {
	while (!empty()) {
		Item* nextItem = last->next;
		delete last;
		last = nextItem;
	}
	stackSize = 0;
}

void emptyStackError(const char* message) {
	std::cerr << "Error: " << message << " Stack is empty!\n";
	exit(EXIT_FAILURE);
}

#endif
