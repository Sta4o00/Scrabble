#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

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
	
	int currRound = 0, allRounds = 10, lettersDisplayed = 10, points = 0;
	for (; currRound < allRounds; currRound++)
	{
		cout << "Round " << currRound + 1 << ". ";
		cout << "Available letters: ";
		displayLetters(letters[currRound]);
		string input;
		cin >> input;
		while (find(wordLibrary.begin(), wordLibrary.end(), input) == wordLibrary.end()) {
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
