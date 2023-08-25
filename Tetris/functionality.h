/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */


// SAAD NADEEM                          ROLL NO 22I-1030                  PROJECT

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum, int& b, bool& space, bool bomb, int level, int shadowblock[][2]){


    if (timer>delay){ 
    	int i=0;
        while (i<4) {
        	shadowblock[i][0]=point_1[i][0];
            shadowblock[i][1]=point_1[i][1];
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
            i++;
        }
        
        
        if(space && !bomb) //hard drops pieces until anamoly is false 
       		while(anamoly())
       		{
       			for (int i=0;i<4;i++){
            		point_2[i][0]=point_1[i][0];
           			point_2[i][1]=point_1[i][1];
            		point_1[i][1]+=1;}
       		}
       		
       	space=0;
       	
        if (!anamoly()){
        	for(int i=0;i<4;i++)
        		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
        		
        	colorNum=1+rand()%7;
        	
        	int n;
        	
        	if(level==1)  //according to level blocks will be selected
             n=rand()%5;
            else if(level==2)
             n=rand()%8;
            
            b=n;  //making a copy of current index
            
                for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2; 
                }
                
                int randomplace = 1+rand()%7;   //blocks will spawn at random places
                 for (int i=0;i<4;i++){
            	point_2[i][0] = point_1[i][0] ;
            	point_2[i][1] = point_1[i][1] ;
            	point_1[i][0]+= randomplace ;                
        		}  			   
        }
        timer=0;
    }
}


//////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

/////////////////////////////////////////
//////moving blocks left ///////////////

void leftmove(int& delta_x, bool bomb)
{ 	
	if(!bomb) //bomb will not move
	{
	
	if(delta_x > 0 )
		{
		
			for (int i=0;i<4;i++){     //to stop blocks from overlapping
				if (gameGrid[point_1[i][1]][point_1[i][0]+1]!=0){
					delta_x=0;
					return;
				}
			}
		
			for (int i=0;i<4;i++){ //to check if all the pieces of the block lie within the grid 
			if(point_1[i][0] >= 9){  //to stop the block at the border of the grid on right side.
				delta_x=0;
				return;
			}	
			}
			for (int i=0;i<4;i++){
            	point_2[i][0] = point_1[i][0] ;
            	point_2[i][1] = point_1[i][1] ;
            	point_1[i][0]+=1 ;     //how much units right              
        		}
      	delta_x=0;
   
		}
	 }
	 
}

////////////////////////////////////////
//////moving blocks right /////////////

void rightmove(int &delta_x, bool bomb) 
{
	 if(!bomb)
	 {
	
	if(delta_x < 0 )
		{
		
			for (int i=0;i<4;i++){		//to stop blocks from overlapping
				if (gameGrid[point_1[i][1]][point_1[i][0]-1]!=0){
					delta_x=0;
					return;
				}
			}
		
			for (int i=0;i<4;i++){ 	  //to check if all the pieces of the block lie within the grid 
			if(point_1[i][0] <= 0){  //to stop the block at the border of the grid on left side.
				delta_x=0;
				return;
			}	
			}
			
			for (int i=0;i<4;i++){
    	        point_2[i][0] = point_1[i][0] ;
    	        point_2[i][1] = point_1[i][1] ;
    	        point_1[i][0]-=1 ;    //how much units right               
    		    }
        delta_x=0;
                    
		}
	}
}

/////////////////////////////////////////
//////to check if a line is filled//////
/////and update score//////////////////
void checkline(int& countscore)  

{	


	countscore=0;
	int p=M-1;
	int i=M-1;
		while(i>0)
		{
			int count=0;
			for(int j=0;j<N;j++)
			{
				if(gameGrid[i][j]) 
					count++;
				gameGrid[p][j]=gameGrid[i][j];
			}
			if(count<N) 
				p--;
				
			i--;
		}
	
	countscore =  (p-i);  //tells how many lines destroyed.
}

////////////////////////////////////
/////////to rotate a piece/////////
//////////////////////////////////

