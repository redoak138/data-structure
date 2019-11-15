#ifndef STACK_H
#define STACK_H

#include <iostream>

template<typename Type>
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
		Item(Type val, Item* ptr = nullptr) : value(val), next(ptr) {}
		Type value;
		Item* next;
	};
	Item *last;
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
	Item* newItem = new Item(val, last);
	last = newItem;
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
	Item* copyStack = stack.last;
	while (copyStack != nullptr) {
		Item* nextItem = new Item(copyStack->value);
		if (prevItem != nullptr)
			prevItem->next = nextItem;
		else
			this->last = nextItem;
		prevItem = nextItem;
		copyStack = copyStack->next;
	}
	this->stackSize = stack.stackSize;
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
