#include "main.h"

void CMain::OnLoop(){
	switch(CurrentStage){
		case 0: { //Main Menu
			if(!music){
				CMusicBank::MusicControl.Play(Menu);
				music = true;
			}
			if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowStart1P == true)){
				CurrentStage = 1;
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowStart2P == true)){
				CurrentStage = 5;
				multiplayer=true;
				music=false;
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowOptions == true)){
				CurrentStage = 6;
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowQuit == true)){
				Running = false;
			}
			break;
		}

		case 1: { //Gameplay single player

			Move(Player);
			if((Player.Body_x >=0 && Player.Body_x < GRID_WIDTH)&&(Player.Body_y >=0 && Player.Body_y <GRID_HEIGHT)){
				if(Player.aux_x == Player.Body_x && Player.aux_y == Player.Body_y){//In case it didn't move for some weird reason
					Player.aux_x = Player.Body_x;
					Player.aux_y = Player.Body_y;
				}else{
					for(int i = 0;i<GRID_WIDTH;i++){
						for(int j = 0;j<GRID_HEIGHT;j++){
							if(track[i][j] == 1 && Player.Body_x==i && Player.Body_y == j){
								if(CurrentStage!=2){
									CurrentStage=2;
									Enemy.score++;
									Player.win = false;
								}
							}
						}
					}
				}
				track[Player.Body_x][Player.Body_y] = 1;
			}else if(CurrentStage!=2){
				CurrentStage=2;
				Enemy.score++;
				Player.win = false;								
			}
			BestMove(Player, Enemy);
			Move(Enemy);
			if((Enemy.Body_x >=0 && Enemy.Body_x <GRID_WIDTH)&&(Enemy.Body_y >=0 && Enemy.Body_y <GRID_HEIGHT)){	
				if(Enemy.aux_x == Enemy.Body_x && Enemy.aux_y == Enemy.Body_y){//In case it didn't move for some weird reason
					Enemy.aux_x = Enemy.Body_x;
					Enemy.aux_y = Enemy.Body_y;
				}else{
					for(int i = 0;i<GRID_WIDTH;i++){
						for(int j = 0;j<GRID_HEIGHT;j++){
							if(track[i][j] == 1 && track[Enemy.Body_x][Enemy.Body_y] == 1){
								if(CurrentStage!=2){
									CurrentStage=2;
									Player.score++;
									Player.win = true;								
								}
							}
						}
					}
				}
				track[Enemy.Body_x][Enemy.Body_y] = 1;
			}else if (CurrentStage != 2){
				CurrentStage=2;
				Player.score++;
				Player.win = true;
			}
			break;
			
		}
		case 2: {//End Round
			
			if(CControl::Keys.PressMouseL == true){
				if(multiplayer){
					/*if((Player1.score ==  3) && (Player1.score > Player2.score)){
						Player1.win_game = true;
						CurrentStage  = 4;
					}else if((Player2.score ==  3) && (Player2.score > Player1.score)){
						Player1.win_game = false;
						CurrentStage  = 4;
					}else{*/

					CurrentStage = 5;
					for(int i = 0;i<GRID_WIDTH;i++){
						for(int j = 0;j<GRID_HEIGHT;j++){
							track[i][j] = 0;
							Player1.BlackList[i][j] = 0;
							Player2.BlackList[i][j] = 0;
						}
					}
					
					Init_Players();
					check_grid = false;
					check_background = false;
					boostTime = 100;

					//}
				}else{
					if((Player.score ==  3) && (Player.score > Enemy.score)){
						Player.win_game = true;
						CurrentStage  = 4;
					}else if((Enemy.score ==  3) && (Enemy.score > Player.score)){
						Player.win_game = false;
						CurrentStage  = 4;
					}else{
						CurrentStage = 1;
						for(int i = 0;i<GRID_WIDTH;i++){
							for(int j = 0;j<GRID_HEIGHT;j++){
								track[i][j] = 0;
								Player.BlackList[i][j] = 0;
								Enemy.BlackList[i][j] = 0;
							}
						}
					
						Init_Players();
						check_grid = false;
						check_background = false;
						boostTime = 100;
					}
				}
			}
			break;
		}
		case 3: {//Game Over
			if(!music){
				CMusicBank::MusicControl.Play(Menu);
				music = true;
			}
			if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowPAgain == true)){
				CurrentStage = 0;
				Init_Players();
				check_grid = false;
				check_background = false;
				boostTime = 100;
				Player.score =  0;
				Enemy.score =  0;
				Player1.score =  0;
				Player2.score =  0;
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowQuit == true)){
				Running = false;
			}
			break;
		}
		case 4: {
			if(CControl::Keys.PressMouseL == true){
				CurrentStage = 3;
				music = false;
			}
			break;
		}
		case 5: {// Multiplayer Gameplay
			if(!music){
				CMusicBank::MusicControl.Play(InGame);
				music = true;
			}
			Move(Player1);
			if((Player1.Body_x >=0 && Player1.Body_x < GRID_WIDTH)&&(Player1.Body_y >=0 && Player1.Body_y <GRID_HEIGHT)){
				if(Player1.aux_x == Player1.Body_x && Player1.aux_y == Player1.Body_y){//In case it didn't move for some weird reason
					Player1.aux_x = Player1.Body_x;
					Player1.aux_y = Player1.Body_y;
				}else{
					for(int i = 0;i<GRID_WIDTH;i++){
						for(int j = 0;j<GRID_HEIGHT;j++){
							if(track[i][j] == 1 && Player1.Body_x==i && Player1.Body_y == j){
								if(CurrentStage!=2){
									Player2.score++;
									if(Player2.score==3){
										CurrentStage=4;
										Player1.win_game = false;
										Player2.score = 0;
										return;
									}else{
										CurrentStage=2;
										Player1.win = false;
										Player2.win = true;
										return;
									}
								}
							}
						}
					}
				}
				track[Player1.Body_x][Player1.Body_y] = 1;
			}else if(CurrentStage!=2){
				Player2.score++;
				if(Player2.score==3){
					CurrentStage=4;
					Player1.win_game = false;
					Player2.score = 0;
					return;
				}else{
					CurrentStage=2;
					Player1.win = false;
					Player2.win = true;
					return;
				}								
			}
			Move(Player2);
			if((Player2.Body_x >=0 && Player2.Body_x <GRID_WIDTH)&&(Player2.Body_y >=0 && Player2.Body_y <GRID_HEIGHT)){	
				if(Player2.aux_x == Player2.Body_x && Player2.aux_y == Player2.Body_y){//In case it didn't move for some weird reason
					Player2.aux_x = Player2.Body_x;
					Player2.aux_y = Player2.Body_y;
				}else{
					for(int i = 0;i<GRID_WIDTH;i++){
						for(int j = 0;j<GRID_HEIGHT;j++){
							if(track[i][j] == 1 && track[Player2.Body_x][Player2.Body_y] == 1){
								if(track[Player1.Body_x][Player1.Body_y] == 1 && track[Player2.Body_x][Player2.Body_y] == 1 &&
									Player1.Body_x == Player2.Body_x && Player1.Body_y == Player2.Body_y){
									if(CurrentStage!=2){
										CurrentStage=2;
										Player1.win = false;
										Player2.win = false;
										return;
									}
								}else{
										if(CurrentStage!=2){
										Player1.score++;
											if(Player1.score==3){
												CurrentStage=4;
												Player1.win_game = true;
												Player1.score = 0;
												return;
											}else{
												CurrentStage=2;
												Player1.win = true;
												return;
											}								
										}
								}
							}
						}
					}
				}
				track[Player2.Body_x][Player2.Body_y] = 1;
			}else if (CurrentStage != 2){
				Player1.score++;
				if(Player1.score==3){
					CurrentStage=4;
					Player1.win_game = true;
					Player1.score = 0;
					return;
				}else{
					CurrentStage=2;
					Player1.win = true;
					return;
				}
			}
			break;	

		case 6: {
			if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowLArrowP1 == true)){	
				Player1Ship++;
				if(Player1Ship >=6) Player1Ship=0;
				char aux[150];
				sprintf_s(aux, "./gfx/body%d.png",Player1Ship);
				Player1.Surf_Body = CSurface::Load_Image(aux);
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowRArrowP1 == true)){
				Player1Ship--;
				if(Player1Ship <=0) Player1Ship=6;
				char aux[150];
				sprintf_s(aux, "./gfx/body%d.png",Player1Ship);
				Player1.Surf_Body = CSurface::Load_Image(aux);
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowLArrowP2 == true)){
				Player2Ship++;
				if(Player2Ship >=6) Player2Ship=0;
				char aux[150];
				sprintf_s(aux, "./gfx/body%d.png",Player2Ship);
				Player2.Surf_Body = CSurface::Load_Image(aux);
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowRArrowP2 == true)){
				Player2Ship--;
				if(Player2Ship <=0) Player2Ship=6;
				char aux[150];
				sprintf_s(aux, "./gfx/body%d.png",Player2Ship);
				Player2.Surf_Body = CSurface::Load_Image(aux);
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowLArrowVolume == true)){
				if(CMusicBank::MusicControl.Volume>0){
					CMusicBank::MusicControl.Volume-=5;
				}else{
					CMusicBank::MusicControl.Volume=0;
				}
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowRArrowVolume == true)){
				if(CMusicBank::MusicControl.Volume<115){
					CMusicBank::MusicControl.Volume+=5;
				}else{
					CMusicBank::MusicControl.Volume=115;
				}
			}else if((CControl::Keys.PressMouseL == true)&&(CControl::Keys.ShowBack == true)){
				CurrentStage = 0;
				music=false;
			}


			break;		
		}
		}
	}
}

