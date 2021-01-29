/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Stanislav Ignatov
* @idnumber 62417
* @compiler Visual Studio
*
* <cpp file with the whole project in it>
* UPDATE
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <fstream>

using namespace std;

void options(string gameOptions, vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit, fstream& wordsInTxt);


void displayOptions() {
	cout << "> 1. New game" << endl;
	cout << "> 2. Settings" << endl;
	cout << "> 3. Add a word" << endl;
	cout << "> 4. Exit" << endl;
	cout << "//Write to access one of the options." << endl << "//If you write random symbols, a new game will start." << endl;
}

void goBack(vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit, fstream& wordsInTxt) {
	cin.ignore(256, '\n');
	displayOptions();

	string opt;
	getline(cin, opt);

	options(opt, wordLibrary, letters, roundCount, exit, wordsInTxt);
}

vector<vector<char>> originalLetters;

void settings(vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit, fstream& wordsInTxt) {
	cout << "> 1. Change letters count" << endl;
	cout << "> 2. Change rounds count" << endl;
	cout << "Press '*' to go back to the menu." << endl;
	string s;
	getline(cin, s);
	if (s == "*") {
		goBack(wordLibrary, letters, roundCount, exit, wordsInTxt);
		return;
	}
	if (s == "Change letters count" || s == "change letters count" || s == "1") {
		cout << "How many letters should be given: " << endl;
		int num;
		cin >> num;
		originalLetters = letters;
		for (int i = 0; i < letters.size(); i++)
		{
			letters[i].erase(letters[i].begin() + num, letters[i].end());
		}
	}
	else if (s == "Change rounds count" || s == "change rounds count" || s == "2")
	{
		cout << "How many rounds should be given: " << endl;
		int num;
		cin >> num;
		roundCount = num;
	}
	else {
		cout << "Invalid input.";
	}
	goBack(wordLibrary, letters, roundCount, exit, wordsInTxt);
}

void strToLower(string& s) {
	for (int i = 0; i < s.size(); i++) {
		if (isupper(s[i]))
			s[i] = tolower(s[i]);
	}
}

void newWord(vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit, fstream& wordsInTxt) {
	cout << "What word do you want to add to the game?" << endl;
	cout << "Press '*' to go back to the menu." << endl;
	string newWord;
	cin >> newWord;
	if (newWord == "*") {
		goBack(wordLibrary, letters, roundCount, exit, wordsInTxt);
		return;
	}
	strToLower(newWord);
	bool valid = true;
	for (int i = 0; i < newWord.size(); i++)
	{
		if (newWord[i] < 'a' || newWord[i] > 'z') {
			cout << "That is not a word!" << endl;
			valid = false;
			break;
		}
	}
	if (find(wordLibrary.begin(), wordLibrary.end(), newWord) != wordLibrary.end()) {
		cout << "The word is already in the library!" << endl;
		valid = false;
	}
	if (valid) {
		wordLibrary.push_back(newWord);
		wordsInTxt.clear();
		wordsInTxt << endl << newWord;
	}
	goBack(wordLibrary, letters, roundCount, exit, wordsInTxt);
}

void exitGame(bool& exit) {
	exit = true;
}

void options(string gameOptions, vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit, fstream& wordsInTxt) {
	if (gameOptions == "Settings" || gameOptions == "settings" || gameOptions == "2")
		settings(wordLibrary, letters, roundCount, exit, wordsInTxt);
	if (gameOptions == "Add a word" || gameOptions == "add a word" || gameOptions == "3")
		newWord(wordLibrary, letters, roundCount, exit, wordsInTxt);
	if (gameOptions == "Exit" || gameOptions == "exit" || gameOptions == "4")
		exitGame(exit);
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
	fstream wordsInTxt;
	string currWord;
	vector<string> wordLibrary;
	wordsInTxt.open("wordLibrary.txt", ios::app | ios::in | ios::out);
	//I haven't added all possible words on purpose, so the player can test the "Add a word" setting
	vector<vector<char>> letters = { {'a','m','g','e','d','a','v','s','t','i'}, {'f','d','e','e','m','s','t','g','g','k'},
		{'m','e','d','a','r','z','a','e','g','p'}, {'s','e','k','e','d','u','c','z','d','e'},
		{'u','r','l','e','t','a','m','s','t','r'}, {'m','a','g','p','d','a','m','e','k','i'} ,
		{'w','a','t','h','e','b','r','v','e','m'}, {'d','a','v','e','d','n','g','s','t','a'} ,
		{'v','e','g','o','y','r','m','o','t','i'}, {'c','h','i','g','b','a','r','z','s','m'} };
	int infLoop = 1;
	bool exit = false;
	if (wordsInTxt.is_open()) {
		while (getline(wordsInTxt, currWord))
		{
			wordLibrary.push_back(currWord);
		}
	}
	while (infLoop) {
		jumpHere:
		if (!wordsInTxt.is_open())
		{
			cout << "File couldn't open.\n";
			break;
		}
		displayOptions();

		string gameOptions;
		getline(cin, gameOptions);

		int currRound = 0, allRounds = 10, points = 0;

		options(gameOptions, wordLibrary, letters, allRounds, exit, wordsInTxt);
		
		if (exit)
			break;
		for (; currRound < allRounds; currRound++)
		{
			cout << "Round " << currRound + 1 << ". ";
			cout << "Available letters: ";
			displayLetters(letters[currRound]);
			cout << "Press '*' to go back to the menu." << endl;
			string input;
			cin >> input;
			if (input == "*") {
				cin.ignore(256, '\n');
				goto jumpHere;
			}
			while (!validWord(input, letters[currRound], wordLibrary)) {
				cout << "Invalid word. Try again with: ";
				displayLetters(letters[currRound]);
				cin >> input;
			}
			points += input.size();
			if (currRound != allRounds - 1)
				cout << "Your points so far are: " << points << endl;
		}
		cout << "Your total points are " << points << "." << endl;

		cout << "Good game!\n" << endl;

		cin.ignore(256, '\n');

		letters = originalLetters;
	}
	cout << "Thanks for playing!" << endl;
	wordsInTxt.close();

	return 0;
}
