#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template<typename Type>
class Queue {
public:
	Queue();
	bool empty();
	void push(Type val);
	void pop();
	Type front();
	Type back();
	size_t size();
	Queue<Type>& operator= (const Queue<Type>&);
	~Queue();
private:
	struct Item {
		Item(Type val, Item* ptr = nullptr) : value(val), next(ptr) {}
		Type value;
		Item* next;
	};
	Item *first, *last;
	size_t queueSize;
};

void emptyQueueError(const char*);

template<typename Type>
Queue<Type>::Queue() : first(nullptr), queueSize(0) {}

template<typename Type>
bool Queue<Type>::empty() {
	return (first == nullptr);
}

template<typename Type>
void Queue<Type>::push(Type val) {
	Item* newItem = new Item(val);
	if (empty())
		first = newItem;
	else
		last->next = newItem;
	last = newItem;
	++queueSize;
}

template<typename Type>
void Queue<Type>::pop() {
	if (empty()) {
		emptyQueueError("Item can't be pop.");
	}
	Item* nextItem = first->next;
	delete first;
	first = nextItem;
	--queueSize;
}

template<typename Type>
Type Queue<Type>::front() {
	if (empty()) {
		emptyQueueError("Can't be take front element.");
	}
	return first->value;
}

template<typename Type>
Type Queue<Type>::back() {
	if (empty()) {
		emptyQueueError("Can't be take back element.");
	}
	return last->value;
}

template<typename Type>
size_t Queue<Type>::size() {
	return queueSize;
}

template<typename Type>
Queue<Type>& Queue<Type>::operator= (const Queue<Type>& queue) {
	this->~Queue();
	Item *copyQueue = queue.first;
	while (copyQueue != nullptr) {
		this->push(copyQueue->value);
		copyQueue = copyQueue->next;
	}
	return *this;
}

template<typename Type>
Queue<Type>::~Queue() {
	while (!empty()) {
		Item* nextItem = first->next;
		delete first;
		first = nextItem;
	}
	queueSize = 0;
}

void emptyQueueError(const char* message) {
	std::cerr << "Error: " << message << " Queue is empty!\n";
	exit(EXIT_FAILURE);
}

#endif
