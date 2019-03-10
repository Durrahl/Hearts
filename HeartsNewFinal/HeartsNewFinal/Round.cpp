#include "pch.h"
#include <vector>
#include "DeckShuffler.h"
#include "Round.h"
#include "Hand.h"
#include "Pile.h"
#include "AI.h"
#include "UI.h"
#include <iostream>
#include <fstream>
AI ai;
Card dummyCard;
Hand roundHand;
Pile pile;
mainClass mainClassRound;;
bool firstCircle;
bool finished;
bool UIEnabledRound = false;
bool heartsBroke;
Card startCard;
int roundNumOfCards = 0;
int roundNumOfPlayers = 0;
std::vector<Card> roundCardDeck;
int currentRound;
std::vector<Player> holdPlayers;
std::vector<Card> Round::PassCards(std::vector<Card> targetDeck, std::vector<Card> passedCards)
{
	for (int i = 0; i < 3; i++)
	{
		targetDeck.push_back(passedCards.at(i));
	}
	return targetDeck;
}

bool Round::startUI()
{
	UIEnabledRound = pile.StartUI();
	//std::cout << "UIENABLED: " << UIEnabledRound << std::endl;
	return UIEnabledRound;
}

std::vector<Player> Round::BeginRound(std::vector<Player> players,Card startingCard, int numOfCards, std::vector<Card> cardDeck, int _numOfPlayers)
{

	holdPlayers = players;
	firstCircle = true;
	finished = false;
	heartsBroke = false;
	startCard = startingCard;
	roundNumOfCards = numOfCards;
	roundCardDeck = cardDeck;
	Circle(players); // TODO ADD COMPAT FOR STARTING CARD.
	return holdPlayers;
}



std::vector<Player> Circle(std::vector<Player> players)
{

	//std::cout << "Started Circle" << std::endl;
	pile.MakePile(players.size());
	int CurrentPlayer = 0;
	std::ofstream saveFile;
	saveFile.open("saveFile.txt", std::ofstream::app);
	saveFile << "" << std::endl;
	saveFile << "" << std::endl;
	saveFile << "" << std::endl;
	saveFile << "" << std::endl;
	saveFile << "Game Start" << std::endl;
	while (finished == false) 
	{
		pile.UIPile.PlaceDummyCards(0);
		//std::cout << "Round start" << std::endl;
		
		for (int i = 0; i < players.size(); i++) // Check if score limit has been reached.
		{
			if (players.at(i).score >= 100)
			{
				finished = true; //End round.
			}
		}
	
		if (players.at(0).hand.size() == 0) // Check if the player is out of cards.
		{
			std::cout << "OUT OF CARDS!" << std::endl;
			players = mainClassRound.cardShuffle(players, roundNumOfCards, roundCardDeck);
		
			
		}

		if (firstCircle == true) // Find starter card.
		{
			bool findFirst = false;
			while (findFirst == false)
			{
				for (int i = 0; i < players.size(); i++)
				{
					if (roundHand.CheckIfContain(players.at(i).hand, startCard, 1))
					{
						CurrentPlayer = i;
						findFirst = true;
					}
				}
			}
			//Switch to check for first play TODO
			//turn(players);
			firstCircle = false;
		}

		players = turn(players);

		// Rotating Player Order

		Player transPlayer = players.at(0);
		players.erase(players.begin());
		players.push_back(transPlayer);
	
		// Reseting Pile
		
		pile.ClearPile();
		saveFile << "ROUND START" << std::endl;
		for (int h = 0; h < players.size(); h++)
		{
			saveFile << "PLAYER " << players.at(h).playerName << std::endl;
			saveFile << players.at(h).score << std::endl;
		}
	
	}
	system("CLS");
	std::cout << "____Final Scores____" << std::endl;
	for (int h = 0; h < players.size(); h++)
	{
		std::cout << players.at(h).playerName << " : " << players.at(h).score << std::endl;
	}
	system("PAUSE");

	getHighScore(players);

	system("PAUSE");
	exit(EXIT_FAILURE);
	return players;
}

