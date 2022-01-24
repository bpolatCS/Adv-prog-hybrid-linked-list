#include "bpolat_polat_sarpbora_hw3_SubSeqsListClass.h"

SubSeqsList::SubSeqsList() // default constructor
{
	hHead=NULL;
}

SubSeqHeadNode * SubSeqsList::copyPrevious(SubSeqHeadNode * nodeCopy)
{
	// copy the nodeCopy with deep copying
	SubSeqHeadNode *newCopy = new SubSeqHeadNode(nodeCopy->size, NULL, NULL); 
	newCopy->sHead = new SubSeqNode(nodeCopy->sHead->value, NULL);

	SubSeqNode *itr1, *itr2;

	itr1=nodeCopy->sHead->next;
	itr2= newCopy->sHead;
	while (itr1 != NULL)
	{
		itr2 ->next = new SubSeqNode(itr1->value, NULL);
		itr1 = itr1->next;
		itr2 = itr2->next;
	}
	return newCopy;
}

void SubSeqsList::suitablePlace(SubSeqHeadNode *inserted)
{
	//When the nodes are adding, we should find a appropirate place according to first size second value. This function finds appr. place
	SubSeqHeadNode *headIteration= hHead;
	if (inserted->size == 1 && inserted->sHead->value < headIteration->sHead->value)
	{		
		hHead = inserted;
		hHead->next = headIteration;
	}
	else
	{
		while (headIteration != NULL && headIteration->next != NULL && inserted->size > headIteration->next->size)
		{
			headIteration=headIteration->next;
		}
		while (headIteration != NULL && headIteration->next != NULL && inserted->size >= headIteration->next->size )
		{
			if (compareTwo(inserted, headIteration->next))
			{
				SubSeqHeadNode * temp = headIteration->next; //place holder
				headIteration->next = inserted;
				inserted ->next = temp;
				return;
			}
			else
			{
				headIteration=headIteration->next;
			}
		}
	
		SubSeqHeadNode * temp = headIteration->next; 
		headIteration->next = inserted;
		inserted ->next = temp;
	}
	

}

bool SubSeqsList::insertList(int num) //to insert one or more subsequence list(s) to data structure
{
	SubSeqHeadNode *headIteration= hHead;
	SubSeqHeadNode *brandNewNode;


	if(headIteration == NULL) //at the first time we put first num. Than goes to second num
	{
		hHead = new SubSeqHeadNode(1, new SubSeqNode(num, NULL), NULL);

		return true;
	}
	else //beginning of the second num, function goes here directly
	{	
		headIteration= hHead;
		while (headIteration->next != NULL)
		{
			if (doesExist(num, findOneNode)) // if there is a value that same with incoming num then return false and break the chain.
			{
				return false;
			}
			headIteration = headIteration->next;
		}

		SubSeqHeadNode *headIteration= hHead;  

		brandNewNode = new SubSeqHeadNode(1, new SubSeqNode(num, NULL), NULL); //every time we need to this node 1 | (num). It creates that node and add at the end of the hHead.

		suitablePlace(brandNewNode);

		while (headIteration != NULL) //after adding size 1 node, rest of the code adds other size'd nodes like 2 | 1 2 or 3 | 1 2 3
		{
			SubSeqNode *headIterationInsideLastNode=headIteration->sHead;
			headIterationInsideLastNode=findLastNode(headIterationInsideLastNode);

			if (headIterationInsideLastNode->value < num) //Algorithm goes as every iteration of num value, if num bigger than head nodes value, copy it and create new node put it and find approriate place to add.
			{
				SubSeqHeadNode* newlyCopy = copyPrevious(headIteration);

				SubSeqHeadNode *tempHeadIteration=headIteration;

				newlyCopy->size=tempHeadIteration->size+1; //size changing / upgrading

				SubSeqNode *ptr = newlyCopy->sHead;

				ptr=findLastNode(ptr); // update ptr to to last of the node (untill NULL)

				SubSeqNode *newSubSeq = new SubSeqNode(num,NULL); //upgraded size -> sHead

				ptr->next=newSubSeq;

				suitablePlace(newlyCopy); // find suitable place and put it there

			}
			headIteration=headIteration->next;
		}	
	}
	return true;
}

SubSeqHeadNode * SubSeqsList::findLastHeadNode(SubSeqHeadNode * nodetoFindLast) // to find last node
{
	SubSeqHeadNode *lastNode = nodetoFindLast; 
	while (lastNode->next != NULL)
		lastNode = lastNode->next;
	return lastNode;
}

