#include "include/Node.h"
#include "include/SuffixTree.h"
#include "include/utils.h"
#include <sstream>

void test_one(string query) {
	
	// Declarations
	struct timespec requestStart, requestEnd;
	string all_lines;
	vector <int> end_points;
	auto title_map = get_data("AesopTales.txt", &all_lines, &end_points);
	
	// Build the suffix tree
	clock_gettime(CLOCK_REALTIME, &requestStart);
	SuffixTree st(all_lines);
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	
	cout << "\nTree Built in: " << accum_time(requestStart, requestEnd) << endl;
	
	// Get list of all occurences of substring within documents.
	clock_gettime(CLOCK_REALTIME, &requestStart);
	auto index_list = st.check_for_sub_string(query.c_str());
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	
	// If atleast one match exists
	if(index_list.size()) {
		cout << "\nMatches found in: " << accum_time(requestStart, requestEnd) << endl << endl;
	
		auto it_m = title_map.begin();
		
		for(auto it = index_list.begin(); it != index_list.end(); ++it) {
			
			// Get document index
			auto pos = nearest_search(end_points, *it);
			print_result(title_map[pos], all_lines.substr(*(it)-40, 80));
		}
	}
	
	else {
		cout << "Pattern not a substring";
		cout << "\nNo matches found in: " << accum_time(requestStart, requestEnd) << endl << endl;
	}
	
	// Clear suffix tree
	st.free_suffix_tree_by_post_order(st.get_root());
}

// BUG: Valgrind shows errors
void test_two(string query) {
	
	struct timespec requestStart, requestEnd;
	auto stories = get_stories("AesopTales.txt");
	
	clock_gettime(CLOCK_REALTIME, &requestStart);
	for(auto it = stories.begin(); it != stories.end(); it++) {
		// string text = it->second+"#"+query+"$";
		SuffixTree st((it->second), query);
		
		int max_height = 0;
		auto index_list = st.get_LCS(&max_height);
		
		if(index_list.size() == 0) {
			print_result(it->first, "");
			continue;
		}
		
		auto min_index = min_element(index_list.begin(), index_list.end());
		
		try {
			print_result(it->first, (it->second).substr(*(min_index), 60), (it->second).substr(*(min_index), max_height));
		}
		catch(const char *msg) {
			print_result(it->first, (it->second).substr(*(min_index)-30, 60), (it->second).substr(*(min_index), max_height));
		}
		
		// Clear suffix tree
		st.free_suffix_tree_by_post_order(st.get_root());
		
	}
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	
	cout << "\nFound in: " << accum_time(requestStart, requestEnd) << endl;
}

// TODO: Get k greatest instead of all.
//       Add more parameters for score.
void test_three(string query) {
	// Match string
	// Match substr
	// Match less stop_words
	auto stop_words = get_stop_words("stopwords");
	vector <pair<string, int>> scores;
	struct timespec requestStart, requestEnd;
	auto stories = get_stories("AesopTales.txt");
	
	clock_gettime(CLOCK_REALTIME, &requestStart);
	for(auto it = stories.begin(); it != stories.end(); it++) {
		// Full match
		// string text = it->second+"#"+query+"$";
		SuffixTree st((it->second), query);
		int max_height = 0;
		auto index_list = st.get_LCS(&max_height);
		scores.push_back((pair<string, int>(it->first, 0)));
		if(!index_list.size()) {
			continue;
		}
		scores.back().second = max_height;
		
		// words match
		istringstream iss(query);
		vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
		
		for(auto it_s = tokens.begin(); it_s != tokens.end(); it_s++) {
			 index_list.clear();
			 max_height = 0;
			 index_list =  st.check_for_sub_string((it_s)->c_str());
			 if(stop_words.find(*(it_s)) != stop_words.end())
	 		 	scores.back().second += (index_list.size()*2);
	 		 else
	 		 	scores.back().second += (index_list.size());
		}
	}
	
	sort(scores.begin(), scores.end(), 
		[](const pair<string,int> &a, const pair<string,int> &b) -> bool { 
			return (a.second < b.second); 
		}	
	);
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	
	for(auto it = scores.begin(); it != scores.end(); it++) {
		print_result(it->first, it->second);
	}
	
	cout << "\nFound in: " << accum_time(requestStart, requestEnd) << endl;
}

// Sandbox
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
	
	#if 0
	auto stories = get_stories("AesopTales.txt");
	
	for(auto it = stories.begin(); it != stories.end(); it++) {
		// cout << it->second+"#"+query+"$";
		string text = it->second+"#"+query+"$";
		// clock_gettime(CLOCK_REALTIME, &requestStart);
		SuffixTree st(text, (it->second).size());
		// clock_gettime(CLOCK_REALTIME, &requestEnd);
		
		int max_height;
		auto index_list = st.get_LCS(&max_height);
		// cout << index_list.size();
		auto min_index = min_element(index_list.begin(), index_list.end());
		
		for(auto it = index_list.begin(); it != index_list.end(); it++) {
			cout << *it << " ";
		}
		// print_result(it->first, (it->second).substr(*(min_index), 80));
		// cout << *min_element(index_list.begin(), index_list.end());
		
		// cout << "\nTree Built in: " << accum_time(requestStart, requestEnd) << endl;
		
	}
	return;
	
	#endif
	
	#if 0
	string s("Somewhere down the road");
	istringstream iss(s);

	vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
              
        for(auto it = tokens.begin(); it != tokens.end(); ++it) {
        	cout << *it << endl;
        }
        
        #endif
        
        auto stop = get_stop_words("stopwords");
        
        for(auto it = stop.begin(); it != stop.end(); it++) {
        	cout << *it << endl;
        }
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
			test_two(query);
		}
		
		if(mode == "-3") {
			test_three(query);
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
