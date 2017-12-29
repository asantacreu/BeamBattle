#include "main.h"

void CMain::OnCleanUp(){
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(Surf_Grid);
	SDL_FreeSurface(Surf_End_Win);
	SDL_FreeSurface(Surf_End_Lost);
	SDL_FreeSurface(Surf_Score);
	SDL_FreeSurface(Surf_Score_Background);
	SDL_FreeSurface(Surf_Title);
	SDL_FreeSurface(Player.Surf_Body);
	SDL_FreeSurface(Enemy.Surf_Body);


}