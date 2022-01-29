/*	This is the console executable, that makes use of the BullCow class
* This acts as the view in a MVC pattern, and is responsibe for all user interaction.
* For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = FString;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instentiate a new game, which we re-use across plays

// entry point for our application
int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; // exit the application
}

void PrintIntro() {
	std::cout << "Koszontelek a Bikak es Bocik cimu jatekban!\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ 				"<< std::endl;
	std::cout << "          (o o)        (o o) 			    "<< std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\    "<< std::endl;
	std::cout << "  / | BIKA |O            O| BOCI | \\     "<< std::endl;
	std::cout << " *  |-,--- |              |------|  *     "<< std::endl;
	std::cout << "    ^      ^              ^      ^ 		"<< std::endl;
	std::cout << "                                                 +&-" << std::endl;
	std::cout << "                                               _.-^-._    .--."  << std::endl;
	std::cout << "                                            .-'   _   '-. |__|"  << std::endl;
	std::cout << "           __n__n__                        /     |_|     \\|  |" << std::endl;
	std::cout << "    .------`-\\00/-'                       /               \\  |"<< std::endl;
	std::cout << "   /  ##  ## (oo)                        /|     _____     |\\ |" << std::endl;
	std::cout << "  / \\## __   ./                           |    |==|==|    |  |" << std::endl;
	std::cout << "     |//YY \\|/        |---|---|---|---|---|    |--|--|    |  |" << std::endl;
	std::cout << "     |||   |||   \\|/  |---|---|---|---|---|    |==|==|    |  |" << std::endl;
	std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"  << std::endl;
	std::cout << "Ki tudod talalni a(z) " << BCGame.GetHiddenWordLength();
	std::cout << " betus szot amire gondoltam?\n";
	std::cout << std::endl;

	return; 
}

// plays a single game to completion
void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bikak = " << BullCowCount.Bulls;
		std::cout << ". Bocik = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << CurrentTry << ". probalkozas a " << BCGame.GetMaxTries() << "-bol.";
		std::cout << " Ird be a tipped : ";
		getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Kerlek egy olyan szot irj amiben nem ismetlodnek a betuk.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Kerlek kisbetukkel irj.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Kerlek irj egy " << BCGame.GetHiddenWordLength() << " betus szot.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "szeretnel jatszani meg egyszer ugyanezzel a rejtett szoval (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "SZEP MUNKA - NYERTEL!\n";
	}
	else {
		std::cout << "Legkozelebb sikerulni fog!\n";
	}
}
