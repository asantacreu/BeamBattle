#include "SDL.h" 
#include "SDL_image.h" 
#include "SDL_ttf.h"
#include "SDL_draw.h"
#include "SDL_mixer.h"

#pragma once

//#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
//#include <windows.h>

// C RunTime Header Files
/*#include <stdlib.h>
#include <malloc.h>
#include <memory.h>*/
#include <tchar.h>

#include "CSoundBank.h"
#include "CMusicBank.h"
#include "Define.h"
#include "events.h"
#include "CBeam.h"
#include "CMenu.h"
#include "Control.h"
#include "Surface.h"
#include "CFPS.h"
//#include "aStarLibrary.h";


class CMain : public CEvent{
		
	public:
		//test FindPAth
		int onClosedList;
		//Create needed arrays
		char walkability [GRID_WIDTH][GRID_HEIGHT];
		int openList[GRID_WIDTH*GRID_HEIGHT+2]; //1 dimensional array holding ID# of open list items
		int whichList[GRID_WIDTH+1][GRID_HEIGHT+1];  //2 dimensional array used to record 
	// 		whether a cell is on the open list or on the closed list.
		int openX[GRID_WIDTH*GRID_HEIGHT+2]; //1d array stores the x location of an item on the open list
		int openY[GRID_WIDTH*GRID_HEIGHT+2]; //1d array stores the y location of an item on the open list
		int parentX[GRID_WIDTH+1][GRID_HEIGHT+1]; //2d array to store parent of each cell (x)
		int parentY[GRID_WIDTH+1][GRID_HEIGHT+1]; //2d array to store parent of each cell (y)
		int Fcost[GRID_WIDTH*GRID_HEIGHT+2];	//1d array to store F cost of a cell on the open list
		int Gcost[GRID_WIDTH+1][GRID_HEIGHT+1]; 	//2d array to store G cost for each cell.
		int Hcost[GRID_WIDTH*GRID_HEIGHT+2];	//1d array to store H cost of a cell on the open list
		int PathLength;     //stores length of the found path for critter
		int pathLocation;   //stores current position along the chosen path for critter		
		int* pathBank ;

		//music declaration
		int Collision;
		int InGame;
		int Menu;
		bool music;

		//Path reading variables
		int pathStatus;
		int xPath;
		int yPath;

	private:
		bool Running;

		SDL_Surface* Surf_Display;
		SDL_Surface* Surf_Options_Background;
		SDL_Surface* Surf_Background;
		SDL_Surface* Surf_Volume;
		SDL_Surface* Surf_Volume_Tile;
		SDL_Surface* Surf_Grid;
		SDL_Surface* Surf_End_Win;
		SDL_Surface* Surf_End_Draw;
		SDL_Surface* Surf_End_Lost;
		SDL_Surface* Surf_End_MPWin;
		SDL_Surface* Surf_End_MPLost;
		SDL_Surface* Surf_End_MPWin_Game;
		SDL_Surface* Surf_End_MPLost_Game;
		//SDL_Surface* Surf_Button_Start;
		//SDL_Surface* Surf_Button_Start_P;
		SDL_Surface* Surf_Button_PAgain;
		SDL_Surface* Surf_Button_PAgain_P;
		//SDL_Surface* Surf_Button_Options;
		//SDL_Surface* Surf_Button_Options_P;
		//SDL_Surface* Surf_Button_Quit;
		//SDL_Surface* Surf_Button_Quit_P;
		//SDL_Surface* Surf_LArrow;
		//SDL_Surface* Surf_RArrow;
		SDL_Surface* Surf_Score;
		SDL_Surface* Surf_Score_Background;
		SDL_Surface* Surf_Title;
		SDL_Surface* Surf_FPS;

		TTF_Font *font;
		TTF_Font *font2;

		int track[GRID_WIDTH][GRID_HEIGHT];
		int neutral_zone[GRID_WIDTH][GRID_HEIGHT];

		int CurrentStage;
		bool multiplayer;
		int Behaviour;
		int Player1Ship;
		int Player2Ship;

		CBeam Player;
		CBeam Enemy;
		CBeam Player1;
		CBeam Player2;

		CMenu btnStart1P;
		CMenu btnStart2P;
		CMenu btnOptions;
		CMenu btnExit;

		CMenu btnLArrowP1;
		CMenu btnRArrowP1;
		CMenu btnLArrowP2;
		CMenu btnRArrowP2;
		CMenu btnLArrowVolume;
		CMenu btnRArrowVolume;
		CMenu btnBack;

		bool check_grid;
		bool check_background;
		//int SpeedFactor;
		int dt;

		int NewTime;
		int OldTime;
		int boostTime;

		

	public:
		CMain();

		void            OnEvent(SDL_Event* Event);

		void			OnInit();

		void			OnLoop();

		void			OnRender();

		void			OnCleanUp();

		void            OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

		void            OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

		void			OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

		void			OnLButtonDown(int mX, int mY);
		
		void			OnLButtonUp(int mX, int mY);

        void			OnRButtonDown(int mX, int mY);

        void			OnRButtonUp(int mX, int mY);

		int				Execute();

		void			ChooseLocation(CBeam &Player, CBeam &Enemy);

		void			Voronoi(CBeam &Player, CBeam &Enemy);

		void			BestMove(CBeam &Player, CBeam &Enemy);

		int				Find_Path(int startX, int startY,int targetX, int targetY, int other_path);

		int				ReadPathY(int pathLocation);

		int				ReadPathX(int pathLocation);

		void			ReadPath(int currentX,int currentY, int pixelsPerFrame);

		void			Move(CBeam &Beam);

		void			Init_Players();
		void			Init_Menu();

};