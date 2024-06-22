#include <iostream>
#include <stdexcept>
template<typename Type>
class LinkedStack {
	struct Node {
		Type value;
		Node* next;
		Node(const Type& val): value(val), next(nullptr){}
	};
	Node* _head;
public:
	LinkedStack(): _head(nullptr) {}
	~LinkedStack() {
		while (!isEmpty()) pop();
	}
	bool isEmpty() const {
		return _head == nullptr;
	}
	void push(const Type& value) {
		Node* newNode = new Node(item);
		newNode->next = _head;
		_head = newNode;
	}
	void pop() {
		if (isEmpty()) throw std::underflow_error("Stack is empty.");
		Node* temp = _head;
		_head = _head->next;
		delete temp;
	}
	Type top() {
		if (isEmpty()) throw std::underflow_error("Stack is empty.");
		return _head->value;
	}
};
class ArrayStack {
	int* _stack;
	int _capacity;
	int _top;
public:
	ArrayStack(int size) : _capacity(size), _top(-1) {
		_stack = new int[_capacity];
	}
	~ArrayStack() {
		delete[] _stack;
	}
	bool isEmpty() const {
		return _top == -1;
	}
	bool isFull() const {
		return _top == _capacity - 1;
	}
	void push(const int& value) {
		if (isFull()) throw std::overflow_error("Stack is full.");
		_stack[++_top] = value;
	}
	void pop() {
		if (isEmpty()) throw std::underflow_error("Stack is empty.");
		--_top;
	}
	int top() {
		if (isEmpty()) throw std::underflow_error("Stack is empty.");
		return _stack[_top];
	}
};