#include "pch.h"
#include "AI.h"
#include "Hand.h"
#include <iostream>
bool HeartsBroken = false;
Hand hand;
std::vector<Card> AI::PassThree(std::vector<Card> passedHand)
{
	Card first;
	Card second;
	Card third;
	std::vector<Card> movedCards;

	// Initial population
	first, second, third = passedHand.at(0);
	for (int i = 0; i < passedHand.size(); i++)
	{
		if (hand.CheckIfContain(passedHand,passedHand.at(i),3))
		{
			// Skip special cards such as 2/3 of clubs and queen of spades as the rules are different for these. 
		}
		else if (passedHand.at(i).cardMember > first.cardMember)
		{
			first = passedHand.at(i);
		}
		else if (passedHand.at(i).cardMember > second.cardMember)
		{
			second = passedHand.at(i);
		}
		else if (passedHand.at(i).cardMember > third.cardMember)
		{
			third = passedHand.at(i);
		}
	}

	movedCards.assign(3, first);
	movedCards.at(1) = second;
	movedCards.at(2) = third;

	return movedCards;

} // Used for initial passing of cards

Card AI::PlayCard(std::vector<Card> pile, std::vector<Card> hand)
{
	Card cardToPlay;
	//std::cout << "AI: PLAYCARD START" << std::endl;

	
		//std::cout << "AI: PLAYCARD ELSE START" << std::endl;
		std::vector<Card> passingCards = checkIfPlayable(pile.at(0).cardSuit, hand);
		//std::cout << "AI: PLAYCARD MIDDLE" << std::endl;
		//std::cout << "Passing Cards " << passingCards.size() << std::endl;
		cardToPlay = pickLargest(passingCards);
		//std::cout << "AI: PLAYCARD ELSE END" << std::endl;
	
	

	return cardToPlay;
}

Card pickLargest(std::vector<Card> selection)
{
	Card highest;
	//std::cout << "Debug entry "<< selection.size() << std::endl;
	highest = selection.at(0);
	//std::cout << "Debug entry " << selection.size() << std::endl;
	
	if (selection.size() == 1)
	{
		//std::cout << "DEBUG : AI : 1 CARD CATCH" << std::endl;
		// Catch for only one card.
		return highest;
	}
	//std::cout << "DEBUG : AI : OTHER2" << std::endl;
	for (int i = 0; i < selection.size(); i++)
	{ 
		//std::cout << "DEBUG : AI : OTHER1" << std::endl;
		if (selection.at(i).cardMember > highest.cardMember)
		{
			//std::cout << "DEBUG : AI : OTHER" << std::endl;
			//TODO HEART BREAK LOGIC.
			highest = selection.at(i);
		}
	}

	return highest;
}

std::vector<Card> checkIfPlayable(int targetSuit, std::vector<Card> hand)
{

	std::vector<Card> playableCards;
	int heartCount = 0;
	if (targetSuit == 2)
	{
		HeartsBroken = true;
	}
	for (int i = 0; i < (hand.size()); i++)
	{

		if (hand.at(i).cardSuit == targetSuit)
		{
			if (HeartsBroken == true)
			{
				playableCards.push_back(hand.at(i));
			}
			else if (hand.at(i).cardSuit != 2)
			{
				playableCards.push_back(hand.at(i));
			}
			if (hand.at(i).cardSuit == 2)
			{
				heartCount = heartCount + 1;
			}

		}
		if (playableCards.size() == 0)
		{
			if (heartCount == playableCards.size())
			{
				HeartsBroken = true;
			}
			playableCards = hand;
		}
	
	}
	return playableCards;
}

AI::AI()
{
}


AI::~AI()
{
}
