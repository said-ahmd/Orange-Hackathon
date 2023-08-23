#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
int main(){
    RenderWindow window(VideoMode(400,500),"diamond");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);
    bool play= true;
    Event action;
    //vars
    bool rightup= false,leftup= false,rightdown= false,leftdown= false;
    //shapes
    //rects
    RectangleShape uprect(Vector2f(80,15));
    uprect.setFillColor(Color::Red);
    int xposup=210;
    RectangleShape downrect(Vector2f(80,15));
    uprect.setFillColor(Color::Red);
    int xposdown=210;
    //ballRed
    CircleShape ball;
    ball.setRadius(10);
    ball.setFillColor(Color::Red);
    int dx=1,dy=3;
    int x=255,y=220;

    while (play){
        //events
        while (window.pollEvent(action)){
            if(action.type==Event::KeyPressed){
                if(action.key.code==Keyboard::Right){
                    rightup= true;
                }
                if(action.key.code==Keyboard::Left){
                    leftup= true;
                }
                if(action.key.code==Keyboard::A){
                    leftdown= true;
                }
                if(action.key.code==Keyboard::D){
                    rightdown= true;
                }
                if(action.type==Event::Closed){
                    window.close();
                }
            }
        }
        //logic
        //rects
        if(leftup){
            xposup-=20;
            leftup= false;
            if(xposup<0)xposup=0;
        }
        if(rightup){
            xposup+=20;
            rightup= false;
            if(xposup>420)xposup=440;
        }
        if(leftdown){
            xposdown-=20;
            leftdown= false;
            if(xposdown<0)xposdown=0;
        }
        if(rightdown){
            xposdown+=20;
            rightdown= false;
            if(xposdown>440)xposdown=440;
        }
        uprect.setPosition(xposup,0);
        downrect.setPosition(xposdown,420);
        //ball
        //colision
        if(uprect.getGlobalBounds().intersects(ball.getGlobalBounds())){
            dy=-dy;
        }
        if(downrect.getGlobalBounds().intersects(ball.getGlobalBounds())){
            dy=-dy;
        }
        if(x<0||x>510)dx=-dx;
        x+=dx;
        y+=dy;
        ball.setPosition(x,y);
        //render
        window.clear();
        window.draw(uprect);
        window.draw(downrect);
        window.draw(ball);
        window.display();
    }

    window.close();
    return 0;
}
