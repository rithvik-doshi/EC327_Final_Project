#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
using std::vector;
using std::pow;

int main(){
  sf::RenderWindow window(sf::VideoMode(300,300),"Graph");
  window.setFramerateLimit(60);

  vector <int> x,y;
  int i,count;

  for (i=0;i<10;i++){
    x.push_back(i);
  }

  for (auto e:x){
    y.push_back(pow(e,2));
  }

  //creating shape
  sf::CircleShape coord;
  coord.setRadius(1);
  coord.setOutlineColor(sf::Color::Red);
  coord.setPosition(100,100);

  //running window
    while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) window.close();
    }
    if (count == x.size()-1){
      count = 0;
    }
    coord.setPosition(x.at(count),y.at(count));
    window.draw(coord);
    count++;
    window.display();
  }
}


/*sf::Vector2u size;
sf::Image graph;

graph.create(size.x, size.y, sf::Color(255, 255, 255));
// y = 2x
for (unsigned int x = 0; x < size.x; x++)
{
    unsigned int y = 2u * x;
    if (y < size.y)
    {
        graph.setPixel(x, y, sf::Color(0, 0, 0));
    }
}*/
