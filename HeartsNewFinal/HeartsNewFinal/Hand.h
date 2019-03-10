#pragma once
#include <vector>
#include "Card.h"
#include "Player.h"


class Hand
{
public:
	bool CheckIfContain(std::vector<Card> sentHand,Card queryCard, int searchType);
	int getInputCard(std::vector<Card> sentHand);
	std::vector<Card> RemoveHearts(std::vector<Card> passedDeck);
	std::vector<Card> RemoveCard(std::vector<Card> passedDeck, Card cardToRemove);
	std::string CardConverter(int convertData, int ConvertType);
	std::vector<Card> CheckIfPlayable(int targetSuit, std::vector<Card> usableCards);
	void ShowHand(Player shownPlayer);
	int AddToOffHand(Player playerToAdd, std::vector<Card> cardsToAdd);
	Hand();
	~Hand();
};

int countHearts(std::vector<Card> pile);


