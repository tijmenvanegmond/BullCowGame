#pragma once
#include <string>
#include <ctime>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessValidityStatus {
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_lowercase
};


class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetCurrentTry () const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	FString GetGameDuration() const;
	bool IsGameWon() const;
	bool IsTryLeft() const;
	EGuessValidityStatus CheckGuessValidity(FString)const;
	FBullCowCount SubmitValidGuess(FString);
	void Reset();
	void SetWordLength(int32);
private:
	time_t MyStartTime;
	FString MyHiddenWord;
	int32 MyMaxTries;
	int32 MyCurrentTry;
	bool bGameIsWon;	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};