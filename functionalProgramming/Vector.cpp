#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <iterator>
using namespace std;

struct Node {
public:
	int value;
	Node* father;
	Node* leftSon;
	Node* rightSon;
	Node(int input) : value(input), father(NULL), leftSon(NULL), rightSon(NULL) {}
	Node(int input, Node* left, Node* right) : value(input), father(NULL), leftSon(left), rightSon(right) {}
};

vector<int> readVector() {
	vector<int> result;
	fstream input("input.txt");
	copy(istream_iterator<int>(input), istream_iterator<int>(), back_inserter(result));
	return result;
}

int findMiddle(int leftEnd, int rightEnd) {
	return ((leftEnd + rightEnd) % 2 == 0 ? (leftEnd + rightEnd) / 2 : (leftEnd + rightEnd) / 2 + 1);
}

Node* buildTree(vector<int> input, int start, int end) {
	return (start > end) ? NULL : new Node(input[findMiddle(start, end)], buildTree(input, start, findMiddle(start, end) - 1), buildTree(input, findMiddle(start, end) + 1, end));
}

Node* findRoot(vector<int> input) {
	return (input.size() == 1) ? new Node(input[0]) : buildTree(input, 0, input.size() - 1);
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
	vector<int> input = readVector();
	return printTreeFromGivenNode(findRoot(input));
}