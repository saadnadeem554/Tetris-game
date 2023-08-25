/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
 
 // SAAD NADEEM                          ROLL NO 22I-1030                  PROJECT
 
#include <sstream>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;

int main(){

//the do while loop helps to restart the game.
bool restart=1;
do{
                    for(int i=0;i<20;i++)  //clears the grid at the start of the game
					for(int j=0;j<10;j++)
						gameGrid[i][j] = 0;
						
						
						for (int i=0;i<4;i++){  // clears the one block on the grid
           		 	point_2[i][0]=point_1[i][0]; //also helps when user restarts the game
            		point_2[i][1]=point_1[i][1];
            		point_1[i][1]+=30;                
    				}
						
/////////////////////////////////////////////////////
////file handling///////////////////////////////////
    int highscores[10];
     std::ifstream file;
     file.open("highscore.txt");
     
     	int num=0;
		while(num<10)
		{
			file >> highscores[num];
			num++;
		}
	file.close();
	
////////////////////////////////////////////////////////////////
////////OBJECTS////////////////////////////////////////////////
    srand(time(0));
    RenderWindow window(VideoMode(500, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9, obj10;
    Font font;
    font.loadFromFile("OpenSans-Regular.ttf");
    
   	Music music;
    music.openFromFile("mainmusic.ogg");
    music.play();
    
    Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setString("SCORE:");
    text.setPosition(350.f,100.f);
    
    Text Score;
    std::stringstream ss;
    int score=0;
    ss<<score;
    Score.setFont(font);
    Score.setString(ss.str());
    Score.setCharacterSize(20);
    Score.setPosition(350.f,150.f);
    
    
    Text hscore1;
    Text hscore2;
    Text hscore3;
    
    std::ostringstream hiscore1, hiscore2, hiscore3;
    
    hiscore1<<"1. "<<highscores[0];
    hiscore2<<"2. "<<highscores[1];
    hiscore3<<"3. "<<highscores[2];
    
    hscore1.setString(hiscore1.str());
    hscore1.setFont(font);
    hscore1.setCharacterSize(20);
    hscore1.setPosition(20.f, 30.f);
    hscore2.setString(hiscore2.str());
	hscore2.setFont(font);
    hscore2.setCharacterSize(20);
    hscore2.setPosition(20.f, 50.f);
    hscore3.setString(hiscore3.str());
	hscore3.setFont(font);
    hscore3.setCharacterSize(20);
    hscore3.setPosition(20.f, 70.f);
    

 	obj1.loadFromFile("img/tiles.png");
 	obj2.loadFromFile("img/background.png");
 	obj3.loadFromFile("img/frame.png");
 	obj4.loadFromFile("img/Pause.png");
 	obj5.loadFromFile("img/instructions.png");
 	obj6.loadFromFile("img/gameover.png");
 	obj7.loadFromFile("img/menu.png");
 	obj8.loadFromFile("img/black.png");
 	obj9.loadFromFile("img/Level.png");
 	obj10.loadFromFile("img/tiles.png");
 	////////////////////////////////////////////////////////////////////////////////////////////////////////
 	
    Sprite sprite(obj1), instructions(obj5), background(obj2), frame(obj3), gameover(obj6), Pause(obj4), menu(obj7), black(obj8), Level(obj9), ghost(obj10);


    int level=1;
    int delta_x=0, colorNum=5, b, countscore;
    float timer=0, delay=0.3;
    bool rotate=0, pause=0, drop=0, bomb=0, space=0; restart=0; bool gameoover=0; bool instruct=1;
    int xcordinate;
	int ycordinate;
    
    Clock clock;
    
    bool play=1;
    
    while(play) //main menu
    {  
    	window.draw(menu);
    	window.display();
       if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			while(1){
			window.draw(Level);
			window.display();
			       if (Keyboard::isKeyPressed(Keyboard::A))
			       {
			       		level=1;
			       		break;
			       }
			       else if (Keyboard::isKeyPressed(Keyboard::B))
			       {
			       		level=2;
			       		break;
			       }
			    }
			    
			    play=0;
		}		
			
		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{			instruct=true;
					while(instruct){
					window.draw(instructions);
					window.display();
					if (Keyboard::isKeyPressed(Keyboard::C)){
					instruct=false;}
					        		}
        }
        if (Keyboard::isKeyPressed(Keyboard::Num3))
		{		
					while(1)
					{
					   window.draw(black);
					   window.draw(hscore1);
					   window.draw(hscore2);
					   window.draw(hscore3);
					   window.display();
					     if (Keyboard::isKeyPressed(Keyboard::Num0))
					        break;	 
           					
					}	 
       }
       
       
	}		 
	
	int shadowblock[4][2];
	
	
    while (window.isOpen()){
    
    
    if(score>highscores[9]) //if the user has made it to the list of highscores
    	highscores[9]=score;
    
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
		
		if(level==1)
        delay=0.3;
        else if(level==2)
        delay=0.1;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
            	else if (e.key.code == Keyboard::P)       //pauses game
            	{
            		if(pause==true)
            		pause=false;
            		else
            		pause=true;}
            		
            	else if (e.key.code == Keyboard::Space)
            		space=true;
            		}
        		}
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            if(!bomb)//bomb will not go quickly down
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
       		
        	

				while(pause)  //display the pause menu
				{
					
					        window.draw(Pause);
					        window.display();
					        if (Keyboard::isKeyPressed(Keyboard::Num1))
					        {		pause=false;	 
           					}
           					if (Keyboard::isKeyPressed(Keyboard::Num4))
					        {		return 0;
           					}
           					if (Keyboard::isKeyPressed(Keyboard::Num2))
					        {		restart=true;
					        		pause=false;	 
           					}
           					if (Keyboard::isKeyPressed(Keyboard::Num3))
					        {			instruct=true;
					        			while(instruct){
					        			 window.draw(instructions);
					        			 window.display();
					        			 if (Keyboard::isKeyPressed(Keyboard::Enter)){
					        			 	instruct=false;}
					        			 	}
           					}
           					if (Keyboard::isKeyPressed(Keyboard::Num9))
					        {		
					        	while(1)
					        	{
					        		window.draw(hscore1);
					        		window.draw(hscore2);
					        		window.draw(hscore3);
					        		window.display();
					        		if (Keyboard::isKeyPressed(Keyboard::Num8))
					        {		break;	 
           					}
					        	}	 
           					}	
				}
				
				if(restart) //restart game
				break;
				
				int ylocation;
		int xlocation;
		ylocation=point_1[1][1];
		xlocation=point_1[1][0];

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        if(!pause){
        
        fallingPiece(timer, delay, colorNum, b, space, bomb, level, shadowblock); //piece starts to fall
        
        ghostfunction(shadowblock); //shadow function
        
        isbomb(bomb, b);           //to check if the block is the bomb. will return bool value. which will help further in program
        
        rotatepiece(rotate, bomb, b, xcordinate, ycordinate, xlocation, ylocation); //to rotate a piece. takes copy of index as argument
        																		//as one block will not rotate. takes other prameters which will hepl in rotation
        leftmove(delta_x, bomb);   //to move piece left or right. delta x will determine where to move
        
        rightmove(delta_x, bomb);   //to move piece left or right
        
        checkline(countscore);              //to check if a line is filled and tells how many lines destroyed
        
        updatescore(score, countscore);   //updates the score according to the lines destroyed.
        ss.str(""); //converting score into string to display
		ss<<score;
		Score.setString(ss.str());
        
        checkbomb(bomb, colorNum);	//implements the function of bomb. clears grid or 4 blocks
		
		isgameover(gameoover);      //checks if the game is over. checks if blocks have reached the top of grid         
          }
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

		if(gameoover) break;	//game over breaks the loop
		
        window.clear(Color::Black);
        window.draw(background);
        window.draw(text);
        window.draw(Score);
        
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
          
          
          // working of shadow just likke point 1 //
          
          	for (int i=0; i<4; i++){
            ghost.setTextureRect(IntRect(colorNum*18,0,18,18));
            if(bomb)//color of bomb will be invisible
            ghost.setColor(Color(10,10,10,10));
            else
            ghost.setColor(Color(125,125,125,125));//color of shadow
            ghost.setPosition(shadowblock[i][0]*18,shadowblock[i][1]*18);
            ghost.move(28,31);
            window.draw(ghost);
          }
          
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        
    }
    
    
/////////sorting highscore array in descending order////////////
///////////////////////////////////////////////////////////////
    for(int j=0; j<10; j++) 
	{
		 for(int i=0; i<10-1; i++) 
		{
			if(highscores[i]<highscores[i+1])
			{
				int temp=highscores[i];
				highscores[i]=highscores[i+1];
				highscores[i+1]=temp;
			}
		}
	}
/////////////////////////file handling///////////////////////////////

    std::ofstream filee;
    filee.open("highscore.txt");
    
	int count=0;
		while(count<10)   // replacing the highscore file with current array.
		{
			filee << highscores[count] << std::endl;
			count++;
		}
    filee.close();
        
        if(gameoover) //game over screen
        while(1)
					{
						window.draw(gameover);
					    window.display();
					    if (Keyboard::isKeyPressed(Keyboard::Num1))
					        {		restart=true;
					        		break;	 
           					}
           					if (Keyboard::isKeyPressed(Keyboard::Num2))
					        {		return 0;
           					}
					}
    
}while(restart);  //if user restarts the game
    return 0;
}
