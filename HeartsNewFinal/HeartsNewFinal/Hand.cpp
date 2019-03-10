#include "pch.h"
#include "Hand.h"
#include <iostream>
#include "UI.h"
bool PlayerHeartsBroken = false;
UI UIHander;
bool Hand::CheckIfContain(std::vector<Card> sentHand,Card queryCard, int searchType)
{
	bool hasGot = false;
	bool searchComplete = false;
	
	if (searchType == 3 && queryCard.cardSuit == 0 && queryCard.cardMember == 1 ) // Check for special
	{
		hasGot = true;
		return hasGot;
	} 

	if (searchType == 3 && queryCard.cardSuit == 0 && queryCard.cardMember == 2) // Check for special
	{
		hasGot = true;
		return hasGot;
	}

	if (searchType == 3 && queryCard.cardSuit == 3 && queryCard.cardMember == 50) // Check for special
	{
		hasGot = true;
		return hasGot;
	}
	else
	{
		while (searchComplete == false)
		{
			for (int i = 0; i < sentHand.size(); i++)
			{
				if (sentHand.at(i).cardSuit == queryCard.cardSuit && searchType == 0) // Check for matching suit
				{
					hasGot = true;
					searchComplete = true;
				}
				else if (sentHand.at(i).cardSuit == queryCard.cardSuit && searchType == 1 && sentHand.at(i).cardMember == queryCard.cardMember) // Check for matching suit and member
				{
					hasGot = true;
					searchComplete = true;
				}

			}
			searchComplete = true;
		}
	}

	return hasGot;
}

int Hand::getInputCard(std::vector<Card> sentHand) // Check if the inputted card was valid.
{
	int trialInput = 0;
	bool accepted = false;
	while (accepted == false)
	{
		std::cin >> trialInput;
		try 
		{
			if (trialInput >= 0 && trialInput < sentHand.size())
			{
				accepted = true;
			}
		} 
		catch (const std::exception& e)
		{
			std::cout << "That input wasent quite right. Try again!" << std::endl;
			std::cin >> trialInput;
		}
	
	}
	
	return trialInput;
}

std::vector<Card> Hand::RemoveHearts(std::vector<Card> passedDeck)
{
	std::vector<Card> usableDeck;
	if (PlayerHeartsBroken == true)
	{
		return passedDeck;
	}
	else
	{
		for (int i = 0; i < passedDeck.size(); i++)
		{
			if (passedDeck.at(i).cardSuit == 2)
			{
				// Do nothing
			}
			else
			{
				usableDeck.push_back(passedDeck.at(i));
			}
		}
	}
	if (usableDeck.size() == 0)
	{
		return passedDeck;
	}
	return usableDeck;
}

std::vector<Card> Hand::RemoveCard(std::vector<Card> passedDeck, Card cardToRemove) // Find a provided card and remove it from the players hand.
{
	bool cardFound = false;
	int cardToRemoveSlot = 0;
	while (cardFound == false)
	{
		
		for (int i = 0; i < (passedDeck.size()-1); i++)
		{
		
			if (passedDeck.at(i).cardMember == cardToRemove.cardMember && passedDeck.at(i).cardSuit == cardToRemove.cardSuit)
			{
			
				cardToRemoveSlot = i; //todo pos not working
				cardFound = true;
			}
		}

		cardFound = true;
		
	}

	passedDeck.erase(passedDeck.begin() + (cardToRemoveSlot));

	return passedDeck;
}

void Hand::ShowHand(Player shownPlayer)
{

	std::cout << "-------------------- Name: " << shownPlayer.playerName << " --------------------" << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;
	for (int i = 0; i < shownPlayer.hand.size(); i++)
	{
		UIHander.PlaceCard(shownPlayer.hand.at(i).cardID,i);
		std::cout << "Position: " << i << std::endl;
		std::cout << std::endl;
		std::cout << "| Member: " << CardConverter(shownPlayer.hand.at(i).cardMember, 1);
		std::cout << " | Suit: " << CardConverter(shownPlayer.hand.at(i).cardSuit, 0) << std::endl;
		std::cout << "----------------------------------------------------------" << std::endl;
	}
	
}

int Hand::AddToOffHand(Player playerToAdd, std::vector<Card> cardsToAdd)
{
	for (int i = 0; i < cardsToAdd.size(); i++)
	{
		playerToAdd.offHand.push_back(cardsToAdd.at(i));
	}
	
	return countHearts(cardsToAdd);
}

int countHearts(std::vector<Card> pile)
{
	int heartCount = 0;
	for (int i = 0; i < pile.size(); i++)
	{
		if (pile.at(i).cardSuit == 2) // Check for hearts
		{
			heartCount = +1;
		}
		if (pile.at(i).cardSuit == 3 && pile.at(i).cardMember == 11) // Check for queen of spades.
		{
			heartCount = +13;
		}
	}
	return heartCount;
}

std::string Hand::CardConverter(int convertData, int ConvertType)
{

	std::string finalConvert;
	std::string members[13] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","King","Queen"};
	std::string suits[4] = { "Clubs","Diamonds","Hearts","Spades" };

	if (convertData < 0 || convertData > 60)
	{
		return "Not Played";
	}
	if (ConvertType == 1) // Convert Member
	{
	
		finalConvert = members[convertData];
	}
	else // Convert Suit
	{

		finalConvert = suits[convertData];

	}

	return finalConvert;
}

std::vector<Card> Hand::CheckIfPlayable(int targetSuit, std::vector<Card> usableCards)
{
	Card startCard;
	startCard.cardID = 15;
	startCard.cardMember = 1;
	startCard.cardSuit = 1;
	std::vector<Card> safeDeck;
	std::vector<Card> firstCardDeck;
	firstCardDeck.assign(1, startCard);
	safeDeck = usableCards;
	int heartsCount = 0;
	for (int i = 0; i < usableCards.size(); i++)
	{
		if (usableCards.at(i).cardSuit == 1 && usableCards.at(i).cardMember == 1) // Force Starter Cards
		{
			return firstCardDeck;
		}

		if (usableCards.at(i).cardSuit == targetSuit)
		{
			// Do nothing
		}
		else
		{
			if (usableCards.at(i).cardSuit == 2)
			{
				heartsCount = heartsCount + 1;
				
			}
			usableCards.erase(usableCards.begin() + i);
			i = i - 1;
			
		}
	}

	if (usableCards.size() == 0)
	{
		if (safeDeck.size() == heartsCount)
		{
			PlayerHeartsBroken = true;
		}
		return safeDeck;
	}

	return usableCards;
}



Hand::Hand()
{
}


Hand::~Hand()
{
}
