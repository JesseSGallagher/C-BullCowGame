#pragma once

#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	INVALID_STATUS,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};
class FBullCowGame 
{
private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool bIsIsogram(FString) const;
	bool bIsLowercase(FString) const;
public:
	FBullCowGame(); 
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord(int32);
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void Reset(int32); 
	FBullCowCount SubmitValidGuess(FString);
	
};