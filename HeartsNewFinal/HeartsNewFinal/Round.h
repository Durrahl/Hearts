#pragma once
#include "Player.h"
#include "Card.h"
#include "UI.h"
class Round
{
public:
	std::vector<Card> PassCards(std::vector<Card> targetDeck, std::vector<Card> passedCards);
	bool startUI();
	std::vector<Player> BeginRound(std::vector<Player> players,Card startingCard, int numOfCards,std::vector<Card> cardDeck, int _numOfPlayers);

	std::vector<Player> PassCardsPre(std::vector<Player> players, int numOfPlayers);
	Round();
	~Round();
};

std::vector<Player> Circle(std::vector<Player> players);

std::vector<Player> getHighScore(std::vector<Player> playerf);

std::vector<Player> turn(std::vector<Player> players);

std::vector<Player> logWinner(int winner, std::vector<Player> players);
