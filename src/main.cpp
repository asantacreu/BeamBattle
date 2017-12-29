#include "main.h"

int CMain::Execute(){	
	int last_time = 0;
    int cur_time = 0;
    int diff_time = 0;
	Behaviour = 0;

	onClosedList = 10;
	

    int accumulator = 0;
	OnInit();
	SDL_Event Event;	
	
	while(Running){

		while(SDL_PollEvent(&Event)){
			OnEvent(&Event);
		}
		cur_time = SDL_GetTicks();
		diff_time = cur_time - last_time;

        accumulator += diff_time;

        if(accumulator > 75)
        {
            accumulator -= 75;
			int a = SDL_GetTicks();
			OnLoop();
			int b = SDL_GetTicks();
			int c = b-a;
			if(c<100){
				SDL_Delay(boostTime-c);
			}
			printf("%d\n",c);
			OnRender();
	
        }

        last_time = cur_time;
	}
		

	OnCleanUp(); 
    SDL_Quit();
    return 0;
};


int _tmain(int argc, char* argv[]) {//int argc, char* argv[]
	CMain BBmain;

	return BBmain.Execute();
}




