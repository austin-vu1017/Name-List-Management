#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

struct person { string id, first, last, dob, gpa; };	//struct that holds person's info
void error(string filename);
void sorting(string filename, person info[], int iterator);

int main(int argc, char* argv[]) {
	/*
	if (argc != 2 && argc != 4) {
		cout << "Usage: sort \"input = <file>; output = <file>; sort = <file>\"" << endl;
		return -1;
	}
	*/
	ArgumentManager am(argc, argv);
	string inFilename = am.get("input");
	string outFilename = am.get("output");
	string sortFilename = am.get("sort");

	cout << "File name for name list: " << inFilename << endl <<
		"File name for output: " << outFilename << endl <<
		"File name for sorting order: " << sortFilename << endl;
	cout << "input file: ";
	cin >> inFilename;
	ifstream inFile(inFilename.c_str());
	error(inFilename);

	person nameList[2000];
	string inLine;
	int i = 0;

	while (getline(inFile, inLine) && i < 2000) {	//getline() parses first ':'
		string delCommand, attribute;

		istringstream iss(inLine);		

		if (inLine.find("delete") != string::npos) {	//detects if "delete" is found in string
			iss >> delCommand >> attribute;
		}

		inLine.erase(0, inLine.find('{'));	//ignore white spaces
		
		if (inLine[0] == '{') {		//if the line has '{', the line is split and inputted
			getline(getline(iss, inLine, '{'),inLine, ':');
			getline(getline(iss, nameList[i].id, ','), inLine, ':');	//parses ',' and ':' to get info
			getline(getline(iss, nameList[i].first, ','), inLine, ':');
			getline(getline(iss, nameList[i].last, ','), inLine, ':');
			getline(getline(iss, nameList[i].dob, ','), inLine, ':');
			getline(iss, nameList[i].gpa, '}');
			i++;
		}

		else if (delCommand == "delete") {	//runs if delete was found
			for (int count = 0; count < i; count++) {	//loops through all struct array currently made
				if ((nameList[count].id == attribute) || (nameList[count].first == attribute)	//a very ugly condition 
					|| (nameList[count].last == attribute) || (nameList[count].dob == attribute)
					|| (nameList[count].gpa == attribute)) {
					for (int j = count; j < i - count; j++) {
						nameList[j].id = nameList[j + 1].id;
						nameList[j].first = nameList[j + 1].first;
						nameList[j].last = nameList[j + 1].last;
						nameList[j].dob = nameList[j + 1].dob;
						nameList[j].gpa = nameList[j + 1].gpa;
					}
					i--;
					break;
				}
			}
		}
		
		for (int count = 0; count < i - 1; count++) {	//loops through all struct array currently made
			string temp;
			temp = nameList[i - 1].id;	//temp is attached to current element's id
			if (nameList[count].id == temp) {
				nameList[count] = nameList[i - 1];	//matching id is found, all of it's attribute is now the same as the current's
				i--;	//decrease size to prevent duplicates
			}
		}
	}
	cout << "sort file: ";
	cin >> sortFilename;
	ifstream sortFile(sortFilename.c_str());
	error(sortFilename);
	sorting(sortFilename, nameList, i);

	cout << "output file: ";
	cin >> outFilename;
	ofstream outFile(outFilename.c_str());
	error(outFilename);

	for (int count = 0; count < i; count++) {
		if (count == i - 1) {
			outFile << "{id:" << nameList[count].id << ",first:" << nameList[count].first
				<< ",last:" << nameList[count].last << ",DOB:" << nameList[count].dob <<
				",GPA:" << nameList[count].gpa << "}";
		}
		else {
			outFile << "{id:" << nameList[count].id << ",first:" << nameList[count].first
				<< ",last:" << nameList[count].last << ",DOB:" << nameList[count].dob <<
				",GPA:" << nameList[count].gpa << "}" << endl;
		}
	}
	
	inFile.close();
	outFile.close();
	
	return 0;
}

	void sorting(string filename, person info[], int iterator) {	//sorting function
	//ifstream inputFile(filename.c_str());
	ifstream inputFile(filename.c_str());
	error(filename.c_str());	//use error function to see if file can be open
	string line;
	int flag = 0;	//keeps check if there were any sorting. 
	while (getline(inputFile, line)) {	//read line by line
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());	//ignore white spaces. found online in stackoverflow

		if (line == "id") {	//if line is "id" or empty, sort by id
			person temp;
			for (int i = 1; i < iterator; i++) {	//bubble sorting
				for (int j = 0; i < iterator - j; j++) {
					if (info[j].id > info[j + 1].id) {
						temp = info[j];
						info[j] = info[j + 1];
						info[j + 1] = temp;
					}
				}
			}
			flag++;
		}
		else if (line == "first") {	//if line is "first", sort by first name
			person temp;
			for (int i = 1; i < iterator; i++) {
				for (int j = 0; i < iterator - j; j++) {
					if (info[j].first > info[j + 1].first) {
						temp = info[j];
						info[j] = info[j + 1];
						info[j + 1] = temp;
					}
				}
			}
			flag++;
		}
		else if (line == "last") {	//if line is "last", sort by last name
			person temp;
			for (int i = 1; i < iterator; i++) {
				for (int j = 0; i < iterator - j; j++) {
					if (info[j].last > info[j + 1].last) {
						temp = info[j];
						info[j] = info[j + 1];
						info[j + 1] = temp;
					}
				}
			}
			flag++;
		}
		else if (line == "DOB") {	//if line is "DOB", sort by date of birth
			person temp;
			for (int i = 1; i < iterator; i++) {
				for (int j = 0; i < iterator - j; j++) {
					if (info[j].dob > info[j + 1].dob) {
						temp = info[j];
						info[j] = info[j + 1];
						info[j + 1] = temp;
					}
				}
			}
			flag++;
		}
		else if (line == "GPA") {	//if line is "GPA", sort by GPA
			person temp;
			for (int i = 1; i < iterator; i++) {
				for (int j = 0; i < iterator - j; j++) {
					if (info[j].gpa > info[j + 1].gpa) {
						temp = info[j];
						info[j] = info[j + 1];
						info[j + 1] = temp;
					}
				}
			}
			flag++;
		}
	}
	if (flag == 0) {	//if no sorting was made, then sort by id by default
		person temp;
		for (int i = 1; i < iterator; i++) {
			for (int j = 0; i < iterator - j; j++) {
				if (info[j].id > info[j + 1].id) {
					temp = info[j];
					info[j] = info[j + 1];
					info[j + 1] = temp;
				}
			}
		}
	}
	else {	//if flag is > than 0, shows list is sorted and now sorts id
		for (int i = 1; i < iterator; i++) {
			person temp;
			for (int j = 0; i < iterator - j; j++) {
				if (info[j].id > info[j + 1].id) {	//if id of temp is greater than info[i]'s id
					temp = info[j];	//temp == info[0]
					info[j] = info[j + 1];
					info[j + 1] = temp;
				}
			}
		}
	}
	inputFile.close();
}

void error(string filename) {	//function to check if file is found or can't be opened
	ifstream inputFile(filename.c_str());
	string line;

	if (!inputFile.is_open()) {
		cout << "-----ERROR CAN'T OPEN FILE-----";
	}
}