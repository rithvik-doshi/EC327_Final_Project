#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
using std::vector;
using std::pow;
using std::cout;
using std::to_string;
using std::string;
using std::fstream;
using std::getline;

int main(){
  //values that are interchangable
  float ysetmax = 500, xsetmax = 500;
  float xpointmin = -10, xpointmax = 10;
  string filename = "Data.txt";
  float ypointmin, ypointmax;

  //reading a file
  fstream myfile;
  vector <string> filereader;
  string s;
  
  //values that are not interchangable
  vector <int> x,y;
  vector <float> originalX, originalY;
  float yscale, xscale, originalYmax, originalYmin;
  int i,j, placeholder, deviation, count = 0, count2=0;
  int xpointmaxgraph = xpointmax, xpointmingraph = xpointmin;
  float offsetx = ((abs(xpointmin)+0.0)/(abs(xpointmin)+abs(xpointmax)));
  float originx = offsetx*xsetmax;

  myfile.open(filename);
  while (getline(myfile, s)){
    filereader.push_back(s);
  }
  for (auto e:filereader){
    for (i=0;i<e.length();i++){
      if (e.at(i)==','){
        s.clear();
        for (j=0;j<i;j++){
          s.push_back(e.at(j));
        }
        originalX.push_back(stoi(s));
        s.clear();
        for (j=i+1;j<e.length();j++){
          s.push_back(e.at(j));
        }
        originalY.push_back(stof(s));
      }
    }
  }

  //getting x-negative values
  for (i=0;i<=abs(xpointmax)+abs(xpointmin);i++){
    x.push_back(i+xpointmin);
  }

  //getting y values

  for (auto e:x){
    y.push_back(9*pow(e,2)-3);
  }


  //getting max y
  ypointmax = y.at(0);
  for (auto e:y){
    if (e>ypointmax){
      ypointmax = e;
    }
  }
  originalYmax = originalY.at(0);
  for (auto e:originalY){
    if (e>originalYmax){
      originalYmax = e;
    }
  }
  /*if (originalYmax > ypointmax){
    ypointmax = originalYmax;
  }*/

  //getting min y

  ypointmin = y.at(0);
  for (auto e:y){
    if (e<ypointmin){
      ypointmin = e;
    }
  }
  originalYmin = originalY.at(0);
  for (auto e:originalY){
    if (e<originalYmin){
      originalYmin = e;
    }
  }


  /*if (originalYmin < ypointmin){
    ypointmin = originalYmin;
  }*/

  if (ypointmin == 0){
    ypointmin = -(ypointmax/10);
  }
  if (ypointmax == 0){
    ypointmax = -(ypointmin/10);
  }

  int ypointmingraph = ypointmin, ypointmaxgraph = ypointmax;
  float offsety = ((abs(ypointmax)+0.0)/((abs(ypointmin)+abs(ypointmax))));
  float originy = offsety*ysetmax;
  //cout << offsety << ' ' << originy << '\n';
  
  //getting x scale
  xscale = xsetmax/(abs(xpointmax)+abs(xpointmin));
  //getting y scale
  yscale = ysetmax/(abs(ypointmax)+abs(ypointmin));


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

  //cout << originx << ' ' << originy << '\n';

  //creating text
  sf::Text ymaxtext(to_string(ypointmaxgraph), font);
  ymaxtext.setCharacterSize(10);
  ymaxtext.setFillColor(sf::Color::White);
  ymaxtext.setPosition(originx,0);
  window.draw(ymaxtext);

  sf::Text ymintext(to_string(ypointmingraph), font);
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

  for (i=0;i<y.size();i++){
    y.at(i) = y.at(i)*-1;
  }
  for (i=0;i<originalY.size();i++){
    originalY.at(i) = originalY.at(i)*-1;
  }

  //creating shape
  sf::CircleShape coord;
  coord.setRadius(2);
  coord.setFillColor(sf::Color::White);
  coord.setPosition(x.at(count)*xscale+originx,-(y.at(count)*yscale+originy));
  window.draw(coord);

  sf::CircleShape ogCoord;
  ogCoord.setRadius(2);
  ogCoord.setFillColor(sf::Color::Blue);
  ogCoord.setPosition(originalX.at(count)*xscale+originx,(originalY.at(count)*yscale+originy));
  window.draw(ogCoord);

  /*cout << (x.at(count)*xscale)+originx << ' ' << (y.at(count)*yscale)+originy << ' ';
  cout << (originalX.at(count)*xscale)+originx << ' ' << (originalY.at(count)*yscale)+originy << ' ';
  cout << originalX.at(count) << ' ' << originalY.at(count) << ' ';
  cout << x.at(count) << ' ' << y.at(count) << '\n';*/

  //running window
  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) window.close();
    }
    window.draw(ogCoord);
    if (count < x.size()-1){
      count++;
      coord.setPosition((x.at(count)*xscale)+originx,(y.at(count)*yscale)+originy);
      window.draw(coord);
      /*cout << (x.at(count)*xscale)+originx << ' ' << (y.at(count)*yscale)+originy << ' ';
      cout << (originalX.at(count)*xscale)+originx<< ' ' << (originalY.at(count)*yscale)+originy << ' ';
      cout << originalX.at(count) << ' ' << originalY.at(count) << ' ';
      cout << x.at(count) << ' ' << y.at(count) << '\n';*/
    }
    if (count2 < originalX.size()-1){
      count2++;
      ogCoord.setPosition((originalX.at(count)*xscale)+originx,(originalY.at(count)*yscale)+originy);
      window.draw(ogCoord);
    }
    window.display();
  }
}


