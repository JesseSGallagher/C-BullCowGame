#pragma once

#include "FBullCowGame.h"
#include<iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

//following Unreal standards in c++
#define Tmap std::map 
using FString = std::string;
using int32 = int;

bool FBullCowGame::bIsIsogram(FString Word) const
{
	// checks to see if the letters in the word are repeated and returns a boolean
	if (Word.length() <= 1) { return true; }

	Tmap<char, bool> LetterSeen; 
	for (auto Letter : Word) 
	{
		Letter = tolower(Letter); 
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true; 
}
bool FBullCowGame::bIsLowercase(FString Word) const
{	
	// checks to see if each letter in the word is lowercase
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) 
		{
			return false;
		}
	}
	return true;
}
FBullCowGame::FBullCowGame()
{
	MyHiddenWord = GetHiddenWord(4); //initalize with word with length of passed value
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
int32 FBullCowGame::GetMaxTries() const 
{
	//returns the amount of tries based on word length
	Tmap <int32, int32> WordLengthToMaxTries{{3,3},{4,3},{5,5},{6,5},{7,10},{8,10}}; 
	//first int (wordlength), second int (numberoftries)
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry; 
}
int32 FBullCowGame::GetHiddenWordLength() const 
{ 
	return MyHiddenWord.length(); 
}
FString FBullCowGame::GetHiddenWord(int32 wordLength)
{
	std::string oneWord;
	std::string Words[10];
	int32 count = 0;

	std::ifstream wordsFile;
	wordsFile.open("words.txt");
	while (wordsFile >> oneWord) {
		if (oneWord.length() == wordLength) {
			Words[count] = oneWord;
			count++;
		}
	}
	srand(time(NULL));
	oneWord = Words[rand() % 10];
	wordsFile.close();
	return oneWord;
}
bool FBullCowGame::IsGameWon() const
{ 
	return bGameIsWon;
}
void FBullCowGame::Reset(int32 wordLen)
//intializes, and restarts game
{
	MyHiddenWord = GetHiddenWord(wordLen); //variable changes word length
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// returns the status of the guess
	if (!bIsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!bIsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

											  // loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}