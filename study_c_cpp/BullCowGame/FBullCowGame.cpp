#include "FBullCowGame.h"


FBullCowGame::FBullCowGame() { reset(); }

int32 FBullCowGame::getMaxTries() const { return myMaxTries; }
int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }


FBullCowCount FBullCowGame::submitGuess(FString guess)
{
	myCurrentTry++;
	FBullCowCount bullCowCount;
	for (int32 i = 0; i < myHiddenWord.length(); i++) {
		for (int32 j = 0; j < guess.length(); j++) {
			if (myHiddenWord[i] == guess[j]) {
				if (i==j) {
					bullCowCount.bulls++;
				}
				else {
					bullCowCount.cows++;
				}

			}
		}
	}
	return bullCowCount;
}

void FBullCowGame::reset()
{
	constexpr int32 MAX_TRIES = 5;
	myHiddenWord = "xuwen";
	myMaxTries = MAX_TRIES;
	myCurrentTry = 1;
}




bool FBullCowGame::isGameWon() const
{
	return false;
}

EWordStatus FBullCowGame::checkGameValidity(FString) const
{
	return EWordStatus::OK;
}