void rotatepiece(bool& rotate, bool bomb, int b, int& xcordinate, int& ycordinate, int xlocation, int ylocation)
{ 	
//the square piece is at index 7
//it will not rotate
	if(b==7)
	{
		rotate=0;
		return;
	}

	if(!bomb){  //bomb will not rotate

		for (int i=0;i<4;i++){ //if the block is at the end of the grid, it will not rotate
				if(point_1[i][0] >= 9 || point_1[i][0] <= 0){  
					rotate=0;
					return;
					}	
				}
	

	if(rotate){
				int r=0;
				while( r<4 )
				{
					xcordinate=point_1[r][1]-ylocation; //swaping the block according to the trnslation
					ycordinate=point_1[r][0]-xlocation;
					point_1[r][0]=xlocation-xcordinate; //swapping will rotate the block
					point_1[r][1]=ylocation+ycordinate;
				r++;
				}
			}

			 
      rotate=false;
	
	}
}


/////////////////////////////////////////
//cordinates of bomb are at index 4///// 
void isbomb(bool& bomb, int b)
{	
			if(b==4)
			bomb=true;
			else
			bomb=false;
}

/////////////////////////////////////////////////////////////
////////////BOOM BOOM///////////////////////////////////////
///////////BOMB IMPLEMENTATION/////////////////////////////

void checkbomb(bool bomb, int& colorNum)             //checks the color of bomb. if it matches
{                                                   //the whole grid gets deleted. if not, 4 blocks are destroyed
	
	bool clear=0;
	
	if(bomb)
	{
	
		for(int i=0;i<4;i++)
		{
				if(gameGrid[point_1[i][1]+1][point_1[i][0]] == colorNum)
				{
					clear=true;
				}
		}
		
			if(clear)//clears the grid
			{
				for(int i=0;i<20;i++){
					for(int j=0;j<10;j++)
						gameGrid[i][j] = 0;
				}
				
				for (int i=0;i<4;i++){
           		 	point_2[i][0]=point_1[i][0];
            		point_2[i][1]=point_1[i][1];
            		point_1[i][1]+=20;                
    				}	
    		}
    		
    		else
    		
    		{
    		for(int i=0;i<4;i++)  
				if(gameGrid[point_1[i][1]+1][point_1[i][0]] != 0 ) //if bomb lies on a different colored block
				{												  //four blocks below will be destroyed
					for(int i=0;i<4;i++)
					gameGrid[point_1[i][1]+1][point_1[i][0]] = 0;
					for(int i=0;i<4;i++)
					gameGrid[point_1[i][1]+2][point_1[i][0]] = 0;
					for(int i=0;i<4;i++)
					gameGrid[point_1[i][1]+3][point_1[i][0]] = 0;
					for(int i=0;i<4;i++)
					gameGrid[point_1[i][1]+4][point_1[i][0]] = 0;
				
				for (int i=0;i<4;i++)
					{
           		 	point_2[i][0]=point_1[i][0];
            		point_2[i][1]=point_1[i][1];
            		point_1[i][1]+=20;                
    				}	
				}
    		}				
	}
}



///////////////////////////////////////////////////////////////////
/////////////updaate score functon////////////////////////////////
/////////////////////////////////////////////////////////////////
void updatescore(int& score, int countscore)
{
	// updating score according to lines destroyed
 if(countscore==1)
 	score+=10;
 else if(countscore==2)
 	score+=30;
 else if(countscore==3)
 	score+=60;
 else if(countscore==4)
 	score+=100;
}



//////////////////////////////////////////////////////////////////////
/////////this function checks if game is over/////////////////////////
//////////////////////////////////////////////////////////////////////


void isgameover(bool& gameoover)
{
	for (int i=0;i<10;i++){     // Game Over
				if (gameGrid[1][i]!=0){ gameoover = true;}
				}
}
///////////////////////////////////////////////////////////////////////
/////////////////shadow piece/////////////////////////////////////////
void ghostfunction(int shadowblock[4][2])
{
	for(;ghostanamoly(shadowblock);)
	{
		int i=0;
		while(i<4)
		{
			shadowblock[i][1]=shadowblock[i][1]+1;
			i++;
		}
	}
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
