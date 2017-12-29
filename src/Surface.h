#include "sdl.h"
#include "sdl_image.h"


class CSurface{

	public:
		CSurface();

		static SDL_Surface*	Load_Image(char* File);

		static bool			Draw_Image(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y);

};