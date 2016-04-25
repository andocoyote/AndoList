/*Andrew Mikesell
10-26-01
*/

#include "List.h"
#include <iostream>
using namespace std;

List::List() //constructor
{
	Node *dummy = new Node; //create a dummy node
	dummy->next = NULL; //set dummy->next to NULL
	dummy->prev = NULL; //set dummy->prev to NULL

	head = dummy; //point head to dummy
	cur = head; //make cur head
	
	curIndex = 0; 
	listSize = 0;
}

//-----------------------------------------------------------------------

//destructor
List::~List()
{
	while(!isEmpty()) //while list contains nodes
	{
		remove(); //remove current node
	}

	delete head;
	head = NULL;
}

//-----------------------------------------------------------------------

//copy constructor
List::List(const List& aList): listSize(aList.listSize), curIndex(aList.curIndex) 
{
	int count = 0; //nodes copied so far

	Node *dummy = new Node; //create a dummy node
	dummy->next = NULL; //set dummy->next to NULL
	dummy->prev = NULL; //set dummy->prev to NULL

	head = dummy; //point head to dummy
	cur = head; //make cur head

	if(aList.head->next == NULL) //if original list is empty
	{
		curIndex = 0;
		listSize = 0;
	}
	
	else //copy first node
	{
		cout << "copy constructor invoked" << endl;

		cur = new Node; //cur points to new node
		cur->item = aList.head->next->item; //new node = first item

		cur->prev = head; //current's previous pointer points to dummy
		cur->next = NULL; //current's next pointer is NULL

		head->next = cur; //dummy's next points to current node

		++count;//increment number of nodes copied
		cout << "node " << count << " copied" << endl;

		//copy each item from original list to new list
		for(Node *origPtr = aList.head->next->next;
				origPtr != NULL;
				origPtr = origPtr->next)
		{
			Node *newPtr = new Node; //create a new node
			newPtr->item = origPtr->item; //put original item in new node

			newPtr->prev = cur; //add new node to list after current node
			newPtr->next = NULL; //set new node's next pointer to NULL
			
			cur->next = newPtr; //current node's next pointer points to new node
			cur = newPtr; //make new node the current node

			++count;//increment number of nodes copied
			cout << "node " << count << " copied" << endl;
		}
	
	}//end if
}

//-----------------------------------------------------------------------

//overloaded assignment operator
void List::operator=(const List& aList)
{
	//if the list is being assigned to itself, return
	if(this == &aList)
		return;

	while(listSize != 0) //while list contains nodes
	{
		remove(); //remove current node
	}

	if(aList.head->next == NULL) //if original list is empty
	{
		cout << "list was empty" << endl;
		curIndex = 0;
		listSize = 0;
	}
	
	else //copy first node
	{
		curIndex = aList.getCur();//set curIndex == aList's curIndex
		listSize = aList.getLength();//set listSize == aList's size

		cur = new Node; //cur points to new node
		cur->item = aList.head->next->item; //new node = first item

		cur->prev = head; //current's previous pointer points to dummy
		cur->next = NULL; //current's next pointer is NULL

		head->next = cur; //dummy's next points to current node
		
		//Node *newPtr = cur; //newPtr points to last item in new list

		//copy each item from original list to new list
		for(Node *origPtr = aList.head->next->next;
				origPtr != NULL;
				origPtr = origPtr->next)
		{
			Node *newPtr = new Node; //create a new node
			newPtr->item = origPtr->item; //put original item in new node

			newPtr->prev = cur; //add new node to list after current node
			newPtr->next = NULL; //set new node's next pointer to NULL
			
			cur->next = newPtr; //current node's next pointer points to new node
			cur = newPtr;
		}
	
	}//end if
	setCur(aList.getCur());//set current node == aList's current node
}

//-----------------------------------------------------------------------

//insert a node before the current node, current node does not change
void List::insert(ListItemType entry)
{
	if(cur->prev == NULL) //if cur is the dummy node, the list is empty
	{
		cout << "There is no entry to insert before." << endl;
		cout << "The new entry will be added." << endl;
		add(entry); //add the entry instead of inserting it
	}

	else //if(cur->prev != NULL),then the list contains at least one entry
	{
		Node *newItem = new Node; //allocate a new node
		newItem->item = entry; //set data field of new node == entry

		newItem->next = cur; //insert new item before current item
		newItem->prev = cur->prev;
		cur->prev->next = newItem;
		cur->prev = newItem;

		++listSize; //increment the list size
		++curIndex; //increment curIndex so currnet item doesn't change
	}
	
}

//-----------------------------------------------------------------------

//add a node after the current node, new node becomes the current node
void List::add(ListItemType entry)
{
	Node *newItem = new Node; //allocate a new node
	newItem->item = entry; //set data field of new node == entry

	newItem->next = cur->next; //add new item to list after current item
	newItem->prev = cur;
	cur->next = newItem;

	//if newly added item is not the last item in the list,
	//connect its next item's previous pointer to it
	if(newItem->next != NULL)
		newItem->next->prev = newItem;

	cur = newItem; //make the new item the current item
	++listSize; //increment the list's size
	++curIndex; //increment the current index number

}

//-----------------------------------------------------------------------

//remove the current node, the following node becomes the current node
void List::remove()
{
	if(!isEmpty()) //there exists a node to be removed
	{
		Node *removePtr = cur; //point removePtr to cur for removal
		
		if(removePtr->next == NULL) //if deleting the last node
		{
			cur = cur->prev; //point newCur to cur's prev, to set cur to it
			cur->next = NULL; //detatch cur's forward pointer, set to NULL
			--listSize; //decrement listSize
			curIndex = listSize; //set curIndex to the last node
		}

		else //if deleting a middle node
		{
			cur = removePtr->next;
			cur->prev = removePtr->prev;
			removePtr->prev->next = cur;

			--listSize; //decrement list size
		}

		delete removePtr; //deallocate node removePtr points to
		removePtr = NULL; //set removePtr to NULL

	}

	else //if the list is already empty, say so
		cout << "The list is already empty" << endl;
}

//-----------------------------------------------------------------------

//retrieve the data item in the current node
bool List::retrieve(ListItemType& dataItem)
{
	if(cur->prev == NULL)//if the list is empty, return false
		return false;

	else
	{
		dataItem = cur->item;//assign cur's item to dataItem
		return true;
	}
}

//-----------------------------------------------------------------------

//set the current node to the index number given in the parameter
void List::setCur(int index)
{
	//if index is outside of allowable range, say so
	if((index < 0) || (index > listSize))
		cout << "Can't set cur to index number. Index is out of range" << endl;

	else//set curIndex to index and find that node
	{
		curIndex = index;
		cur = find(index);
	}
}

//-----------------------------------------------------------------------

//return the current node
List::Node* List::find(int index)
{
	//if index is out of allowable range, return NULL
	if((index < 0) || (index > getLength()))
		return NULL;

	else if(index > 0)//if index > 0, return corresponding node
	{
		cur = head->next;

		for(int nodeNumber = 1; nodeNumber < index; ++nodeNumber)
		{
			cur = cur->next;
		}

		return cur;
	}

	else//if index == 0, return head node, or dummy
	{
		cur = head;
		return cur;
	}

}



