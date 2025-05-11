//#include "stdafx.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;
void updateBranches(int seed);
const int NUM_BRANCHES=6;

enum class side{LEFT,RIGHT,NONE };
side branchPosition[NUM_BRANCHES];

int main(){

     //VideoMode vm(1920, 1080);
     VideoMode vm(960, 540);
     View view(FloatRect(0,0,1920,1080));
     RenderWindow window(vm, "Timber Game !!!", Style::Fullscreen);
     
     window.setView(view);
     
     Texture textureBackGround,textureCloud,          textureTree,textureBee,textureBranch,texturePlayer,textureLog,textureAxe,textureGravestone,textureRip;
     Sprite spriteBackGround,spriteCloud1,spriteCloud2,spriteCloud3, spriteTree,spriteBee,spriteBranches[NUM_BRANCHES],spritePlayer,spriteLog,spriteAxe,spriteGravestone,spriteRip;
     //Player
            texturePlayer.loadFromFile("graphics/me2.png");
            spritePlayer.setTexture(texturePlayer);
            spritePlayer.setPosition(580,720);
            side playerSide=side::LEFT;
     //Axe
            textureAxe.loadFromFile("graphics/axe.png");
            spriteAxe.setTexture(textureAxe);
            spriteAxe.setPosition(700,830);
            const float AXE_POSITION_LEFT=700;
            const float AXE_POSITION_RIGHT=1075;
     //Log
            textureLog.loadFromFile("graphics/log.png");
            spriteLog.setTexture(textureLog);
            spriteLog.setPosition(810,720);
            bool logActive=false;
            float logSpeedX=1000;
            float logSpeedY=1000;
  
     //Rip
            textureRip.loadFromFile("graphics/rip.png");
            spriteRip.setTexture(textureRip);
            spriteRip.setPosition(600,860);
            
            
     //Background
           textureBackGround.loadFromFile("graphics/back.png");
           spriteBackGround.setTexture(textureBackGround);
           spriteBackGround.setPosition(0,0);
     
     //Tree
          textureTree.loadFromFile("graphics/tree.png");
          spriteTree.setTexture(textureTree);
          spriteTree.setPosition(810,0);
     
     //Cloud 1
          textureCloud.loadFromFile("graphics/cloud.png");
          spriteCloud1.setTexture(textureCloud);
          spriteCloud1.setPosition(0,0);
     
     
     //Cloud 2
  
         spriteCloud2.setTexture(textureCloud);
         spriteCloud2.setPosition(0,250);
     
     
     //Cloud 3

         spriteCloud3.setTexture(textureCloud);
         spriteCloud3.setPosition(0,500);
     
     // BEE

         textureBee.loadFromFile("graphics/bee.png");
         spriteBee.setTexture(textureBee);
         spriteBee.setPosition(0,800);
     
     //Branch
     textureBranch.loadFromFile("graphics/branch.png");
     for (int i=0;i<NUM_BRANCHES;i++)
        {
          spriteBranches[i].setTexture(textureBranch);
          spriteBranches[i].setPosition(2000,2000);
          spriteBranches[i].setOrigin(220,20);
       }
     
     
     // Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	
	int score = 0;

	Text messageText;
	Text scoreText;
	Text fpsText;
     // Handling Sound
     
     SoundBuffer deathBuffer;
     deathBuffer.loadFromFile("sound/death.wav");
     Sound death;
     death.setBuffer(deathBuffer);
     
     SoundBuffer chopBuffer;
     chopBuffer.loadFromFile("sound/chop.wav");
     Sound chop;
     chop.setBuffer(chopBuffer);
     
     SoundBuffer ootBuffer;
     ootBuffer.loadFromFile("sound/out_of_time.wav");
     Sound oot;
     oot.setBuffer(ootBuffer);
     
     //Font
    // We need to choose a font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	
	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);
	//fpsText.setFont(font);
	

	/* Set up the fps text
	fpsText.setFillColor(Color::White);
	fpsText.setCharacterSize(100);
	fpsText.setPosition(1200, 20);
	*/
	
	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	
	// Choose a color
	messageText.setFillColor(Color::Red);
	scoreText.setFillColor(Color::White);


// Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	// Backgrounds for the text
	RectangleShape rect1;
	rect1.setFillColor(sf::Color(0, 0, 0, 150));
	rect1.setSize(Vector2f(750,105));
	rect1.setPosition(0,30);

	RectangleShape rect2;
	rect2.setFillColor(sf::Color(0, 0, 0, 150));
	rect2.setSize(Vector2f(1000, 105));
	rect2.setPosition(1150, 30);

     
     Clock clock;
   
   
   
     // For  bee 
     bool beeActive=false;
     float beeSpeed=0.0f;

     
     //Cloud animation
       
     bool cloudActive1=false;
     float cloudSpeed1=0.0f;
       
     bool cloudActive2=false;
     float cloudSpeed2=0.0f;
       
     bool cloudActive3=false;
     float cloudSpeed3=0.0f;
     
     bool paused=true;  
     
     bool acceptInput = false;
     
   while(window.isOpen()){
    /*  updateBranches(1);
      updateBranches(2);
      updateBranches(3);
      updateBranches(4);
      updateBranches(5);
      updateBranches(6);
   
    score++;
    */
    
      Event event;
         while(window.pollEvent(event))
          {
            if (event.type==Event::KeyReleased && !paused)
               {
                  acceptInput=true;
                  //hide the Axe
                  spriteAxe.setPosition(2000,spriteAxe.getPosition().y);
                }
            }
    
    
     if(Keyboard::isKeyPressed(Keyboard::Escape))
       {
        window.close();
       }
     if (Keyboard::isKeyPressed(Keyboard::Return))
      {
	paused = false;
	
	// Reset the time and the score
           score = 0;
	timeRemaining = 6.0f;
	
	// Make all the branches disappear
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
	branchPosition[i] = side::NONE;
	}
	
	// Move the player into position
	spritePlayer.setPosition(580, 720);

           //Make sure the gravestone is hidden
	spriteRip.setPosition(680, 2000);

	 acceptInput = true;
      }
   if(acceptInput)
   {
     if(Keyboard::isKeyPressed(Keyboard::Right))
        {
          chop.play();
          playerSide=side::RIGHT;
          score++;
          timeRemaining +=(0.15+2/score);
          spriteAxe.setPosition(AXE_POSITION_RIGHT,spriteAxe.getPosition().y);
          spritePlayer.setPosition(1200,720);
          updateBranches(score);
          spriteLog.setPosition(810,720);
          logActive=true;
          logSpeedX=5000;
          acceptInput=false;
        }
        
     if(Keyboard::isKeyPressed(Keyboard::Left))
        {
          chop.play();
          playerSide=side::LEFT;
          score++;
          timeRemaining +=(0.15+2/score);
          spriteAxe.setPosition(AXE_POSITION_LEFT,spriteAxe.getPosition().y);
          spritePlayer.setPosition(580,720);
          updateBranches(score);
          spriteLog.setPosition(810,720);
          logActive=true;
          logSpeedX=-5000;
          acceptInput=false;
        }   
        
   }		
       
    if(!paused)
    {

       // Measure time
	Time dt = clock.restart();

      // Subtract from the amount of time remaining
	timeRemaining -= dt.asSeconds();
       // size up the time bar
	timeBar.setSize(Vector2f(timeBarWidthPerSecond *
		timeRemaining, timeBarHeight));
		
     if(timeRemaining <= 0.0f)
     {
       paused=true;
       messageText.setString("Out Of Time !! ");
       oot.play();
       
       FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

// Play the out of time sound
       // outOfTime.play();
  
     } 
     		
   // Bee     
     if(!beeActive)
     {
        srand((int)time(0));
        beeSpeed=rand()%200+200;
        
        srand((int)time(0));
        float height =rand()%500+500;
        spriteBee.setPosition(2000,height);
        beeActive=true;
      }
    else
      { 
        spriteBee.setPosition(spriteBee.getPosition().x-beeSpeed*dt.asSeconds(),
        spriteBee.getPosition().y);
        if(spriteBee.getPosition().x<-100)
        {
        beeActive=false;
        }	
      }  
      // Cloud 
      
      if(!cloudActive1)
       {
        srand((int)time(0)*10);
        cloudSpeed1=rand()%200;
        
        srand((int)time(0)*10);
        float height =rand()%150;
        spriteCloud1.setPosition(-300,height);
        cloudActive1=true;
      }
    else
      { 
        spriteCloud1.setPosition(spriteCloud1.getPosition().x+cloudSpeed1*dt.asSeconds(),
        spriteCloud1.getPosition().y);
        if(spriteCloud1.getPosition().x > 1920)
        {
        cloudActive1=false;
        }	
      }  
      //  c2
      
      if(!cloudActive2)
      {
        srand((int)time(0)*20);
        cloudSpeed2=rand()%200;
        
        srand((int)time(0)*20);
        float height =rand()%300-150;
        spriteCloud2.setPosition(-300,height);
        cloudActive2=true;
      }
    else
      { 
        spriteCloud2.setPosition(spriteCloud2.getPosition().x+cloudSpeed2*dt.asSeconds(),
        spriteCloud2.getPosition().y);
        if(spriteCloud2.getPosition().x > 1920)
        {
          cloudActive2=false;
        }	
      } 
      //c3
      
      if(!cloudActive3){
        srand((int)time(0)*30);
        cloudSpeed3=rand()%200;
        
        srand((int)time(0)*30);
        float height =rand()%450-150;
        spriteCloud3.setPosition(-300,height);
        cloudActive3=true;
       }
      else
      { 
        spriteCloud3.setPosition(spriteCloud3.getPosition().x+cloudSpeed3*dt.asSeconds(),
        spriteCloud3.getPosition().y);
        if(spriteCloud3.getPosition().x > 1920)
        {
        cloudActive3=false;
        }	
      } 
      
 std::stringstream ss;
 ss<<"Score = "<<score;
 scoreText.setString(ss.str());
 
   for (int i=0;i< NUM_BRANCHES; i++)
   {
     float height= i*150;
     if(branchPosition[i]==side::LEFT)
     {
       spriteBranches[i].setPosition(610,height);
       spriteBranches[i].setRotation(180);
     }
     else if(branchPosition[i]==side::RIGHT)
     {
       spriteBranches[i].setPosition(1330,height);
       spriteBranches[i].setRotation(0);
     } 
     else
     {
        spriteBranches[i].setPosition(2550,height);
        //spriteBranches[i].setRotation(180);
     }
     
   }
 
 	//Handle Log
 	if(logActive)
 	{
 	  spriteLog.setPosition(spriteLog.getPosition().x+logSpeedX*dt.asSeconds(),
 	                         spriteLog.getPosition().y+logSpeedY*dt.asSeconds());
 	   if(spriteLog.getPosition().x <-100 || spriteLog.getPosition().x>2000)
 	   {
 	     logActive=false;
 	     spriteLog.setPosition(810,720);
 	   }                      
 	}
 	
 	// Handle Player's Death
 	if ( branchPosition[5]   == playerSide)
 	{
 	   paused=true;
 	   acceptInput= false;
 	   death.play();
 	   // Hide  the player
 	   spritePlayer.setPosition(2000,720);
 	  // make rip visible
 	  spriteRip.setPosition(525,720);
 	  //Update the text message
 	  messageText.setString("SQUISHED !!!");
 	  
 	  // Position the text
              textRect = messageText.getLocalBounds();

	   messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	   messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
 	  
 	}
 	  
 
  }   //End of if(!paused)
     window.clear();
     window.draw(spriteBackGround);
     window.draw(spriteTree);
     window.draw(spriteCloud1);
     window.draw(spriteCloud2);
     window.draw(spriteCloud3);
     window.draw(spriteBee);
          window.draw(spritePlayer);
          window.draw(spriteAxe);
          window.draw(spriteLog);
          window.draw(spriteRip);
          window.draw(spriteBee); 																																
     // Draw backgrounds for the text
		window.draw(rect1);
		//window.draw(rect2);
// Draw the score
    window.draw(scoreText);

// Draw the FPS
   window.draw(fpsText);

// Draw the timebar
    window.draw(timeBar);

// Draw the branches
    for (int i=0;i<NUM_BRANCHES;i++)
          window.draw(spriteBranches[i]);
   	
   	
   		
     
     if(paused)
       window.draw(messageText);	
     
     window.display();
   }
   return 0;
}


void updateBranches(int seed)
{
 branchPosition[NUM_BRANCHES];   
 for(int j=NUM_BRANCHES-1; j>0;j--)
 {
    branchPosition[j]=branchPosition[j-1];
 }
 srand((int)time(0)+seed);
 int r= rand()%5;
   switch(r)
    {
       case 0 : branchPosition[0]=side::LEFT;
       break;
       
       case 1: branchPosition[0 ]=side::RIGHT;
       break;
       
       default:
               branchPosition[0]=side::NONE;
       
     } 
}
