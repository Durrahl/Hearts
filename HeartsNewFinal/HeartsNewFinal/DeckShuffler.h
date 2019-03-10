#pragma once
#include "Player.h"
#include <vector>
#include "Card.h"
class mainClass
{
public:
	std::vector<Player> cardShuffle(std::vector<Player> players, int numOfCards, std::vector<Card> cardDeck);
};