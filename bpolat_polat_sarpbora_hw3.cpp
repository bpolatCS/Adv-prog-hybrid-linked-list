#include <iostream>
#include <sstream>
#include "bpolat_polat_sarpbora_hw3_SubSeqsListClass.h"

using namespace std;

int main()
{
	string input, inputNumbers, numbers, word;
	cout<<"Please enter the numbers in a line: ";
	getline(cin,inputNumbers);
	SubSeqsList sslist;

			
	istringstream correction(inputNumbers); //entering format correction. Based on deleting spaces
	int num;
	while (correction >> num) //taking every number one by one and do the following. After loop finish basicly numbers are also finished.
	{
		if (num >=0)
		{
			if (sslist.insertList(num)) //if positive add num here
			{
				cout<<"Subsequence(s) containing " << num <<" has/have been added"<<endl;
										
			}
			else
			{
				cout<<num <<" has already exist in the list"<<endl;
			}
		}
		else
		{
			num=num*(-1);
			if (sslist.deleteList(num)) //if we need to delete, delete here
			{
				cout << "All subsequence(s) containing " << num << " has/have been deleted" << endl;
			}
			else
			{
				cout << "There is no subsequence that contains " << num << " to be deleted" << endl;
			}

		}
	
	}
	
	cout<<endl<<"FINAL CONTENT"<<endl;

	if (sslist.isListEmpty()) //if list is empty after some operations
	{
		cout<<"List is empty!"<<endl;
	}
	else
	{
		sslist.display();
	}
	cout<<endl;
	
	
	
	return 0;
}
