#pragma once
#include <string>
#include <vector>
#include "Card.h"
class Player
{
public:
	std::vector<Card> offHand;
	std::string playerName = "";
	std::vector<Card> hand;
	int score = 0;
	int playerID;
	int playerType = 1;
	Player();
	~Player();
};

