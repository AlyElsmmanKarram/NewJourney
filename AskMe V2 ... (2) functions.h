

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>// file stream
#include <sstream>// string stream
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

vector<string> ReadFileLines(const string& path);
void writeFileLines(const string& path, const vector<string>& lines, bool append = true) ;
vector<string> splitString(const string& line, const string& delimiter = ",");
int toInt(const string& str);
int readInt(int low, int high);
int showReadMenu(const vector<string>& choices);

#endif /* FUNCTIONS_H_ */
