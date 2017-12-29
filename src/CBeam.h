
#include "sdl.h"
#include "Define.h"


class CBeam{

	public:
		
		int Body_x; 
		int Body_y;

		int aux_x;
		int aux_y;

		bool win;
		bool win_game;

		int total_zona;
		int score;

		SDL_Surface* Surf_Body;

		char *Direction;
		
		int light_zone[GRID_WIDTH][GRID_HEIGHT];
		int BlackList[GRID_WIDTH][GRID_HEIGHT];

	public:
		CBeam();
		~CBeam();
		
};