void CMain::Move(CBeam &Beam){
		if(Beam.Direction == "D"){
			Beam.Body_y=Beam.Body_y+1;//SpeedFactor;	
		}else if (Beam.Direction == "U"){
			Beam.Body_y=Beam.Body_y-1;//SpeedFactor;	
		}else if (Beam.Direction == "L"){
			Beam.Body_x=Beam.Body_x-1;//SpeedFactor;	
		}else if (Beam.Direction == "R"){
			Beam.Body_x=Beam.Body_x+1;//SpeedFactor;	
		}
}

void CMain::ChooseLocation(CBeam &Player, CBeam &Enemy){
	//Down
	if(((Enemy.Body_y+1 >= GRID_HEIGHT)||(track[Enemy.Body_x][Enemy.Body_y+1] == 1)) && (Enemy.Direction == "D")){
		if((Enemy.Body_x >= GRID_WIDTH/2)&&(track[Enemy.Body_x-1][Enemy.Body_y] == 0)){
			Enemy.Direction = "L";
		}else{
			Enemy.Direction = "R";
		}
	}
	//Up
	if(((Enemy.Body_y <= 0)||(track[Enemy.Body_x][Enemy.Body_y-1] == 1)) && (Enemy.Direction == "U")){
		if((Enemy.Body_x >= GRID_WIDTH/2)&&(track[Enemy.Body_x-1][Enemy.Body_y] == 0)){
			Enemy.Direction = "L";
		}else if (track[Enemy.Body_x+1][Enemy.Body_y] == 0){
			Enemy.Direction = "R";
		}else{
			Enemy.Direction = "L";
		}
	}
	//Left
	if(((Enemy.Body_x <= 0)||(track[Enemy.Body_x-1][Enemy.Body_y] == 1)) && (Enemy.Direction == "L")){
		if((Enemy.Body_y >= GRID_HEIGHT/2)&&(track[Enemy.Body_x][Enemy.Body_y-1] == 0)){
			Enemy.Direction = "U";
		}else{
			Enemy.Direction = "D";
		}
	}
	//Right
	if(((Enemy.Body_x+1 >= GRID_WIDTH)||(track[Enemy.Body_x+1][Enemy.Body_y] == 1)) && (Enemy.Direction == "R")){
		if((Enemy.Body_y >= GRID_HEIGHT/2)&&(track[Enemy.Body_x][Enemy.Body_y-1] == 0)){
			Enemy.Direction = "U";
		}else{
			Enemy.Direction = "D";
		}
	}
}

