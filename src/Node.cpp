#include "../include/Node.h"

Node::Node(int start, int *end) {

	for (int i = 0; i < MAX_CHAR; i++)
		set_children(i, NULL); // node->children[i] = NULL;

	// node->set_suffix_link(root); // node->suffix_link = root;
	set_start(start);
	set_end(end);

	/*suffix_index will be set to -1 by default and
	actual suffix index will be set later for leaves
	at the end of all phases*/
	set_suffix_index(-1);
}


Node::~Node() {
	
}


 Node* Node::get_children(int index) { 
	return children[index]; 
}

 Node* Node::get_suffix_link() { 
	return suffix_link; 
}

 int Node::get_suffix_index() { 
	return suffix_index;
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

 void Node::set_suffix_index(int index) { 
	suffix_index = index; 
}

 void Node::set_suffix_link(Node *link) { 
	suffix_link = link; 
}

 void Node::set_start(int start) { 
	this->start = start; 
}

 void Node::set_end(int *end) {
	this->end = end; 
}