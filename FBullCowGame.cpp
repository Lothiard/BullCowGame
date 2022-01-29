#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "auto"; // auto, kocsi, duda, hajo

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity (FString Guess) const {
	if (!IsIsogram(Guess)) {// if the guess isn't an isogram, 
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) { // if the guess isn't all lowercase 
		return EGuessStatus::Not_Lowercase;	// TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same elength as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters againts the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they are in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter word isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) {   // for all letters of the word
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else { // otherwise
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) { // if not a lowercase letter
			return false;
		}
	}
	return true;
}