void CMain::BestMove(CBeam &Player, CBeam &Enemy){
	int x = Enemy.Body_x;
	int y = Enemy.Body_y;
	int best =-10000;
	Enemy.total_zona = 0;
	Player.total_zona = 0;
	char* move = "L";
	switch(Behaviour){
		case 0: { // EndGame
			//Voronoi(Player, Enemy);
			//best = Enemy.total_zona-Player.total_zona;
			//if(Enemy.total_zona>=Player.total_zona){
				//ChooseLocation(Player,Enemy); // Avoid crashing
				if((track[Enemy.Body_x+1][Enemy.Body_y] == 0)&&(Enemy.Body_x+1 != GRID_WIDTH)&&(Enemy.Direction !="L")){
					Enemy.Body_x = Enemy.Body_x +1;
					Voronoi(Player, Enemy);
					best = Enemy.total_zona-Player.total_zona;
					move = "R";
					Enemy.Body_x = Enemy.Body_x - 1;
				}
				if((track[Enemy.Body_x-1][Enemy.Body_y] == 0)&&(Enemy.Body_x-1 != 0)&&(Enemy.Direction !="R")){
					Enemy.Body_x = Enemy.Body_x - 1;
					Voronoi(Player, Enemy);
					if((Enemy.total_zona-Player.total_zona) >= best){
						best = Enemy.total_zona-Player.total_zona;
						move = "L";
					}
					Enemy.Body_x = Enemy.Body_x + 1;
				}
				if((track[Enemy.Body_x][Enemy.Body_y-1] == 0)&&(Enemy.Body_y-1 != 0)&&(Enemy.Direction !="D")){
					Enemy.Body_y = Enemy.Body_y - 1;
					Voronoi(Player, Enemy);
					if((Enemy.total_zona-Player.total_zona) >= best){
						best = Enemy.total_zona-Player.total_zona;
						move = "U";
					}
					Enemy.Body_y = Enemy.Body_y + 1;
				}
				if((track[Enemy.Body_x][Enemy.Body_y+1] == 0)&&(Enemy.Body_y+1 != GRID_HEIGHT)&&(Enemy.Direction !="U")){
					Enemy.Body_y = Enemy.Body_y + 1;
					Voronoi(Player, Enemy);
					if((Enemy.total_zona-Player.total_zona) >= best){
						best = Enemy.total_zona-Player.total_zona;
						move = "D";
					}
					Enemy.Body_y = Enemy.Body_y - 1;
				}
				Enemy.Direction = move;
			/*}else{
				ChooseLocation(Player,Enemy);
			}*/
			
			break;
		}
		case 1: { //Agressive


			break;				  
		}
	}
}
void CMain::Voronoi(CBeam &Player, CBeam &Enemy){
	int a=0,b=0,c =0;
	int distance_p;
	int distance_e;
	Enemy.total_zona = 0;
	Player.total_zona = 0;
	a = SDL_GetTicks();
	for(int i = 0;i<GRID_WIDTH;i++){
		for(int j = 0;j<GRID_HEIGHT;j++){
			if(track[i][j]==0){
				distance_e = 0;
				distance_p = 0;
				
				//distance_e = abs(i-Enemy.Body_x) + abs(j-Enemy.Body_y);
				if(Enemy.BlackList[i][j]==0){
					distance_e = Find_Path(Enemy.Body_x,Enemy.Body_y,i,j,900000);
					if(distance_e ==-1){
						Enemy.BlackList[i][j]=1;
					}
				}
				//distance_p = abs(i-Player.Body_x) + abs(j-Player.Body_y);
				if(Player.BlackList[i][j]==0){
					distance_p = Find_Path(Player.Body_x,Player.Body_y,i,j, distance_e);
					if(distance_p ==-1) {
						Player.BlackList[i][j]=1;
					}
				}
				b = SDL_GetTicks();
				c = b-a;
				if(c < 10){
					//SDL_Delay(10-c);//Avoids going extra fast
				}
				if(distance_e > 0 && distance_p > 0){ 
					if(distance_e == distance_p){
						neutral_zone[i][j] = 1;
					}else if(distance_e>distance_p){
						//Player.light_zone[i][j] = 1;
						Player.total_zona++;
					}else if(distance_e<distance_p){
						//Enemy.light_zone[i][j] = 1;
						Enemy.total_zona++;
					}
				}
			}
		}
	}
}


