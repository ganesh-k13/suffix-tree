#include "include/Node.h"
#include "include/SuffixTree.h"
#include "include/utils.h"

void test_one(string query) {
	struct timespec requestStart, requestEnd;
	string all_lines;
	vector <int> end_points;
	// cout << "enter";
	auto title_map = get_data("AesopTales.txt", &all_lines, &end_points);
	
	clock_gettime(CLOCK_REALTIME, &requestStart);
	SuffixTree st(all_lines);
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	
	cout << "\nTree Built in: " << accum_time(requestStart, requestEnd) << endl;
	
	clock_gettime(CLOCK_REALTIME, &requestStart);
	auto index_list = st.check_for_sub_string(query.c_str());
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	cout << "\nMatches found in: " << accum_time(requestStart, requestEnd) << endl << endl;
	
	auto it_m = title_map.begin();
	// for(auto it_v = index_list.begin(); it_v != index_list.end(); ++it_v) {
		// cout << *it_v << endl;
	// }
	
	for(auto it = index_list.begin(); it != index_list.end(); ++it) {
		auto pos = nearest_search(end_points, *it);
		// cout << *(pos_pair.second)-10 << " " << *(pos_pair.second)+10;
		// cout << "[" << title_map[pos] << "] : ... " << all_lines.substr(*(it)-40, 80) << " ..." <<  endl;
		print_result(title_map[pos], all_lines.substr(*(it)-40, 80));
	}
	
	#if 0
	
	cout << endl << endl;
	for(auto it = end_points.begin(); it != end_points.end(); ++it) {
		cout << *it << endl;
	}
	#endif
	
	st.free_suffix_tree_by_post_order(st.get_root());
}

void test_two(string query) {
	struct timespec requestStart, requestEnd;
	auto stories = get_stories("AesopTales.txt");
	
	clock_gettime(CLOCK_REALTIME, &requestStart);
	for(auto it = stories.begin(); it != stories.end(); it++) {
		string text = it->second+"#"+query+"$";
		// clock_gettime(CLOCK_REALTIME, &requestStart);
		SuffixTree st(text, (it->second).size());
		// clock_gettime(CLOCK_REALTIME, &requestEnd);
		
		auto index_list = st.get_LCS();
		auto min_index = min_element(index_list.begin(), index_list.end());
		
		// cout << *min_index;
		// print_result(it->first, (it->second).substr(*(min_index), 80));
		// cout << *min_element(index_list.begin(), index_list.end());
		
		// cout << "\nTree Built in: " << accum_time(requestStart, requestEnd) << endl;
		st.free_suffix_tree_by_post_order(st.get_root());
		
	}
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	
	cout << "\nFound in: " << accum_time(requestStart, requestEnd) << endl;
}

void test_three() {
	
}

void test_test(string query) {
	
	#if 0
	string text = "xabxaabxa#babxba$";
	int size_sub_str = 10;
	SuffixTree st(text, size_sub_str);
	st.get_LCS();
	auto index_list = st.check_for_sub_string("abxa");
	
	cout << index_list.size();
	
	st.free_suffix_tree_by_post_order(st.get_root());
	#endif
	
	#if 0
	auto stories = get_stories("AesopTales.txt");
	
	for(auto it = stories.begin(); it != stories.end(); it++) {
		cout << it->first << endl << it->second << endl << endl;
	}
	
	#endif
	
	auto stories = get_stories("AesopTales.txt");
	
	for(auto it = stories.begin(); it != stories.end(); it++) {
		string text = it->second+"#"+query+"$";
		// clock_gettime(CLOCK_REALTIME, &requestStart);
		SuffixTree st(text, (it->second).size());
		// clock_gettime(CLOCK_REALTIME, &requestEnd);
		
		auto index_list = st.get_LCS();
		auto min_index = min_element(index_list.begin(), index_list.end());
		
		for(auto it = index_list.begin(); it != index_list.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
		// print_result(it->first, (it->second).substr(*(min_index), 80));
		// cout << *min_element(index_list.begin(), index_list.end());
		
		// cout << "\nTree Built in: " << accum_time(requestStart, requestEnd) << endl;
		
	}
	return;
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

		if(mode == "-2") {
			// cout << "enter";
			test_two(query);
		}
		
		if(!strcmp(args[0], "-3")) {
			test_three();
		}
		
		if(mode == "-t") {
			test_test(query);
		}
	}

}

int main(int argl, char** argv) {
    
    run_tests(argv + 1, argl - 1);
    
    return 0;
}
