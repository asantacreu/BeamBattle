#include"main.h"

CMain::CMain(){
	Running = true;
	CurrentStage = 0;
	multiplayer=false;

	Surf_Display = NULL;
	Surf_Options_Background = NULL;
	Surf_Background = NULL;
	Surf_Grid = NULL;
	Surf_End_Win = NULL;
	Surf_End_Draw = NULL;
	Surf_End_Lost = NULL;
	Surf_End_MPWin = NULL;
	Surf_End_MPLost = NULL;
	Surf_End_MPWin_Game = NULL;
	Surf_End_MPLost_Game = NULL;
	//Surf_Button_Start = NULL;
	//Surf_Button_Start_P = NULL;
	Surf_Button_PAgain = NULL;
	Surf_Button_PAgain = NULL;
	Surf_Score = NULL;
	Surf_Score_Background = NULL;
	Surf_Title = NULL;
	Surf_FPS = NULL;
	font = NULL;
	font2 = NULL;
	Player1Ship = 0;
	Player2Ship = 1;

	check_grid = false;
	check_background = false;
	//SpeedFactor = 1;

	for(int i = 0;i<GRID_WIDTH;i++){
		for(int j = 0;j<GRID_HEIGHT;j++){
			track[i][j] = 0;
			neutral_zone[i][j] = 0;
		}
	}

	NewTime = 0;
	OldTime = 0;
	boostTime = 100;

}

void CMain::OnInit(){

	SDL_Init(SDL_INIT_EVERYTHING);
	Init_Players();

	TTF_Init();

	Surf_Display = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_HWSURFACE | SDL_DOUBLEBUF); //SDL_RESIZABLE

	SDL_WM_SetCaption("Beam Battle", NULL); // En NULL se puede substituir por los FPS pero no se como...
	SDL_Color textColor = {255, 255, 255 }; // No me gusta esto!! Lo tenemos definido tambien en main.h...
	font = TTF_OpenFont( "./fonts/NewBrilliant.ttf", 30 );
	font2 = TTF_OpenFont( "./fonts/SF Funk Master.ttf", 38 );
	Surf_Title = TTF_RenderText_Solid(font2, "BEAM BATTLE", textColor );
	//Surf_Score = TTF_RenderText_Solid(font, "SCORE = ", textColor );
	
	//Surf_Grid = CSurface::Load_Image("./gfx/grid.png");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Collision		= CSoundBank::SoundControl.OnLoad("./sounds/collision.wav");
	Menu			= CMusicBank::MusicControl.OnLoad("./sounds/menu.wav");
	InGame			= CMusicBank::MusicControl.OnLoad("./sounds/ingame.wav");
	CMusicBank::MusicControl.Volume = 115;
	CSoundBank::SoundControl.Volume = 100;

	Init_Menu();
	Surf_Options_Background = CSurface::Load_Image("./gfx/options_background.png");
	Surf_Background = CSurface::Load_Image("./gfx/background.png");
	Surf_Volume = CSurface::Load_Image("./gfx/volume.png");
	Surf_Volume_Tile = CSurface::Load_Image("./gfx/volume_tile.png");
	Surf_End_Win = CSurface::Load_Image("./gfx/win.png");
	Surf_End_Draw = CSurface::Load_Image("./gfx/draw.png");
	Surf_End_Lost = CSurface::Load_Image("./gfx/lost.png");
	Surf_End_MPWin = CSurface::Load_Image("./gfx/player1win.png");
	Surf_End_MPLost = CSurface::Load_Image("./gfx/player2win.png");
	Surf_End_MPWin_Game = CSurface::Load_Image("./gfx/player1GameWin.png");
	Surf_End_MPLost_Game = CSurface::Load_Image("./gfx/player2GameWin.png");
	Player1.Surf_Body = CSurface::Load_Image("./gfx/body0.png");
	Player2.Surf_Body = CSurface::Load_Image("./gfx/body1.png");
	Player.Surf_Body = CSurface::Load_Image("./gfx/body0.png");
	Enemy.Surf_Body = CSurface::Load_Image("./gfx/body1.png");

	Surf_Score_Background = CSurface::Load_Image("./gfx/score_background.png");

}

void CMain::Init_Players(){
	//Single player
	Player.Body_x = 30;//52;
	Player.Body_y = 30;//30;
	Player.Direction = "L";
	Player.win = false;
	Enemy.Body_x = 10;//18;
	Enemy.Body_y = 10;//30;
	Enemy.Direction = "R";
	Enemy.win = false;
	//Multiplayer
	Player1.Body_x = 52;
	Player1.Body_y = 30;
	Player1.Direction = "L";
	Player1.win = false;
	Player2.Body_x = 18;
	Player2.Body_y = 30;
	Player2.Direction = "R";
	//Player2.win = false;

	for(int i = 0;i<GRID_WIDTH;i++){
		for(int j = 0;j<GRID_HEIGHT;j++){
			track[i][j] = 0;
			neutral_zone[i][j] = 0;
		}
	}
}

