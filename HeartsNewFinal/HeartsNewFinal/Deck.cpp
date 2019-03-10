#include "pch.h"
#include "Deck.h"
#include "Player.h"
#include <iostream>
std::string suits[4] = {"Clubs","Diamonds","Hearts","Spades"};

std::vector<Card> mainDeck;
Deck::Deck()
{
}


Deck::~Deck()
{
}

std::vector<Player> Deck::ShuffleAnDeal(std::vector<Player> players, int numOfCards, std::vector<Card> cardDeck) // Deal cards to players
{
	// Initilisation
	std::cout << "ShuffleAnDeal: Entry" << std::endl;
	cardDeck = ShuffleDeck(cardDeck);
	int numOfPlayers = players.size();

	Card dummyCard;
	std::cout << "ShuffleAnDeal: Loop start" << std::endl;
	for (int i = 0; i < numOfPlayers; i++)
	{
	
		players.at(i).hand.assign(numOfCards, dummyCard);
		std::cout << "ShuffleAnDeal: Sub-Loop Start" << std::endl;
		for (int j = 0; j < numOfCards; j++)
		{
			std::cout << "ShuffleAnDeal: Sub-Loop LINE 1" << std::endl;
			players.at(i).hand.at(j) = cardDeck.at((i*numOfCards) + j);
			std::cout << "ShuffleAnDeal: Sub-Loop LINE 2" << std::endl;
			players.at(i).hand.at(j).cardHolder = i;
			
		}
		std::cout << "ShuffleAnDeal: Sub-Loop End" << std::endl;
	}
	std::cout << "ShuffleAnDeal: Loop End" << std::endl;
	return players;
}

std::vector<Card> Deck::CreateDeck(int size)
{
	// Create Deck
	Card demoCard;
	mainDeck.assign(size, demoCard);

	// Assign Deck
	for (int i = 0; i < 52; i++)
	{
		mainDeck.at(i) = GenerateCard(i);
		mainDeck.at(i).cardID = i+1;
	}
	return mainDeck;
}

Card Deck::GenerateCard(int cardID)
{
	Card tempCard;
	int suit;
	if (cardID < 13)        // Clubs
	{
		suit = 0;
	}
	else if (cardID < 26)   // Diamonds
	{
		suit = 1;
	}
	else if (cardID < 39)  // Hearts
	{
		suit = 2;
	}
	else                  // Spades
	{
		suit = 3;
	}
	tempCard.cardMember = (cardID -(suit*13));
	tempCard.cardSuit = suit;

	return tempCard;
}

std::vector<Card> Deck::ShuffleDeck(std::vector<Card> cardDeck)
{
	Card rndCard1;
	Card rndCard2;
	int rnd1;
	int rnd2;
	for (int i = 0; i < cardDeck.size(); i++)
	{
		// Generate random numbers
		rnd1 = std::rand() % (cardDeck.size() - 0);
		rnd2 = std::rand() % (cardDeck.size() - 0);

		// Find cards at positions
		rndCard1 = cardDeck.at(rnd1);
		rndCard2 = cardDeck.at(rnd2);

		// Shuffle
		cardDeck.at(rnd1) = rndCard2;
		cardDeck.at(rnd2) = rndCard1;
	}
	return cardDeck;
}