std::vector<Player> getHighScore(std::vector<Player> playerf)
{
	std::fstream hscFileRead;
	hscFileRead.open("Resources/hscore.txt");
	std::vector<int> lines;
	lines.assign(5, 0);
	std::vector<std::string> lines2;
	lines2.assign(5, "");


	for (int i = 0; i < 5; i++)
	{
		std::string storeString = "";
		std::getline(hscFileRead, storeString);
		

		lines.at(i) = std::stoi(storeString);
			
		std::getline(hscFileRead, lines2.at(i));

	}

	// Find Lowest

	int currentReview = 0;
	int currentLowest = 0;
	int currentScore = 10000;
	int currentCompare = 1;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines.at(i) < currentScore)
		{
			currentScore = lines.at(i);
			currentLowest = i;
		}
	}

	for (int i = 0; i < playerf.size(); i++)
	{
		if (playerf.at(i).score < currentScore)
		{
			lines.at(currentLowest) = playerf.at(i).score;
			lines2.at(currentLowest) = playerf.at(i).playerName;
		}

	}

	hscFileRead.close();
	std::ofstream hscoreFile;
	hscoreFile.open("Resources/hscore.txt");
	hscoreFile << "";
	hscoreFile.close();
	hscoreFile.open("Resources/hscore.txt", std::ofstream::app);
	system("CLS");
	std::cout << "____HIGH SCORE____" << std::endl;

	for (int i = 0; i < lines.size(); i++)
	{
		std::cout << lines2.at(i) << " : " << lines.at(i) << std::endl;
		hscoreFile << lines.at(i) << std::endl;
		hscoreFile << lines2.at(i) << std::endl;
	}
	hscoreFile.close();
	return playerf;
}
std::vector<Player> turn(std::vector<Player> players)
{
	
	for (int i = 0; i < players.size(); i++)
	{
		std::vector<Card> playableCards;
		Player fakePlayer; // Used to show altered Selection.
		if ((players.at(players.size()-1).hand.size()) == 0)
		{
			return players; // end round.
		}
		if (players.at(i).playerType == 0) // Local controlled Player.
		{
			system("CLS");

			if (i > 0) // Checking if this play is first!
			{
				playableCards = roundHand.CheckIfPlayable(pile.cardPile.at(0).cardSuit, players.at(i).hand);
			}
			else // is First
			{
				playableCards = players.at(1).hand;
			}
			fakePlayer = players.at(i);
			fakePlayer.hand = roundHand.RemoveHearts(playableCards);
			std::cout << fakePlayer.hand.size() << std::endl; // Special cards not showing last here reme to start hgere
			roundHand.ShowHand(fakePlayer);

			
			

			
			for (int j = 0; j < pile.cardPile.size(); j++) // Show played cards.
			{

				if (pile.cardPile.at(j).cardSuit != 903)
				{

					std::cout << players.at(j).playerName << " | " << roundHand.CardConverter(pile.cardPile.at(j).cardSuit, 0);

					std::cout << " " << roundHand.CardConverter(pile.cardPile.at(j).cardMember, 1) << std::endl;

				}
				else
				{
					std::cout << players.at(j).playerName << " Not Played" << std::endl;
				}
			}

			std::cout << "What cards do you want to play? " << players.at(i).score << std::endl;

			if (players.at(i).hand.size() == 1)
			{
				for (int j = 0; j < players.size(); j++)
				{
					std::cout << players.at(j).playerName << " | " << players.at(j).hand.size() << std::endl;

				}
			}

			bool isUsable = false;
			Card chosenCard;
			int IntChosenCard;
			

			if (UIEnabledRound == true)
			{
				IntChosenCard = pile.UIPile.GetInputCard();
			}
			else
			{
				IntChosenCard = roundHand.getInputCard(players.at(i).hand);
			}

			
			chosenCard = playableCards.at(IntChosenCard);

			pile.PlaceCard(chosenCard,i); // Checks if input is valid.
			players.at(i).hand = roundHand.RemoveCard(players.at(i).hand,chosenCard); // Remove played card from hand.
	


		}
	
		if (players.at(i).playerType == 1) // AI controlled Player.
		{


			Card chosenCard = ai.PlayCard(pile.cardPile, players.at(i).hand); // Choose card using AI
		
			pile.PlaceCard(chosenCard, i); // Place card.
		
			players.at(i).hand = roundHand.RemoveCard(players.at(i).hand, chosenCard); // Remove played card from hand.

			std::cout << "AI PLAYED: " << roundHand.CardConverter(chosenCard.cardMember, 1) << " of " << roundHand.CardConverter(chosenCard.cardSuit, 0) << std::endl;

			
			
		}

		if (players.at(i).playerType == 2) // Network controlled Player.
		{
		// Not inplemented yet // NWPTODO
		}
	}
	
	// Call pile check
	players = logWinner(pile.FindWinner(), players);
	return players;
}

