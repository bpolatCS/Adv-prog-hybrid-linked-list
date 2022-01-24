#ifndef _BPOLAT_POLAT_SARPBORA_HW3_SUBSEQSLISTCLASS_H
#define _BPOLAT_POLAT_SARPBORA_HW3_SUBSEQSLISTCLASS_H

#include <iostream>

using namespace std;

struct SubSeqNode
{
	int value;
	SubSeqNode *next;

	SubSeqNode(int val, SubSeqNode *n)
		:value(val), next(n)
	{};
};

struct SubSeqHeadNode
{
	int size; // number of elements in the subsequence
	SubSeqNode *sHead; // head of the subsequence list
	SubSeqHeadNode *next;

	SubSeqHeadNode(int sz, SubSeqNode *sH, SubSeqHeadNode *n)
		:size(sz), sHead(sH), next(n)
	{};
};


class SubSeqsList
{
public:
	SubSeqsList();  //default constructor that creates an empty list
	void display();//the display the entire structure
	bool insertList(int num); //to insert one or more subsequence list(s) to data structure
	bool deleteList(int num); //to delete one or more subsequence list(s) from the data structure, 	
	~SubSeqsList(); //destructor
	bool isListEmpty(); //at the end of the program
	// member functions come here

private:
	SubSeqHeadNode * hHead;
	SubSeqHeadNode *findOneNode;
	bool doesExist(int num,  SubSeqHeadNode * findOneNode); //to find whether a particular value exists in the data structure
	SubSeqHeadNode * copyPrevious(SubSeqHeadNode * nodeCopy); //deep copy process
	SubSeqNode * findLastNode(SubSeqNode * nodetoFindLast); // finding last node of SubSeqNode
	SubSeqHeadNode * findLastHeadNode(SubSeqHeadNode * nodetoFindLast); // finding last node of SubSeqHeadNode
	bool doesExistForDeletion(int num, SubSeqHeadNode * findOneNode); //looking if it is exist for deletion
	void deleteSubSeqNode(SubSeqHeadNode * findOneNode); //deleting SubSeqNode
	void suitablePlace(SubSeqHeadNode *inserted); //key function for the ordering. To find place that node should be placed.
	bool compareTwo(SubSeqHeadNode *first, SubSeqHeadNode *second);	// comparing consecutive two nodes
};

#endif