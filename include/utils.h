#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
 
using namespace std;

map <int, string> get_data(string file_name, string *all_lines, vector<int> *start_points);