#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(1920, 1080), "Final Game");
    app.setFramerateLimit(60);
    app.setKeyRepeatEnabled(false);

    //score
    sf::Font font;
    font.loadFromFile("/home/said/Desktop/hackathonData/Ubuntu-Bold.ttf");
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    int score=0;
    scoreText.setString("Score: " + std::to_string(score));
    //HomePage texture
    Texture fStart, fExit,fmiddle,fRMiddle,fLMiddle,fName;
    fStart.loadFromFile("../projectsPhotos/snake/Start.jpg");
    fExit.loadFromFile("../projectsPhotos/snake/Exit.png");
    fmiddle.loadFromFile("../projectsPhotos/snake/redRaceCar.png");
    fLMiddle.loadFromFile("../projectsPhotos/snake/LeftArrow.png");
    fRMiddle.loadFromFile("../projectsPhotos/snake/rightArrow.png");

    //font
    Font Arial;
    if(!Arial.loadFromFile("font/Comix Loud.ttf"))
        std::cout<<"NOT";

    Text Information;
    Information.setFont(Arial);
    Information.setString("Weclome to our final project \n Team member: \n Mohamed Elsayed \n Khaled salama \n Mostafa Fetouh \n Said Ahmed \n Omnia Saad");
    Information.setCharacterSize(24);
    Information.setPosition(1470,775);
    Information.setFillColor(sf::Color(255,0,0));
    Information.setStyle(sf::Text::Bold);

    //HomePage temps
    RectangleShape middle,rMiddle,lMiddle,bStart,bExit,bName,bSound,bInfo,tInfo;


    //Background(game) name
    bName.setSize(Vector2f(780,120));
    bName.setPosition(560,70);

    middle.setSize(Vector2f(320,320));
    middle.setPosition(800,325);
    middle.setTexture(&fmiddle);

    rMiddle.setSize(Vector2f(160,160));
    rMiddle.setPosition(1280,405);
    rMiddle.setTexture(&fRMiddle);

    lMiddle.setSize(Vector2f(160,160));
    lMiddle.setPosition(480,405);
    lMiddle.setTexture(&fLMiddle);

    bStart.setSize(Vector2f(640,65));
    bStart.setPosition(640,710);
    bStart.setTexture(&fStart);

    bExit.setSize(Vector2f(640,65));
    bExit.setPosition(640,840);
    bExit.setTexture(&fExit);

    bInfo.setSize(Vector2f(80,80));
    bInfo.setPosition(1800,960);

    tInfo.setSize(Vector2f(400,225));
    tInfo.setPosition(1440,775);

    bSound.setSize(Vector2f(80,80));
    bSound.setPosition(40,960);

    begining :

    //define HomePage variables
    bool HomePage = 1,rMov = 0,lMov = 0,start = 0,exit = 0,info = 0,sound = 1,infoPage = 0,gameOver = 0 ;

    //game variables
    bool moveRight=0,moveLeft=0,moveUp=0,moveDown=0;


    // game temps
    vector<CircleShape>snak;
    CircleShape head;
    int x=960,y=525;
    head.setPosition(x,y);
    head.setRadius(10);
    for(int i=0; i<5; i++)
    {
        snak.push_back(head);
    }
    int tempx=960;
    for(int i=1; i<5; i++)
    {
        tempx-=30;
        snak[i].setPosition(tempx,y);

    }
    sf::CircleShape food[10];
    for(int i=0; i<2; i++)
        food[i].setRadius(10);
    std::pair<int,int>foodPosition[10];
    for(int i=0; i<2; i++)
    {
        foodPosition[i].first=rand()%1900+10;


        foodPosition[i].second=rand()%1060+10;
    }

    // Start the game loop
    while (!exit)
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            //if(!start)

            //bName
            if(Mouse::getPosition().x>560 && Mouse::getPosition().x<1340
               &&Mouse::getPosition().y>70 && Mouse::getPosition().y<190)
            {
                bName.setOutlineThickness(5);
                bName.setOutlineColor(Color::Red);
            }
            //middle
            if(Mouse::getPosition().x>800 && Mouse::getPosition().x<1220
               &&Mouse::getPosition().y>325 && Mouse::getPosition().y<645)
            {
                middle.setOutlineThickness(5);
                middle.setOutlineColor(Color::Yellow);
            }
            //rMiddle
            if(Mouse::getPosition().x>1280 && Mouse::getPosition().x<1440
               &&Mouse::getPosition().y>405 && Mouse::getPosition().y<565
               &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
            {
                rMiddle.setOutlineThickness(5);
                rMiddle.setOutlineColor(Color::Yellow);
                rMov=true;
            }
            //lMiddle
            if(Mouse::getPosition().x>=480 && Mouse::getPosition().x<=640
               &&Mouse::getPosition().y>=405 && Mouse::getPosition().y<=565
               &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
            {
                lMiddle.setOutlineThickness(5);
                lMiddle.setOutlineColor(Color::Yellow);
                lMov=true;
            }

            //bStart
            if(Mouse::getPosition().x>=640 && Mouse::getPosition().x<=1280
               &&Mouse::getPosition().y>=710 && Mouse::getPosition().y<=775
               &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
            {
                bStart.setOutlineThickness(5);
                bStart.setOutlineColor(Color::Yellow);
                start = true;
                HomePage = 0;
            }

            //bExit
            if(Mouse::getPosition().x>=640 && Mouse::getPosition().x<=1280
               &&Mouse::getPosition().y>=840 && Mouse::getPosition().y<=905
               &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
            {
                bExit.setOutlineThickness(5);
                bExit.setOutlineColor(Color::Yellow);
                exit = true;

            }

            //bSound
            if(Mouse::getPosition().x>=40 && Mouse::getPosition().x<=120
               &&Mouse::getPosition().y>=960 && Mouse::getPosition().y<=1040
               &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
                sound = !sound;
            //bInfo
            if(Mouse::getPosition().x>=1800 && Mouse::getPosition().x<=1880
               &&Mouse::getPosition().y>=960 && Mouse::getPosition().y<=1040)infoPage=true;




            //Game Events
            if(event.type==Event::KeyPressed&&event.key.code==sf::Keyboard::Up)
            {
                moveUp=true;
                moveDown=moveLeft=moveRight=false;
            }
            if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Down)
            {
                moveDown=true;
                moveUp=moveLeft=moveRight=false;
            }
            if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Right)
            {
                moveRight=true;
                moveDown=moveLeft=moveUp=false;
            }
            if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Left)
            {
                moveLeft=true;
                moveDown=moveRight=moveUp=false;
            }





        }
        if(HomePage)
        {
            app.clear();
            app.draw(bName);
            app.draw(middle);
            app.draw(rMiddle);
            app.draw(lMiddle);
            app.draw(bStart);
            app.draw(bExit);
            app.draw(bSound);
            app.draw(bInfo);
            if(info)
            {
                app.draw(tInfo);
                app.draw(Information);
            }
            app.display();
        }
        else if(infoPage)
        {
            //play the game
            app.clear();

            app.display();
        }
        else if(start)
        {
            //play the game
            app.clear();
            if(moveUp)
            {
                app.clear();
                y-=10;
                x=((x%1920)+1920)%1920;
                y=((y%1080)+1080)%1080;
                for(int i=snak.size()-1; i>=0; i--)
                {
                    int xn=snak[i-1].getPosition().x;
                    int yn=snak[i-1].getPosition().y;
                    snak[i].setPosition(xn,yn);

                }
                snak[0].setPosition(x,y);
                for(int i=0; i<snak.size(); i++)
                {
                    app.draw(snak[i]);
                }

                //app.display();
            }
            else if(moveDown)
            {
                app.clear();
                y+=10;
                x=((x%1920)+1920)%1920;
                y=((y%1080)+1080)%1080;
                for(int i=snak.size()-1; i>=0; i--)
                {
                    int xn=snak[i-1].getPosition().x;
                    int yn=snak[i-1].getPosition().y;
                    snak[i].setPosition(xn,yn);

                }
                snak[0].setPosition(x,y);
                for(int i=0; i<snak.size(); i++)
                {
                    app.draw(snak[i]);
                }
                //app.display();
            }
            else if(moveLeft)
            {
                app.clear();
                x-=10;
                x=((x%1920)+1920)%1920;
                y=((y%1080)+1080)%1080;
                for(int i=snak.size()-1; i>=0; i--)
                {
                    int xn=snak[i-1].getPosition().x;
                    int yn=snak[i-1].getPosition().y;
                    snak[i].setPosition(xn,yn);

                }
                snak[0].setPosition(x,y);
                for(int i=0; i<snak.size(); i++)
                {
                    app.draw(snak[i]);
                }
                //app.display();
            }
            else if(moveRight)
            {
                app.clear();
                x+=10;
                x=((x%1920)+1920)%1920;
                y=((y%1080)+1080)%1080;
                for(int i=snak.size()-1; i>=0; i--)
                {
                    int xn=snak[i-1].getPosition().x;
                    int yn=snak[i-1].getPosition().y;
                    snak[i].setPosition(xn,yn);

                }
                snak[0].setPosition(x,y);
                for(int i=0; i<snak.size(); i++)
                {
                    app.draw(snak[i]);
                }
                //app.display();
            }
            for(int i=0; i<2; i++)
            {
                app.draw(food[i]);
                if(snak[0].getGlobalBounds().intersects(food[i].getGlobalBounds()))
                {
                    score += 5;
                    scoreText.setString("Score: " + std::to_string(score));
                    foodPosition[i].first=rand()%1900+10;
                    foodPosition[i].second=rand()%1060+10;
                    food[i].setPosition(foodPosition[i].first,foodPosition[i].second);
                    int xn=snak[snak.size()-1].getPosition().x;
                    int yn=snak[snak.size()-1].getPosition().y;

                    for(int i=0;i<5; i++)
                    {
                        head.setPosition(xn+10,yn);
                        snak.push_back(head);
                        app.draw(head);
                        xn=snak[snak.size()-1].getPosition().x;
                        yn=snak[snak.size()-1].getPosition().y;

                    }

                }
            }

            for(int i=1;i<snak.size();i++)
            {
                if(snak[0].getPosition().x==snak[i].getPosition().x&&snak[0].getPosition().y==snak[i].getPosition().y)
                {
                    sleep(milliseconds(5000));
                    gameOver=1;
                    start=0;
                }
            }
            app.draw(scoreText);
            app.display();

        }
        else if(gameOver)
        {
            //Game Over
            //score
            //Do you want to play again ?
            app.clear();
            gameOver=0;
            HomePage=1;
            score=0;
            goto begining;


            app.display();
        }


    }

    return EXIT_SUCCESS;
}
