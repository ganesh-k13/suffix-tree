#include <iostream>
#include <string>
#include <stdio.h>

#define MAX_CHAR 256

using namespace std;

class Node {
	
	public:
		Node *children[MAX_CHAR];
		Node *suffix_link;
		
		int start;
		int *end;
		
		int suffixIndex;
		
		Node() {
			for (int i = 0; i < MAX_CHAR; i++)
				children[i] = NULL;
			
			suffix_link = NULL;
			start = 0;
			end = new int;
			
			suffixIndex = 0;
			
		}
		
		Node(int start, int *end) {
			for (int i = 0; i < MAX_CHAR; i++)
				children[i] = NULL;
			
			suffix_link = NULL;
			start = start;
			end = end;

			/*suffixIndex will be set to -1 by default and
			actual suffix index will be set later for leaves
			at the end of all phases*/
			suffixIndex = -1;
		}
		
		// int edge_length() {
			// return *(end) - (start) + 1;
		// }
		
};

Node *root = NULL;

class SuffixTree {
	string text;
	Node *lastNewNode;
	Node *activeNode;
	
	int activeEdge;
	int activeLength;

	int remainingSuffixCount;
	int leafEnd;
	int *rootEnd;
	int *splitEnd;
	int size;
	
	public:
		
		SuffixTree(string s) {
			text = s;
			lastNewNode = NULL;
			activeNode = NULL;
			activeEdge = -1;
			activeLength = 0;

			activeEdge = -1;
			activeLength = 0;
			
			remainingSuffixCount = 0;
			leafEnd = -1;
			rootEnd = new int;
			splitEnd = new int;
			size = -1;
		}
		
		int edge_length(Node *n) {
			
			if(n == root) 
				return 0;
			
			return (*(n->end) - (n->start) + 1);
		}
		
		int walk_down(Node *curr_node) {
			
			// return 0;
			if (activeLength >= edge_length(curr_node)) {
				activeEdge += edge_length(curr_node);
				activeLength -= edge_length(curr_node);
				// return 1;
				activeNode = curr_node;
				return 1;
			}
			return 0;
		}
		
		void extendSuffixTree(int pos) {
			
			leafEnd = pos;

			remainingSuffixCount++;

			lastNewNode = NULL;

			#if 1
			while(remainingSuffixCount > 0) {

				if (activeLength == 0)
					activeEdge = pos;
				//cout << ((text.c_str())[0]);
				// return;
				if (activeNode->children[((text.c_str())[activeEdge])] == NULL)
				{
					
					//Extension Rule 2 (A new leaf edge gets created)
					activeNode->children[((text.c_str())[activeEdge])] = new Node(pos, &leafEnd);
					activeNode->children[((text.c_str())[activeEdge])]->suffix_link = new Node;
					activeNode->children[((text.c_str())[activeEdge])]->suffix_link = root;
					
					if (lastNewNode != NULL)
					{
						lastNewNode->suffix_link = new Node;
						lastNewNode->suffix_link = activeNode;
						lastNewNode = NULL;
					}
				}
				
				#if 1
				else
				{
					Node *next = activeNode->children[((text.c_str())[activeEdge])];
					if (walk_down(next)) {
						continue;
					}
					/*Extension Rule 3 (current character being processed
					is already on the edge)*/
					// return;
					if (text[next->start + activeLength] == text[pos])
					{
						if(lastNewNode != NULL && activeNode != root)
						{
							lastNewNode->suffix_link = new Node;
							lastNewNode->suffix_link = activeNode;
							lastNewNode = NULL;
						}

						activeLength++;
						break;
					}

					splitEnd = new int;
					*splitEnd = next->start + activeLength - 1;

					
					Node *split = new Node(next->start, splitEnd);
					activeNode->children[((text.c_str())[activeEdge])] = split;

					//New leaf coming out of new internal node
					split->children[((text.c_str())[pos])] = new Node(pos, &leafEnd);
					next->start += activeLength;
					split->children[((text.c_str())[next->start])] = next;

					/*We got a new internal node here. If there is any
					internal node created in last extensions of same
					phase which is still waiting for it's suffix link
					reset, do it now.*/
					if (lastNewNode != NULL) {
					/*suffixLink of lastNewNode points to current newly
					created internal node*/
						lastNewNode->suffix_link = new Node;
						lastNewNode->suffix_link = split;
					}
					
					
					lastNewNode = split;
				}

				/* One suffix got added in tree, decrement the count of
				suffixes yet to be added.*/
				remainingSuffixCount--;
				if (activeNode == root && activeLength > 0) //APCFER2C1
				{
					activeLength--;
					activeEdge = pos - remainingSuffixCount + 1;
				}
				else if (activeNode != root) {
					activeNode = activeNode->suffix_link;
				}
				
				#endif
			} 
			#endif
		}
		
