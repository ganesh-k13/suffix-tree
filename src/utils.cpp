#include "../include/utils.h"
#include <algorithm>

// Computes time taken given the starting and ending times
double accum_time(struct timespec requestStart, struct timespec requestEnd) {
    
    return ((requestEnd.tv_sec - requestStart.tv_sec)) * 1000 +
            (( requestEnd.tv_nsec - requestStart.tv_nsec ) / MILLION);
}


// To find which document a given substring belongs to given an index.
// end_points vector indicates the ending index of all the documents.
// TODO: Implement a log(n) algo of the same.
int nearest_search(vector <int> end_points, int index) {
	
	int index_found = 0;
	// cout << index;
	for(auto it = end_points.begin(); it != end_points.end(); ++index_found, ++it) {
		if(*it > index) {
			return index_found;
		}
	}
}

//This functions helps in finding three main items:
// title_map: Map containing: [Key] -> Story index; [Value] -> Story title
// all_lines: A string with all the document contents in one string.
// end_points: Vector with end index of all documnets in all_lines
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

// Returns a map with: [Key] -> Title; [Value] -> content
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

/*
The three functions bellow help in printing the result.
*/

void print_result(string title, string lines) {
	
	if(lines.size()) {
		cout << "[ " << title << "] : ... " << lines << " ..." <<  endl;
		return;
	}
	
	cout << "[ " << title << "] : No results found!! "<<  endl;
}

void print_result(string title, string lines, string substring) {
	
	if(lines.size()) {
		cout << "[ " << title << "] : ... " << lines << " ..." <<  endl;
		cout << "First longest substring matched: " << substring << endl << endl;
		return;
	}
	cout << "[ " << title << "] : No results found!! "<<  endl;
	
}

void print_result(string title, int score) {
	cout << "[ " << title << "] : Score : " << score <<  endl;
}

// Get all English stop_words
unordered_set <string> get_stop_words(string file_name) {
	string line;
	ifstream file(file_name.c_str());	
	unordered_set <string> stop_words;
	
	while(getline(file, line)) {
		stop_words.insert(line);
	}
	
	return stop_words;
}

