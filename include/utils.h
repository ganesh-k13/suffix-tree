#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>
#include <time.h>

#define MILLION 1E6

using namespace std;

map <int, string> get_data(string file_name, string *all_lines, vector<int> *end_points);
vector <int>::iterator nearest_binary_search(vector <int> end_points);
int nearest_search(vector <int> end_points, int index);
double accum_time(struct timespec requestStart, struct timespec requestEnd);
map <string, string> get_stories(string file_name);
void print_result(string title, string lines);
void print_result(string title, string lines, string substring);