int CMain::Find_Path(int startX, int startY,int targetX, int targetY, int other_path)
{
	int onOpenList=0, parentXval=0, parentYval=0,
	a=0, b=0, m=0, u=0, v=0, temp=0, corner=0, numberOfOpenListItems=0,
	addedGCost=0, tempGcost = 0, path = 0,
	tempx, pathX, pathY, cellPosition,
	newOpenListItemID=0;
	int temps2;
	int temps = SDL_GetTicks();

//2.Quick Path Checks: Under the some circumstances no path needs to
//	be generated ...

//	If starting location and target are in the same location...
	if (startX == targetX && startY == targetY){
		PathLength = 0;
		return PathLength;
	}
	/*if (startX == targetX && startY == targetY && pathLocation[pathfinderID] == 0)
		return nonexistent;*/

//3.Reset some variables that need to be cleared
	if (onClosedList > 100000) //reset whichList occasionally
	{
		for (int x = 0; x < GRID_WIDTH;x++) {
			for (int y = 0; y < GRID_HEIGHT;y++){
				whichList [x][y] = 0;
			}
		}
		onClosedList = 10;	
	}
	/*for (int x = 0; x < GRID_WIDTH;x++) {
			for (int y = 0; y < GRID_HEIGHT;y++){
				if(track[x][y] == 1){
					walkability [x][y] = unwalkable;
				}
			}
		}*/
	onClosedList = onClosedList+2; //changing the values of onOpenList and onClosed list is faster than redimming whichList() array
	onOpenList = onClosedList-1;
	PathLength  = notStarted;//i.e, = 0
	pathLocation  = notStarted;//i.e, = 0
	Gcost[startX][startY] = 0; //reset starting square's G value to 0

//4.Add the starting location to the open list of squares to be checked.
	numberOfOpenListItems = 1;
	openList[1] = 1;//assign it as the top (and currently only) item in the open list, which is maintained as a binary heap (explained below)
	openX[1] = startX; 
	openY[1] = startY;

//5.Do the following until a path is found or deemed nonexistent.
	while (1){

//6.If the open list is not empty, take the first cell off of the list.
//	This is the lowest F cost cell on the open list.
		if (numberOfOpenListItems != 0){

//7. Pop the first item off the open list.
		parentXval = openX[openList[1]];
		parentYval = openY[openList[1]]; //record cell coordinates of the item
		whichList[parentXval][parentYval] = onClosedList;//add the item to the closed list

//	Open List = Binary Heap: Delete this item from the open list, which
//  is maintained as a binary heap. For more information on binary heaps, see:
//	http://www.policyalmanac.org/games/binaryHeaps.htm
		numberOfOpenListItems--;//reduce number of open list items by 1	
		
//	Delete the top item in binary heap and reorder the heap, with the lowest F cost item rising to the top.
		openList[1] = openList[numberOfOpenListItems+1];//move the last item in the heap up to slot #1
		v = 1;

//	Repeat the following until the new item in slot #1 sinks to its proper spot in the heap.
		while(1){
			u = v;		
			if (2*u+1 <= numberOfOpenListItems) //if both children exist
			{
	 			//Check if the F cost of the parent is greater than each child.
				//Select the lowest of the two children.
				if (Fcost[openList[u]] >= Fcost[openList[2*u]]) 
					v = 2*u;
				if (Fcost[openList[v]] >= Fcost[openList[2*u+1]]) 
					v = 2*u+1;		
			}
			else
			{
				if (2*u <= numberOfOpenListItems) //if only child #1 exists
				{
	 			//Check if the F cost of the parent is greater than child #1	
					if (Fcost[openList[u]] >= Fcost[openList[2*u]]) 
						v = 2*u;
				}
			}

			if (u != v) //if parent's F is > one of its children, swap them
			{
				temp = openList[u];
				openList[u] = openList[v];
				openList[v] = temp;			
			}
			else{
				break; //otherwise, exit loop
			}		
		}//while (!KeyDown(27));//reorder the binary heap


//7.Check the adjacent squares. (Its "children" -- these path children
//	are similar, conceptually, to the binary heap children mentioned
//	above, but don't confuse them. They are different. Path children
//	are portrayed in Demo 1 with grey pointers pointing toward
//	their parents.) Add these adjacent child squares to the open list
//	for later consideration if appropriate (see various if statements
//	below).
		for (b = parentYval-1; b <= parentYval+1; b++){
			for (a = parentXval-1; a <= parentXval+1; a++){
				//	If not off the map (do this first to avoid array out-of-bounds errors)
				if ((a != -1) && (b != -1) && (a != GRID_WIDTH) && (b != GRID_HEIGHT)){
					//	If not already on the closed list (items on the closed list have
					//	already been considered and can now be ignored).			
					if (whichList[a][b] != onClosedList){ 
						//	If not a wall/obstacle square.
						if (track[a][b] == 0){ //walkability[a][b] != unwalkable
							//	Don't cut across corners
							corner = walkable;	
							if (a == parentXval-1){
								if (b == parentYval-1){
									if (track[parentXval-1][parentYval] == 1 || track[parentXval][parentYval-1] == 1){
										corner = unwalkable;
									}
								}else if (b == parentYval+1){
									if (track[parentXval][parentYval+1] == 1 || track[parentXval-1][parentYval] == 1){ 
										corner = unwalkable; 
									}
								}
							}else if (a == parentXval+1){
								if (b == parentYval-1){
									if (track[parentXval][parentYval-1] == 1 || track[parentXval+1][parentYval] == 1){ 
										corner = unwalkable;
									}
								}else if (b == parentYval+1){
									if (track[parentXval+1][parentYval] == 1 || track[parentXval][parentYval+1] == 1){
										corner = unwalkable; 
									}
								}
							}
							
							if (corner == 0){//(corner == walkable
								//	If not already on the open list, add it to the open list.	
								
									if (whichList[a][b] != onOpenList) {
										/*if(numberOfOpenListItems>120){
											PathLength = 0;
											return PathLength;
										}*/
										//Create a new open list item in the binary heap.
										newOpenListItemID++; //each new item has a unique ID #
										m = numberOfOpenListItems+1;
										openList[m] = newOpenListItemID;//place the new open list item (actually, its ID#) at the bottom of the heap
										openX[newOpenListItemID] = a;
										openY[newOpenListItemID] = b;//record the x and y coordinates of the new item

										//Figure out its G cost
										if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)//ALgun dia lo modificaremos porque no puede ir en diagonal
											addedGCost = 14;//cost of going to diagonal squares
										else
											addedGCost = 10;//cost of going to non-diagonal squares				
										Gcost[a][b] = Gcost[parentXval][parentYval] + addedGCost;

										//Figure out its H and F costs and parent
										Hcost[openList[m]] = 10*(abs(a - targetX) + abs(b - targetY));
										Fcost[openList[m]] = Gcost[a][b] + Hcost[openList[m]];
										parentX[a][b] = parentXval ; 
										parentY[a][b] = parentYval;	

										//Move the new open list item to the proper place in the binary heap.
										//Starting at the bottom, successively compare to parent items,
										//swapping as needed until the item finds its place in the heap
										//or bubbles all the way to the top (if it has the lowest F cost).
										while (m != 1) //While item hasn't bubbled to the top (m=1)	
										{
											//Check if child's F cost is < parent's F cost. If so, swap them.	
											if (Fcost[openList[m]] <= Fcost[openList[m/2]]){
												temp = openList[m/2];
												openList[m/2] = openList[m];
												openList[m] = temp;
												m = m/2;
											}else{
												break;
											}
										}
										numberOfOpenListItems++;//add one to the number of items in the heap

										//Change whichList to show that the new item is on the open list.
										whichList[a][b] = onOpenList;
									}

								//8.If adjacent cell is already on the open list, check to see if this 
								//	path to that cell from the starting location is a better one. 
								//	If so, change the parent of the cell and its G and F costs.	
									else //If whichList(a,b) = onOpenList
									{
										//Figure out the G cost of this possible new path
										if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
											addedGCost = 14;//cost of going to diagonal tiles	
										else	
											addedGCost = 10;//cost of going to non-diagonal tiles				
										tempGcost = Gcost[parentXval][parentYval] + addedGCost;
										
										//If this path is shorter (G cost is lower) then change
										//the parent cell, G cost and F cost. 		
										if (tempGcost < Gcost[a][b]) //if G cost is less,
										{
											parentX[a][b] = parentXval; //change the square's parent
											parentY[a][b] = parentYval;
											Gcost[a][b] = tempGcost;//change the G cost			

											//Because changing the G cost also changes the F cost, if
											//the item is on the open list we need to change the item's
											//recorded F cost and its position on the open list to make
											//sure that we maintain a properly ordered open list.
											for (int x = 1; x <= numberOfOpenListItems; x++) //look for the item in the heap
											{
												if (openX[openList[x]] == a && openY[openList[x]] == b) //item found
												{
													Fcost[openList[x]] = Gcost[a][b] + Hcost[openList[x]];//change the F cost
												
												//See if changing the F score bubbles the item up from it's current location in the heap
													m = x;
													while (m != 1) //While item hasn't bubbled to the top (m=1)	
													{
														//Check if child is < parent. If so, swap them.	
														if (Fcost[openList[m]] < Fcost[openList[m/2]])
														{
															temp = openList[m/2];
															openList[m/2] = openList[m];
															openList[m] = temp;
															m = m/2;
														}
														else
															break;
													} 
													break; //exit for x = loop
												} //If openX(openList(x)) = a
											} //For x = 1 To numberOfOpenListItems
										}//If tempGcost < Gcost(a,b)
									}//else If whichList(a,b) = onOpenList
							}//If not cutting a corner
						}//If not a wall/obstacle square.
					}//If not already on the closed list 
				}//If not off the map
			}//for (a = parentXval-1; a <= parentXval+1; a++){
		}//for (b = parentYval-1; b <= parentYval+1; b++){

	}//if (numberOfOpenListItems != 0)

//9.If open list is empty then there is no path.	
		else{
			path = nonexistent;
			PathLength = -1;
			break;
		}  
	//If target is added to open list then path has been found.
		if (whichList[targetX][targetY] == onOpenList){
			path = found; 
			break;
		}
	}//Do until path is found or deemed nonexistent, END while

