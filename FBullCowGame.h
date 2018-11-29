#pragma once

#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid_Status,
	OK, 
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();
	void Reset();
	
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	bool IsGameOver() const;
	int32 GetCurrentTry() const;
	EWordStatus CheckGuessValidity(FString) const;
	FBullCowCount SubmitValidGuess(FString);
	FString RevealHiddenWord() const;

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bIsGameWon;
	int32 FindNumberOfMaxTries() const;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
