#include "CBeam.h"

CBeam::CBeam(){
		
		
		Body_x = 0; 
		Body_y = 0;

		aux_x = 0;
		aux_y = 0;


		win = false;
		total_zona = 0;
		score = 0;
		
		
		Surf_Body = NULL;
		
		Direction = "D";
		for(int i = 0;i<GRID_WIDTH;i++){
			for(int j = 0;j<GRID_HEIGHT;j++){
				light_zone[i][j] = 0;
				BlackList[i][j] = 0;
			}
		}
}

CBeam::~CBeam(){};