//10.Save the path if it exists.
	if(path == 1){//path == found

//a.Working backwards from the target to the starting location by checking
//	each cell's parent, figure out the length of the path.
		pathX = targetX; 
		pathY = targetY;
		int a = 0,b = 0;

		while(pathX != startX || pathY != startY){
			//Look up the parent of the current cell.	
			tempx = parentX[pathX][pathY];		
			pathY = parentY[pathX][pathY];
			pathX = tempx;
			/*if(pathX != a){
				PathLength++;
				a = pathX;
			}
			if(pathY != b){
				PathLength++;
				b = pathY;
			}*/
			//Figure out the path length			
			PathLength++;
			/*if(PathLength>other_path){
				return PathLength;
			}*/
			//PathLength = path 
		};
/*int temps3 = SDL_GetTicks();
printf("\t%d\n\t%d",temps2-temps, temps3 - temps2);*/
//b.Resize the data bank to the right size in bytes
		//pathBank = (int*) realloc (pathBank,PathLength*8);

//c. Now copy the path information over to the databank. Since we are
//	working backwards from the target to the start location, we copy
//	the information to the data bank in reverse order. The result is
//	a properly ordered set of path data, from the first step to the
//	last.
		pathX = targetX ; pathY = targetY;
		cellPosition = PathLength*2;//start at the end	
		while(pathX != startX || pathY != startY){
			cellPosition = cellPosition - 2;//work backwards 2 integers
			//pathBank [cellPosition] = pathX;
			//pathBank [cellPosition+1] = pathY;

//d.Look up the parent of the current cell.	
			tempx = parentX[pathX][pathY];		
			pathY = parentY[pathX][pathY];
			pathX = tempx;

//e.If we have reached the starting square, exit the loop.	
		};

//11.Read the first path step into xPath/yPath arrays
		//ReadPath(startX,startY,1);
	}

	int bb = SDL_GetTicks();
	//printf("\n*%d\n",bb-aa);
	return PathLength;
}

