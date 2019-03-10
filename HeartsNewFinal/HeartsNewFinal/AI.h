#pragma once
#include <vector>
#include "Card.h"
#include "Player.h"
class AI
{
public:
	std::vector<Card> PassThree(std::vector<Card> passedHand);
	Card PlayCard(std::vector<Card> pile, std::vector<Card> hand);
	AI();
	~AI();
};

Card pickLargest(std::vector<Card> selection);

std::vector<Card> checkIfPlayable(int targetSuit, std::vector<Card> hand);
