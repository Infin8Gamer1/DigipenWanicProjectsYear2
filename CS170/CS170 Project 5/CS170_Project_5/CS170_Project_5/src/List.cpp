#include <iomanip>  // setw
#include <iostream> // ostream, endl
#include "List.h"

namespace CS170
{
    /*
	Public Methods
	*/

	List::List()
	{
		head = nullptr; // pointer to the head of the list
		tail = nullptr; // pointer to the last node
		size = 0;   // number of items in the list
		list_count++;
	}

	List::List(const List & list)
	{
	}

	List::List(const int * array, int size)
	{
	}

	List::~List()
	{
	}

	void List::push_front(int value_)
	{
		//create the new node
		Node* tempNode = new_node(value_);

		//check that the tail and the head aren't currently null
		if (tail != nullptr && head != nullptr) {
			//set the new heads next pointer to be the old heads pointer
			tempNode->next = head;
			//set the head pointer to the new head
			head = tempNode;
		}
		else {
			//if they are null then make this new node the new head and tail
			head = tempNode;
			tail = tempNode;
		}
	}

	void List::push_back(int value_)
	{
		//create the new node
		Node* tempNode = new_node(value_);

		//check that the tail and the head aren't currently null
		if (tail != nullptr && head != nullptr) {
			//set the current tails pointer to the new tail
			tail->next = tempNode;
			//set the tail to the new tail
			tail = tempNode;
		} else {
			//if they are null then make this new node the new head and tail
			head = tempNode;
			tail = tempNode;
		}
		
	}

	int List::pop_front()
	{
		//make a temp node
		Node* temp = head->next;
		//store the old head data
		int oldHeadData = head->data;
		//delete the old head
		delete head;
		//make the new head the temp
		head = temp;
		
		return oldHeadData;
	}

	int List::pop_back()
	{
		//make a temp node and set it to the head
		Node* temp = head;

		//loop until we find the node that is pointing to the tail
		while (temp->next != tail)
		{
			temp = temp->next;
		}
		
		//store the old tail data
		int oldTailData = tail->data;

		//delete the old tail
		delete tail;

		//make sure that the new tail isn't pointing to the old tail (that we deleted)
		temp->next = nullptr;

		//make the new tail the temp
		tail = temp;

		return oldTailData;
	}

	void List::remove_node_by_value(int value_)
	{
		//create a pointer to the node that we want to get rid of
		Node* nodeToBeDeleted = head;

		//loop until we find a node that has the value we are looking for
		while (nodeToBeDeleted->data == value_)
		{
			nodeToBeDeleted = nodeToBeDeleted->next;
		}

		//create a pointer to the previous node from the one we want to delete
		Node* previousNode = head;

		//loop until we find the node that is pointing to the node that we are going to delete
		while (previousNode->next != nodeToBeDeleted)
		{
			previousNode = previousNode->next;
		}

		//make a pointer to the next node that the node we are getting rid of is pointing to
		Node* nextNode = nodeToBeDeleted->next;

		//update the previous node to point to the next node
		previousNode->next = nextNode;

		//delete the one we want to get rid of
		delete nodeToBeDeleted;
	}

	void List::insert_node_at(int location_, int value_)
	{
		//create a pointer to the node that we want to add
		Node* nodeToBeAdded = new_node(value_);

		//create a pointer to the previous node from the one we want to delete
		Node* nodeAtLocation = head;

		//loop until we find the node that is at the desired location
		for (size_t i = 0; i < location_; i++)
		{
			nodeAtLocation = nodeAtLocation->next;
		}

		//make a pointer to the next node that the node we are getting rid of is pointing to
		Node* previousNode = head;

		//loop until we find the node that previous to the node at the location
		while (previousNode->next != nodeAtLocation)
		{
			previousNode = previousNode->next;
		}

		//set the new nodes next to be the the node that was at the location
		nodeToBeAdded->next = nodeAtLocation;

		//set the previous nodes next to be the new node
		previousNode->next = nodeToBeAdded;
	}

	List & List::operator=(const List & list_)
	{
		//clear this list
		this->clear();

		//make a temp node
		Node* temp = list_.head;

		//loop through the entire list_ and add the temp node
		do {
			this->push_back(temp->data);
			temp = temp->next;
		} while (temp != list_.tail);

		return *this;
	}

	List List::operator+(const List & list_) const
	{
		//make a new list


		//make a temp node
		Node* temp = list_.head;

		//loop through the entire list_ and add the temp node
		do {
			this->push_back(temp->data);
			temp = temp->next;
		} while (temp != list_.tail);

		return *this;
	}

	List & List::operator+=(const List & list_)
	{
		// TODO: insert return statement here
	}

	int List::list_size() const
	{
		return 0;
	}

	bool List::empty() const
	{
		return false;
	}

	void List::clear()
	{
	}

	/////////////////////////////////////////////////////////////////////////
	// Function: operator<<
	//  Purpose: Output the list into an ostream object
	//   Inputs: os - ostream object
	//           list - the List to output
	//  Outputs: Returns an ostream object.
	/////////////////////////////////////////////////////////////////////////
	std::ostream & operator<<(std::ostream & os_, const List &list_)
	{
		// Start at the top
		List::Node *pnode = list_.head;

		// Print each item
		while (pnode != 0)
		{
			os_ << std::setw(4) << pnode->data;
			pnode = pnode->next;
		}
		os_ << std::endl;
		return os_;
	}

	int List::created_list_count()
	{
		return list_count;
	}

	int List::alive_node_count()
	{
		return Node::nodes_alive;
	}


	/*
	Private Methods
	*/

	List::Node::Node(int _data)
	{
		next = nullptr;  // pointer to the next Node
		data = _data;  // the actual data in the node
		nodes_alive++;
	}

	List::Node::~Node()
	{
		nodes_alive--;
	}

	List::Node *List::new_node(int data) const
	{
		// Make sure we have room
		Node *node = new Node(data); // create the node
		return node;
	}

	

} //namespace CS170