		void build_tree(string text) {
			size = text.size();
			*rootEnd = -1;
			
			root = new Node(-1, rootEnd);
			
			activeNode = root; //First activeNode will be root
			for (int i = 0; i < size; i++)
				extendSuffixTree(i);
			int labelHeight = 0;
			// setSuffixIndexByDFS(root, labelHeight);
			
		}
		
		void print(int i, int j) {
			int k;
			for (k=i; k<=j; k++)
				printf("%c", text[k]);
		}
		
		void setSuffixIndexByDFS(Node *n, int labelHeight) {
			if (!n)
				return;
			if (n->start != -1) {
				//Print the label on edge from parent to current node
				//Uncomment below line to print suffix tree
			print(n->start, *(n->end));
			}
			int leaf = 1;
			int i;
			for (i = 0; i < MAX_CHAR; i++) {
				if (n->children[i] != NULL) {
					//Uncomment below two lines to print suffix index
				if (leaf == 1 && n->start != -1)
					printf(" [%d]\n", n->suffixIndex);

					//Current node is not a leaf as it has outgoing
					//edges from it.
					leaf = 0;
					setSuffixIndexByDFS(n->children[i], labelHeight +
										edge_length(n->children[i]));
				}
			}
			if (leaf == 1) {
				n->suffixIndex = size - labelHeight;
				//Uncomment below line to print suffix index
				printf(" [%d]\n", n->suffixIndex);
			}
		}
		
		void freeSuffixTreeByPostOrder(Node *n) {
			if (n == NULL)
				return;
			int i;
			for (i = 0; i < MAX_CHAR; i++)
			{
				if (n->children[i] != NULL)
				{
					freeSuffixTreeByPostOrder(n->children[i]);
				}
			}
			if (n->suffixIndex == -1)
				delete (n->end);
			delete (n);
		}
		int do_traversal(Node *n, int label_height, int* max_height, int* substring_start_index)
		{
			if(n == NULL)
			{
				return NULL;
			}
			int i=0;
			int ret = -1;
			if(n->suffixIndex < 0) //If it is internal node
			{
				for (i = 0; i < MAX_CHAR; i++)
				{
					if(n->children[i] != NULL)
					{
						ret = do_traversal(n->children[i], label_height + 
							edgeLength(n->children[i]), 
							max_height, substring_start_index);
						 
						if(n->suffixIndex == -1)
							n->suffixIndex = ret;
						else if((n->suffixIndex == -2 && ret == -3) ||
							(n->suffixIndex == -3 && ret == -2) || 
							n->suffixIndex == -4)
						{
							n->suffixIndex = -4;//Mark node as XY
							//Keep track of deepest node
							if(*max_height < label_height)
							{
								*max_height = label_height;
								*substring_start_index = *(n->end) - 
									label_height + 1;
							}
						}
					}
				}
			}
			else if(n->suffixIndex > -1 && n->suffixIndex < size1)//suffix of X
				return -2;//Mark node as X
			else if(n->suffixIndex >= size1)//suffix of Y
				return -3;//Mark node as Y
			return n->suffixIndex;
		}
		 
		void getLongestCommonSubstring()
		{
			int max_height = 0;
			int substring_start_index = 0;
			// do {
				// printf("Enter");
				do_traversal(root, 0, &max_height, &substring_start_index);
			// }while(max_height != 0);
			int k;
			for (k=0; k<max_height; k++)
				printf("%c", text[k + substring_start_index]);
			if(k == 0)
				printf("No common substring");
			else
				printf(", of length: %d",max_height);
			printf("\n");
		}
};

int main() {
	
	string s = "Hello";
	
	SuffixTree *st = new SuffixTree(s);
	
	// int *arr = new int;
	
	// cout << (arr == NULL);
	
	// cout << ((s.c_str())[0] == 's');
	
	// cout << endl << (s[0] == s[1]);
	
	st->build_tree(s);
	// st->freeSuffixTreeByPostOrder(root);	
	
	// delete st;
	
	return 0;
}