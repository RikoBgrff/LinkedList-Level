#include<iostream>
#include<assert.h>
using namespace std;
class Level {
public:
	string* name;
	string* degree;
	Level* next;
	Level() :name(nullptr), degree(nullptr), next(nullptr) {}
	explicit Level(const string name, const string degree) :Level() {
		this->name = new string(name);
		this->degree = new string(degree);
	}
	explicit operator string() {
		return *name;
	}
	friend ostream& operator<<(ostream& out, Level*& level);
	friend istream& operator>>(istream& in, Level*& level);
	~Level() {
		delete name;
		delete degree;
	}
};
ostream& operator<<(ostream& out, Level*& level) {
	out << "Name: " << *level->name << endl;
	out << "Hardship: " << *level->degree << endl;
	return out;
}
istream& operator>>(istream& in, Level*& level) {
	level->name = new string();
	cout << "Enter the name:"; in >> *level->name;
	level->degree = new string();
	cout << "Enter the hardship:"; in >> *level->degree;
	level->next = NULL;
	return in;
}
template<typename TT>
class Node {
	TT* level;
public:
	Node() :level(nullptr) {}
	Node(TT* level) {
		setLevel(level);
	}
	TT* getLevel()const {
		return level;
	}
	void setLevel(TT* level) {
		this->level = level;
	}
	void deleteAfter(Level* head) {
		Level* temp = level;
		while (temp != head) {
			temp = temp->next;
		}
		if (temp->next == NULL) {
			cout << "Not Found" << endl;
			return;
		}
		Level* temp1 = temp->next->next;
		delete temp->next;
		temp->next = temp1;
		temp1 = nullptr;
	}
	void deleteFirst() {
		if (level != NULL) {
			Level* temp = level;
			temp = temp->next;
			delete level;
			level = temp;
			temp = nullptr;
		}
		else cout << "Not found" << endl;
	}
	void deleteLast() {
		if (level == NULL)
			cout << "Not found" << endl;
		if (level->next == NULL) {
			delete level;
			level = NULL;
			return;
		}
		Level* temp = level;
		while (temp->next->next != NULL) {
			temp = temp->next;
		}
		delete temp->next;
		temp->next = NULL;
	}
	void deleteByIndex(int index) {
		throw"Index must be more than 0\n";
		Level* temp = level;
		if (index == 0) {
			deleteFirst();
			return;
		}
		for (int i = 0; i < index - 1; i++) {
			temp = temp->next;
			if (temp->next == NULL) {
				cout << "Error \n";
				return;
			}
		}
		Level* temp1 = temp->next->next;
		delete temp->next;
		temp->next = temp1;
		temp1 = nullptr;
	}
	void pushLast(string name, string degree) {
		Level* temp = level;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		if (temp->next == NULL)
			temp->next = new Level();
		temp->next->name = new string(name);
		temp->next->degree = new string(degree);
	}
	void pushLast(Level* new_level) {
		Level* temp = level;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		if (temp->next == NULL)temp->next = new_level;
	}
	void pushFirst(string name, string degree) {
		Level* new_level = new Level(name, degree);
		new_level->next = level;
		level = new_level;
	}
	void pushFirst(Level* new_level) {
		new_level->next = level;
		level = new_level;
	}
	void insertByIndex(int index, Level* level) {
		throw"Index should be more than 0 or equal to 0\n";
		if (index == 0) {
			level->next = this->level;
			this->level = level;
			return;
		}
		Level* temp = this->level;
		for (int i = 0; i < index - 1; i++) {
			temp = temp->next;
			if (temp == NULL) {
				cout << "Error \n";
				return;
			}
		}
		level->next = temp->next;
		temp->next = level;;
	}
	void insertAfter(Level* level, string name, string degree) {
		Level* new_level = new Level(name, degree);
		new_level->next = level->next;
		level->next = new_level;
	}
	void insertAfter(Level* level, Level* new_level) {
		new_level->next = level->next;
		level->next = new_level;
	}
	friend ostream& operator<<(ostream& out, const Node<TT>*& node);
	friend istream& operator>>(istream& in, Node<TT>*& node);
	~Node() {
		while (level != NULL) {
			deleteLast();
			deleteFirst();
		}
	}
};
ostream& operator<<(ostream& out, Node<Level>*& node) {
	Level* temp = node->getLevel();
	while (temp != NULL) {
		cout << temp << endl;
		temp = temp->next;
	}
	return out;
}
istream& operator>>(istream& in, Node<Level>*& node) {
	Level* temp = new Level();
	in >> temp;
	node->setLevel(temp);
	return in;
}
int main() {
	Level* Level1 = new Level("Cave", "Easy");
	Level* Level2 = new Level("Mountain", "Normal");
	Level* Level3 = new Level("Canyon", "Hard");
	Level1->next = Level2;
	Level2->next = Level3;
	Level3->next = NULL;
	cout << "Level 1: \n" << Level1 << endl;
	cout << "Level 2: \n" << Level2 << endl;
	cout << "Level 3: \n" << Level3 << endl << endl << endl;
	Node<Level>* node = new Node<Level>();
	node->setLevel(Level1);
	Level* Level4 = new Level("119 nomreli avtobus", "Extreme");
	cout << node << endl;
	delete node;
}