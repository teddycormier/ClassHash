// This program implements a class for a hash table

#include <iostream>

using namespace std;

const int SIZE = 10;

struct node
{
	string name;
	int IDnum;
	node *next;		  // the next node in each row of the table
	node *prev;		  // the last node in each row of the table
	node *alpha_next; // the next node in the alphabetical double LL
	node *alpha_prev; // the prev node in the alphabetical double LL
};

class hash_table
{
public:
	node *table[SIZE]; // an array of FIRST pointers, one for each row
	int length[SIZE];  // an array to hold the lengths of the LL in each row of the chart
	int size;		   // size of LL
	node *first;	   // points to the first node in the alpha double LL
	node *last;		   // points to the last node in the alpha double LL
	node *temp;
	node *temp2;
	node *runner;
	bool isEmpty; // tracks if the table is empty

	// ADD additional data members if you want

	//  Constructor
	hash_table()
	{
		for (int i = 0; i < SIZE; i++)
		{
			table[i] = NULL;
			length[i] = 0;
			first = NULL;
			last = NULL;
			temp = NULL;
			isEmpty = true;
		}
	}

	//  Methods
	int hashing(int key_ID)
	{
		return key_ID % SIZE;
	}

	void print_table() // Don't change this function
	{
		cout << "-------------------";
		cout << endl;
		for (int i = 0; i < SIZE; i++)
		{
			temp = table[i];
			cout << '|' << i << "| ";
			for (int j = 0; j < length[i]; j++)
			{
				cout << "[" << temp->name << " - " << temp->IDnum << "] -> ";
				temp = temp->next;
			}
			cout << "NULL\n";
		}
		cout << "____________________";
		cout << endl;
		cout << endl;
	}

	void print_alpha(node *temp)
	{
		if (temp == NULL)
		{
			cout << " -> [DONE]\n";
		}
		else
		{
			cout << " -> [" << temp->name << " - " << temp->IDnum << "]\n";
			temp = temp->alpha_next;
			print_alpha(temp);
		}
	}

	void addNode(int key_ID, string name)
	{
		cout << endl;
		cout << "[Please enter a NAME and ID num]\n";
		cout << "NAME -> ";
		cin >> name;
		cout << "ID NUM -> ";
		cin >> key_ID;
		int row = hashing(key_ID);
		temp = table[row];
		table[row] = new node;
		table[row]->name = name;
		table[row]->IDnum = key_ID;
		table[row]->next = temp;
		if (temp != NULL)
		{
			temp->prev = table[row];
		}
		length[row] = (length[row] + 1);

		// ----------------------------

		if (first == NULL || first->name >= table[row]->name)
		{
			table[row]->alpha_next = first;
			first = table[row];
		}
		else
		{
			temp2 = first;
			while (temp2->alpha_next != NULL && temp2->alpha_next->name < temp2->name)
			{
				temp2 = temp2->alpha_next;
			}
			table[row]->alpha_next = temp2->alpha_next;
			temp2->alpha_next = table[row];
		}
	}

	void removeNode(int key_ID)
	{
		int row = hashing(key_ID);
		temp = table[row];
		temp2 = first;

		if (table[row] == NULL)
		{
			cout << "[Your list is now empty]\n";
		}
		else if (table[row]->IDnum == key_ID)
		{
			table[row] = table[row]->next;
			length[row] = (length[row] - 1);
			size--;
		}
		else
		{
			while (temp != NULL && temp->IDnum != key_ID)
			{
				temp = temp->next;
			}
			if (temp == NULL)
			{
				cout << "The number was not found.\n";
			}
			else if (temp->IDnum == key_ID)
			{
				temp->next->prev = temp->prev;
				temp->prev->next = temp->next;
				length[row] = (length[row] - 1);
				size--;
			}
		}
		if (temp == first)
		{
			temp = temp->alpha_next;
			delete first;
			temp->alpha_prev = NULL;
			first = temp;
		}
		else if (temp == last)
		{
			temp = temp->alpha_prev;
			delete last;
			temp->alpha_next = NULL;
			last = temp;
		}
		else
		{
			temp->alpha_next->alpha_prev = temp->alpha_prev;
			temp->alpha_prev->alpha_next = temp->alpha_next;
			delete temp;
		}
	}

	void IDLookup(node *temp, int key_ID)
	{
		if (temp == NULL)
		{
			cout << "[The number you searched for IS NOT in the list]\n";
		}
		else if (key_ID == temp->IDnum)
		{
			cout << "[Your number IS in the list]\n";
		}
		else
		{
			temp = temp->alpha_next;
			print_alpha(temp);
		}
	}

	bool nameLookup(node *temp, string key_name)
	{
		if (temp == NULL)
		{
			return false;
		}
		else if (key_name == temp->name)
		{
			return true;
		}
		else
		{
			temp = temp->alpha_next;
			print_alpha(temp);
		}
	}
};

int main()
{
	int choice, key_ID;
	string name;
	node *temp;
	node *first;
	string key_name;
	hash_table chart; // Declares a hash table called chart

	do
	{
		cout << "_______________________________________________\n"
			 << "[                                             ]\n"
			 << "[ 1. Print the table                          ]\n"
			 << "[ 2. Print the nodes in alphabetical order    ]\n"
			 << "[ 3. Add a node                               ]\n"
			 << "[ 4. Delete a node                            ]\n"
			 << "[ 5. Look up a node in the table by ID number ]\n"
			 << "[ 6. Look up a node in the table by name      ]\n"
			 << "[ 7. Quit                                     ]\n"
			 << "[ What do you want to do:                     ]\n"
			 << "[_____________________________________________]\n\n"
			 << "YOUR CHOICE -> ";
		cin >> choice;

		if (choice == 1)
		{
			chart.print_table();
		}
		else if (choice == 2)
		{
			cout << "--------------------";
			cout << endl;
			chart.print_alpha(chart.first);
			cout << "____________________";
			cout << endl;
		}
		else if (choice == 3)
		{
			chart.addNode(key_ID, name);
		}
		else if (choice == 4)
		{
			cout << "Please enter a number to delete: ";
			cin >> key_ID;
			chart.removeNode(key_ID);
		}
		else if (choice == 5)
		{
			cout << "\nWhat ID number do you want to search for: ";
			cin >> key_ID;
			temp = chart.table[chart.hashing(key_ID)];
			chart.IDLookup(temp, key_ID);
		}
		else if (choice == 6)
		{
			cout << "What name do you want to search for: ";
			cin >> key_name;
			if (chart.nameLookup(chart.first, key_name))
				cout << "[" << key_name << " has been found!]\n";
			else
				cout << "[" << key_name << " IS NOT in the chart]\n";
		}

	} while (choice != 7);

	return 0;
}
