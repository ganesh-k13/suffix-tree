#include "../include/Node.h"

Node::Node(int start, int *end) {

	for (int i = 0; i < MAX_CHAR; i++)
		set_children(i, NULL); // node->children[i] = NULL;

	// node->set_suffixlink(root); // node->suffixLink = root;
	set_start(start);
	set_end(end);

	/*suffixIndex will be set to -1 by default and
	actual suffix index will be set later for leaves
	at the end of all phases*/
	set_suffixIndex(-1);
}


Node::~Node() {
	
}


 Node* Node::get_children(int index) { 
	return children[index]; 
}

 Node* Node::get_suffixLink() { 
	return suffixLink; 
}

 int Node::get_suffixIndex() { 
	return suffixIndex;
}

 int Node::get_start() { 
	return start; 
}

 int* Node::get_end() {
	return end; 
}


 void Node::set_children(int index, Node* value) {
	children[index] = value; 
}

 void Node::set_suffixIndex(int index) { 
	suffixIndex = index; 
}

 void Node::set_suffixlink(Node *link) { 
	suffixLink = link; 
}

 void Node::set_start(int start) { 
	this->start = start; 
}

 void Node::set_end(int *end) {
	this->end = end; 
}