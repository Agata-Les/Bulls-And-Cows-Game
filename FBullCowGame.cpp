#include "FBullCowGame.h"

#include <map>
#include <cctype>

#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "amount";

	bIsGameWon = false;
	MyMaxTries = FindNumberOfMaxTries();
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameOver() const { return bIsGameWon; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::FindNumberOfMaxTries() const
{
	using WordLength = int32;
	using NumberOfTries = int32;

	TMap<WordLength, NumberOfTries> WordLengthToTries{ {3, 4}, { 4, 8 },{ 5, 10 },{ 6, 15 },{ 7, 16 } };
	return WordLengthToTries[GetHiddenWordLength()];
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Word) const
{
	if (GetHiddenWordLength() != Word.length())
	{
		return EWordStatus::Wrong_Length;
	}
	else if (!IsLowercase(Word))
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (!IsIsogram(Word))
	{
		return EWordStatus::Not_Isogram;
	}
	else
	{
		return EWordStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	const int32 WordLength = MyHiddenWord.length();

	for(int32 i = 0; i < WordLength; ++i)
	{
		for(int32 j = 0; j < WordLength; ++j)
		{
			if(MyHiddenWord[i] == Guess[j])
			{
				if (i == j) BullCowCount.Bulls++;
				else BullCowCount.Cows++;
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) bIsGameWon = true;

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	TMap<char, bool> LettersSeen;

	for (auto Letter : Word)
	{
		Letter = std::tolower(Letter);
		if(LettersSeen[Letter]) return false;
		else LettersSeen[Letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for(auto Letter : Word)
	{
		if (!std::islower(Letter)) return false;
	}
	return true;
}
