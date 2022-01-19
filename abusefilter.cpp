#include <bits/stdc++.h>
using namespace std;


class TrieNode {
public:
	char data;
	TrieNode **children;
	bool isTerminal;

	TrieNode(char data) {
		this -> data = data;
		children = new TrieNode*[26];
		for(int i = 0; i < 26; i++) {
			children[i] = NULL;
		}
		isTerminal = false;
	}
};


class Trie {
	TrieNode *root;

public:
	Trie() {
		root = new TrieNode('\0');
	}

	// Insert Word
	void insertWordHelper(TrieNode *root, string word) {
		// Base Case
		if(!word.size()) {
			root -> isTerminal = true;
			return;
		}

		// Small Calculation
		TrieNode *child;
		int index = word[0] - 'a';
		if(root -> children[index]) {
			child = root -> children[index];
		} else {
			child = new TrieNode(word[0]);
			root -> children[index] = child;
		}

		// Recursive Call
		insertWordHelper(child, word.substr(1));
	}

	void insertWord(string word) {
		insertWordHelper(root, word);
	}

	// Search Word
	bool SearchHelper(TrieNode *root, string word) {
		// Base Case
		if(!word.size()) {
			if(root -> isTerminal) {
				return true;
			}
			return false;
		}

		// Small Calculation
		int index = word[0] - 'a';
		TrieNode *child;
		if(root -> children[index]) {
			child = root -> children[index];
		} else {
			return false;
		}

		// Recursive Call
		return SearchHelper(child, word.substr(1)); 
	}

	bool search(string word) {
		return SearchHelper(root, word);
	}

	// Remove Word
	void removeWordHelper(TrieNode *root, string word) {
		if(!word.size()) {
			root -> isTerminal = false;
			return;
		}

		int index = word[0] - 'a';
		TrieNode *child;
		if(root -> children[index]) {
			child = root -> children[index];
		} else {
			return;
		}

		removeWordHelper(child, word.substr(1));

		// Remove the child if not needed
		if(!root -> isTerminal) {
			for(int i = 0; i < 26; i++) {
				if(root -> children[i]) {
					return;
				}
			}
			delete child;
			root -> children[index] = NULL;
		}
	}

	void removeWord(string word) {
		removeWordHelper(root, word);
	}
};

int main() {
	Trie abuseDictionary;
	vector<string> abuseList = {"harami", "gandu", "chutiya", "chutiyapa"};

	// Adding the abuse list word in the trie
	for(auto it = abuseList.begin(); it != abuseList.end(); it++) {
		string abuse = *it;
		abuseDictionary.insertWord(abuse);
	}

	string userInput;
	cout << "Enter Message: ";
	getline(cin, userInput);
	vector<string> userInputWords;
	string perWord = "";
	cout << "Process Running..." << endl;

	// Sperating each word and cloning them in a vector of strings
	for(int i = 0; i < userInput.length(); i++) {
		if(userInput[i] == ' ') {
			if(abuseDictionary.search(perWord)) {
				for(int j = 1; j < perWord.length() - 1; j++) {
					perWord[j] = '*';
				}
			}
			userInputWords.push_back(perWord);
			perWord = "";
		} else {
			perWord += userInput[i];
		}
	}
	userInputWords.push_back(perWord);
	
	// Printing the message
	for(auto it = userInputWords.begin(); it != userInputWords.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}