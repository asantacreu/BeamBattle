#include "main.h"

void CMain::OnRender(){

	switch(CurrentStage){
		case 0: {
			
			SDL_Flip(Surf_Display);
			CSurface::Draw_Image(Surf_Display, Surf_Background, 0,0);
			CSurface::Draw_Image(Surf_Display, Surf_Title, 100, 50);
			//Surf_FPS = TTF_RenderText_Solid(font2, "Press SPACE to START", textColor);
			//CSurface::Draw_Image(Surf_Display, Surf_FPS, 50, 275);
			if(CControl::Keys.ShowStart1P == true){
				CSurface::Draw_Image(Surf_Display, btnStart1P.Surf_Body_Pressed, btnStart1P.x, btnStart1P.y);
			}else{
				CSurface::Draw_Image(Surf_Display, btnStart1P.Surf_Body, btnStart1P.x, btnStart1P.y);
			}
			if(CControl::Keys.ShowStart2P == true){
				CSurface::Draw_Image(Surf_Display, btnStart2P.Surf_Body_Pressed, btnStart2P.x, btnStart2P.y);
			}else{
				CSurface::Draw_Image(Surf_Display, btnStart2P.Surf_Body, btnStart2P.x, btnStart2P.y);
			}
			if(CControl::Keys.ShowOptions == true){
				CSurface::Draw_Image(Surf_Display, btnOptions.Surf_Body_Pressed, btnOptions.x, btnOptions.y);
			}else{
				CSurface::Draw_Image(Surf_Display, btnOptions.Surf_Body, btnOptions.x, btnOptions.y);
			}
			if(CControl::Keys.ShowQuit == true){
				CSurface::Draw_Image(Surf_Display, btnExit.Surf_Body_Pressed, btnExit.x, btnExit.y);
			}else{
				CSurface::Draw_Image(Surf_Display, btnExit.Surf_Body, btnExit.x, btnExit.y);
			}
			SDL_Flip(Surf_Display);

			break;
		}
		case 1: {
			if(check_background == false){
				SDL_FillRect(Surf_Display, &Surf_Display->clip_rect, SDL_MapRGB(Surf_Display->format, 0, 0, 0));
				check_background = true;
			}
			if(check_grid == false){
				//unsigned char red = 0x000000FF;
				Uint32 white = SDL_MapRGB(Surf_Display->format, 255,255,255);
				for(int i = 0;i<GRID_WIDTH;i++){
					for(int j = 0; j<GRID_HEIGHT; j++){
						Draw_Line(Surf_Display, i*CELL_SIZE, 0, i*CELL_SIZE, GRID_HEIGHT*CELL_SIZE, white );
						Draw_Line(Surf_Display, 0, j*CELL_SIZE, GRID_WIDTH*CELL_SIZE, j*CELL_SIZE, white );
					}
				}
				check_grid = true;
			}
			CSurface::Draw_Image(Surf_Display, Surf_Score_Background, 0, 480);
			char score[150];
			SDL_Color textColor2 = {255, 255, 255 };
			sprintf_s(score, "Computer = %d          Player  = %d ",Enemy.score, Player.score);
			Surf_Score = TTF_RenderText_Solid(font2, score, textColor2);
			CSurface::Draw_Image(Surf_Display, Surf_Score, 8,480);
			CSurface::Draw_Image(Surf_Display, Player.Surf_Body, Player.Body_x*CELL_SIZE, Player.Body_y*CELL_SIZE);					
			CSurface::Draw_Image(Surf_Display, Enemy.Surf_Body, Enemy.Body_x*CELL_SIZE, Enemy.Body_y*CELL_SIZE);
			
			//Frames per second Management
			//CFPS::FPSControl.OnLoop();	
			//char name[73];
			/*sprintf(name, "FPS: %d", CFPS::FPSControl.GetFPS());
			Surf_FPS = TTF_RenderText_Solid(font, name, textColor);
			CSurface::Draw_Image(Surf_Display, Surf_FPS, 10, 10);
			*/
			
			SDL_Flip(Surf_Display);
			break;
		}
		
		case 2: {

			if(!multiplayer){
				if(Player.win){
					CSurface::Draw_Image(Surf_Display, Surf_End_Win, 0, 0);
				}else{
					CSurface::Draw_Image(Surf_Display, Surf_End_Lost, 0, 0);
				}
			}else{
				if(Player1.win && !Player2.win){
					CSurface::Draw_Image(Surf_Display, Surf_End_MPWin, 0, 0);
				}else if(!Player1.win && Player2.win){
					CSurface::Draw_Image(Surf_Display, Surf_End_MPLost, 0, 0);
				}else if(!Player1.win && !Player2.win){
					CSurface::Draw_Image(Surf_Display, Surf_End_Draw, 0, 0);
				}
			}
			SDL_Flip(Surf_Display);
			break;
		}
		case 3: {CSurface::Draw_Image(Surf_Display, Surf_Title, 100, 50);
			//Surf_FPS = TTF_RenderText_Solid(font2, "Press SPACE to START", textColor);
			//CSurface::Draw_Image(Surf_Display, Surf_FPS, 50, 275);
			SDL_FillRect(Surf_Display, NULL, SDL_MapRGB(Surf_Display->format, 0, 0, 0));
			if(CControl::Keys.ShowPAgain == true){
				CSurface::Draw_Image(Surf_Display, Surf_Button_PAgain_P, 150, 200);
			}else{
				CSurface::Draw_Image(Surf_Display, Surf_Button_PAgain, 150, 200);
			}
			/*if(CControl::Keys.ShowOptions == true){
				CSurface::Draw_Image(Surf_Display, btnOptions.Surf_Body_Pressed, btnOptions.x, btnOptions.y);
			}else{
				CSurface::Draw_Image(Surf_Display, btnOptions.Surf_Body, btnOptions.x, btnOptions.y);
			}*/
			if(CControl::Keys.ShowQuit == true){
				CSurface::Draw_Image(Surf_Display, btnExit.Surf_Body_Pressed, btnExit.x, btnExit.y);
			}else{
				CSurface::Draw_Image(Surf_Display, btnExit.Surf_Body, btnExit.x, btnExit.y);
			}
			SDL_Flip(Surf_Display);

			break;
		}
		case 4: {
			if(!multiplayer){
				if(Player.win_game == true){
					CSurface::Draw_Image(Surf_Display, Surf_End_Win, 0, 0);
				}else{
					CSurface::Draw_Image(Surf_Display, Surf_End_Lost, 0, 0);
				}
			}else{
				if(Player1.win_game == true){
					CSurface::Draw_Image(Surf_Display, Surf_End_MPWin_Game, 0, 0);
				}else{
					CSurface::Draw_Image(Surf_Display, Surf_End_MPLost_Game, 0, 0);
				}
			}
			SDL_Flip(Surf_Display);
			break;
		}
		case 5: {
			if(check_background == false){
				SDL_FillRect(Surf_Display, &Surf_Display->clip_rect, SDL_MapRGB(Surf_Display->format, 0, 0, 0));
				check_background = true;
			}
			if(check_grid == false){
				//unsigned char red = 0x000000FF;
				Uint32 white = SDL_MapRGB(Surf_Display->format, 255,255,255);
				for(int i = 0;i<GRID_WIDTH;i++){
					for(int	 j = 0; j<GRID_HEIGHT; j++){
						Draw_Line(Surf_Display, i*CELL_SIZE, 0, i*CELL_SIZE, GRID_HEIGHT*CELL_SIZE, white );
						Draw_Line(Surf_Display, 0, j*CELL_SIZE, GRID_WIDTH*CELL_SIZE, j*CELL_SIZE, white );
					}
				}
				check_grid = true;
			}
			CSurface::Draw_Image(Surf_Display, Surf_Score_Background, 0, 480);
			char score[150];
			SDL_Color textColor2 = {255, 255, 255 };
			sprintf_s(score, "Player1 = %d     Player2  = %d ",Player1.score, Player2.score);
			Surf_Score = TTF_RenderText_Solid(font2, score, textColor2);
			CSurface::Draw_Image(Surf_Display, Surf_Score, 8,480);
			CSurface::Draw_Image(Surf_Display, Player1.Surf_Body, Player1.Body_x*CELL_SIZE, Player1.Body_y*CELL_SIZE);					
			CSurface::Draw_Image(Surf_Display, Player2.Surf_Body, Player2.Body_x*CELL_SIZE, Player2.Body_y*CELL_SIZE);
			
			//Frames per second Management
			//CFPS::FPSControl.OnLoop();	
			//char name[73];
			/*sprintf(name, "FPS: %d", CFPS::FPSControl.GetFPS());
			Surf_FPS = TTF_RenderText_Solid(font, name, textColor);
			CSurface::Draw_Image(Surf_Display, Surf_FPS, 10, 10);
			*/
			
			SDL_Flip(Surf_Display);	
			break;
		}

		case 6: {
			    SDL_Flip(Surf_Display);
				CSurface::Draw_Image(Surf_Display, Surf_Options_Background, 0,0);
				SDL_Color textColor = {255, 255, 255 };
				Surf_FPS = TTF_RenderText_Solid(font2, "Player 1 Ship Color", textColor);
				CSurface::Draw_Image(Surf_Display, Surf_FPS, 10, 100);
				Surf_FPS = TTF_RenderText_Solid(font2, "Player 2 Ship Color", textColor);
				CSurface::Draw_Image(Surf_Display, Surf_FPS, 10, 140);
				Surf_FPS = TTF_RenderText_Solid(font2, "Volume", textColor);
				CSurface::Draw_Image(Surf_Display, Surf_FPS, 10, 180);
				Surf_FPS = TTF_RenderText_Solid(font2, "Player 1 Control: 'arrows'", textColor);
				CSurface::Draw_Image(Surf_Display, Surf_FPS, 10, 220);
				Surf_FPS = TTF_RenderText_Solid(font2, "Player 2 Control:  'WASD'", textColor);
				CSurface::Draw_Image(Surf_Display, Surf_FPS, 10, 260);
				Surf_FPS = TTF_RenderText_Solid(font2, "Movement Boost:     'B'", textColor);
				CSurface::Draw_Image(Surf_Display, Surf_FPS, 10, 300);
				
				if(CControl::Keys.ShowLArrowP1 == true){
					CSurface::Draw_Image(Surf_Display, btnLArrowP1.Surf_Body_Pressed, btnLArrowP1.x, btnLArrowP1.y);
				}else{
					CSurface::Draw_Image(Surf_Display, btnLArrowP1.Surf_Body, btnLArrowP1.x, btnLArrowP1.y);
				}
				CSurface::Draw_Image(Surf_Display, Player1.Surf_Body, 510, 120);
				if(CControl::Keys.ShowRArrowP1 == true){
					CSurface::Draw_Image(Surf_Display, btnRArrowP1.Surf_Body_Pressed, btnRArrowP1.x, btnRArrowP1.y);
				}else{
					CSurface::Draw_Image(Surf_Display, btnRArrowP1.Surf_Body, btnRArrowP1.x, btnRArrowP1.y);
				}
				if(CControl::Keys.ShowLArrowP2 == true){
					CSurface::Draw_Image(Surf_Display, btnLArrowP2.Surf_Body_Pressed, btnLArrowP2.x, btnLArrowP2.y);
				}else{
					CSurface::Draw_Image(Surf_Display, btnLArrowP2.Surf_Body, btnLArrowP2.x, btnLArrowP2.y);
				}
				CSurface::Draw_Image(Surf_Display, Player2.Surf_Body, 510, 160);
				if(CControl::Keys.ShowRArrowP2 == true){
					CSurface::Draw_Image(Surf_Display, btnRArrowP2.Surf_Body_Pressed, btnRArrowP2.x, btnRArrowP2.y);
				}else{
					CSurface::Draw_Image(Surf_Display, btnRArrowP2.Surf_Body, btnRArrowP2.x, btnRArrowP2.y);
				}
				if(CControl::Keys.ShowBack == true){
					CSurface::Draw_Image(Surf_Display, btnBack.Surf_Body_Pressed, btnBack.x, btnBack.y);
				}else{
					CSurface::Draw_Image(Surf_Display, btnBack.Surf_Body, btnBack.x, btnBack.y);
				}
				if(CControl::Keys.ShowLArrowVolume == true){
					CSurface::Draw_Image(Surf_Display, btnLArrowVolume.Surf_Body_Pressed, btnLArrowVolume.x, btnLArrowVolume.y);
				}else{
					CSurface::Draw_Image(Surf_Display, btnLArrowVolume.Surf_Body, btnLArrowVolume.x, btnLArrowVolume.y);
				}
				CSurface::Draw_Image(Surf_Display, Surf_Volume, 215, 197);
				if(CControl::Keys.ShowRArrowVolume == true){
					CSurface::Draw_Image(Surf_Display, btnRArrowVolume.Surf_Body_Pressed, btnRArrowVolume.x, btnRArrowVolume.y);
				}else{
					CSurface::Draw_Image(Surf_Display, btnRArrowVolume.Surf_Body, btnRArrowVolume.x, btnRArrowVolume.y);
				}
				int volumeM = CMusicBank::MusicControl.Volume/3.45; //3.86;
				for(int i = 0;i<volumeM;i++){
						CSurface::Draw_Image(Surf_Display, Surf_Volume_Tile, 220+(10*i), 202);
				}
				SDL_Flip(Surf_Display);
				break;	   
		}

	}

			

}