SubSeqNode * SubSeqsList::findLastNode(SubSeqNode * nodetoFindLast)  //to find last node
{
	SubSeqNode *lastNode = nodetoFindLast;
	while (lastNode->next != NULL)
		lastNode = lastNode->next;
	return lastNode;
}

bool SubSeqsList::compareTwo(SubSeqHeadNode *actual, SubSeqHeadNode *nextComparedNode) //it is used in 27'th line function.
{
	SubSeqNode *temp1= actual->sHead;
	SubSeqNode *temp2 = nextComparedNode-> sHead;
	int counter = 0;
	while (counter < actual->size)
	{
		if (temp1->value < temp2->value)
		{
			return true;
		}
		else if (temp1->value > temp2->value)
		{
			return false;
		}
		else
		{
			counter ++;
			temp1=temp1->next;
			temp2=temp2->next;
		}	
	}
	return true;
}

void SubSeqsList::display()
{

	SubSeqHeadNode* headNodePtr = hHead;
	SubSeqNode* subSeqNodePtr = NULL;

	while (headNodePtr != NULL)
	{
		cout<<headNodePtr->size<<" | ";
		subSeqNodePtr=headNodePtr->sHead;
		cout << subSeqNodePtr->value;
		subSeqNodePtr=subSeqNodePtr->next;
		while (subSeqNodePtr != NULL)
		{
			cout << " --> " << subSeqNodePtr->value;
			subSeqNodePtr = subSeqNodePtr->next;
		}
		cout<<endl;

		headNodePtr=headNodePtr->next;
	}
}

bool SubSeqsList::doesExist(int num, SubSeqHeadNode * findOneNode) //to find whether a particular value exists in the data structure
{
	SubSeqHeadNode *headIteration= hHead;
	while (headIteration -> next != NULL && headIteration->next != findOneNode) //findOneNode = points last node that size has 1. If any num placed in node that has size 1, it means no need to add to the list.
	{
		if (headIteration-> sHead->value == num)
		{
			return true;
		}
		headIteration=headIteration->next;
	}
	return false;
}

SubSeqsList::~SubSeqsList () //destructor
{
	SubSeqHeadNode * ptr = hHead;
	SubSeqNode * insideNode1, *insideNode2;

	while (ptr != NULL) 
	{
		insideNode1 = hHead->sHead;
		insideNode2 = insideNode1;
					 
		while (insideNode1 != NULL)
		{		
			insideNode1 = insideNode1->next;

			delete insideNode2;
			insideNode2 = insideNode1;		
		}
		ptr = ptr->next;
		delete hHead;
		hHead=ptr;
	}	
}

bool SubSeqsList::isListEmpty() //at the and of the program look for the emptyness.
{
	return (hHead==NULL);
}

bool SubSeqsList::doesExistForDeletion(int num, SubSeqHeadNode * findOneNode) //to find whether a particular value exists in the data structure when the deletion process
{
	SubSeqNode *nodeIteration= findOneNode->sHead;

	while (nodeIteration != NULL) //findOneNode = points last node that size has 1. If any num placed in node that has size 1, it means no need to add to the list.
	{
		if (nodeIteration->value == num)
		{
			return true;
		}
		nodeIteration=nodeIteration->next;
	}
	return false;
}

void SubSeqsList::deleteSubSeqNode(SubSeqHeadNode * toBeDeleted) //to delete SubSeqNode. Used in deleteList function
{
	SubSeqNode *tempSubNode = NULL;
	tempSubNode = toBeDeleted->sHead;
	SubSeqNode *tempSubNode2 = tempSubNode;	

	while (tempSubNode != NULL)
	{
		tempSubNode2 = tempSubNode->next;
		delete tempSubNode;
		tempSubNode = tempSubNode2;
		
	}
	delete toBeDeleted;
}
bool SubSeqsList::deleteList(int num) //to delete one or more subsequence list(s) from the data structure, 
{
	SubSeqHeadNode * ptr = hHead;
	bool isOnce = false;
	while (ptr != NULL)
	{
		if (doesExistForDeletion(num,ptr))
		{
			isOnce=true;
			if (hHead->next == NULL)    
			{				
				deleteSubSeqNode(ptr);				
				hHead=NULL;
				ptr=NULL;
				continue;
			}
			else
			{
				if (hHead == ptr)
				{
					hHead = hHead->next;
					deleteSubSeqNode(ptr);
					ptr=hHead;
				}
				else
				{
					SubSeqHeadNode *tempdel = hHead;
					while (tempdel->next != ptr)
						tempdel=tempdel->next;
					tempdel->next = ptr->next;
					deleteSubSeqNode(ptr);
					ptr=tempdel;
				}
			}
		}
		ptr=ptr->next;
	}
	return isOnce;

}




