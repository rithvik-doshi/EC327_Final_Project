#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
using std::vector;
using std::pow;
using std::cout;
using std::to_string;
using std::string;

int main(){
  vector <int> x,y;
  float yscale, xscale, ysetmax = 500, xsetmax = 500;
  float xpointmin = -500, xpointmax = 500;
  int i, deviation, ypointmax = 0, ypointmin = 0, count = 0;
  int originy = ysetmax/2;
  int xpointmaxgraph = xpointmax, xpointmingraph = xpointmin;
  float offsetx = ((abs(xpointmin)+0.0)/(abs(xpointmin)+abs(xpointmax)));
  float originx = offsetx*xsetmax;

  //getting x-negative values
  for (i=0;i<=abs(xpointmax)+abs(xpointmin);i++){
    x.push_back(i+xpointmin);
  }
  
  //getting y values
  for (auto e:x){
    y.push_back(-(pow(e,2)));
  }

  //getting max y
  for (auto e:y){
    if (e>ypointmax){
      ypointmax = e;
    }
  }

  //getting min y
  for (auto e:y){
    if (e<ypointmin){
      ypointmin = e;
    }
  }

  //getting y scale
  if (abs(ypointmin) > abs(ypointmax)){
    yscale = (ysetmax/ypointmin)/2;
    ypointmax = abs(ypointmin);
  } else {
    yscale = (ysetmax/ypointmax)/2;
    ypointmin = abs(ypointmax);
  }

  if (yscale < 0){
    yscale = yscale * -1;
  }

  //getting x scale
  xscale = xsetmax/(abs(xpointmax)+abs(xpointmin));

  sf::RenderWindow window(sf::VideoMode(xsetmax,ysetmax),"Graph");
  window.setFramerateLimit(120);

  //creating axis
  sf::RectangleShape xaxis;
  xaxis.setSize(sf::Vector2f(xsetmax,1));
  xaxis.setOutlineColor(sf::Color::White);
  xaxis.setPosition(0,originy);
  window.draw(xaxis);

  sf::RectangleShape yaxis;
  yaxis.setSize(sf::Vector2f(1,ysetmax));
  yaxis.setOutlineColor(sf::Color::White);
  yaxis.setPosition(originx,0);
  window.draw(yaxis);

  //creating font
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");

  //creating text
  sf::Text ymaxtext(to_string(ypointmax), font);
  ymaxtext.setCharacterSize(10);
  ymaxtext.setFillColor(sf::Color::White);
  ymaxtext.setPosition(originx,0);
  window.draw(ymaxtext);

  sf::Text ymintext(to_string(ypointmin), font);
  ymintext.setCharacterSize(10);
  ymintext.setFillColor(sf::Color::White);
  ymintext.setPosition(originx,ysetmax-10);
  window.draw(ymintext);

  string xpointmax_s = to_string(xpointmaxgraph);
  deviation = xpointmax_s.length()*6;
  sf::Text xmaxtext(to_string(xpointmaxgraph), font);
  xmaxtext.setCharacterSize(10);
  xmaxtext.setFillColor(sf::Color::White);
  xmaxtext.setPosition(xsetmax-deviation,originy);
  window.draw(xmaxtext);

  sf::Text xmintext(to_string(xpointmingraph), font);
  xmintext.setCharacterSize(10);
  xmintext.setFillColor(sf::Color::White);
  xmintext.setPosition(0,originy);
  window.draw(xmintext);

  //creating shape
  sf::CircleShape coord;
  coord.setRadius(1);
  coord.setOutlineColor(sf::Color::White);
  coord.setPosition(x.at(0)*xscale,y.at(0)*yscale);
  cout << (x.at(count)*xscale)+originx << ' ' << (y.at(count)*yscale)+originy << '\n';

  //running window
  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) window.close();
    }
    if (count < x.size()-1){
      count++;
      coord.setPosition((x.at(count)*xscale)+originx,(y.at(count)*yscale)+originy);
      window.draw(coord);
      cout << (x.at(count)*xscale)+originx << ' ' << (y.at(count)*yscale)+originy << '\n';
    }
    window.display();
  }
}


