// Main.cpp

#include<string.h>
#include<iostream>
#include<fstream>
#include "RBnode.h"

using namespace std;

int main()
{
    bool done = false;
    char input[80];
    int value;

    RBnode::newRBTree();

    do
    {
        cout << "RED BLACK TREE " << endl;
        cout << "Add" << endl;
        cout << "Read" << endl;
	cout << "Print" << endl;
	cout << "Search" << endl;
	cout <<"Delete" << endl;
	cout << "Done" << endl;
	cout << "Command: ";

        cin.getline(input, 80);
	if (!strcmp(input, "Add"))
	{
            cin >> value;
	    RBnode::insert(value);
	}
	else if (!strcmp(input, "Read"))
	{
            cin.getline(input, 80);
            ifstream inputFile(input);
	    while (inputFile >> value)
	    {
                RBnode::insert(value);
                inputFile.get();		
	    }
	}
	else if (!strcmp(input, "Print"))
	{
	    RBnode::print();
	}
	else if (!strcmp(input, "Search"))
	{
            cin >> value;
	    if (RBnode::search(value) == true) 
	    {
                cout << value << " is in the tree" << endl;
	    }
	    else
	    {
                cout << value << " is not in the tree" << endl;
	    }
	}
	else if (!strcmp(input, "Delete"))
	{
            cin >> value;
	    RBnode::remove(value);
	}
	else if (!strcmp(input, "Done"))
	{
	    done = true;
	}
    } while (!done);

    return 1;
}
