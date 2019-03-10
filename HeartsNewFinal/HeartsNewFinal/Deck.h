#pragma once
#include <vector>
#include "Card.h"
#include "Player.h"
class Deck
{
private:
	Card GenerateCard(int cardID);
public:
	Deck();
	~Deck();
	std::vector<Player> ShuffleAnDeal(std::vector<Player> players, int numOfCards, std::vector<Card> cardDeck);
	std::vector<Card> CreateDeck(int size);
	std::vector<Card> ShuffleDeck(std::vector<Card> cardDeck);
};


