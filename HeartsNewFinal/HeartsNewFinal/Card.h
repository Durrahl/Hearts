#pragma once
class Card
{

public:
	int cardSuit;
	int cardMember;
	int cardHolder;
	bool cardTurned = false;
	int cardID;
	Card();
	~Card();
};

