#include "pch.h"
#include "UI.h"
#include <string>
#include <iostream>
#include <SDL.h>
#include <sstream>
SDL_Window *mainUIWindow;
SDL_Renderer *mainUIRenderer;
SDL_Surface * mainCreationSurface;
SDL_Event mainUI_Event;
bool UIEnabled = false;
void UI::GenerateUI()
{
	
	mainUIWindow = SDL_CreateWindow("Hearts!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1280,720, SDL_WINDOW_SHOWN);
	mainUIRenderer = SDL_CreateRenderer(mainUIWindow, -1, 0);
	mainCreationSurface = SDL_GetWindowSurface(mainUIWindow);

	SDL_SetRenderDrawColor(mainUIRenderer, 0, 255, 0, 255); // Set background colour
	SDL_RenderClear(mainUIRenderer);
	SDL_RenderPresent(mainUIRenderer);
	GenerateGUI("Resources/CardWallet.bmp",0, 423,1280,297);

	PlaceDummyCards(0);
	Menu();
	PlaceDummyCards(0);
}

void UI::Pause()
{
	bool cont = false;
	PlaceCard(56, 0);
	while (cont == false)
	{
		if (GetInputCard() == 0)
		{
			cont = true;
		}
	}
}

void UI::Menu()
{
	bool hasStarted = false;
	PlaceCard(53, 0);
	PlaceCard(54, 1);
	PlaceCard(55, 2);
	int choice = 0;
	while (hasStarted == false)
	{
		
		choice = GetInputCard();
		choice = choice + 1;
		switch (choice)
		{
			case 1: // Start game
				hasStarted = true;
				break;

			case 2: // Music
				
				break;

			case 3: // Quit
				exit(EXIT_FAILURE);
				break;

		default:
			break;
		}
		
	}
}

int UI::GetInputCard()
{
	while (true)
	{
		while (SDL_PollEvent(&mainUI_Event))
		{
			switch (mainUI_Event.type)
			{
			case SDL_MOUSEBUTTONUP:
				int mouseX = mainUI_Event.motion.x;
				int mouseY = mainUI_Event.motion.y;

				if (mouseY > 424) // Card Wallet
				{
					if (mouseY > 569) // Bottom Row
					{
						return (floor(mouseX/110));
					}
					else // Top Row
					{
						return (floor(mouseX / 110)+11);
					}
				}

				if (mouseY < 151) // Top Row
				{

				}

				break;
			}
		}
	}
}

void UI::PlaceDummyCards(int starter)
{
	for (int i = starter; i < 27; i++)
	{
		PlaceCard(0, i);
	}
}

bool UI::Enabled()
{

	return false;
}

void UI::PlaceCard(int cardNum, int slot)
{
	std::cout << "Placing Card at: " << cardNum << ", " << slot << std::endl;
	std::stringstream ss;
	int placeHeight = 574;
	int placeWidthAjust = 35;
	if (slot > 21)
	{
		placeHeight = 5;
		placeWidthAjust = 0;
		slot = slot - 22;
	}
	else if (slot > 10)
	{
		placeHeight = 428;
		slot = slot - 11;
	}
	ss << "Resources/Cards/" << cardNum << ".bmp";
	std::string nameString;

	nameString = ss.str();


	SDL_FreeSurface(mainCreationSurface);
	SDL_Texture *mainTexture;
	mainCreationSurface = SDL_LoadBMP(nameString.c_str());
	mainTexture = SDL_CreateTextureFromSurface(mainUIRenderer, mainCreationSurface);
	SDL_Rect mainRect = { (slot * 110)+placeWidthAjust,placeHeight,100,141 };
	SDL_RenderCopy(mainUIRenderer, mainTexture, NULL, &mainRect);
	SDL_RenderPresent(mainUIRenderer);
}

void UI::GenerateGUI(std::string imgName, int x, int y, int w, int h)
{
	SDL_FreeSurface(mainCreationSurface);
	SDL_Texture *mainTexture;
	mainCreationSurface = SDL_LoadBMP(imgName.c_str());
	mainTexture = SDL_CreateTextureFromSurface(mainUIRenderer, mainCreationSurface);
	SDL_Rect mainRect = {x,y,w,h};
	SDL_RenderCopy(mainUIRenderer, mainTexture, NULL, &mainRect);
	SDL_RenderPresent(mainUIRenderer);
}

UI::UI()
{
}


UI::~UI()
{
}
