#include "../include/SuffixTree.h"

SuffixTree::SuffixTree(string text) {
	this->text = text;
	root = NULL;
	last_new_node = NULL;
	active_node = NULL;
	
	active_edge = -1;
	active_length = 0;
	
	remaining_suffix_count = 0;
	leaf_end = -1;
	root_end = NULL;
	split_end = NULL;
	size = -1; //Length of input string
	size_sub_str = -1;
	build_suffix_tree();
	index_list.clear();
}

SuffixTree::SuffixTree(string doc, string query) {
	this->text = doc+"#"+query+"$";
	this->size_sub_str = doc.size();
	root = NULL;
	last_new_node = NULL;
	active_node = NULL;
	
	active_edge = -1;
	active_length = 0;
	
	remaining_suffix_count = 0;
	leaf_end = -1;
	root_end = NULL;
	split_end = NULL;
	size = -1; 
	build_suffix_tree();
	index_list.clear();
}

SuffixTree::~SuffixTree() {
	
}

 Node* SuffixTree::get_root() { 
	return root; 
}

Node* SuffixTree::new_node(int start, int *end) {
	Node *node = new Node(start, end);
	node->set_suffix_link(root); 
	
	return node;
}

 int SuffixTree::edge_length(Node *n) {
	return n == root ? 0 : *(n->get_end()) - (n->get_start()) + 1;
}

int SuffixTree::walk_down(Node *currNode) {
	
	if (active_length >= edge_length(currNode)) {
		active_edge += edge_length(currNode);
		active_length -= edge_length(currNode);
		active_node = currNode;
		return 1;
	}
	return 0;
}

void SuffixTree::extend_suffix_tree(int pos) {
	
	leaf_end = pos;

	remaining_suffix_count++;

	last_new_node = NULL;

	while(remaining_suffix_count > 0) {

		if (active_length == 0)
			active_edge = pos;

		if (active_node->get_children(text[active_edge]) == NULL) {
			
			active_node->set_children(text[active_edge], new_node(pos, &leaf_end)); 

			if (last_new_node != NULL) {
				last_new_node->set_suffix_link(active_node); 
				last_new_node = NULL;
			}
		}
		
		else {
			Node *next = active_node->get_children(text[active_edge]); 
			if (walk_down(next)) {
				continue;
			}
			if (text[next->get_start() + active_length] == text[pos]) {
				if(last_new_node != NULL && active_node != root) {
					last_new_node->set_suffix_link(active_node);
					last_new_node = NULL;
				}

				active_length++;
				break;
			}

			split_end = new int;
			*split_end = next->get_start() + active_length - 1;

			Node *split = new_node(next->get_start(), split_end);
			active_node->set_children(text[active_edge], split);

			split->set_children(text[pos], new_node(pos, &leaf_end));
			next->set_start(next->get_start()+active_length);
			split->set_children(text[next->get_start()], next); 

			if (last_new_node != NULL) {
				last_new_node->set_suffix_link(split);
			}

			last_new_node = split;
		}

		remaining_suffix_count--;
		if (active_node == root && active_length > 0) {
			active_length--;
			active_edge = pos - remaining_suffix_count + 1;
		}
		else if (active_node != root) {
			active_node = active_node->get_suffix_link();
		}
	}
}


void SuffixTree::set_suffix_index_by_DFS(Node *n, int labelHeight) {
	if (n == NULL) return;

	int leaf = 1;
	int i;
	for (i = 0; i < MAX_CHAR; i++) {
		if (n->get_children(i) != NULL) {
			//Current node is not a leaf as it has outgoing
			//edges from it.
			leaf = 0;
			set_suffix_index_by_DFS(n->get_children(i), labelHeight + edge_length(n->get_children(i)));
		}
	}
	if (leaf == 1) {
		n->set_suffix_index(size - labelHeight);
	}
}

