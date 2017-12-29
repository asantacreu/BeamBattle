#include "main.h"


void CMain::OnEvent(SDL_Event* Event){
	CEvent::OnEvent(Event);
	if(Event->type == SDL_QUIT) {
        Running = false;
    }
}

void CMain::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
	switch(sym) {
		case SDLK_LEFT: {
			CControl::Keys.PressLeft = true;
			if(multiplayer){
				if(Player1.Direction != "R")Player1.Direction = "L";
			}else{
				if(Player.Direction != "R")Player.Direction = "L";
			}
            break;
        }
		case SDLK_RIGHT: {
			CControl::Keys.PressRight = true;
			if(multiplayer){
				if(Player1.Direction != "L")Player1.Direction = "R";
			}else{
				if(Player.Direction != "L")Player.Direction = "R";
			}
            break;
        }
		case SDLK_UP: {
			CControl::Keys.PressUp = true;
			if(multiplayer){
				if(Player1.Direction != "D")Player1.Direction = "U";
			}else{
				if(Player.Direction != "D")Player.Direction = "U";
			}
            break;
        }
		case SDLK_DOWN: {
			CControl::Keys.PressDown = true;
			if(multiplayer){
				if(Player1.Direction != "U")Player1.Direction = "D";
			}else{
				if(Player.Direction != "U")Player.Direction = "D";
			}
            break;
        }
		case SDLK_a: {
			CControl::Keys.PressA = true;
			if(Player2.Direction != "R")Player2.Direction = "L";
            break;
        }
		case SDLK_d: {
			CControl::Keys.PressD= true;
			if(Player2.Direction != "L")Player2.Direction = "R";
			
            break;
        }
		case SDLK_w: {
			CControl::Keys.PressW = true;
			if(Player2.Direction != "D")Player2.Direction = "U";
            break;
        }
		case SDLK_s: {
			CControl::Keys.PressS = true;
			if(Player2.Direction != "U")Player2.Direction = "D";
            break;
        }
		case SDLK_b: {
			CControl::Keys.PressB = true;
			boostTime = 50;
            break;
        }
		case SDLK_SPACE: {
			CControl::Keys.PressSpace = true;
			break;
		}
	}
}

void CMain::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){
	switch(sym) {
		case SDLK_LEFT: {
			CControl::Keys.PressLeft = false;
            break;
        }
		case SDLK_RIGHT: {
			CControl::Keys.PressRight = false;
            break;
        }
		case SDLK_UP: {
			CControl::Keys.PressUp = false;
            break;
        }
		case SDLK_DOWN: {
			CControl::Keys.PressDown = false;
            break;
        }
		case SDLK_a: {
			CControl::Keys.PressA = false;
            break;
        }
		case SDLK_d: {
			CControl::Keys.PressD= false;
			
            break;
        }
		case SDLK_w: {
			CControl::Keys.PressW = false;
            break;
        }
		case SDLK_s: {
			CControl::Keys.PressS = false;
            break;
        }
		case SDLK_b: {
			CControl::Keys.PressB = false;
            break;
        }
		case SDLK_ESCAPE: {
			//Running = false;
            break;
        }
		case SDLK_SPACE: {
			CControl::Keys.PressSpace = false;
			break;
		}
	}
}

void CMain::OnLButtonDown(int mX, int mY){
		CControl::Keys.PressMouseL = true;
};

void CMain::OnLButtonUp(int mX, int mY){
	CControl::Keys.PressMouseL = false;
};

void CMain::OnRButtonDown(int mX, int mY){
	CControl::Keys.PressMouseR = true;
};

void CMain::OnRButtonUp(int mX, int mY){
	CControl::Keys.PressMouseR = false;
};

