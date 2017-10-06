#include "stdafx.h"
#include "FBullCowGame.h"
#include  <map>
#define TMap std::map

FBullCowGame::FBullCowGame() //constructor
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "ant";
	MyStartTime = time(0);
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

void FBullCowGame::SetWordLength(int32 LengthOfWord)
{
	TMap<int32, FString> WordLengthToHiddenWords{ { 3, "ant" },{ 4, "goat" },{ 5,"chimp" },{ 6,"cougar" },{ 7,"dolphin" } };
	MyHiddenWord = WordLengthToHiddenWords[LengthOfWord];
}

int32 FBullCowGame::GetCurrentTry () const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{ 4,10 },{ 5,15},{ 6,20 },{ 7,25 } };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

FString FBullCowGame::GetGameDuration() const
{
	//gets the diffrence from now since the start of the game
	return std::to_string( time(0) - MyStartTime );
}

bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto letter : word)
	{
		letter = tolower(letter);
		if (LetterSeen[letter])
			return false; //its not a isogram
		else
			LetterSeen[letter] = true;
	}
	return true; //no duplicates, it's an isogram
}

bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto letter : word)
	{
		if (!islower(letter))
			return false;
	}

	return true;
}

bool FBullCowGame::IsGameWon() const
{	
	return bGameIsWon;
}

bool FBullCowGame::IsTryLeft() const
{
	return GetCurrentTry() <= GetMaxTries();
}


EGuessValidityStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (GetHiddenWordLength() != guess.length())
		return EGuessValidityStatus::Wrong_Length;
	if(!IsLowercase(guess))
		return EGuessValidityStatus::Not_lowercase;
	if(!IsIsogram(guess))
		return EGuessValidityStatus::Not_Isogram; 

	return EGuessValidityStatus::OK;
	
}

//analyze a valid guess or the amount of bulls & cows & increments a current tries, guess must be valid!
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrentTry++;

	FBullCowCount bullCowCount;

	int32 WordLength = GetHiddenWordLength(); //asumming it == guess.length
	for (int32 i = 0; i < WordLength; i++)
	{
		if (MyHiddenWord[i] == guess[i])
		{
			bullCowCount.Bulls++;
			continue;
		}

		//search if there's a cow match
		for (int32 j = 0; j < WordLength; j++)
		{
			if (MyHiddenWord[i] == guess[j])
			{
				bullCowCount.Cows++;
				continue;
			}
		}
	}

	if (bullCowCount.Bulls == WordLength)bGameIsWon = true;

	return bullCowCount;
}