//==========================================================
//READ PATH DATA: These functions read the path data and convert
//it to screen pixel coordinates.
void CMain::ReadPath(int currentX,int currentY, int pixelsPerFrame){
/*
;	Note on PixelsPerFrame: The need for this parameter probably isn't
;	that obvious, so a little explanation is in order. This
;	parameter is used to determine if the pathfinder has gotten close
;	enough to the center of a given path square to warrant looking up
;	the next step on the path.
;	 
;	This is needed because the speed of certain sprites can
;	make reaching the exact center of a path square impossible.
;	In Demo #2, the chaser has a velocity of 3 pixels per frame. Our
;	tile size is 50 pixels, so the center of a tile will be at location
;	25, 75, 125, etc. Some of these are not evenly divisible by 3, so
;	our pathfinder has to know how close is close enough to the center.
;	It calculates this by seeing if the pathfinder is less than 
;	pixelsPerFrame # of pixels from the center of the square. 

;	This could conceivably cause problems if you have a *really* fast
;	sprite and/or really small tiles, in which case you may need to
;	adjust the formula a bit. But this should almost never be a problem
;	for games with standard sized tiles and normal speeds. Our smiley
;	in Demo #4 moves at a pretty fast clip and it isn't even close
;	to being a problem.
*/

	//If a path has been found for the pathfinder	...
	if(pathStatus == 1){//path == found

		//If path finder is just starting a new path or has reached the 
		//center of the current path square (and the end of the path
		//hasn't been reached), look up the next path square.
		if (pathLocation < PathLength){
			//if just starting or if close enough to center of square
			if (pathLocation == 0 || (abs(currentX - xPath) < pixelsPerFrame && abs(currentY - yPath) < pixelsPerFrame))
					pathLocation++;
		}

		//Read the path data.		
		xPath = ReadPathX(pathLocation);
		yPath = ReadPathY(pathLocation);

		//If the center of the last path square on the path has been 
		//reached then reset.
		if (pathLocation == PathLength){
			if (abs(currentX - xPath) < pixelsPerFrame && abs(currentY - yPath) < pixelsPerFrame){ //if close enough to center of square
					pathStatus = notStarted; 
			}
		}
	}else{//If there is no path for this pathfinder, simply stay in the currentlocation.	
		xPath = currentX;
		yPath = currentY;
	}
}


