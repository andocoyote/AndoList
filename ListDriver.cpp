/*Andrew Mikesell
10-26-01
CSS 342-C

This program is a driver for the List class. It performs no error handling 
when the user is required to enter a single string, or select from the menu.  
*/

#include "List.h" //include the List class
using namespace std;

int menu(); //displays the user menu, returns the menu selection
void print(List& aList); //prints the list to the screen
void copyList(const List& aList); //copies the list and prints it
void useIterator(List& aList);

//begin main function
void main()
{
	unsigned int choice; //menu choice from user
	bool exit = false;	//user wants to exit program?
	string entry; //string entered by user to be placed in list
	string curItem; //current item retrieved from list

	List myList; //declare a list
	List List2;
	List *deleteList = new List;

	do //while (!exit)
	{
		choice = menu(); //display user menu and get selection

		switch(choice) //perform switch on choice from menu
		{
				//user wants to add a name to the list
		case 1: cout << endl << "Enter a name to add to the list: ";
				cin >> entry; //get the name from user

				myList.add(entry); //add name to list
				exit = false; 
				break;

				//user wants to insert name into list
		case 2: cout << endl << "Enter a name to insert into the list: ";
				cin >> entry; //get name to insert

				myList.insert(entry); //insert name into list
				exit = false;
				break;

				//user wants to see current item
		case 3: cout << endl << "Here is the current item: ";

				//if the list is not empty, display current item
				if(myList.retrieve(curItem) == true)
					cout << curItem << endl << endl;

				else //if the list is empty, say so
					cout << "Error. The list is empty" << endl;

				exit = false;
				break;

				//user wants to remove the current item from the list
		case 4: myList.remove();

				exit = false;
				break;

				//user wants to display list on the screen
		case 5: cout << endl << "Here is your list:" << endl;

				print(myList); //print the list

				exit = false;
				break;

				//user wants to make a copy of the list
		case 6: copyList(myList);
				
				exit = false;
				break;
	
				//assign original list to List2
		case 7: List2 = myList;
				
				exit = false;
				break;

				//print List2
		case 8: print(List2);

				exit = false;
				break;

				//demonstrate destructor
		case 9: delete deleteList;
				deleteList = NULL;

				exit = false;
				break;
				
		case 10: useIterator(myList);

				 exit = false;
				 break;

				//user wants to exit the program
		case 0: exit = true;
				break;
		}

	}while(!exit);//end do while loop for main program

}//end of main program

//-----------------------------------------------------------------------

//beginning of menu()
int menu()
{
	int selection; //holds the user's menu choice

	//display the menu
	cout << "Please choose from the following options" << endl;
	cout << "1.  Add a name to the list" << endl;
	cout << "2.  Insert a name into the list" << endl;
	cout << "3.  Retrieve the current item" << endl;
	cout << "4.  Remove the current node" << endl;
	cout << "5.  Print the list" << endl;
	cout << "6.  Create a copy of the list" << endl;
	cout << "7.  Assign original list to a new list" << endl;
	cout << "8.  Print new list which was assign to" << endl;
	cout << "9.  Demonstrate destructor (deletes a trivial list)" << endl;
	cout << "10. Use the Iterator to print the list" << endl;
	cout << "0.  Exit the program" << endl;
	cout << ": ";
	cin >> selection; //get the selection from the menu

	return selection; //return the selection to main program
}//end function menu()

//-----------------------------------------------------------------------

//beginning of function print()
void print(List& aList)
{
	int curNum = aList.getCur(); //save the index of the current node
	string line; //string holds data item of current node

	cout << endl;

	//travers list and print each index number and item
	for(int number = 1; number <= aList.getLength(); ++number)
	{ 
		//if the list is not empty, print the items
		if(aList.retrieve(line) == true) 
		{
			aList.setCur(number);
			aList.retrieve(line);
			cout << number << ": " << line << endl;
		}

		else //if the list is empty, say so
			cout << "Error. The list is empty" << endl;
	}

	cout << endl;

    aList.setCur(curNum); //set curIndex to what it was before printing list

}//end of function print()

//-----------------------------------------------------------------------

//beginning of function copyList()
void copyList(const List& aList)
{
	List newList(aList);//instantiate a new list as a copy of an old list

	cout << "Here is your copy list" << endl;
	print(newList); //display the new list

}//end of function copyList()

 //-----------------------------------------------------------------------

//beginning of function useIterator()
void useIterator(List& aList)
{
	cout << endl << "Here is your list:" << endl;

	for (List::Iterator iter = aList.begin(); iter != aList.end(); iter++)
	{
		cout << *iter << endl;
	}

	cout << endl;
}//end of function useIterator
