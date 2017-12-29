
#include "sdl.h"
#include "Define.h"


class CMenu{

	public:
		char id;
		int x; 
		int y;

		int h;
		int w;

		SDL_Surface* Surf_Body;	
		SDL_Surface* Surf_Body_Pressed;	

	public:
		CMenu();
		~CMenu();
		
};