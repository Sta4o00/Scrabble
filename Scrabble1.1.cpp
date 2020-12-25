#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void displayOptions() {
	cout << "> New game" << endl;
	cout << "> Settings" << endl;
	cout << "> Add a word" << endl;
	cout << "*write to access one of the options*" << endl;
}

void settings(vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount) {
	cout << "> Change letters count" << endl;
	cout << "> Change rounds count" << endl;
	string s;
	getline(cin, s);
	if (s == "Change letters count" || s == "change letters count") {
		cout << "How many letters should be given: " << endl;
		int num;
		cin >> num;
		for (int i = 0; i < letters.size(); i++)
		{
			letters[i].erase(letters[i].begin() + num, letters[i].end());
		}
	}
	if (s == "Change rounds count" || s == "change rounds count")
	{
		cout << "How many rounds should be given: " << endl;
		int num;
		cin >> num;
		roundCount = num;
	}
}

void newWord(vector<string>& wordLibrary) {
	cout << "What word do you want to add to the game?" << endl;
	string newWord;
	cin >> newWord;
	wordLibrary.push_back(newWord);
}

void options(string gameOptions, vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount) {
	if (gameOptions == "Settings" || gameOptions == "settings")
		settings(wordLibrary, letters, roundCount);
	if (gameOptions == "Add a word" || gameOptions == "add a word")
		newWord(wordLibrary);
}

bool validWord(string input, vector<char> letters, vector<string> wordLibrary) {
	if (find(wordLibrary.begin(), wordLibrary.end(), input) == wordLibrary.end())
		return false;
	for (int i = 0; i < input.size(); i++)
	{
		if (find(letters.begin(), letters.end(), input[i]) != letters.end())
			letters.erase(find(letters.begin(), letters.end(), input[i]));
		else
			return false;
	}
	return true;
}

void displayLetters(vector<char> letters) {
	for (int i = 0; i < letters.size(); i++)
	{
		cout << letters[i] << " ";
	}
	cout << endl;
}

int main() {
	vector<string> wordLibrary = { "cat", "dog", "hat", "rock", "rat", "egg", "pet", "time", "red",
		"blue", "eye", "hair", "yellow", "brain", "program", "side", "bed", "map", "seed", "deck", "letter", "let", "are", "is",
		"map", "geek", "it", "gap", "page", "kit", "what", "whatever", "bear", "gate", "advantage", "site", "sad", "very", "good",
		"mad", "feed", "fed", "game", "seek", "let", "big", "dead", "hate", "go", "greed", "stand", "make", "sit", "duck", "bar",
		"rich", "give", "med" };
	vector<vector<char>> letters = { {'a','m','g','e','d','a','v','s','t','i'}, {'f','d','e','e','m','s','t','g','g','k'},
		{'a','e','m','g','r','z','a','e','d','p'}, {'s','e','k','e','d','u','c','z','d','e'},
		{'u','r','l','e','t','a','m','s','t','r'}, {'m','a','g','p','d','a','m','e','k','i'} ,
		{'w','a','t','h','e','b','r','v','e','m'}, {'d','a','v','e','d','n','g','s','t','a'} ,
		{'v','e','g','o','y','r','m','o','t','i'}, {'c','h','i','g','b','a','r','z','s','m'} };

	displayOptions();
	string gameOptions;
	getline(cin, gameOptions);
	
	int currRound = 0, allRounds = 10, points = 0;

	options(gameOptions, wordLibrary, letters, allRounds);

	for (; currRound < allRounds; currRound++)
	{
		cout << "Round " << currRound + 1 << ". ";
		cout << "Available letters: ";
		displayLetters(letters[currRound]);
		string input;
		cin >> input;
		while (!validWord(input, letters[currRound], wordLibrary)) {
			cout << "Invalid word. Try again with: ";
			displayLetters(letters[currRound]);
			cin >> input;
		}
		points += input.size();
		cout << "Your points so far are: " << points << endl;
	}
	cout << "Your total points are " << points << "." << endl;
	cout << "Good game!" << endl;



	return 0;
}
