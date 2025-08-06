#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
using namespace sf;
void updateBranches (int seed);
const int NUM_BRANCHES =6;
Sprite branches[NUM_BRANCHES];
enum class side{LEFT, RIGHT, NONE};
side branchPosition[NUM_BRANCHES];
int main(){
    VideoMode vm(960, 540);
    RenderWindow window(vm, "Timber!!");
    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);
    
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    side playerside = side::LEFT;
    
     Texture textureRip;
    textureRip.loadFromFile("graphics/rip.png");
    Sprite spriteRip;
    spriteRip.setTexture(textureRip);
    spriteRip.setPosition(680, 880);
    
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);
    const float AXE_POSITION_LEFT=700;
    const float AXE_POSITION_RIGHT=1075;
    
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);
    bool logActive = false;
    float logSpeedX=1000;
     float logSpeedY= -1500;
     bool acceptInput=false;
    

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    bool beeactive = false;
    float beeSpeed = 0.0f;

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud;
    spriteCloud.setTexture(textureCloud);
    spriteCloud.setPosition(0, 200);
    bool Cloudactive = false;
    float CloudSpeed = 0.0f;

    Texture textureCloud1;
    textureCloud1.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1;
    spriteCloud1.setTexture(textureCloud1);
    spriteCloud1.setPosition(0, 250);
    bool Cloud1active = false;
    float Cloud1Speed = 0.0f;

    Texture textureCloud2;
    textureCloud2.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud2;
    spriteCloud2.setTexture(textureCloud2);
    spriteCloud2.setPosition(0, 500);
    spriteCloud2.setScale(0.75f, 0.65f);
    bool Cloud2active = false;
    float Cloud2Speed = 0.0f;

    Clock clock;
    
    RectangleShape timebar;
    float timebarstartwidth=400;
    float timebarheight=80;
    timebar.setSize(Vector2f(timebarstartwidth,timebarheight));
    timebar.setFillColor(Color::Green);
    timebar.setPosition((1920/2)-timebarstartwidth/2,980);
    Time gametimetotal;
    float timeremaining=6.0f;
    float timebarwidthpersec = timebarstartwidth/timeremaining;
    bool paused = true;
    
   
    int score = 0 ;
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    Text messageText;
    Text scoreText;
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("press enter to start the game !!!");
    scoreText.setString("Score= 0 ");
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    messageText.setFillColor(Color::White);    
    scoreText.setFillColor(Color::Red);  
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    for(int i=0;i<NUM_BRANCHES; i++){
    	branches[i].setTexture(textureBranch);
    	branches[i].setPosition(-2000, -2000);
    	branches[i].setOrigin(220,20);
    }
   SoundBuffer deathBuffer;
   deathBuffer.loadFromFile("sound/death.wav");
   Sound death;
   death.setBuffer(deathBuffer);
   
   SoundBuffer out_of_timeBuffer;
   out_of_timeBuffer.loadFromFile("sound/out_of_time.wav");
   Sound out_of_time;
   out_of_time.setBuffer(out_of_timeBuffer);
   
   SoundBuffer chopBuffer;
   chopBuffer.loadFromFile("sound/chop.wav");
   Sound chop;
   chop.setBuffer(chopBuffer);
    

    while (window.isOpen()) {
    //handle player input
    Event event;
    while(window.pollEvent(event)){
    	if(event.type==Event::KeyReleased && !paused){
    	acceptInput=true;
    	spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
    	}
    }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return) && paused) {
            paused = false;
            score=0;
            timeremaining=6;
             for(int i=0;i<NUM_BRANCHES; i++){
             	branchPosition[i]=side::NONE;
             }
             spriteRip.setPosition(675, 2000);
             spritePlayer.setPosition(580, 720);
             acceptInput=true;
            clock.restart();
        }
        if(acceptInput){
        	 if (Keyboard::isKeyPressed(Keyboard::Right)){
        	 	playerside = side::RIGHT;
        	 	score++;
        	 	timeremaining += (2/score)+ .15;
        	 	
        	 	spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y );
        	 	spritePlayer.setPosition(1200,720);
        	 	updateBranches(score);
        	 	spriteLog.setPosition(810,720);
        	 	logSpeedX= -5000;
        	 	logActive=true;
        	 	acceptInput=false;
        	 	chop.play();
        	 }
        	  if (Keyboard::isKeyPressed(Keyboard::Left)){
        	 	playerside = side::LEFT;
        	 	score++;
        	 	timeremaining += (2/score)+ .15;
        	 	
        	 	spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y );
        	 	spritePlayer.setPosition(580,720);
        	 	updateBranches(score);
        	 	spriteLog.setPosition(810,720);
        	 	logSpeedX= 5000;
        	 	logActive=true;
        	 	acceptInput=false;
        	 	chop.play();
        	 }
        }

        if (!paused) {
       //  updateBranches(1);
   // updateBranches(2);
   // updateBranches(3);
    //updateBranches(4);
   // updateBranches(5);
    //updateBranches(6);
            Time dt = clock.restart();
            timeremaining -= dt.asSeconds();
            timebar.setSize(Vector2f (timebarwidthpersec*timeremaining,timebarheight));
            if(timeremaining<=0.0f){
              paused=true;
              messageText.setString("GAME OVER!!!");
              FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    out_of_time.play();
    
            }

            if (!beeactive) {
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeactive = true;
            } else {
                spriteBee.setPosition(spriteBee.getPosition().x - beeSpeed * dt.asSeconds(), spriteBee.getPosition().y);
                if (spriteBee.getPosition().x < -100) {
                    beeactive = false;
                }
            }

            if (!Cloudactive) {
                srand((int)time(0) * 50);
                CloudSpeed = (rand() % 200);
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud.setPosition(-200, height);
                Cloudactive = true;
            } else {
                spriteCloud.setPosition(spriteCloud.getPosition().x + CloudSpeed * dt.asSeconds(), spriteCloud.getPosition().y);
                if (spriteCloud.getPosition().x > 1920) {
                    Cloudactive = false;
                }
            }

            if (!Cloud1active) {
                srand((int)time(0) * 70);
                Cloud1Speed = (rand() % 200);
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud1.setPosition(-200, height);
                Cloud1active = true;
            } else {
                spriteCloud1.setPosition(spriteCloud1.getPosition().x + Cloud1Speed * dt.asSeconds(), spriteCloud1.getPosition().y);
                if (spriteCloud1.getPosition().x > 1920) {
                    Cloud1active = false;
                }
            }

            if (!Cloud2active) {
                srand((int)time(0) * 30);
                Cloud2Speed = (rand() % 150);
                srand((int)time(0) * 30);
                float height = (rand() % 200) - 100;
                spriteCloud2.setPosition(-200, height);
                Cloud2active = true;
            } else {
                spriteCloud2.setPosition(spriteCloud2.getPosition().x + Cloud2Speed * dt.asSeconds(), spriteCloud2.getPosition().y);
                if (spriteCloud2.getPosition().x > 1920) {
                    Cloud2active = false;
                }
            }
        
        std::stringstream ss;
        ss<<"Score ="<< score;
        scoreText.setString(ss.str());
        for(int i=0; i<NUM_BRANCHES; i++){
        float height = i*150;
        if(branchPosition[i]==side::LEFT){
        branches[i].setPosition(610, height);
        branches[i].setRotation(180);
        }else if(branchPosition[i]==side::RIGHT){
        branches[i].setPosition(1330, height);
        branches[i].setRotation(0);
        }else{
        branches[i].setPosition(3000, height);
        }
        
        
        }
        
        if(logActive){
        	spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX*dt.asSeconds()), spriteLog.getPosition().y +(logSpeedY*dt.asSeconds()));
        	if(spriteLog.getPosition().x< -100 || spriteLog.getPosition().x>2000){
        		logActive=false;
        		spriteLog.setPosition(810,720);
        	}
        }
        if(branchPosition[5]==playerside){
        	paused = true;
        	acceptInput=false;
        	spriteRip.setPosition(525,760);
        	spriteAxe.setPosition(2000,660);
        	spritePlayer.setPosition(2000,spriteAxe.getPosition().y);
        	messageText.setString("SQUASHED!!!");
        	FloatRect textRect = messageText.getLocalBounds();
        	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
        	death.play();
        	
        }
        
        }

        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteCloud);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteTree);
        window.draw(spriteBee);
        
        
        for(int i=0; i<NUM_BRANCHES; i++){
        window.draw(branches[i]);
        }
        window.draw(scoreText);
        window.draw(timebar);
        
        window.draw(spriteRip);
         window.draw(spriteAxe);
         window.draw(spritePlayer);
          window.draw(spriteLog);
        
        if (paused) {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}
void updateBranches(int seed){
 for(int i=NUM_BRANCHES; i>0; i--){
 branchPosition[i]=branchPosition[i-1];
 
 }
 srand((int)time(0)+seed);
 int r = (rand()%3);
 switch(r){
 case 0:
 branchPosition[0]= side::LEFT;
 break;
 case 1:
 branchPosition[1]= side::RIGHT;
 break;
 default:
 branchPosition[2]= side::NONE;
 break;
 }
}