void SuffixTree::free_suffix_tree_by_post_order(Node *n) {
	if (n == NULL)
		return;
	int i;
	for (i = 0; i < MAX_CHAR; i++) {
		if (n->get_children(i) != NULL) {
			free_suffix_tree_by_post_order(n->get_children(i));
		}
	}
	if (n->get_suffix_index() == -1)
		delete (n->get_end());
	delete(n);
}

void SuffixTree::build_suffix_tree() {
	size = text.size();
	int i;
	root_end = new int;
	*root_end = - 1;

	root = new_node(-1, root_end);

	active_node = root; //First active_node will be root
	for (i=0; i<size; i++)
		extend_suffix_tree(i);
	int labelHeight = 0;
	set_suffix_index_by_DFS(root, labelHeight);
}

int SuffixTree::build_suffix_tree(const char *str, int idx, int start, int end) {
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

int SuffixTree::do_traversal_to_count_leaf(Node *n) {
	
	if(n == NULL)
		return 0;
	if(n->get_suffix_index() > -1) {
		
		index_list.push_back(n->get_suffix_index());
		return 1;
	}
	
	
	int count = 0;
	int i = 0;
	for (i = 0; i < MAX_CHAR; i++)
	{
		if(n->get_children(i) != NULL)
		{
			count += do_traversal_to_count_leaf(n->get_children(i));
		}
	}
	return count;
}

int SuffixTree::count_leaf(Node *n) {
	if(n == NULL)
		return 0;
	return do_traversal_to_count_leaf(n);
}

int SuffixTree::do_traversal(Node *n, const char* str, int idx) {
	if(n == NULL)
		return -1;
	int res = -1;
	if(n->get_start() != -1) {
		res = build_suffix_tree(str, idx, n->get_start(), *(n->get_end()));
		if(res == -1) 
			return -1;
		if(res == 1) {
			if(n->get_suffix_index() > -1) { 
				
				index_list.push_back(n->get_suffix_index());
			}
			else
				count_leaf(n);
			return 1;
		}
	}
	idx = idx + edge_length(n);
	if(n->get_children(str[idx]) != NULL)
		return do_traversal(n->get_children(str[idx]), str, idx);
	else
		return -1; 
}

vector <int> SuffixTree::check_for_sub_string(const char* str) {
	index_list.clear();
	do_traversal(root, str, 0);
	return index_list;
}

#if 1
vector <int> SuffixTree::get_LCS(int *max_height) {
    int substring_start_index = 0;
    do_traversal(root, 0, max_height, &substring_start_index);
	
	
	index_list.clear();
    if(*max_height == 0) {
        return index_list;
	}
	
	else {
		do_traversal(root, text.substr(substring_start_index, *max_height).c_str(), 0);
	}
    
	return index_list;
}

int SuffixTree::do_traversal(Node *n, int label_height, int* max_height, int* substring_start_index) {
	if(n == NULL) {
		return NULL;
	}
	int i=0;
	int ret = -1;
	if(n->get_suffix_index() < 0) {
		for (i = 0; i < MAX_CHAR; i++) {
			if(n->get_children(i) != NULL) {
				ret = do_traversal(n->get_children(i), label_height +  edge_length(n->get_children(i)),  max_height, substring_start_index);
				 
				if(n->get_suffix_index() == -1)
					n->set_suffix_index(ret);
				else if((n->get_suffix_index() == -2 && ret == -3) || (n->get_suffix_index() == -3 && ret == -2) ||  n->get_suffix_index() == -4) {
					n->set_suffix_index(-4);//Mark node as XY
					//Keep track of deepest node
					if(*max_height < label_height) {
						*max_height = label_height;
						*substring_start_index = *(n->get_end()) - label_height + 1;
					}
				}
			}
		}
	}
	else if(n->get_suffix_index() > -1 && n->get_suffix_index() < size_sub_str)//suffix of X
		return -2;//Mark node as X
	else if(n->get_suffix_index() >= size_sub_str)//suffix of Y
		return -3;//Mark node as Y
	return n->get_suffix_index();
}
 
#endif