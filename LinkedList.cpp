#include <iostream>
template<typename Type>
class LinkedList {
	struct Node {
		Type value;
		Node* next;
		Node(const Type& value) : value(value), next(nullptr) {}
	};
	Node* _head;
public:
	LinkedList() : _head(nullptr) {}
	LinkedList(const LinkedList& other) {
		Node* current = other._head;

		while (current) {
			push_back(current->value);
			current = current->next;
		}
	}
	~LinkedList() {
		clear();
	}
	void push_front(const Type& value) {
		Node* newNode = new Node(value);
		if (!_head) _head = newNode;
		else {
			newNode->next = _head;
			_head = newNode;
		}
	}
	void push_back(const Type& value) {
		Node* newNode = new Node(value);
		if (!_head) _head = newNode;
		else {
			Node* current = _head;
			while (current->next) {
				current = current->next;
			}
			current->next = newNode;
		}
	}
	void clear() {
		Node* current = _head;
		while (current) {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
		_head = nullptr;
	}
	class Iterator {
		Node* current;
	public:
		Iterator(Node* node) : current(node) {}
		Type& operator*() {
			return current->value;
		}
		Iterator& operator++() {
			if (current) current = current->next;
			return *this;
		}
		Iterator operator++(int) {
			Node* temp = *this;
			++(*this);
			return temp;
		}
		bool operator==(const Iterator& other) const {
			return current == other.current;
		}
		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}
		Node* getNode() const {
			return current;
		}
	};
	Iterator begin() {
		return Iterator(_head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}
	Iterator insert(Iterator where, const Type& value) {
		Node* pos = where.getNode();
		Node* newNode = new Node(value);

		if (pos == _head) {
			push_front(value);
			return Iterator(_head);
		}

		Node* current = _head;
		while (current && current->next != pos) {
			current = current->next;
		}

		if (current) {
			newNode->next = current->next;
			current->next = newNode;
		}

		return Iterator(newNode);
	}
	Iterator erase(Iterator where) {
		Node* pos = where.getNode();
		if (!pos) return end();

		if (pos == _head) {
			_head = _head->next;
			delete pos;
			return Iterator(_head);
		}

		Node* current = _head;
		while (current && current->next != pos) {
			current = current->next;
		}

		if (current) {
			current->next = pos->next;
			delete pos;
			return Iterator(current->next);
		}

		return end();
	}
	void display() const {
		Node* current = _head;
		while (current) {
			std::cout << current->value << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
};