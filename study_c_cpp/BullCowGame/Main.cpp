#include <iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;
using FText = std::string;

void introduce();
void playGame();
FText getGuessAndPrintBack();
bool askToPlayAgain();

FBullCowGame BCGame;

//entry point of the game
int main()
{
	bool bPlayAgain = false;
	do {
		introduce();
		playGame();
		bPlayAgain = askToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

//loop the getGuess
void playGame()
{
	BCGame.reset();
	int32 maxTries = BCGame.getMaxTries();
	for (int32 count = 0; count <= maxTries; count++) {
		FText guess = getGuessAndPrintBack();
		FBullCowCount bullCowCount = BCGame.submitGuess(guess);
		std::cout << "Bulls :" << bullCowCount.bulls;
		std::cout << "  Cows :" << bullCowCount.cows;

		std::cout << std::endl;


	}
}

// introduce the game
void introduce() {
	constexpr int32 WORD_LENGTH = 5;
	std::cout << "Welcome to the Bull and Cow game\n";
	std::cout << "Can you guess " << BCGame.getHiddenWordLength() << " letter iosgrame I'm thinking of?\n";
	std::cout << std::endl;
}

//get the word the word
FText getGuessAndPrintBack() {
	int32 currentTry = BCGame.getCurrentTry();
	std::cout << "This is try."<< BCGame.getCurrentTry() <<" Enter your guess : ";
	FText guess = "";
	getline(std::cin, guess);
	std::cout << "Your answer was :" << guess <<"\n";
	std::cout << std::endl;
	return guess;
}

bool askToPlayAgain()
{
	std::cout << "Do you want to to continue?";
	FText answer = "";
	getline(std::cin, answer);
	return answer[0] == 'y' || answer[1] == 'Y';
}

