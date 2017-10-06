#include "include/Node.h"
#include "include/SuffixTree.h"
#include "include/utils.h"

void test_one(string query) {
	string all_lines;
	vector <int> start_points;
	// cout << "enter";
	auto title_map = get_data("AesopTales.txt", &all_lines, &start_points);
	
	SuffixTree st(all_lines);
	
	auto index_list = st.checkForSubString(query.c_str());
	auto it_m = title_map.begin();
	for(auto it_v = index_list.begin(); it_v != index_list.end(); ++it_v) {
		cout << *it_v << endl;
	}
	
	st.freeSuffixTreeByPostOrder(st.get_root());
	
}

void test_two() {
	
}

void test_three() {
	
}

void run_tests(char** args, int no_of_args) {
    int i = 0;
	if(no_of_args > 1) {
		string mode(args[0]);
		string query(args[1]);
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
