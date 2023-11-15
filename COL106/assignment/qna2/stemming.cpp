#include <iostream>
#include <string>
#include<vector>
// #include <unordered_map>
using namespace std;

vector<pair<string, string>> irregularVerbs = {
	{"gone", "go"},
	{"goes", "go"},
	{"went", "go"},
	{"going", "go"},
	{"was", "be"},
	{"were", "be"},
	{"is", "be"},
	{"has", "have"},
	{"had", "have"},
	{"having", "have"},
	{"does", "do"},
	{"done", "do"},
	{"did", "do"},
	{"sees", "see"},
	{"saw", "see"},
	{"seen", "see"},
	{"died", "die"},
	{"dead", "die"},
	{"dying", "die"},
	{"dying", "die"},
	{"national", "nation"},
	{"gandhiji", "gandhi"}
};

string removeVerbSuffix(const string& word) {
	string result = word;

	// Check if the word is in the irregular verbs map
	for (int i = 0; i<irregularVerbs.size(); i++) {
		if (word == irregularVerbs[i].first) {
			result = irregularVerbs[i].second;
			break;
		}
	}

	if (word.size() > 4) {
		// Check for common verb suffixes
		if (word.substr(word.size() - 2) == "ied") {
			result = word.substr(0, word.size() - 3) + 'y';
		} 
		else if (word.substr(word.size() - 3) == "ing") {
			if (word[word.size()-4] == 'v') {
				result = word.substr(0, word.size() - 3) + 'e';
			} 
			else {
				result = word.substr(0, word.size() - 3);
			}
		} 
		else if (word.back() == 's') {
			result = word.substr(0, word.size() - 1);
		} 
		else if (word.substr(word.size() - 2) == "es") {
			result = word.substr(0, word.size() - 2);
		} 
		else if (word.substr(word.size() - 2) == "en") {
			result = word.substr(0, word.size() - 2);
		}

		// Add more rules to handle irregular forms here.
	}

	return result;
}

int main() {

	string word;

	while(cin>>word) {
		cout << "Input Word: " << word <<endl;
		cout << "Stemmed Word: " << removeVerbSuffix(word) << endl;
		cout << endl;
	}
}