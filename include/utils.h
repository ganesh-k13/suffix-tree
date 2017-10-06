#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>
 
using namespace std;

map <int, string> get_data(string file_name, string *all_lines, vector<int> *end_points);

vector <int>::iterator nearest_binary_search(vector <int> end_points);
int nearest_search(vector <int> end_points, int index);