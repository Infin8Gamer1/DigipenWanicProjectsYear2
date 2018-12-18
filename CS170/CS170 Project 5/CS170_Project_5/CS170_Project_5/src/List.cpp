#include <iomanip>  // setw
#include <iostream> // ostream, endl
#include "List.h"

namespace CS170
{
	int List::list_count = 0;
	int List::Node::nodes_alive = 0;

    /*
	Public Methods
	*/

	List::List()
	{
		head = nullptr; // pointer to the head of the list
		tail = nullptr; // pointer to the last node
		size = 0;   // number of items in the list
		List::list_count++;
	}

	List::List(const List & list)
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
		List::list_count++;

		Node *temp = list.head;

		while (temp != nullptr) {
			push_back(temp->data);
			temp = temp->next;
		}
	}

	List::List(const int * array, int _size)
	{
		head = nullptr; // pointer to the head of the list
		tail = nullptr; // pointer to the last node
		size = 0;   // number of items in the list
		List::list_count++;

		for (int i = 0; i < _size; i++)
		{
			push_back(array[i]);
		}
	}

	List::~List()
	{
		this->clear();
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

		size += 1;
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

		size += 1;
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

		size -= 1;
		
		return oldHeadData;
	}

	int List::pop_back()
	{
		//make a temp node and set it to the head
		Node* temp = head;

		//loop until we find the node that is pointing to the tail
		if (temp->next == nullptr) {
			head = nullptr;
		}
		else {
			while (temp->next != tail)
			{
				temp = temp->next;
			}
		}

		
		
		//store the old tail data
		int oldTailData = tail->data;

		//delete the old tail
		delete tail;

		//make sure that the new tail isn't pointing to the old tail (that we deleted)
		temp->next = nullptr;

		//make the new tail the temp
		tail = temp;

		size -= 1;

		return oldTailData;
	}

	void List::remove_node_by_value(int value_)
	{
		if (empty()) {
			return;
		}

		//create a pointer to the node that we want to get rid of
		Node* nodeToBeDeleted = head;

		//loop until we find a node that has the value we are looking for
		while (nodeToBeDeleted->data != value_)
		{
			nodeToBeDeleted = nodeToBeDeleted->next;

			if (nodeToBeDeleted == nullptr) {
				return;
			}
		}

		if (head == nodeToBeDeleted) {
			if (nodeToBeDeleted->next != nullptr) {
				head = nodeToBeDeleted->next;
			} else {
				head = nullptr;
				tail = nullptr;
				size = 0;
				return;
			}

			if (head->next == nullptr) {
				tail = head;
			}
		} else {
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

			if (previousNode->next == nullptr) {
				tail = previousNode;
			}
		}

		//delete the one we want to get rid of
		delete nodeToBeDeleted;

		size -= 1;
	}

	void List::insert_node_at(int location_, int value_)
	{
		//if the location is 0 or smaller then add a node at the front
		if (location_ <= 0) {
			push_front(value_);
		}
		//otherwise if the location is bigger than the size then add a node to the back
		else if (location_ >= size)
		{
			push_back(value_);
		}
		else {
			//get the node at the location
			Node * nodeAtLocation = head;

			for (int i = 0; i < location_; i++)
			{
				nodeAtLocation = nodeAtLocation->next;
			}

			//get the node previous to the location
			Node * nodeAtLocationMinusOne = head;
			while (nodeAtLocationMinusOne->next != nodeAtLocation)
			{
				nodeAtLocationMinusOne = nodeAtLocationMinusOne->next;
			}

			//create the node to be added to the location
			Node *nodeToBeAdded = new_node(value_);

			//make previous node point to new node
			nodeAtLocationMinusOne->next = nodeToBeAdded;

			//make the new node point to the old node at its position
			nodeToBeAdded->next = nodeAtLocation;

			//increase the size
			size += 1;
		}
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
		} while (temp != nullptr);

		return *this;
	}

	List List::operator+(const List & list_) const
	{
		//make a new list
		List outputList = List(*this);

		//make a temp node
		Node* temp = list_.head;

		//loop through the entire list_ and add the temp node
		do {
			outputList.push_back(temp->data);
			temp = temp->next;
		} while (temp != nullptr);

		return outputList;
	}

	List & List::operator+=(const List & list_)
	{
		if (list_.empty()) {
			return *this;
		}

		//make a temp node
		Node* temp = list_.head;

		//loop through the entire list_ and add the temp node
		do {
			this->push_back(temp->data);
			temp = temp->next;
		} while (temp != nullptr);

		return *this;
	}

	int List::list_size() const
	{
		return size;
	}

	bool List::empty() const
	{
		return (head == nullptr || tail == nullptr || size <= 0);
	}

	void List::clear()
	{
		int _size = size;
		for (int i = 0; i < _size; i++)
		{
			pop_back();
		}
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
		Node::nodes_alive += 1;
	}

	List::Node::~Node()
	{
		Node::nodes_alive -= 1;
	}

	List::Node *List::new_node(int data) const
	{
		// Make sure we have room
		Node *node = new Node(data); // create the node
		return node;
	}

} //namespace CS170
