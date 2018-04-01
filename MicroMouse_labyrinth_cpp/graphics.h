#pragma once

#include <vector>
#include <string>

#include <SDL.h>
#undef main
#include <SDL2_gfxPrimitives.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int vo = 10;
const int ho = 10;
const int ts = 10;
const int wallWidth = 2;
const int ms = 3;

typedef Uint32 color;

using std::vector;
using std::string;

class map;
class position;


class graphics {
private:
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	color black;
	color red;
	color green;
public:
	graphics();
	graphics(bool& success);
	~graphics();

	color createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	bool initGraphics();
	bool initSDL();
	bool initWindow();
	bool initRenderer();

	void drawMaps(map virtualMap, map realMap, position currpos);
	void drawPos(map virtualMap, position currpos);
};
