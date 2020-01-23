#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
using namespace std;
#include <sstream>

LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

LinkedList::~LinkedList()
{
	Node* newNode = nullptr;
	while(head != nullptr)
	{
		newNode = head->next;
	    delete head;
	    head = newNode;
	}
	head = nullptr;
	tail = nullptr;
}

LinkedList::LinkedList(const LinkedList& source)
{
	head = nullptr;
	*this = source;
}

LinkedList& LinkedList::operator=(const LinkedList& source)
{
	if(this != &source)
	{
		clear();
		Node* cur = source.head;
		Node* prev = nullptr;
		while (cur != nullptr)
		{
			Node* newNode = new Node(cur->data.id, cur->data.year, cur->data.month, cur ->data.temperature);
			if (head == nullptr)
			{
				head = newNode;
			}
			if (prev != nullptr)
			{
				prev->next = newNode;
			}
			prev = newNode;
			cur = cur->next;
		}
		tail = prev;
	}
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature)
{
	Node* newNode = new Node(location, year, month, temperature);
	Node* cur = head;
	Node* prev = head;

	while (cur != nullptr && cur->data < newNode->data)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur == head)
	{
		head = newNode;
		newNode->next = cur;
	}
	else if (cur == tail)
	{
		tail = newNode;
		prev-> next = newNode;
	}

	else
	{
		prev->next = newNode;
		newNode->next = cur;
	}
}

void LinkedList::clear()
{
	Node* newNode = nullptr;
	while(head != nullptr)
	{
		newNode = head->next;
	    delete head;
	    head = newNode;
	}
	head = nullptr;
	tail = nullptr;
}

Node* LinkedList::getHead() const
{
	return this -> head;
}

string LinkedList::print() const
{
	string outputString;
	ostringstream strOutput;
	Node* cur = head;
	while (cur != nullptr)
	{
		strOutput << cur->data.id << " ";
		strOutput << cur->data.year << " ";
		strOutput << cur->data.month << " ";
		strOutput << cur->data.temperature << endl;
		cur = cur->next;
	}
	outputString = strOutput.str();
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
