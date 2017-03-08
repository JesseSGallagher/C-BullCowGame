/*This is the console exe, that make use of the BullCow class
This acts as a view in a MVC pattern, and is responsible for all
use interaction. For game logivc see the FBullCowGame class*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string; // FText - in Unreal typically means user output
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool PlayAgain();
void PrintGameSummary();


FBullCowGame BCGame; // instantiate new game, reused for new games

// the entry point for the game
int main() 
{
	
	bool bPlays = false;
	do {
		PrintIntro();
		PlayGame();
		bPlays = PlayAgain();
	}
	while (bPlays == true);

	return 0;

}
// introduces the game
void PrintIntro() 
{
	std::cout << "*******************************************************" <<std::endl;
	std::cout << "*( B | U | L | L | S ) ( A | N | D ) ( C | O | W | S )*" << std::endl;
	std::cout << "*******************************************************" << std::endl << std::endl;

	std::cout << "A fun word game. "
		<< "Can you guess the letters of the isogram, that I'm thinking of?" << std::endl;
	return;
}
void PlayGame()
{
		int32 wordLen;
		std::cout << "Enter word length, it may be 4 to 8 characters long: ";
		std::cin >> wordLen; // TODO - possibly add validation
		std::cout << std::endl;
		std::cin.clear();    // restore input stream to working state
		std::cin.ignore(100, '\n');  // get rid of any garbage chars
		BCGame.Reset(wordLen);

		int32 MaxTries = BCGame.GetMaxTries();
		
		// loop asking for guesses while the game
		// is NOT won and there are still tries remaining

		while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
			FText Guess = GetValidGuess();

			// submit valid guess to the game, and receive counts
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

			std::cout << " Bulls = " << BullCowCount.Bulls;
			std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
		}

		PrintGameSummary();
		return;
}
// gets a guess from the player
bool PlayAgain() 
{
	// gets if user wants to play again
	std::cout << "Would you like to play again?(Y/N): ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	std::cout << FString(100, '\n');
	return (Response[0] == 'y' || Response[0] == 'Y');
}
FText GetValidGuess() 
{		
	FText Guess = ""; // needs the #string library
	std::cin.clear();
	EGuessStatus Status = EGuessStatus::INVALID_STATUS;
	do {
		
		
		std::cout << "Enter your Guess: ";
		std::getline(std::cin, Guess);
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries();

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::WRONG_LENGTH:
			std::cout << " Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << " Please enter the word that is all lowercase letters.\n\n";
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << " Please enter a word without repeating letters\n\n";
			break;
		default:
			// means we assume the guess is valid
			break;
		}
	} while (Status !=  EGuessStatus::OK); // keep looking until there are no errors.
	return Guess;
}
void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WON THE GAME!";
	}
	else
	{
		std::cout << "You've lost the game :(";
	}
	std::cout << "\n\n";
}
/* '\n' does not flush the buffer like endl */