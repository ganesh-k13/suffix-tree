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
	Node *suffixLink;
	
	int start;
	int *end;
	
	int suffixIndex;
	
	public:
		
		Node(int start, int *end);
		~Node();
		Node *get_children(int index);
		Node *get_suffixLink();
		int get_suffixIndex();
		int get_start();
		int *get_end();
		
		void set_children(int index, Node* value);
		void set_suffixIndex(int index);
		void set_suffixlink(Node *link);
		void set_start(int start);
		void set_end(int *end);
};
#endif