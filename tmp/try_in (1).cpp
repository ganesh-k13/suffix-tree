// A C program to implement Ukkonen's Suffix Tree Construction
// And find all locations of a pattern in string
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <cstdlib>
#define MAX_CHAR 256

using namespace std;

class Node {
	
	Node *children[MAX_CHAR];
	Node *suffixLink;
	
	int start;
	int *end;
	
	int suffixIndex;
	
	public:
		
		Node(int start, int *end) {
			int i;
			for (i = 0; i < MAX_CHAR; i++)
				set_children(i, NULL); // node->children[i] = NULL;

			// node->set_suffixlink(root); // node->suffixLink = root;
			set_start(start);
			set_end(end);

			/*suffixIndex will be set to -1 by default and
			actual suffix index will be set later for leaves
			at the end of all phases*/
			set_suffixIndex(-1);
		}
	
		Node *get_children(int index) { return children[index]; }
		Node *get_suffixLink() { return suffixLink; }
		int get_suffixIndex() { return suffixIndex; }
		int get_start() { return start; }
		int *get_end() {return end; }
		
		void set_children(int index, Node* value) {children[index] = value; }
		void set_suffixIndex(int index) { suffixIndex = index; }
		void set_suffixlink(Node *link) { suffixLink = link; }
		void set_start(int start) { this->start = start; }
		void set_end(int *end) {this->end = end; }
};


class SuffixTree {
	string text; //Input string
	Node *root; //Pointer to root node

	/*lastNewNode will point to newly created internal node,
	waiting for it's suffix link to be set, which might get
	a new suffix link (other than root) in next extension of
	same phase. lastNewNode will be set to NULL when last
	newly created internal node (if there is any) got it's
	suffix link reset to new internal node created in next
	extension of same phase. */
	Node *lastNewNode;
	Node *activeNode;

	/*activeEdge is represeted as input string character
	index (not the character itself)*/
	int activeEdge;
	int activeLength;

	// remainingSuffixCount tells how many suffixes yet to
	// be added in tree
	int remainingSuffixCount;
	int leafEnd;
	int *rootEnd;
	int *splitEnd;
	int size; //Length of input string
	
	public: 
		
		SuffixTree(string text) {
			this->text = text;
			root = NULL;
			lastNewNode = NULL;
			activeNode = NULL;
			
			activeEdge = -1;
			activeLength = 0;
			
			remainingSuffixCount = 0;
			leafEnd = -1;
			rootEnd = NULL;
			splitEnd = NULL;
			size = -1; //Length of input string
			
			buildSuffixTree();
			
		}
		
		Node *get_root() { return root; }
		
		Node *newNode(int start, int *end)
		{
			Node *node = new Node(start, end);
			node->set_suffixlink(root); // node->suffixLink = root;
			
			return node;
		}

		int edgeLength(Node *n) {
			if(n == root)
				return 0;
			return *(n->get_end()) - (n->get_start()) + 1;
		}

		int walkDown(Node *currNode)
		{
			/*activePoint change for walk down (APCFWD) using
			Skip/Count Trick (Trick 1). If activeLength is greater
			than current edge length, set next internal node as
			activeNode and adjust activeEdge and activeLength
			accordingly to represent same activePoint*/
			if (activeLength >= edgeLength(currNode))
			{
				activeEdge += edgeLength(currNode);
				activeLength -= edgeLength(currNode);
				activeNode = currNode;
				return 1;
			}
			return 0;
		}

