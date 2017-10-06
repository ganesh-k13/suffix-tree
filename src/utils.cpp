#include "../include/utils.h"



map <int, string> get_data(string file_name, string *all_lines, vector<int> *start_points) {
	
	map <int, string> title_map;
	int file_count = 0;
	string line;
	ifstream file(file_name.c_str());
	
	// First Line
	getline(file, line); (*start_points).push_back(0);
	title_map.insert(pair<int, string>(file_count, line));
	file_count+=1;
	// cout << line << endl;
	
	while(getline(file, line)) {
		if(line.empty()) {
			
			getline(file, line);
			while(line.empty())
				getline(file, line);
			(*start_points).push_back((*all_lines).size());
			title_map.insert(pair<int, string>(file_count, line));
			file_count+=1;
			continue;
		}
		(*all_lines)+=(line+" ");
	}
	
	return title_map;
}

#if 0
int main() {
	string all_lines;
	vector <int> start_points;
	auto title_map = get_data("AesopTales.txt", &all_lines, &start_points);
	for (auto itr = title_map.begin(); itr != title_map.end(); ++itr) {
        cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
	
	// cout << all_lines;
	
	for(auto it = start_points.begin(); it != start_points.end(); it++) {
		cout << *it << endl;
	}
	
	cout << all_lines;
}
#endif