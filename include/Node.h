#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#define MAX_CHAR 256

#ifndef NODE_H
#define NODE_H
class Node {
	
	Node *children[MAX_CHAR];
	Node *suffix_link;
	
	int start;
	int *end;
	
	int suffix_index;
	
	public:
		
		Node(int start, int *end);
		~Node();
		Node *get_children(int index);
		Node *get_suffix_link();
		int get_suffix_index();
		int get_start();
		int *get_end();
		
		void set_children(int index, Node* value);
		void set_suffix_index(int index);
		void set_suffix_link(Node *link);
		void set_start(int start);
		void set_end(int *end);
};
#endif