#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct ListElement {
public:
	ListElement* nextElement;
	int value;
	ListElement(int input) : value(input), nextElement(NULL) {}
};

struct List {
public:
	ListElement* beginning;
	ListElement* end;
	int size;
	List() : beginning(NULL), end(NULL), size(0) {}
	List(ListElement* beginningInput, ListElement* endInput, int sizeInput) : beginning(beginningInput), end(endInput), size(sizeInput) {}
};

struct Node {
public:
	int value;
	Node* father;
	Node* leftSon;
	Node* rightSon;
	Node(int input) : value(input), father(NULL), leftSon(NULL), rightSon(NULL) {}
	Node(int input, Node* left, Node* right) : value(input), father(NULL), leftSon(left), rightSon(right) {}
};

//данная функция не соответствует идеям функционального программирования, т.к.
//используется исключительно для ввода данных (формирования односвязного списка)

List* push_back(ListElement* newElement, List* list) {
	return (list->beginning == NULL) ? [list, newElement]() {
		(list->beginning = newElement);
		return new List(newElement, newElement, list->size + 1);
	}() : [list, newElement]() {
		list->end->nextElement = newElement;
		return new List(list->beginning, newElement, list->size + 1);
	}();
}

int findMiddle(int leftEnd, int rightEnd) {
	return ((leftEnd + rightEnd) % 2 == 0 ? (leftEnd + rightEnd) / 2 : (leftEnd + rightEnd) / 2 + 1);
}

ListElement* findElement(int position, ListElement* currentElement) {
	return (position == 0) ? currentElement : findElement(position - 1, currentElement->nextElement);
}

Node* buildTree(List* list, int start, int end) {
	return (start > end) ? NULL : new Node(findElement(findMiddle(start, end), list->beginning)->value, buildTree(list, start, findMiddle(start, end) - 1), buildTree(list, findMiddle(start, end) + 1, end));
}

Node* findRoot(ListElement* currentElement, List* list) {
	return (!currentElement) ? NULL : ((!currentElement->nextElement) ? new Node(currentElement->value) : buildTree(list, 0, list->size - 1));
}

int printTreeFromGivenNode(Node* currentNode) {
	return (currentNode == NULL) ? []() {
		cout << "null ";
		return 0;
	}() : [currentNode]() {
		cout << currentNode->value << ' ';
		return (printTreeFromGivenNode(currentNode->leftSon) + printTreeFromGivenNode(currentNode->rightSon));
	}();
}

int main() {
	List* list = new List();
	ifstream input("input.txt");
	int* a = new int;
	while (input >> *a) {
		list = push_back(new ListElement(*a), list);
	}
	delete a;
	return printTreeFromGivenNode(findRoot(list->beginning, list));
}