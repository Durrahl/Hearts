#include "pch.h"
#include <iostream>
#include "HeartsNewFinal.h"
#include "Round.h"
#include "Hand.h"
#include <vector>
#include <thread>
#include "DeckShuffler.h"
#include <atomic>
#include "AI.h"
#include "UI.h"
Deck mainDeck;
AI aiMain;
Round roundMain;
mainClass mainClassRef;
Hand mainHand;
bool UIEnabledMain = false;
UI mainUI;
Card startingCard;
bool debugMessagesEnabled = false;
std::vector<Card> tempDeck;
std::vector<Card> cardDeck;
std::vector<Player> players;
auto *P_cardDeck = &cardDeck;
int numOfCards = 52;

bool countPlayers = false; // Used to validate if the number of players entered are correct.

int main(int argc, char * argv[])
{
	UIEnabledMain = roundMain.startUI();

  // Start of program.
	std::cout << "|--------------------|" << std::endl;
	std::cout << "  Welcome to Hearts!  " << std::endl;
	std::cout << "|--------------------|" << std::endl;

  // Create Deck
	std::atomic<bool> finished(false);
	std::thread deckGenThread([&finished] 
	{
		*P_cardDeck = mainDeck.CreateDeck(52);
		finished = true;
		
	}); // Putting Deck Generation on alternate thread.

 // Start of data Gathering.
	std::cout << "How many player are we using including you? " << std::endl;
	std::cin >> numbOfPlayers;

// Validate number of players
	while (countPlayers == false) 
			{
				if (numbOfPlayers >= 3 && numbOfPlayers < 6)
					{
						countPlayers = true;
						std::cout << "Starting Game..." << std::endl;
					}
				else 
					{
						std::cout << "That number is not within player range, please select a number between 3 and 5: " << std::endl;
						std::cin >> numbOfPlayers;
					}
	
	
			}  


 // Create Players
	Player dummyPlayer;
	players.assign(numbOfPlayers, dummyPlayer);
	for (int i = 0; i < numbOfPlayers; i++)
	{
		bool isAI = false;
		int playerType = 0;
		system("CLS"); // For readability
		std::cout << "Name of player " << (i + 1) << ": " << std::endl;
		std::cin >> players.at(i).playerName;
		std::cout << "What type of player is it? (AI = 1/ Player = 0/ Network Player = 2): " << std::endl;
		
		// To do add data type validation and 0-2 validation
		while (isAI == false)
		{
			std::cin >> playerType;
			if (playerType == 0)
			{
				players.at(i).playerType = playerType;
				DBMSG("PLAYER CHOSEN");
				isAI = true;
				
			}
			else if (playerType == 1)
			{
				players.at(i).playerType = playerType;
				DBMSG("AI CHOSEN");
				isAI = true;
			}
			else if (playerType == 2)
			{
				players.at(i).playerType = playerType;
				DBMSG("NETWORK PLAYER CHOSEN");
				isAI = true;
			}
			else
			{
				std::cout << "Please select a number 0-2!: " << std::endl;
			}
		}
		DBMSG("Exited while loop");
	}

 // Thread Sync
	if (finished != true) // Check if thread has finished execution
	{
		deckGenThread.join();
	} 
	DBMSG("Finished Thread"); // Debug

	mainClassRef.cardShuffle(players, FindCardNumber(numbOfPlayers), cardDeck);


// Show Player Cards
	for (int i = 0; i < numbOfPlayers; i++) // Disable for final! // Todo
	{
		mainHand.ShowHand(players.at(i));
	}

// Start Round
	roundMain.PassCardsPre(players,numbOfPlayers); // Passing cards
	roundMain.BeginRound(players, startingCard, FindCardNumber(numbOfPlayers),cardDeck, numbOfPlayers);
	

	system("PAUSE");
	return 0;
}

std::vector<Player> mainClass::cardShuffle(std::vector<Player> _players, int _numOfCards, std::vector<Card> _cardDeck)
{
	// Modify Deck & set global cards per person.



	// Shuffle and Deal Deck
	players = mainDeck.ShuffleAnDeal(_players, _numOfCards, _cardDeck);
	return players;
}

int FindCardNumber(int playerCount)
{
	// Card Rules
	// 3 Players 17 cards, 2 of diamonds removed.
	// 4 players 13 cards, none removed.
	// 5 players 10 cards, 2 of diamonds and 2 of clubs removed.
	// 2 of Diamonds = 14.
	// 2 of clubs = 1.
	int cardsEach = 0;
	
	switch(playerCount)
	{
		
		case 3:
			cardsEach = 17;
			cardDeck.erase(cardDeck.begin() + 14);	// Erase 2 of diamonds
			break;

		case 4:
			cardsEach = 13;
			break;

		case 5:
			cardsEach = 10;
			cardDeck.erase(cardDeck.begin() + 14);	// Erase 2 of diamonds
			cardDeck.erase(cardDeck.begin() + 1);	// Erase 2 of clubs
			break;

	}

	return cardsEach;
}



void DBMSG(std::string message)
{
	if (debugMessagesEnabled == true)
	{
		std::cout << "DEBUG: " << message << std::endl;
	}
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


