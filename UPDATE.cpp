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

using namespace std;

void options(string gameOptions, vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit);


void displayOptions() {
	cout << "> 1. New game" << endl;
	cout << "> 2. Settings" << endl;
	cout << "> 3. Add a word" << endl;
	cout << "> 4. Exit" << endl;
	cout << "//Write to access one of the options." << endl << "//If you write random symbols, a new game will start." << endl;
}

void settings(vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit) {
	cout << "> 1. Change letters count" << endl;
	cout << "> 2. Change rounds count" << endl;
	string s;
	getline(cin, s);
	if (s == "Change letters count" || s == "change letters count" || s == "1") {
		cout << "How many letters should be given: " << endl;
		int num;
		cin >> num;
		for (int i = 0; i < letters.size(); i++)
		{
			letters[i].erase(letters[i].begin() + num, letters[i].end());
		}
	}
	if (s == "Change rounds count" || s == "change rounds count" || s == "2")
	{
		cout << "How many rounds should be given: " << endl;
		int num;
		cin >> num;
		roundCount = num;
	}
	cin.ignore(256, '\n');

	displayOptions();

	string opt;
	getline(cin, opt);

	options(opt, wordLibrary, letters, roundCount, exit);
}



void newWord(vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit) {
	cout << "What word do you want to add to the game?" << endl;
	string newWord;
	cin >> newWord;
	wordLibrary.push_back(newWord);

	cin.ignore(256, '\n');

	displayOptions();

	string opt;
	getline(cin, opt);

	options(opt, wordLibrary, letters, roundCount, exit);
}

void exitGame(bool& exit) {
	exit = true;
}

void options(string gameOptions, vector<string>& wordLibrary, vector<vector<char>>& letters, int& roundCount, bool& exit) {
	if (gameOptions == "Settings" || gameOptions == "settings" || gameOptions == "2")
		settings(wordLibrary, letters, roundCount, exit);
	if (gameOptions == "Add a word" || gameOptions == "add a word" || gameOptions == "3")
		newWord(wordLibrary, letters, roundCount, exit);
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
	vector<string> wordLibrary = { "cat", "dog", "hat", "rock", "rat", "egg", "pet", "time", "red",
		"blue", "eye", "hair", "yellow", "brain", "program", "side", "bed", "map", "seed", "deck", "letter", "let", "are", "is",
		"map", "geek", "it", "gap", "page", "kit", "what", "whatever", "bear", "gate", "advantage", "site", "sad", "very", "good",
		"mad", "feed", "fed", "game", "seek", "let", "big", "dead", "hate", "go", "greed", "stand", "make", "sit", "duck", "bar",
		"rich", "give", "med", "stream", "state", "mate", "read", "master", "him", "me" };
	//I haven't added all possible words on purpose, so the player can test the "Add a word" setting
	vector<vector<char>> letters = { {'a','m','g','e','d','a','v','s','t','i'}, {'f','d','e','e','m','s','t','g','g','k'},
		{'m','e','d','a','r','z','a','e','g','p'}, {'s','e','k','e','d','u','c','z','d','e'},
		{'u','r','l','e','t','a','m','s','t','r'}, {'m','a','g','p','d','a','m','e','k','i'} ,
		{'w','a','t','h','e','b','r','v','e','m'}, {'d','a','v','e','d','n','g','s','t','a'} ,
		{'v','e','g','o','y','r','m','o','t','i'}, {'c','h','i','g','b','a','r','z','s','m'} };
	int infLoop = 1;
	bool exit = false;
	while (infLoop) {
		displayOptions();
		
		string gameOptions;
		getline(cin, gameOptions);
		
		int currRound = 0, allRounds = 10, points = 0;

		options(gameOptions, wordLibrary, letters, allRounds, exit);

		if (exit)
			break;
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
			if (currRound != allRounds - 1)
				cout << "Your points so far are: " << points << endl;
		}
		cout << "Your total points are " << points << "." << endl;

		cout << "Good game!\n" << endl;

		cin.ignore(256, '\n');
	}


	return 0;
}
