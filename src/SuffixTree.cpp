#include "../include/SuffixTree.h"

vector <int> index_list;

SuffixTree::SuffixTree(string text) {
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

SuffixTree::~SuffixTree() {
	
}

 Node* SuffixTree::get_root() { 
	return root; 
}

Node* SuffixTree::newNode(int start, int *end) {
	Node *node = new Node(start, end);
	node->set_suffixlink(root); // node->suffixLink = root;
	
	return node;
}

 int SuffixTree::edgeLength(Node *n) {
	return n == root ? 0 : *(n->get_end()) - (n->get_start()) + 1;
}

int SuffixTree::walkDown(Node *currNode) {
	
	if (activeLength >= edgeLength(currNode)) {
		activeEdge += edgeLength(currNode);
		activeLength -= edgeLength(currNode);
		activeNode = currNode;
		return 1;
	}
	return 0;
}

void SuffixTree::extendSuffixTree(int pos) {
	
	leafEnd = pos;

	remainingSuffixCount++;

	lastNewNode = NULL;

	while(remainingSuffixCount > 0) {

		if (activeLength == 0)
			activeEdge = pos;

		if (activeNode->get_children(text[activeEdge]) == NULL) {
			
			activeNode->set_children(text[activeEdge], newNode(pos, &leafEnd)); // activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);

			if (lastNewNode != NULL) {
				lastNewNode->set_suffixlink(activeNode); // lastNewNode->suffixLink = activeNode;
				lastNewNode = NULL;
			}
		}
		
		else {
			Node *next = activeNode->get_children(text[activeEdge]); //activeNode->children[text[activeEdge]];
			if (walkDown(next)) {
				continue;
			}
			if (text[next->get_start() + activeLength] == text[pos]) {
				if(lastNewNode != NULL && activeNode != root) {
					lastNewNode->set_suffixlink(activeNode);// lastNewNode->suffixLink = activeNode;
					lastNewNode = NULL;
				}

				activeLength++;
				break;
			}

			splitEnd = (int*) malloc(sizeof(int));
			*splitEnd = next->get_start() + activeLength - 1;

			Node *split = newNode(next->get_start(), splitEnd);
			activeNode->set_children(text[activeEdge], split);// activeNode->children[text[activeEdge]] = split;

			split->set_children(text[pos], newNode(pos, &leafEnd));// split->children[text[pos]] = newNode(pos, &leafEnd);
			next->set_start(next->get_start()+activeLength);
			split->set_children(text[next->get_start()], next); // split->children[text[next->start]] = next;

			if (lastNewNode != NULL) {
				lastNewNode->set_suffixlink(split);// lastNewNode->suffixLink = split;
			}

			lastNewNode = split;
		}

		remainingSuffixCount--;
		if (activeNode == root && activeLength > 0) {
			activeLength--;
			activeEdge = pos - remainingSuffixCount + 1;
		}
		else if (activeNode != root) {
			activeNode = activeNode->get_suffixLink();
		}
	}
}

void SuffixTree::print(int i, int j) {
	
	for (int k=i; k<=j; k++)
		printf("%c", text[k]);
}

void SuffixTree::setSuffixIndexByDFS(Node *n, int labelHeight) {
	if (n == NULL) return;

	int leaf = 1;
	int i;
	for (i = 0; i < MAX_CHAR; i++) {
		if (n->get_children(i) != NULL) {
			//Uncomment below two lines to print suffix index
		// if (leaf == 1 && n->start != -1)
			// printf(" [%d]\n", n->get_suffixIndex());

			//Current node is not a leaf as it has outgoing
			//edges from it.
			leaf = 0;
			setSuffixIndexByDFS(n->get_children(i), labelHeight + edgeLength(n->get_children(i)));
		}
	}
	if (leaf == 1) {
		n->set_suffixIndex(size - labelHeight);
		//Uncomment below line to print suffix index
		//printf(" [%d]\n", n->get_suffixIndex());
	}
}

void SuffixTree::freeSuffixTreeByPostOrder(Node *n) {
	if (n == NULL)
		return;
	int i;
	for (i = 0; i < MAX_CHAR; i++) {
		if (n->get_children(i) != NULL) {
			freeSuffixTreeByPostOrder(n->get_children(i));
		}
	}
	if (n->get_suffixIndex() == -1)
		free(n->get_end());
	free(n);
}

void SuffixTree::buildSuffixTree() {
	size = text.size();
	int i;
	rootEnd = (int*) malloc(sizeof(int));
	*rootEnd = - 1;

	root = newNode(-1, rootEnd);

	activeNode = root; //First activeNode will be root
	for (i=0; i<size; i++)
		extendSuffixTree(i);
	int labelHeight = 0;
	setSuffixIndexByDFS(root, labelHeight);
}

int SuffixTree::traverseEdge(const char *str, int idx, int start, int end) {
	int k = 0;
	//Traverse the edge with character by character matching
	for(k=start; k<=end && str[idx] != '\0'; k++, idx++) {
		if(text[k] != str[idx])
			return -1; // mo match
	}
	if(str[idx] == '\0')
		return 1; // match
	return 0; // more characters yet to match
}

int SuffixTree::doTraversalToCountLeaf(Node *n) {
	
	if(n == NULL)
		return 0;
	if(n->get_suffixIndex() > -1) {
		printf("\nFound at position: %d", n->get_suffixIndex());
		index_list.push_back(n->get_suffixIndex());
		return 1;
	}
	
	// cout << endl << index_list.size() << endl;
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

int SuffixTree::countLeaf(Node *n) {
	if(n == NULL)
		return 0;
	return doTraversalToCountLeaf(n);
}

int SuffixTree::doTraversal(Node *n, const char* str, int idx) {
	if(n == NULL)
		return -1;
	int res = -1;
	if(n->get_start() != -1) {
		res = traverseEdge(str, idx, n->get_start(), *(n->get_end()));
		if(res == -1) //no match
			return -1;
		if(res == 1) {
			if(n->get_suffixIndex() > -1)
				printf("\nsubstring count: 1 and position: %d",
							n->get_suffixIndex());
			else
				printf("\nsubstring count: %d", countLeaf(n));
			return 1;
		}
	}
	idx = idx + edgeLength(n);
	if(n->get_children(str[idx]) != NULL)
		return doTraversal(n->get_children(str[idx]), str, idx);
	else
		return -1; // no match
}

vector <int> SuffixTree::checkForSubString(const char* str) {
	int res = doTraversal(root, str, 0);
	if(res == 1) {
		printf("\nPattern <%s> is a Substring\n", str);
		cout << endl << index_list.size() << endl;
	}
	else
		printf("\nPattern <%s> is NOT a Substring\n", str);
	
	return index_list;
}
