#include <string>
#include <vector>
#include "Node.h"

using namespace std;

extern vector <int> index_list;

class SuffixTree {
	string text; 
	Node *root; //Pointer to root node

	Node *lastNewNode;
	Node *activeNode;

	int activeEdge;
	int activeLength;

	int remainingSuffixCount;
	int leafEnd;
	int *rootEnd;
	int *splitEnd;
	int size; //Length of input string
	
	public: 
		
		SuffixTree(string text);
		~SuffixTree();
		Node *get_root();
		Node *newNode(int start, int *end);

		int edgeLength(Node *n);

		int walkDown(Node *currNode);

		void extendSuffixTree(int pos);

		void print(int i, int j);
		//Print the suffix tree as well along with setting suffix index
		//So tree will be printed in DFS manner
		//Each edge along with it's suffix index will be printed
		void setSuffixIndexByDFS(Node *n, int labelHeight);

		void freeSuffixTreeByPostOrder(Node *n);

		/*Build the suffix tree and print the edge labels along with
		suffixIndex. suffixIndex for leaf edges will be >= 0 and
		for non-leaf edges will be -1*/
		void buildSuffixTree();
		
		int traverseEdge(const char *str, int idx, int start, int end);

		int doTraversalToCountLeaf(Node *n);

		int countLeaf(Node *n);

		int doTraversal(Node *n, const char* str, int idx);

		vector <int> checkForSubString(const char* str);
};