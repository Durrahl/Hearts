#include "pch.h"
#include "Pile.h"
#include "UI.h"
#include <iostream>
#include <string>
Card dummy_Card;

bool UIEnabledPile = false;



void Pile::ClearPile()
{
	for (int i = 0; i < cardPile.size(); i++)
	{
		cardPile.at(i) = dummy_Card;
		UIPile.PlaceCard(0,i+21);
	}
}

bool Pile::StartUI()
{
	
	std::string trialInput;

	while (true)
	{
		std::cout << "Would you like to enable UI? (Y/N): " << std::endl;
		std::cin >> trialInput;
		if (trialInput == "n" || trialInput == "N")
		{
			return false;
		}
		else if (trialInput == "y" || trialInput == "Y")
		{
			UIEnabledPile = true;
			return true;
		}
	}
	
	
}

void Pile::TestFunction()
{
	UIPile.GenerateUI();
}

void Pile::MakePile(int size)
{
	dummy_Card.cardHolder = 903;
	dummy_Card.cardSuit = 903;
	cardPile.assign(size, dummy_Card);
}

void Pile::PlaceCard(Card placedCard,int slot)
{
	cardPile.at(slot) = placedCard;
	UIPile.PlaceCard(placedCard.cardID,slot+22);
	
}

int Pile::FindWinner()
{
	int winner = 0; // Just to keep compiler happy :)
	Card highestCard;
	highestCard = cardPile.at(0);
	int suit = cardPile.at(0).cardSuit;
	std::vector<Card> possiblePile;
	for (int i = 0; i < cardPile.size(); i++)
	{
		if (cardPile.at(i).cardSuit == suit)
		{
			possiblePile.push_back(cardPile.at(i));
		}
	}
	for (int i = 0; i < possiblePile.size(); i++)
	{
		if (possiblePile.at(i).cardMember > highestCard.cardMember)
		{
			
			highestCard = possiblePile.at(i);
		}
	}

		for (int i = 0; i < cardPile.size(); i++)
		{
			if (cardPile.at(i).cardMember == highestCard.cardMember && cardPile.at(i).cardSuit == highestCard.cardSuit)
			{
				return i;
			}
		}
	
	return winner;
}

Pile::Pile()
{
}


Pile::~Pile()
{
}
