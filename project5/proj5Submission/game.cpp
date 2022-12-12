#define _CRT_SECURE_NO_WARNINGS
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;

const char WORDFILENAME[] = "Words.txt";
const int MAXWORDLISTSIZE = 9000;
const int MAXINPUTLENGTH = 102;

// Windows users:  Use / instead of \ for pathname separators.

int playOneRound(const char words[][7], int nWords, int wordnum);
int validWord(char word[]);
int goldScore(char probe[], char target[]);
int silverScore(char probe[], char target[]);
int strLength(char string[]);


int main()
{
	char w[MAXWORDLISTSIZE][7];

	cout << fixed << showpoint;
	cout << setprecision(2);

	int numWords = getWords(w, MAXWORDLISTSIZE, WORDFILENAME);
	if (numWords == -1) {
		cerr << "The path to your file of words is probably incorrect" << endl;
		return 1;
	}
	else if (numWords < 1) {
		cout << "No words were loaded, so I can't play the game." << endl;
		return 1;
	}
	else if (numWords > MAXWORDLISTSIZE) {
		cout << "Too many words loaded, game unplayable" << endl;
		return 1;
	}

	/*
	// Display word list
	for (int i = 0; i < numWords; i++) {
		cerr << w[i] << " ";
	}
	cerr << endl << numWords << endl;
	*/

	// Main gameplay loop
	int rounds;
	int roundScore;
	float totalScore = 0.0;
	int wordIndex;
	int minScore;
	int maxScore=1;

	cout << "How many rounds do you want to play? ";
	cin >> rounds;
	cin.ignore(9999999, '\n');

	if (rounds < 0) {
		cout << "The number of rounds must be positive." << endl;
		return 1; // Terminate program
	}
	
	for (int i = 0; i < rounds; i++) {
		roundScore = 0;
		cout << endl << "Round " << i + 1 << endl;
		wordIndex = randInt(0, numWords - 1);
		cout << "The hidden word is " << strLength(w[wordIndex]) << " letters long." << endl;
		roundScore = playOneRound(w, numWords, wordIndex);
		totalScore += roundScore;

		if (roundScore > maxScore)
			maxScore = roundScore;
		if (i == 0) // If first round, set score as minimum
			minScore = roundScore;
		else if (roundScore < minScore)
			minScore = roundScore;

		if (roundScore == 1) {
			cout << "You got it in " << roundScore << " try." << endl;
		}
		else {
			cout << "You got it in " << roundScore << " tries." << endl;
		}
		cout << "Average: " << totalScore / (i + 1) << ", minimum: " << minScore << ", maximum: " << maxScore << endl;
	}
}

int playOneRound(const char words[][7], int nWords, int wordnum) {
	char current[7];
	// Error detection and current word setup
	if (wordnum < 0 || wordnum >= nWords || nWords < 0) // Validate index and nWords in array
		return -1;
	strcpy(current, words[wordnum]);
	cerr << "Secretword: " << current << endl;

	// Take guess and score it
	int score = 0; 
	char guess[MAXINPUTLENGTH];
	int numGold;
	int numSilv;
	int known;
 
	while (true){ // Main gameplay loop
		numGold = 0;
		numSilv = 0;
		cout << "Probe word: ";
		cin.getline(guess, MAXINPUTLENGTH);
		if (!validWord(guess) || strcmp(guess, "") == 0) {
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue; // If invalid word, restart loop
		}

		// Check if word in wordlist
		known = 0;
		for (int i = 0; i < nWords; i++) {
			if (strcmp(words[i], guess) == 0) // If guess matches any word in wordlist, return true
				known = 1;
		}
		if (known == 0) {
			cout << "I don't know that word." << endl;
			continue;
		}
		else
			//cerr << "Word Found: " << current << endl;

		score++; // If all checks passed, add as valid guess

		// Score guess
		numGold = goldScore(guess, current);
		numSilv = silverScore(guess, current);
		if (numGold == strLength(current)) { // If perfectly guessed, end round
			return score;
		}
		cout << "Golds: " << numGold << ", Silvers: " << numSilv << endl;

	}


}

// Returns num of golds
int goldScore(char probe[], char target[]) {
	int golds = 0;
	int limit = 0; // Stores length of smaller string to avoid out of range index
	if (strLength(probe) > strLength(target))
		limit = strLength(target);
	else
		limit = strLength(probe);

	for (int i = 0; i < limit; i++) { // For each index within limit
		if (probe[i] == target[i]) { // If matches letter in same spot, immediately add to gold count
			golds++;
		}
	}
	return golds;
}

int silverScore(char probe[], char target[]) {
	int paired[7] = { -1,-1,-1,-1,-1,-1,-1 }; // Array tracks already paired items in target, preventing double scores
	int silvers = 0;
	for (int i = 0; probe[i] != '\0'; i++) { // For each letter in guess
		for (int j = 0; target[j] != '\0'; j++) { // Check each letter in target
			if (probe[i] == target[j] && paired[j] != j) { // If match and target char not already paired

				 // If target char or probe char are gold with something else, don't count and increment target char.
				if ((j < strLength(probe) && probe[j] == target[j]) || (i < strLength(target) && probe[i] == target[i])) {
					continue;
				}
				// If passed all tests, save as paired letter and add to silvers
				paired[j] = j;
				silvers += 1;
				break;
			}
		}
	}
	return silvers;
}

int validWord(char word[]) {
	if (strLength(word) > MAXWORDLEN || strLength(word) < MINWORDLEN) {
		return 0;
	}
	for (int i = 0; i < strLength(word); i++) {
		if (!islower(word[i])){
			return 0;
		}
	}
	return 1;
}

int strLength(char string[]) {
	for (int i = 0; i < MAXINPUTLENGTH; i++) { // Loops runs *forever* til it hits null-terminated character
		if (string[i] == '\0')
			return i;
	}
	return -1;
}