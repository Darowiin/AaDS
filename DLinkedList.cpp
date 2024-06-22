#include <iostream>
template<typename Type>
class DLinkedList {
	struct Node {
		Type value;
		Node* next;
		Node* prev;
		Node(const Type& value) : value(value), next(nullptr), prev(nullptr) {}
	};
	Node* _head;
	Node* _tail;
public:
	DLinkedList(): _head(nullptr), _tail(nullptr) {}
	DLinkedList(const DLinkedList& other) {
		Node* current = other._head;

		while (current) {
			push_back(current->value);
			current = current->next;
		}
	}
	~DLinkedList() {
		clear();
	}
	void push_front(const Type& value) {
		Node* newNode = new Node(value);
		if (!_head) _head = _tail = newNode;
		else {
			newNode->next = _head;
			_head->prev = newNode;
			_head = newNode;
		}
	}
	void push_back(const Type& value) {
		Node* newNode = new Node(value);
		if (!_tail) _head = _tail = newNode;
		else {
			newNode->prev = _tail;
			_tail->next = newNode;
			_tail = newNode;
		}
	}
	void clear() {
		Node* current = _head;
		while (current) {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
		_head = _tail = nullptr;
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
		Iterator& operator--() {
			if (current) current = current->prev;
			return *this;
		}
		Iterator operator++(int) {
			Node* temp = *this;
			++(*this);
			return temp;
		}
		Iterator operator--(int) {
			Node* temp = *this;
			--(*this);
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

		if (!pos) {
			push_back(value);
			return Iterator(_tail);
		}

		if (pos == _head) {
			push_front(value);
			return Iterator(_head);
		}

		newNode->next = pos;
		newNode->prev = pos->prev;
		pos->prev->next = newNode;
		pos->prev = newNode;
		return Iterator(newNode);
	}
	Iterator erase(Iterator where) {
		Node* pos = where.getNode();
		if (!pos) return end();

		if (pos == _head) {
			_head = _head->next;
			if (_head) {
				_head->prev = nullptr;
			}
			else {
				_tail = nullptr;
			}
		}
		else if (pos == _tail) {
			_tail = _tail->prev;
			if (_tail) {
				_tail->next = nullptr;
			}
			else {
				_head = nullptr;
			}
		}
		else {
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;
		}
		delete pos;
		return Iterator(_head);
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