void CMain::Init_Menu(){
	music = false;// NO SE!!
	btnStart1P.Surf_Body = CSurface::Load_Image("./gfx/start1P.png");
	btnStart1P.Surf_Body_Pressed = CSurface::Load_Image("./gfx/start1P_p.png");
	btnStart1P.x = 200;
	btnStart1P.y = 100;
	btnStart1P.w = btnStart1P.Surf_Body->w;
	btnStart1P.h = btnStart1P.Surf_Body->h;

	btnStart2P.Surf_Body = CSurface::Load_Image("./gfx/start2P.png");
	btnStart2P.Surf_Body_Pressed = CSurface::Load_Image("./gfx/start2P_p.png");
	btnStart2P.x = btnStart1P.x - 50;
	btnStart2P.y = btnStart1P.y + btnStart1P.Surf_Body->h;
	btnStart2P.w = btnStart2P.Surf_Body->w;
	btnStart2P.h = btnStart2P.Surf_Body->h;

	Surf_Button_PAgain = CSurface::Load_Image("./gfx/play_again.png");
	Surf_Button_PAgain_P = CSurface::Load_Image("./gfx/play_again_p.png");

	btnOptions.Surf_Body = CSurface::Load_Image("./gfx/options.png");
	btnOptions.Surf_Body_Pressed = CSurface::Load_Image("./gfx/options_p.png");
	btnOptions.x = btnStart1P.x;
	btnOptions.y = btnStart2P.y + btnStart2P.Surf_Body->h;
	btnOptions.w = btnOptions.Surf_Body->w;
	btnOptions.h = btnOptions.Surf_Body->h;

	btnExit.Surf_Body = CSurface::Load_Image("./gfx/quit.png");
	btnExit.Surf_Body_Pressed = CSurface::Load_Image("./gfx/quit_p.png");
	btnExit.x = btnOptions.x;
	btnExit.y = btnOptions.y + btnOptions.Surf_Body->h;
	btnExit.w = btnExit.Surf_Body->w;
	btnExit.h = btnExit.Surf_Body->h;

	btnLArrowP1.Surf_Body = CSurface::Load_Image("./gfx/L_arrow.png");
	btnLArrowP1.Surf_Body_Pressed = CSurface::Load_Image("./gfx/L_arrow_pressed.png");
	btnLArrowP1.x = 450;
	btnLArrowP1.y = 110;
	btnLArrowP1.w = btnLArrowP1.Surf_Body->w;
	btnLArrowP1.h = btnLArrowP1.Surf_Body->h;

	btnRArrowP1.Surf_Body = CSurface::Load_Image("./gfx/R_arrow.png");
	btnRArrowP1.Surf_Body_Pressed = CSurface::Load_Image("./gfx/R_arrow_pressed.png");
	btnRArrowP1.x = 550;
	btnRArrowP1.y = 110;
	btnRArrowP1.w = btnRArrowP1.Surf_Body->w;
	btnRArrowP1.h = btnRArrowP1.Surf_Body->h;

	btnLArrowP2.Surf_Body = CSurface::Load_Image("./gfx/L_arrow.png");
	btnLArrowP2.Surf_Body_Pressed = CSurface::Load_Image("./gfx/L_arrow_pressed.png");
	btnLArrowP2.x = 450;
	btnLArrowP2.y = 150;
	btnLArrowP2.w = btnLArrowP2.Surf_Body->w;
	btnLArrowP2.h = btnLArrowP2.Surf_Body->h;

	btnRArrowP2.Surf_Body = CSurface::Load_Image("./gfx/R_arrow.png");
	btnRArrowP2.Surf_Body_Pressed = CSurface::Load_Image("./gfx/R_arrow_pressed.png");
	btnRArrowP2.x = 550;
	btnRArrowP2.y = 150;
	btnRArrowP2.w = btnRArrowP2.Surf_Body->w;
	btnRArrowP2.h = btnRArrowP2.Surf_Body->h;

	btnLArrowVolume.Surf_Body = CSurface::Load_Image("./gfx/L_arrow.png");
	btnLArrowVolume.Surf_Body_Pressed = CSurface::Load_Image("./gfx/L_arrow_pressed.png");
	btnLArrowVolume.x = 180;
	btnLArrowVolume.y = 195;
	btnLArrowVolume.w = btnLArrowVolume.Surf_Body->w;
	btnLArrowVolume.h = btnLArrowVolume.Surf_Body->h;

	btnRArrowVolume.Surf_Body = CSurface::Load_Image("./gfx/R_arrow.png");
	btnRArrowVolume.Surf_Body_Pressed = CSurface::Load_Image("./gfx/R_arrow_pressed.png");
	btnRArrowVolume.x = 560;
	btnRArrowVolume.y = 195;
	btnRArrowVolume.w = btnRArrowVolume.Surf_Body->w;
	btnRArrowVolume.h = btnRArrowVolume.Surf_Body->h;

	
	btnLArrowVolume;
	btnRArrowVolume;

	btnBack.Surf_Body = CSurface::Load_Image("./gfx/back.png");
	btnBack.Surf_Body_Pressed = CSurface::Load_Image("./gfx/back_pressed.png");
	btnBack.x = 300;
	btnBack.y = 400;
	btnBack.w = btnBack.Surf_Body->w;
	btnBack.h = btnBack.Surf_Body->h;

}