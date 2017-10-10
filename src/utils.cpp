#include "../include/utils.h"
#include <algorithm>

double accum_time(struct timespec requestStart, struct timespec requestEnd) {
    
    return ((requestEnd.tv_sec - requestStart.tv_sec)) * 1000 +
            (( requestEnd.tv_nsec - requestStart.tv_nsec ) / MILLION);
}

int nearest_search(vector <int> end_points, int index) {
	
	int index_found = 0;
	// cout << index;
	for(auto it = end_points.begin(); it != end_points.end(); ++index_found, ++it) {
		if(*it > index) {
			return index_found;
		}
	}
}

map <int, string> get_data(string file_name, string *all_lines, vector<int> *end_points) {
	
	map <int, string> title_map;
	int file_count = 0;
	string line;
	ifstream file(file_name.c_str());
	
	// First Line
	getline(file, line);
	title_map.insert(pair<int, string>(file_count, line));
	file_count+=1;
	// cout << line << endl;
	
	while(getline(file, line)) {
		if(line.empty()) {
			
			getline(file, line);
			while(line.empty())
				getline(file, line);
			(*end_points).push_back((*all_lines).size());
			// cout << (*all_lines).size() << endl;
			title_map.insert(pair<int, string>(file_count, line));
			// cout << line << endl;
			file_count+=1;
			continue;
		}
		(*all_lines)+=(line+" ");
	}
	
	(*end_points).push_back((*all_lines).size());
	
	return title_map;
}

map <string, string> get_stories(string file_name) {
	map<string, string> stories;
	string line, story, title;
	ifstream file(file_name.c_str());
	getline(file, title);
	
	while(getline(file, line)) {
		if(line.empty()) {
			// cout << story << endl;
			stories.insert(pair<string, string>(title, story));
			story = ""; title = "";
			getline(file, title);
			while(title.empty())
				getline(file, title);
			// cout << title << endl;
			continue;
		}
		(story)+=(line+" ");
	}
	
	// cout << endl << title;
	
	stories.insert(pair<string, string>(title, story));
	
	return stories;
}

void print_result(string title, string lines) {
	cout << "[" << title << "] : ... " << lines << " ..." <<  endl;
	return;
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