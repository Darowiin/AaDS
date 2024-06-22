#include <iostream>
#include <stdexcept>
template<typename Type>
class LinkedQueue {
	struct Node {
		Type value;
		Node* next;
		Node(const Type& val) : value(val), next(nullptr) {}
	};
	Node* _front;
	Node* _rear;
public:
	LinkedQueue() : _front(nullptr), _rear(nullptr) {}
	~LinkedQueue() {
		while (!isEmpty()) pop();
	}
	bool isEmpty() const {
		return _front == nullptr;
	}
	void push(const Type& value) {
		Node* newNode = new Node(item);
		if (isEmpty()) _front = _rear = newNode;
		else {
			_rear->next = newNode;
			_rear = newNode;
		}
	}
	void pop() {
		if (isEmpty()) throw std::underflow_error("Queue is empty.");
		Node* temp = _front;
		_front = _front->next;
		if (_front == nullptr) _rear = nullptr;
		delete temp;
	}
	Type front() {
		if (isEmpty()) throw std::underflow_error("Queue is empty.");
		return _front->value;
	}
};
class ArrayStack {
	int* _queue;
	int _capacity;
	int _front;
	int _rear;
	int _size;
public:
	ArrayStack(int size) : _capacity(size), _front(0), _rear(-1), _size(0) {
		_queue = new int[_capacity];
	}
	~ArrayStack() {
		delete[] _queue;
	}
	bool isEmpty() const {
		return _size == 0;
	}
	bool isFull() const {
		return _size == _capacity;
	}
	void push(const int& value) {
		if (isFull()) throw std::overflow_error("Queue is full.");
		_rear = (_rear + 1) % _capacity;
		_queue[_rear] = value;
		++_size;
	}
	void pop() {
		if (isEmpty()) throw std::underflow_error("Queue is empty.");
		_front = (_front + 1) % _capacity;
		--_size;
	}
	int front() {
		if (isEmpty()) throw std::underflow_error("Queue is empty.");
		return _queue[_front];
	}
};