void CMain::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle){
	if(CurrentStage == 0){
		if((mX>=btnStart1P.x) && (mX <=(btnStart1P.x+btnStart1P.w))&&(mY>=btnStart1P.y)&&(mY<=(btnStart1P.y+btnStart1P.h))){
			CControl::Keys.ShowStart1P = true;
		}else{
			CControl::Keys.ShowStart1P = false;
		}
		if((mX>=btnStart2P.x) && (mX <=(btnStart2P.x+btnStart2P.w))&&(mY>=btnStart2P.y)&&(mY<=(btnStart2P.y+btnStart2P.h))){
			CControl::Keys.ShowStart2P = true;
		}else{
			CControl::Keys.ShowStart2P = false;
		}
		if((mX>=btnOptions.x) && (mX <=(btnOptions.x+btnOptions.w))&&(mY>=btnOptions.y)&&(mY<=(btnOptions.y+btnOptions.h))){
			CControl::Keys.ShowOptions= true;
		}else{
			CControl::Keys.ShowOptions = false;
		}
		if((mX>=btnExit.x) && (mX <=(btnExit.x+btnExit.w))&&(mY>=btnExit.y)&&(mY<=(btnExit.y+btnExit.h))){
			CControl::Keys.ShowQuit = true;
		}else{
			CControl::Keys.ShowQuit = false;
		}
	}else if (CurrentStage == 3){
		if((mX>=150) && (mX <=(150+300))&&(mY>=200)&&(mY<(200+89))){
			CControl::Keys.ShowPAgain = true;
		}else{
			CControl::Keys.ShowPAgain = false;
		}
		if((mX>=200) && (mX <=(200+200))&&(mY>=289)&&(mY<(289+75))){
			CControl::Keys.ShowOptions = true;
		}else{
			CControl::Keys.ShowOptions = false;
		}
		if((mX>=200) && (mX <=(200+200))&&(mY>=364)&&(mY<=(364+122))){
			CControl::Keys.ShowQuit = true;
		}else{
			CControl::Keys.ShowQuit = false;
		}
		
	}else if(CurrentStage == 6){
		if((mX>=btnLArrowP1.x) && (mX <=(btnLArrowP1.x+btnLArrowP1.w))&&(mY>=btnLArrowP1.y)&&(mY<=(btnLArrowP1.y+btnLArrowP1.h))){
			CControl::Keys.ShowLArrowP1 = true;
		}else{
			CControl::Keys.ShowLArrowP1 = false;
		}
		if((mX>=btnRArrowP1.x) && (mX <=(btnRArrowP1.x+btnRArrowP1.w))&&(mY>=btnRArrowP1.y)&&(mY<=(btnRArrowP1.y+btnRArrowP1.h))){
			CControl::Keys.ShowRArrowP1 = true;
		}else{
			CControl::Keys.ShowRArrowP1 = false;
		}
		if((mX>=btnLArrowP2.x) && (mX <=(btnLArrowP2.x+btnLArrowP2.w))&&(mY>=btnLArrowP2.y)&&(mY<=(btnLArrowP2.y+btnLArrowP2.h))){
			CControl::Keys.ShowLArrowP2 = true;
		}else{
			CControl::Keys.ShowLArrowP2 = false;
		}
		if((mX>=btnRArrowP2.x) && (mX <=(btnRArrowP2.x+btnRArrowP2.w))&&(mY>=btnRArrowP2.y)&&(mY<=(btnRArrowP2.y+btnRArrowP2.h))){
			CControl::Keys.ShowRArrowP2 = true;
		}else{
			CControl::Keys.ShowRArrowP2 = false;
		}
		if((mX>=btnLArrowVolume.x) && (mX <=(btnLArrowVolume.x+btnLArrowVolume.w))&&(mY>=btnLArrowVolume.y)&&(mY<=(btnLArrowVolume.y+btnLArrowVolume.h))){
			CControl::Keys.ShowLArrowVolume = true;
		}else{
			CControl::Keys.ShowLArrowVolume = false;
		}
		if((mX>=btnRArrowVolume.x) && (mX <=(btnRArrowVolume.x+btnRArrowVolume.w))&&(mY>=btnRArrowVolume.y)&&(mY<=(btnRArrowVolume.y+btnRArrowVolume.h))){
			CControl::Keys.ShowRArrowVolume = true;
		}else{
			CControl::Keys.ShowRArrowVolume = false;
		}
		if((mX>=btnBack.x) && (mX <=(btnBack.x+btnBack.w))&&(mY>=btnBack.y)&&(mY<=(btnBack.y+btnBack.h))){
			CControl::Keys.ShowBack = true;
		}else{
			CControl::Keys.ShowBack = false;
		}
		
	}

};