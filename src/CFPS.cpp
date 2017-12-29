#include "CFPS.h"

CFPS CFPS::FPSControl;

CFPS::CFPS(){
             OldTime  = 0;
             LastTime = 0;

             SpeedFactor = 0;

             Frames      = 0;
             NumFrames   = 0;
}

void CFPS::OnLoop(){
     if(OldTime + 1000 < SDL_GetTicks()){
        OldTime = SDL_GetTicks();

        NumFrames = Frames;

        Frames = 0;

     }
	 int dt = (SDL_GetTicks() - LastTime);
	 if (dt>500)
		 dt=500;
     SpeedFactor = ( dt / 1000.0f) * 18.0f; //This 18.0f was once 32.0f but in Visual Studio it made the Speedfactot too fast! 

     LastTime = SDL_GetTicks();

     Frames ++;

}

int CFPS::GetFPS(){
    return NumFrames;
}

float CFPS::GetSpeedFactor(){
      return SpeedFactor;
}