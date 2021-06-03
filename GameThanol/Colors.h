#pragma once
#include <SDL_pixels.h>
#include <map>

enum class ColorName : int
{
	//Regular
	Red,
	Green,
	Blue,
	Purple,
	Cyan,
	Yellow,

	//Special Colors
	DarkLimeGreen,
	VividOrange,
	CottonCandyPink

};

namespace Colors
{
	static std::map<const ColorName, SDL_Color> COLOR_TABLE
	{
		//Regular
		{ ColorName::Red, SDL_Color{ 255, 0, 0 } },
		{ ColorName::Green, SDL_Color{ 0, 255, 0 } },
		{ ColorName::Blue, SDL_Color{ 0, 0, 255 } },
		{ ColorName::Purple, SDL_Color{ 255, 0, 255 } },
		{ ColorName::Cyan, SDL_Color{ 0, 255, 255 } },
		{ ColorName::Yellow, SDL_Color{ 255, 255, 0 } },

		//Special Colors
		{ ColorName::DarkLimeGreen, SDL_Color{ 33, 185, 49 } },
		{ ColorName::VividOrange, SDL_Color{ 255, 94, 1 } },
		{ ColorName::CottonCandyPink, SDL_Color{ 255, 196, 218 } }
	};

}
