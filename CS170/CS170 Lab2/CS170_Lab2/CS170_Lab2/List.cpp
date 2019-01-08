////////////////////////////////////
//CS170 Linked Lists
//By: Jacob Holyfield
////////////////////////////////////

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
		//if the list is empty just give up
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

		//if the head is the node we are trying to delete then
		if (head == nodeToBeDeleted) {
			//if there is a next node move the head to be that one. other wise make the list empty.
			if (nodeToBeDeleted->next != nullptr) {
				head = nodeToBeDeleted->next;
			} else {
				//make the list empty
				clear();
				return;
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

	void List::insert_node_sorted(int value_)
	{
		//if the head is null then just add the value to the front
		if (head == nullptr) {
			push_front(value_);
			return;
		}

		//if the value is smaller than the head then just add to the front
		if (head->data > value_) {
			push_front(value_);
			return;
		}

		//get the node that has the closest value
		Node * nodeBiggerThanValue = head;

		do {
			nodeBiggerThanValue = nodeBiggerThanValue->next;
			//if the next node is null then just add the value to the end
			if (nodeBiggerThanValue == nullptr) {
				push_back(value_);
				return;
			}
		} while (nodeBiggerThanValue->data < value_);
		

		//get the node previous to the big.exe node
		Node * nodePreviousToNodeBigger = head;
		while (nodePreviousToNodeBigger->next != nodeBiggerThanValue)
		{
			nodePreviousToNodeBigger = nodePreviousToNodeBigger->next;
		}

		//create the node to be added
		Node *nodeToBeAdded = new_node(value_);

		//make previous node point to new node
		nodePreviousToNodeBigger->next = nodeToBeAdded;

		//make the new node point to the old node at its position
		nodeToBeAdded->next = nodeBiggerThanValue;

		//increase the size
		size += 1;
	}

	void List::merge(List & list_)
	{
		//check if list's are null
		if (list_.head == nullptr) {
			return;
		}
		if (head == nullptr && list_.head != nullptr) {
			head = list_.head;
			tail = list_.tail;
			size = list_.size;

			list_.head = nullptr;
			list_.tail = nullptr;
			list_.size = 0;

			return;
		}

		//set pointers
		Node * Curr1 = head;
		Node * Curr2 = list_.head;

		//set the new head to the smaller of the two currs
		Node * newHead = nullptr;

		if (Curr1->data < Curr2->data) {
			newHead = Curr1;
			Curr1 = Curr1->next;
		} else {
			newHead = Curr2;
			Curr2 = Curr2->next;
		}

		Node * newTail = newHead;

		while (Curr1 != nullptr && Curr2 != nullptr)
		{
			//Compare the value of the left node with the right node
			//If the left node is less than or equal to the right node
			if (Curr1->data <= Curr2->data) {
				//Place the left node in the new list
				newTail->next = Curr1;
				newTail = Curr1;
				//Move the left pointer to the next node
				Curr1 = Curr1->next;
			}
			//Else(The left node is greater than the right node)
			else {
				//Place the right node in the new list
				newTail->next = Curr2;
				newTail = Curr2;
				//Move the right pointer to the next node
				Curr2 = Curr2->next;
			}
		}

		//If the right side is empty and the left side still has nodes
		if (Curr2 == nullptr && Curr1 != nullptr) {
			//Add all of the nodes from the left side to the end of the list
			while (Curr1 != nullptr)
			{
				//Place the node in the new list
				newTail->next = Curr1;
				newTail = Curr1;
				//Move the pointer to the next node
				Curr1 = Curr1->next;
			}
		}

		//If the left side is empty and the right side still has nodes
		if (Curr1 == nullptr && Curr2 != nullptr) {
			//Add all of the nodes from the right side to the end of the list
			while (Curr2 != nullptr)
			{
				//Place the node in the new list
				newTail->next = Curr2;
				newTail = Curr2;
				//Move the pointer to the next node
				Curr2 = Curr2->next;
			}
		}

		head = newHead;
		tail = newTail;
		size = size + list_.size;

		list_.head = nullptr;
		list_.tail = nullptr;
		list_.size = 0;
	}

	int List::unique()
	{
		int nodesDeleted = 0;

		//if the list is empty just give up
		if (empty()) {
			return nodesDeleted;
		}

		//get node at i pointer
		Node * nodeAtI = head;

		while (nodeAtI != tail)
		{
			if (nodeAtI->next != nullptr && nodeAtI != nullptr) {

				if (nodeAtI->data == nodeAtI->next->data) {
					//get the next next node
					Node * nextNextNode = nodeAtI->next->next;

					//delete the one we want to get rid of
					delete nodeAtI->next;

					nodesDeleted += 1;
					size -= 1;

					if (nextNextNode == nullptr) {
						nodeAtI->next = nullptr;
						tail = nodeAtI;
					} else {
						//patch up the list refs
						nodeAtI->next = nextNextNode;
					}
				}
				else {
					//move on to the next node
					nodeAtI = nodeAtI->next;
				}
			}
		}

		return nodesDeleted;
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
		//if the list being passed in is empty then just return this
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
