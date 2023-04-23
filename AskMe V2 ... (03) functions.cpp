
#include "functions.h"

vector<string> ReadFileLines(const string& path) {
	vector<string> lines;

	fstream fileHandler(path.c_str());
	if (fileHandler.fail()) {
		cout << "\n\nErrorL Can't open the file.\n]n";
		return lines;
	}
	string line;
	while (getline(fileHandler, line)) {
		if ((int) line.size()) {
			lines.push_back(line);
		}
	}
	fileHandler.close();
	return lines;
}

void writeFileLines(const string& path, const vector<string>& lines, bool append ) {
	auto status = ios::in | ios::out | ios::app;
	if (!append) {
		status = ios::in | ios::out | ios::trunc;
	}
	fstream fileHandler(path.c_str(), status);
	if (fileHandler.fail()) {
		cout << "\n\nErrorL Can't open the file.\n]n";
		return;
	}
	for(const auto& line : lines){
		fileHandler << line << "\n";
	}
	fileHandler.close();
}


vector<string> splitString(const string& line, const string& delimiter){
	string lineCopy = line;
	vector<string> substrs;

	int pos = 0;
	string substr;
	while((pos = (int) lineCopy.find(delimiter)) != -1){
		substr = lineCopy.substr(0, pos);
		substrs.push_back(substr);
		lineCopy.erase(0, pos + (int) delimiter.size());
	}
	substrs.push_back(lineCopy);
	return substrs;
}


int toInt(const string& str){
	istringstream iss(str);

	int num;
	iss >> num;

	return num;
}


int readInt(int low, int high){
	cout << "\nEnter choice in range ["<< low << ", " << high << "]: ";
	int num;

	cin >> num;

	if(low <= num && num <= high){
		return num;
	}
	cout << "\n\nError: Invalid number... Try again\n";
	return readInt(low, high);
}

int showReadMenu(const vector<string>& choices){
	cout << "\nMenu:\n";
	for(int i = 0 ; i<(int)choices.size(); i++){
		cout << "\t" << i + 1 << ": " << choices[i] << ".\n";
	}
	return readInt(1, (int)choices.size());
}
