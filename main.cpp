/* This is the console executable, that makes use of the BullCows class
 * This acts as the view in MVC pattern and is responsible for all 
 * user interaction. For game logic see FBullCowGame class.
 */

#include "FBullCowGame.h"

#include <iostream>
#include <string>

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain());

	return 0;
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows - a fun word game.\n\n";
	std::cout << "              }     {          _____" << std::endl;
	std::cout << "              ( O O )         ( o o ) " << std::endl;
	std::cout << "     /---------\\   /           \\   /--------\\" << std::endl;
	std::cout << "    /  | BULL |  O               O |  COW   |\\" << std::endl;
	std::cout << "   *   |-,----|                    |--------| * " << std::endl;
	std::cout << "       ^      ^                    ^        ^ " << std::endl;
	std::cout << std::endl;
	std::cout << " The goal of the game is to guess the isogram called The Hidden Word.\n"
	" If you guess the letter that is in The Hidden Word and you got it in the right place,\n"
	" you will get a bull.\n"
	" If you guess the letter, but it is on another position in The Hidden Word,\n"
	" then you will get a cow.\n" << std::endl;
	std::cout<< "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram?\n\n";
	return;
}

FText GetValidGuess()
{
	EWordStatus WordStatus = EWordStatus::Invalid_Status;
	FText Guess;

	do
	{
		const int32 currentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << currentTry << " of " << BCGame.GetMaxTries() << ". Write your guess here: ";

		std::getline(std::cin, Guess);
		WordStatus = BCGame.CheckGuessValidity(Guess);

		switch (WordStatus)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a valid isogram. \n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Enter your word in lowercase. \n\n";
			break;
		default:
			break;
		}
	} while (EWordStatus::OK != WordStatus);

	return Guess;
}

void PlayGame()
{
	BCGame.Reset();

	const int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "Number of guesses: " << MaxTries << std::endl;

	while(!BCGame.IsGameOver() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		const FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: "<< BullCowCount.Bulls << ". Cows: " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response;
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameOver()) std::cout << "Congratulations. You won!\n";
	else std::cout << "You run out of turns. The hidden word is: " << BCGame.RevealHiddenWord() << "/n/n";
}
