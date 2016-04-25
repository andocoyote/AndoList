/*Andrew Mikesell
10-26-01
CSS 342-C Fukuda

List class: this program creates a doubly linked list. The first node in
the list is a dummy node, which is not used for storing data. The data type
used is string and can be changed in the type definition at the top of
the class definition. Normally function insert() will insert a new node
before the current node. However, if the list is empty, function add()
will add the new node to the list and a corresponding message will be
displayed.
*/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <iterator>

class List
{
public:

	typedef std::string ListItemType; //type definition

	List(); //constructor

	List(const List& aList); //copy constructor

	~List(); //destructor

	//overloaded = operator
	void operator=(const List& aList);

	//inserts entry before current node, current node doesn't change
	void insert(ListItemType entry); 

	//adds an entry after current node, new entry becomes current node
	void add(ListItemType entry); 

	//removes the current node
	void remove();

	//assigns item in current node to 'dataItem' in main program
	bool retrieve(ListItemType& dataItem);

	//sets curIndex, the index number of the current node, to 'index'
	void setCur(int index);

	//returns curIndex, the index number of the current node
	int getCur() const { return curIndex;}

	//returns true if list is empty, or false if list is not empty
	bool isEmpty() const {return (listSize == 0);}

	//returns listSize, the number of item holding nodes in the list
	int getLength() const {return listSize;}

private:

	struct Node //definition of struct Node
	{
		ListItemType item; //holds the data in the node
		Node *prev; //pointer to the previous node in the list, or NULL
		Node *next; //pointer to the next node in the list, or NULL
	};

	int listSize; //number of item holding nodes, dummy does not count 
	int curIndex; //index number of current node
	Node *cur; //pointer to the current node
	Node *head; //pointer to the head node, which is the dummy
	Node* find(int index); //returns a pointer to the current node

public:

	//
	// Begin Iterator Class
	//

	class Iterator : public std::iterator<std::forward_iterator_tag, ListItemType>
	{
	public:

		Iterator(Node* p) : _node(p) {}
		~Iterator() {}

		Iterator& operator=(const Iterator& other)
		{
			_node = other._node;
			return(*this);
		}

		bool operator==(const Iterator& other)
		{
			return(_node == other._node);
		}

		bool operator!=(const Iterator& other)
		{
			return(_node != other._node);
		}

		// Preincrement
		Iterator& operator++()
		{
			if (_node != NULL)
			{
				_node = _node->next;
			}
			return(*this);
		}

		// Postincrement
		Iterator operator++(int)
		{
			Iterator tmp(*this);
			++(*this);
			return(tmp);
		}

		ListItemType& operator*()
		{
			return(_node->item);
		}

		ListItemType* operator->()
		{
			return(&*(List::Iterator)*this);
		}

	private:

		Node* _node;
	}; // End Iterator class

	Iterator begin()
	{
		return(Iterator(head));
	}

	Iterator end()
	{
		return(Iterator(NULL));
	}

}; // End List class

#endif


