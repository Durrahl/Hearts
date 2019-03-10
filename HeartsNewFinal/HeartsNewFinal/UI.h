#pragma once
#include <string>
class UI
{
public:
	void GenerateUI();
	void Pause();
	void Menu();
	int GetInputCard();
	void PlaceDummyCards(int starter);
	bool Enabled();
	void PlaceCard(int cardNum,int slot);
	void GenerateGUI(std::string imgName, int x, int y, int w, int h);
	UI();
	~UI();
};


