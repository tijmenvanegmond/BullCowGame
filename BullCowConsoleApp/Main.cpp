/*	Main.cpp : Defines the entry point for the console application.
	Uses the FBullCowGame class, and acts as an view for the game
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
int32 GetValidWordLength();
FText GetValidGuess();
FText GetGuess();
void PrintFeedback(FBullCowCount);
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame;
FText const LINE_BREAK = "-------------------------------------------------------------------------------\n";

//Starts application
int main()
{
	PrintIntro();
	do {
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

//Introduces the game.
void PrintIntro()
{
	std::cout << LINE_BREAK;
	std::cout << "Welcome to bulls and cows.\n";	
	std::cout << LINE_BREAK;
	std::cout << "You need to guess the isogram (a word with no repeating letters).\n";
	std::cout << "Bulls mean a letter is used in the exact same place.\n";
	std::cout << "Cows mean a letter is used but its not in the right place.\n";
	std::cout << LINE_BREAK;
}

//Starts the game and keeps it running until its done.
void PlayGame()
{	
	BCGame.Reset();
	BCGame.SetWordLength(GetValidWordLength());
	
	while (BCGame.IsTryLeft() && !BCGame.IsGameWon())
	{
		std::cout << LINE_BREAK;
		std::cout << "Try " << BCGame.GetCurrentTry() << " out of " << BCGame.GetMaxTries() << std::endl;
		std::cout << LINE_BREAK;

		FString validGuess = GetValidGuess();
		
		PrintFeedback(BCGame.SubmitValidGuess(validGuess));		
	}
	std::cout << LINE_BREAK;
	PrintGameSummary();
}

int32 GetValidWordLength()
{	
	std::cout << "Choose the length (between 3 and 7) of isogram you want to guess : ";	
	FString input;
	std::getline(std::cin, input);	
	int32 number;
	try {
		number = stoi(input);		
	}
	catch (...)//the cast to interger failed
	{
		std::cout << "Thats not a number :( \n";
		return GetValidWordLength();
	}

	if (number >= 3 && number <= 7) {
		return number;
	}
	else {
		std::cout << "That\'s not a number between 3 and 7.\n";
		return GetValidWordLength();
	}
		
}

//Keeps asking the player for a guess until a valid guess is put in.
FText GetValidGuess()
{
	FString guess = GetGuess();
	EGuessValidityStatus status = BCGame.CheckGuessValidity(guess);
	switch (status)
	{
		case EGuessValidityStatus::OK:
			return guess;
		case EGuessValidityStatus::Not_lowercase:
			std::cout << "Please only use lowercase letters. \n";
			return GetValidGuess(); //fck yeah recursion
		case EGuessValidityStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters. \n";
			return GetValidGuess(); //fck yeah recursion
		case EGuessValidityStatus::Wrong_Length:
			std::cout << "Please enter a word with "<< BCGame.GetHiddenWordLength() << " letters. \n";
			return GetValidGuess();
		default:
			std::cout << "Please enter a valid word. \n";
			return GetValidGuess();
	}
}

//Asks the player for a guess trough the console
FText GetGuess()
{	
	FText	Guess = "";
	std::cout << "Enter a " << BCGame.GetHiddenWordLength() << " letter isogram: ";
	std::getline(std::cin, Guess);
	return Guess;
}

void PrintFeedback(FBullCowCount bullsAndCows)
{
	std::cout << "Your guess contained: " << bullsAndCows.Bulls << " bulls and " << bullsAndCows.Cows << " cows."<< std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "Congratualations you won, you guessed the word in " << BCGame.GetCurrentTry() -1 << " tries. And took " << BCGame.GetGameDuration() <<" seconds. \n";
	else 
		std::cout << "You didn't guess the word, better luck next time. \n";
}

bool AskToPlayAgain()
{
	std::cout << LINE_BREAK;
	std::cout << "Play again? (y/n):";
	FText response = "";
	std::getline(std::cin, response);
	char firstChar = response[0];
	if (firstChar == 'y' || firstChar == 'Y')
		return true; 
	else if (firstChar == 'n' || firstChar == 'N')
		return false;
	else {
		std::cout << "Did not get that.\n";
		return AskToPlayAgain();
	}
}