//The following two functions read the raw path data from the pathBank.
//You can call these functions directly and skip the readPath function
//above if you want. Make sure you know what your current pathLocation
//is.

//-----------------------------------------------------------------------------
// Name: ReadPathX
// Desc: Reads the x coordinate of the next path step
//-----------------------------------------------------------------------------
int CMain::ReadPathX(int pathLocation)
{
	int x;
	if (pathLocation <= PathLength)
	{

	//Read coordinate from bank
	x = pathBank [pathLocation*2-2];

	//Adjust the coordinates so they align with the center
	//of the path square (optional). This assumes that you are using
	//sprites that are centered -- i.e., with the midHandle command.
	//Otherwise you will want to adjust this.
	//x = tileSize*x + .5*tileSize;
	
	}
	return x;
}	


//-----------------------------------------------------------------------------
// Name: ReadPathY
// Desc: Reads the y coordinate of the next path step
//-----------------------------------------------------------------------------
int CMain::ReadPathY(int pathLocation){
	int y;
	if (pathLocation <= PathLength)
	{

	//Read coordinate from bank
	y = pathBank [pathLocation*2-1];

	//Adjust the coordinates so they align with the center
	//of the path square (optional). This assumes that you are using
	//sprites that are centered -- i.e., with the midHandle command.
	//Otherwise you will want to adjust this.
	//y = tileSize*y + .5*tileSize;
	
	}
	return y;
};
