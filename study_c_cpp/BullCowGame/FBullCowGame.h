#pragma once
#include <string>

using FString = std::string;
using int32 = int;


struct FBullCowCount
{
	int bulls = 0;
	int cows = 0;
};

enum EWordStatus
{
	OK,
	not_isograme,
	wrong_length,
	is_upcase
	
};

class FBullCowGame {
public:
	FBullCowGame(); //constructer
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	EWordStatus checkGameValidity(FString) const;

	void reset();//TODO to make a more rich return value
	FBullCowCount submitGuess(FString);

private:
	int32 myCurrentTry;
	int32 myMaxTries;
	FString myHiddenWord;


};