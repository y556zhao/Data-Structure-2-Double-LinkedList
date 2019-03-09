// Name: Yuchi Zhao
// Date: 25/02/2019
// DoublyLinked List
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include "DoublyLinkedList.hpp"

DoublyLinkedList::Node::Node(DataType data)
{
	value=data;
	prev=NULL;
	next=NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
	size_=0;
	head_=NULL;
	tail_=NULL;
}

DoublyLinkedList::~DoublyLinkedList()
{
	size_=0;
	Node* now=head_;
	Node* temp=NULL;
	while(now!=NULL)
	{
		temp=now->next;   // or temp=temp->next;
		delete now;		  //    delete temp->prev;
		now=temp;
	}
	now=temp=head_=tail_=NULL;
}


bool DoublyLinkedList::empty() const
{
	return size_==0;
}

unsigned int DoublyLinkedList::size() const
{
	return size_;
}


unsigned int DoublyLinkedList::capacity() const
{
	return CAPACITY;
}


void DoublyLinkedList::print() const
{
	if (!empty())
	{
		Node* node_now=head_;
		while (node_now!=NULL)
		{
			cout<<node_now->value<<endl;
			node_now=node_now->next;
		}
	}
}



bool DoublyLinkedList::insert_front(DataType value)
{
	if (size_<CAPACITY)
	{
		Node* new_head=new Node(value);
		new_head->prev=NULL;
		if(empty())
		{
			head_=new_head;
			tail_=new_head;
			new_head -> next = NULL;
		}
		else
		{
			new_head->next=head_;
			head_=new_head;
		}
		size_++;
		return true;
	}
	return false;
}

bool DoublyLinkedList::remove_front()  //returns true if successful
{
	if (!empty())
	{
		Node* new_head=head_->next;
		delete head_;

		if (size_==1)
		{
			head_=NULL;
			tail_=NULL;
		}
		else
		{
			head_=new_head;
			head_->prev=NULL;
		}
		size_--;
		return true;
	}
	return false;
}

bool DoublyLinkedList::insert_back(DataType value)
{
	if (size_<=CAPACITY)
	{
		Node* new_tail=new Node(value);
		if(empty())
		{
			head_=new_tail;
			tail_=new_tail;
			new_tail->next=NULL;
			new_tail->prev=NULL;
		}
		else
		{
			new_tail->prev=tail_;
			tail_->next=new_tail;
			tail_=new_tail;
			tail_->next=NULL;
		}
		size_++;
		return true;
	}
	return false;
}

bool DoublyLinkedList::remove_back()  //returns true if successful
{
	if (!empty())
	{
		Node* new_tail=tail_->prev;
		delete tail_;
		if (size_==1)
		{
			tail_=NULL;
			head_=NULL;
		}
		else
		{
			tail_=new_tail;
			new_tail->next=NULL;
		}
		size_--;
		return true;
	}
	return false;
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) //the new node will insert in front of the original index
{
	if(index==0)
	{
		return insert_front(value);     //plus check if the the index is less than zero
	}
	if(index==size_-1)
	{
		return insert_back(value);
	}
	if (size_<CAPACITY && index<size_)
	{
		Node* old_ind;

		Node* new_node=new Node(value);
		old_ind=head_;
		for (unsigned int i=1;i<=index;i++)
		{
			old_ind=old_ind->next;
		}

		new_node->prev=old_ind->prev;
		new_node->next=old_ind;

		new_node->prev->next=new_node;
		old_ind->prev=new_node;
		size_++;
		return true;
	}
	return false;
}

bool DoublyLinkedList::remove(unsigned int index)
{
	if ((size_-1)>=index)
	{
			if (empty())
			{
				return false;
			}

			else if(size_==1)
			{
				delete(head_);
				head_=NULL;
				tail_=NULL;
				size_--;
				return true;
			}

			else
			{
				Node* old_ind;
				Node* prev_node;
				Node* next_node;
				old_ind=head_;
				for (unsigned int i=0;i<index;i++)    // same as int i=1; i<=index
				{
					old_ind=old_ind->next;
				}
				prev_node=old_ind->prev;
				next_node=old_ind->next;
				prev_node->next=next_node;
				next_node->prev=prev_node;
				delete(old_ind);
				size_--;
				return true;
			}
	}
	return false;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
	if (!empty())
	{
	    int index=0;
		Node* temp=head_;
		while (temp!=NULL && index<=size_)
		{
			if (temp->value==value)
			{
				return index;
			}
			temp=temp->next;
			index++;
		}
	}
	return size_;
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
	if (head_==NULL )
		return tail_->value;
	else
	{
		Node* node_now;
		node_now=head_;
		if (index>=size_)
		{
			return tail_->value;
		}
		for (unsigned int i=0;i<index;i++)
		{
			node_now=node_now->next;
		}
		return node_now->value;
	}
}


bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
	if (head_!=NULL && index<size_)
	{
		Node* node_now=head_;
		for (unsigned int i=0;i<index;i++)
		{
			node_now=node_now->next;
		}
		node_now->value=value;
		return true;
	}
    return false;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
	Node* node_now=head_;
	for(unsigned int i=1;i<=index;i++)
	{
		node_now=node_now->next;
	}
	return node_now;
}


bool DoublyLinkedList::full() const
{
	return size_==CAPACITY;
}

