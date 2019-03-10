#pragma once
#include <vector>
#include "Card.h"
#include "UI.h"
class Pile
{
public:
	std::vector<Card> cardPile;
	UI UIPile;
	void ClearPile();
	bool StartUI();
	void TestFunction();
	void MakePile(int size);
	void PlaceCard(Card placedCard, int slot);
	int FindWinner();
	Pile();
	~Pile();
};

