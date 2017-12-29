#include "Surface.h"


CSurface::CSurface(){
}

SDL_Surface* CSurface::Load_Image(char* File){
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	Surf_Temp = IMG_Load(File);
	if(Surf_Temp == NULL){
		return NULL;
	}
	Surf_Return = SDL_DisplayFormat(Surf_Temp);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

bool CSurface::Draw_Image(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y){
	if(Surf_Dest == NULL || Surf_Src == NULL){
		return false;
	}

	SDL_Rect DestR;

	DestR.x = x;
	DestR.y = y;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

	return true;
}
