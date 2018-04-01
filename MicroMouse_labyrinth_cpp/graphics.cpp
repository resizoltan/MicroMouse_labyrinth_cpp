#include "stdafx.h"
#include "graphics.h"
#include "position.h"
#include "map.h"
#include "enumerations.h"

#include <iostream>

using std::cerr;
using std::endl;

color graphics::createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	color col = (a << 24 | b << 16 | g << 8 | r);
	return col;
}

graphics::graphics(bool& success) {
	if (initSDL()) {
		if (initWindow()) {
			if (initRenderer()) {
				success = true;
			}
		}
	}
}

graphics::graphics() {

}

graphics::~graphics() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}

bool graphics::initGraphics() {
	bool success = false;
	if (initSDL()) {
		if (initWindow()) {
			if (initRenderer()) {
				success = true;
			}
		}
	}
	return success;
}

bool graphics::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		string error = SDL_GetError();
		cerr << "Failed to init SDL. Error: " << error << endl;
		return false;
	}
	else {
		cerr << "SDL init successful" << endl;
		return true;
	}
}

bool graphics::initWindow() {
	window = SDL_CreateWindow("MicroMouse labyrinth", 1200, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		string error = SDL_GetError();
		cerr << "Failed to create window. Error: " << error << endl;
		return false;
	}
	else {
		cerr << "Window created" << endl;
		return true;
	}
}

bool graphics::initRenderer() {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		cerr << "Failed to create renderer" << endl;
		return false;
	}
	else {
		cerr << "Renderer created" << endl;
		black = createColor(0, 0, 0, 255);
		red = createColor(255, 0, 0, 255);
		green = createColor(0, 180, 0, 255);
		return true;
	}
}

void graphics::drawMaps(map virtualMap, map realMap, position currpos) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	for (int r = 0; r <= virtualMap.rows; ++r) {
		for (int c = 1; c <= virtualMap.columns; ++c) {
			if(r==0) thickLineRGBA(renderer, ho + ts * c, vo + ts * (r + 1), ho + ts * (c + 1), vo + ts * (r + 1), wallWidth, 0, 0, 0, 255);
			else {
				tile * tmpTile = virtualMap.getTile(position(c, r));
				if (tmpTile->getWall(wwall)) thickLineRGBA(renderer, ho + ts * c, vo + ts * r, ho + ts * c, vo + ts * (r + 1), wallWidth, 0, 0, 0, 255);
				if (tmpTile->getWall(swall)) thickLineRGBA(renderer, ho + ts * c, vo + ts * (r + 1), ho + ts * (c + 1), vo + ts * (r + 1), wallWidth, 0, 0, 0, 255);
				if(c==virtualMap.columns) thickLineRGBA(renderer, ho + ts * (c + 1), vo + ts * r, ho + ts * (c + 1), vo + ts * (r + 1), wallWidth, 0, 0, 0, 255);
			}
		}
	}
	position trepos = *realMap.getTrepos();
	if(currpos == trepos)filledCircleColor(renderer, ho + (currpos.Getx() + 0.5) * ts, vo + (currpos.Gety() + 0.5) * ts, ms, green);
	else {
		filledCircleColor(renderer, ho + (currpos.Getx() + 0.5) * ts, vo + (currpos.Gety() + 0.5) * ts, ms, black);
		filledCircleColor(renderer, ho + (trepos.Getx() + 0.5) * ts, vo + (trepos.Gety() + 0.5) * ts, ms, red);
	}

	int rho = ho + (virtualMap.columns + 1) * ts + ho;
	int rvo = vo;

	for (int r = 0; r <= realMap.rows; ++r) {
		for (int c = 1; c <= realMap.columns; ++c) {
			if (r == 0) thickLineRGBA(renderer, rho + ts * c, rvo + ts * (r + 1), rho + ts * (c + 1), rvo + ts * (r + 1), wallWidth, 0, 0, 0, 255);
			else {
				tile * tmpTile = realMap.getTile(position(c, r));
				if (tmpTile->getWall(wwall)) thickLineRGBA(renderer, rho + ts * c, rvo + ts * r, rho + ts * c, rvo + ts * (r + 1), wallWidth, 0, 0, 0, 255);
				if (tmpTile->getWall(swall)) thickLineRGBA(renderer, rho + ts * c, rvo + ts * (r + 1), rho + ts * (c + 1), rvo + ts * (r + 1), wallWidth, 0, 0, 0, 255);
				if (c == realMap.columns) thickLineRGBA(renderer, rho + ts * (c + 1), rvo + ts * r, rho + ts * (c + 1), rvo + ts * (r + 1), wallWidth, 0, 0, 0, 255);
			}
		}
	}
	if (currpos == trepos)filledCircleColor(renderer, rho + (currpos.Getx() + 0.5) * ts, rvo + (currpos.Gety() + 0.5) * ts, ms, green);
	else {
		filledCircleRGBA(renderer, rho + (currpos.Getx() + 0.5) * ts, rvo + (currpos.Gety() + 0.5) * ts, ms, 0, 0, 0, 255);
		filledCircleRGBA(renderer, rho + (trepos.Getx() + 0.5) * ts, rvo + (trepos.Gety() + 0.5) * ts, ms, 255, 0, 0, 255);
	}

	SDL_RenderPresent(renderer);
}

void graphics::drawPos(map virtualMap, position currpos) {
	circleColor(renderer, ho + (currpos.Getx() + 0.5) * ts, vo + (currpos.Gety() + 0.5) * ts, ms, black);
	SDL_RenderPresent(renderer);
}