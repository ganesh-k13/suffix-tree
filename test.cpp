#include "include/Node.h"
#include "include/SuffixTree.h"
#include "include/utils.h"

void test_one(string query) {
	string all_lines;
	vector <int> end_points;
	// cout << "enter";
	auto title_map = get_data("AesopTales.txt", &all_lines, &end_points);
	
	SuffixTree st(all_lines);
	
	auto index_list = st.check_for_sub_string(query.c_str());
	auto it_m = title_map.begin();
	// for(auto it_v = index_list.begin(); it_v != index_list.end(); ++it_v) {
		// cout << *it_v << endl;
	// }
	
	for(auto it = index_list.begin(); it != index_list.end(); ++it) {
		auto pos = nearest_search(end_points, *it);
		// cout << *(pos_pair.second)-10 << " " << *(pos_pair.second)+10;
		cout << "[" << title_map[pos] << "] : ... " << all_lines.substr(*(it)-20, 40) << " ..." <<  endl;
	}
	
	#if 0
	
	cout << endl << endl;
	for(auto it = end_points.begin(); it != end_points.end(); ++it) {
		cout << *it << endl;
	}
	#endif
	
	st.free_suffix_tree_by_post_order(st.get_root());
}

void test_two() {
	
}

void test_three() {
	
}

void run_tests(char** args, int no_of_args) {
    int i = 0;
	if(no_of_args > 1) {
		string mode(args[0]);
		string query;
		for(i = 1; i < no_of_args; i++) {
			query+=(string(args[i])+" ");
		}
		query.pop_back();
		if(mode == "-1") {
			test_one(query);
		}

		if(!strcmp(args[0], "-2")) {
			test_two();
		}
		
		if(!strcmp(args[0], "-3")) {
			test_three();
		}
	}

}

int main(int argl, char** argv) {
    
    run_tests(argv + 1, argl - 1);
    
    return 0;
}
