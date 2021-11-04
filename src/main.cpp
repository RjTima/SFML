#include <SFML/Graphics.hpp>

using namespace sf;

int ground = 900;

float currentFrame=0;

class Player
{
     public:
     float dx,dy;
     FloatRect rect;
     bool onGround;
     Sprite sprite;
     float currentFrame;

          Player(Texture &image)
          {
               sprite.setTexture(image);
               rect = FloatRect(84,4,87,94);
               dx=dy=0;
               currentFrame=0;
          }
          void update(float time)
          {
               rect.left+=dx*time;
               if (!onGround)dy=dy+0.0005*time;
               rect.top+=dy*time;
               onGround=false;
               if(rect.top>ground)
               {
                    rect.top=ground;
                    dy=0;
                    onGround=true;
               }
               currentFrame += 0.005*time;
               if (currentFrame > 6) currentFrame -=6;
               if (dx<0) sprite.setTextureRect(IntRect(84*int(currentFrame)+84,4,-87,94));
               if (dx>0)sprite.setTextureRect(IntRect(84*int(currentFrame),4,87,94));
               sprite.setPosition(rect.left,rect.top);
               dx=0;
          }
};

int main()
{
     RenderWindow window( VideoMode(1920, 1080), "Test!");
     
     Texture t;
     t.loadFromFile("images/pngwing.com.png");
     Player p(t);

     Clock clock;

     while (window.isOpen())
     {
          float time = clock.getElapsedTime().asMicroseconds();
          clock.restart();
          time = time/700;

          Event event;
          while (window.pollEvent(event))
               {
                    if (event.type == sf::Event::Closed)
                    window.close();
               }
          if (Keyboard::isKeyPressed(Keyboard::Left))
               {
                    p.dx=-0.1;
               }
          if (Keyboard::isKeyPressed(Keyboard::Right))
               {
                    p.dx=0.1;
               }
          if (Keyboard::isKeyPressed(Keyboard::Up))
               {
                    if (p.onGround) {p.dy=-0.4; p.onGround=false;}
               }
          if (Keyboard::isKeyPressed(Keyboard::Space))
               {
                    if (p.onGround) {p.dy=-0.4; p.onGround=false;}
               }     
          if (Keyboard::isKeyPressed(Keyboard::Down))
               {
               }
          p.update(time);
          window.clear();
          window.draw(p.sprite);
          window.display();
     }

     return 0;
}