		void extendSuffixTree(int pos)
		{
			/*Extension Rule 1, this takes care of extending all
			leaves created so far in tree*/
			leafEnd = pos;

			/*Increment remainingSuffixCount indicating that a
			new suffix added to the list of suffixes yet to be
			added in tree*/
			remainingSuffixCount++;

			/*set lastNewNode to NULL while starting a new phase,
			indicating there is no internal node waiting for
			it's suffix link reset in current phase*/
			lastNewNode = NULL;

			//Add all suffixes (yet to be added) one by one in tree
			while(remainingSuffixCount > 0) {

				if (activeLength == 0)
					activeEdge = pos; //APCFALZ

				// There is no outgoing edge starting with
				// activeEdge from activeNode
				if (activeNode->get_children(text[activeEdge]) == NULL)
				{
					//Extension Rule 2 (A new leaf edge gets created)
					activeNode->set_children(text[activeEdge], newNode(pos, &leafEnd)); // activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);

					/*A new leaf edge is created in above line starting
					from an existng node (the current activeNode), and
					if there is any internal node waiting for it's suffix
					link get reset, point the suffix link from that last
					internal node to current activeNode. Then set lastNewNode
					to NULL indicating no more node waiting for suffix link
					reset.*/
					if (lastNewNode != NULL)
					{
						lastNewNode->set_suffixlink(activeNode); // lastNewNode->suffixLink = activeNode;
						lastNewNode = NULL;
					}
				}
				// There is an outgoing edge starting with activeEdge
				// from activeNode
				else
				{
					// Get the next node at the end of edge starting
					// with activeEdge
					Node *next = activeNode->get_children(text[activeEdge]); //activeNode->children[text[activeEdge]];
					if (walkDown(next))//Do walkdown
					{
						//Start from next node (the new activeNode)
						continue;
					}
					/*Extension Rule 3 (current character being processed
					is already on the edge)*/
					if (text[next->get_start() + activeLength] == text[pos])
					{
						//If a newly created node waiting for it's 
						//suffix link to be set, then set suffix link 
						//of that waiting node to curent active node
						if(lastNewNode != NULL && activeNode != root)
						{
							lastNewNode->set_suffixlink(activeNode);// lastNewNode->suffixLink = activeNode;
							lastNewNode = NULL;
						}

						//APCFER3
						activeLength++;
						/*STOP all further processing in this phase
						and move on to next phase*/
						break;
					}

					/*We will be here when activePoint is in middle of
					the edge being traversed and current character
					being processed is not on the edge (we fall off
					the tree). In this case, we add a new internal node
					and a new leaf edge going out of that new node. This
					is Extension Rule 2, where a new leaf edge and a new
					internal node get created*/
					splitEnd = (int*) malloc(sizeof(int));
					*splitEnd = next->get_start() + activeLength - 1;

					//New internal node
					Node *split = newNode(next->get_start(), splitEnd);
					activeNode->set_children(text[activeEdge], split);// activeNode->children[text[activeEdge]] = split;

					//New leaf coming out of new internal node
					split->set_children(text[pos], newNode(pos, &leafEnd));// split->children[text[pos]] = newNode(pos, &leafEnd);
					next->set_start(next->get_start()+activeLength);
					split->set_children(text[next->get_start()], next); // split->children[text[next->start]] = next;

					/*We got a new internal node here. If there is any
					internal node created in last extensions of same
					phase which is still waiting for it's suffix link
					reset, do it now.*/
					if (lastNewNode != NULL)
					{
					/*suffixLink of lastNewNode points to current newly
					created internal node*/
						lastNewNode->set_suffixlink(split);// lastNewNode->suffixLink = split;
					}

					/*Make the current newly created internal node waiting
					for it's suffix link reset (which is pointing to root
					at present). If we come across any other internal node
					(existing or newly created) in next extension of same
					phase, when a new leaf edge gets added (i.e. when
					Extension Rule 2 applies is any of the next extension
					of same phase) at that point, suffixLink of this node
					will point to that internal node.*/
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
				else if (activeNode != root) //APCFER2C2
				{
					activeNode = activeNode->get_suffixLink();
				}
			}
		}

		void print(int i, int j)
		{
			int k;
			for (k=i; k<=j; k++)
				printf("%c", text[k]);
		}

		//Print the suffix tree as well along with setting suffix index
		//So tree will be printed in DFS manner
		//Each edge along with it's suffix index will be printed
		void setSuffixIndexByDFS(Node *n, int labelHeight)
		{
			if (n == NULL) return;

			if (n->get_start() != -1) //A non-root node
			{
				//Print the label on edge from parent to current node
				//Uncomment below line to print suffix tree
			// print(n->get_start(), *(n->get_end()));
			}
			int leaf = 1;
			int i;
			for (i = 0; i < MAX_CHAR; i++)
			{
				if (n->get_children(i) != NULL)
				{
					//Uncomment below two lines to print suffix index
				// if (leaf == 1 && n->start != -1)
					// printf(" [%d]\n", n->get_suffixIndex());

					//Current node is not a leaf as it has outgoing
					//edges from it.
					leaf = 0;
					setSuffixIndexByDFS(n->get_children(i), labelHeight + edgeLength(n->get_children(i)));
				}
			}
			if (leaf == 1)
			{
				n->set_suffixIndex(size - labelHeight);
				//Uncomment below line to print suffix index
				//printf(" [%d]\n", n->get_suffixIndex());
			}
		}

		void freeSuffixTreeByPostOrder(Node *n)
		{
			if (n == NULL)
				return;
			int i;
			for (i = 0; i < MAX_CHAR; i++)
			{
				if (n->get_children(i) != NULL)
				{
					freeSuffixTreeByPostOrder(n->get_children(i));
				}
			}
			if (n->get_suffixIndex() == -1)
				free(n->get_end());
			free(n);
		}

		/*Build the suffix tree and print the edge labels along with
		suffixIndex. suffixIndex for leaf edges will be >= 0 and
		for non-leaf edges will be -1*/
		void buildSuffixTree()
		{
			size = text.size();
			int i;
			rootEnd = (int*) malloc(sizeof(int));
			*rootEnd = - 1;

			/*Root is a special node with start and end indices as -1,
			as it has no parent from where an edge comes to root*/
			root = newNode(-1, rootEnd);

			activeNode = root; //First activeNode will be root
			for (i=0; i<size; i++)
				extendSuffixTree(i);
			int labelHeight = 0;
			setSuffixIndexByDFS(root, labelHeight);
		}

		int traverseEdge(char *str, int idx, int start, int end)
		{
			int k = 0;
			//Traverse the edge with character by character matching
			for(k=start; k<=end && str[idx] != '\0'; k++, idx++)
			{
				if(text[k] != str[idx])
					return -1; // mo match
			}
			if(str[idx] == '\0')
				return 1; // match
			return 0; // more characters yet to match
		}

		int doTraversalToCountLeaf(Node *n)
		{
			if(n == NULL)
				return 0;
			if(n->get_suffixIndex() > -1)
			{
				printf("\nFound at position: %d", n->get_suffixIndex());
				return 1;
			}
			int count = 0;
			int i = 0;
			for (i = 0; i < MAX_CHAR; i++)
			{
				if(n->get_children(i) != NULL)
				{
					count += doTraversalToCountLeaf(n->get_children(i));
				}
			}
			return count;
		}

		int countLeaf(Node *n)
		{
			if(n == NULL)
				return 0;
			return doTraversalToCountLeaf(n);
		}

		int doTraversal(Node *n, char* str, int idx)
		{
			if(n == NULL)
			{
				return -1; // no match
			}
			int res = -1;
			//If node n is not root node, then traverse edge
			//from node n's parent to node n.
			if(n->get_start() != -1)
			{
				res = traverseEdge(str, idx, n->get_start(), *(n->get_end()));
				if(res == -1) //no match
					return -1;
				if(res == 1) //match
				{
					if(n->get_suffixIndex() > -1)
						printf("\nsubstring count: 1 and position: %d",
									n->get_suffixIndex());
					else
						printf("\nsubstring count: %d", countLeaf(n));
					return 1;
				}
			}
			//Get the character index to search
			idx = idx + edgeLength(n);
			//If there is an edge from node n going out
			//with current character str[idx], travrse that edge
			if(n->get_children(str[idx]) != NULL)
				return doTraversal(n->get_children(str[idx]), str, idx);
			else
				return -1; // no match
		}

		void checkForSubString(char* str)
		{
			int res = doTraversal(root, str, 0);
			if(res == 1)
				printf("\nPattern <%s> is a Substring\n", str);
			else
				printf("\nPattern <%s> is NOT a Substring\n", str);
		}
};
// driver program to test above functions
int main(int argc, char *argv[])
{
	// strcpy(text, "GEEKSFORGEEK;sdalghsd;glhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlhds;lghsdlS$"); 
	// buildSuffixTree(); 
	// printf("Text: GEEKSFORGEEKS, Pattern to search: GEEKS");
	// checkForSubString("lghsdlhds");
	// printf("\n\nText: GEEKSFORGEEKS, Pattern to search: GEEK1");
	// checkForSubString("GEEK1");
	// printf("\n\nText: GEEKSFORGEEKS, Pattern to search: FOR");
	// checkForSubString("FOR");
	// //Free the dynamically allocated memory
	// freeSuffixTreeByPostOrder(root);

	string text = "AABAACAADAABAAABAA$";
	SuffixTree st(text);   
	printf("\n\nText: AABAACAADAABAAABAA, Pattern to search: AABA");
	st.checkForSubString("AABA");
	printf("\n\nText: AABAACAADAABAAABAA, Pattern to search: AA");
	st.checkForSubString("AA");
	printf("\n\nText: AABAACAADAABAAABAA, Pattern to search: AAE");
	st.checkForSubString("AAE");
	//Free the dynamically allocated memory
	st.freeSuffixTreeByPostOrder(st.get_root());

	// strcpy(text, "AAAAAAAAA$");
	// buildSuffixTree(); 
	// printf("\n\nText: AAAAAAAAA, Pattern to search: AAAA");
	// checkForSubString("AAAA");
	// printf("\n\nText: AAAAAAAAA, Pattern to search: AA");
	// checkForSubString("AA");
	// printf("\n\nText: AAAAAAAAA, Pattern to search: A");
	// checkForSubString("A");
	// printf("\n\nText: AAAAAAAAA, Pattern to search: AB");
	// checkForSubString("AB");
	// //Free the dynamically allocated memory
	// freeSuffixTreeByPostOrder(root);

	// cout << (text.at(0) == text[0]);
	return 0;
}
