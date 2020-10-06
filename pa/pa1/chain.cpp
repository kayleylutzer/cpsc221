#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
  clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
		Node* tail = walk(head_, length_);
		tail->next = new Node(ndata);
		tail->next->next = head_;
        length_++;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
	
	
  Node* i_node_prev = walk(head_, i-1);
  Node* j_node_prev = walk(head_, j-1);

  Node* i_node = i_node_prev->next;
  Node* j_node = j_node_prev->next;
  
  Node* i_node_next = i_node->next;
  Node* j_node_next = j_node->next;
  
  if(i == j - 1){
	  i_node->next = j_node_next;
	  j_node->next = i_node;
	  i_node_prev->next = j_node;
  }else if (j == i - 1){
	  j_node->next = i_node_next;
	  i_node->next = j_node;
	  j_node_prev->next = i_node;
  }else{
	i_node->next = j_node_next;
	j_node_prev->next = i_node; //i_node now has a before and after
	
	j_node->next = i_node_next;
	i_node_prev->next = j_node; //j_node now has a before and after
  }

}

/**
 * Reverses the chain
 */
void Chain::reverse()
{ 	
	for(int x = 1; x <= ((length_ % 2 == 0) ? length_ / 2 : (length_ - 1) / 2); x++)
		swap(x, length_ - x + 1);
}

/*
* Modifies the current chain by "rotating" every group of k nodes by one position.
* In every k-node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/

void Chain::rotate(int k)
{
	if(k > length_ || k == 1)
		return;
	
	for(int i = 1; i < length_; i += k){
		for(int j = 0; j < k - 1; j++){
			swap(j+i, j+i+1);	
			}
	}
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
	/*
  	head_ = new Node();
  
	for(int x = 1; x <= length_; x++){
			Node* temp = walk(head_, x);
			delete(temp);
	} */

  	Node* curr = head_->next;
	Node* placeholder;
    while (curr != head_) {
         placeholder = curr->next;
         delete curr;
         curr = placeholder;
     }
     delete head_;
     length_ = 0;
  
  //delete(head_);
  
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
	
	width_ = other.width_;
    height_ = other.height_;
	length_ = 0;

    head_ = new Node();
    
	head_->next = head_;

    Node* other_curr = other.head_->next;

     for (int i = 0; i < other.size(); i++) {
         insertBack(other_curr->data);
         other_curr = other_curr->next;
     }

}