std::vector<Player> logWinner(int winner,std::vector<Player> players)
{
	int scoreAdded = 0;
	scoreAdded = roundHand.AddToOffHand(players.at(winner), pile.cardPile);
	players.at(winner).score = players.at(winner).score + scoreAdded;
	
	system("CLS");
	std::cout << "------------- " << players.at(winner).playerName << " Lost the round" << " ------------" << std::endl;
	for (int i = 0; i < pile.cardPile.size(); i++)
	{
		std::cout << "ID: " << i << " | " << players.at(i).playerName << " | " << roundHand.CardConverter(pile.cardPile.at(i).cardMember, 1) << " : " << roundHand.CardConverter(pile.cardPile.at(i).cardSuit, 0) << std::endl;
	}
	std::cout << "--------------------------" << std::endl;
	if (UIEnabledRound == true)
	{
		pile.UIPile.Pause();
	}
	else
	{
		system("PAUSE");
	}
	return players;
}


std::vector<Player> Round::PassCardsPre(std::vector<Player> players, int numOfPlayers)
{

	// Setting starting variables.
	if (UIEnabledRound == true)
	{
		pile.UIPile.GenerateUI();
	}

	std::vector<Card> dummyVector;
dummyVector.assign(numOfPlayers, dummyCard);

std::vector<std::vector<Card>> swapCards;
swapCards.assign(numOfPlayers, dummyVector);

for (int i = 0; i < numOfPlayers; i++)
{
	swapCards.at(i).assign(3, dummyCard);


	if (players.at(i).playerType == 0) // Local controlled Player.
	{
		system("CLS");
		


		for (int j = 0; j < 3; j++)
		{
			int chosenCard = 0;
			pile.UIPile.PlaceDummyCards(0);
			roundHand.ShowHand(players.at(i));
			std::cout << "What cards do you want to pass, 1 at a time please. " << std::endl;
			//TODO add text for card selection.
			if (UIEnabledRound == true)
			{
				chosenCard = pile.UIPile.GetInputCard();
			}
			else
			{
				chosenCard = roundHand.getInputCard(players.at(i).hand);
			}
			
			swapCards.at(i).at(j) = players.at(i).hand.at(chosenCard);
			players.at(i).hand = roundHand.RemoveCard(players.at(i).hand, players.at(i).hand.at(chosenCard));
		}

	}

	if (players.at(i).playerType == 1) // AI controlled Player.
	{
		swapCards.at(i) = ai.PassThree(players.at(i).hand); // TODO REMOVE AI'S CARDS
	}

	if (players.at(i).playerType == 2) // Network controlled Player.
	{
		// Not inplemented yet // NWPTODO
	}

}

for (int i = 0; i < numOfPlayers; i++)
{

	int target;
	if (i < numOfPlayers - 1) { target = i + 1; }
	else { target = 0; }

	PassCards(players.at(target).hand, swapCards.at(i)); // Send cards to next player

}
return players;
}

Round::Round()
{
}


Round::~Round()
{
}

