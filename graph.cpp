#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include "Best_Fit.h"
using std::vector;
using std::pow;
using std::cout;
using std::to_string;
using std::string;
using std::fstream;
using std::getline;



float makeAbsolute(float num){
  if (num < 0){
    return num*-1;
  } else {
    return num*1;
  }
}

int main(){
  float xpointmin=-10, xpointmax=20; 
  string filename = "data.csv";
  string lobftype = "linear";

  std::transform(lobftype.begin(), lobftype.end(), lobftype.begin(),
    [](unsigned char c){ return tolower(c); });

  //reading a file
  fstream myfile;
  vector <string> filereader;
  string s;
  //values that are not interchangable
  vector <double> lineOfFit;
  float ysetmax = 500, xsetmax = 500;
  float ypointmin, ypointmax;
  vector <float> x,y;
  vector <float> originalX, originalY;
  vector <double> originalXdouble, originalYdouble;
  float yscale, xscale, originalYmax, originalYmin;
  int i,j, placeholder, deviation, count = 0, count2=0;
  int xpointmaxgraph = xpointmax, xpointmingraph = xpointmin;
  float offsetx = ((makeAbsolute(xpointmin)+0.0)/(makeAbsolute(xpointmin)+makeAbsolute(xpointmax)));
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
        originalXdouble.push_back(stod(s));
        s.clear();
        for (j=i+1;j<e.length();j++){
          s.push_back(e.at(j));
        }
        originalY.push_back(stof(s));
        originalYdouble.push_back(stod(s));
      }
    }
  }
  //getting x-negative values
  for (i=0;i<mak)

  for (i=0;i<=makeAbsolute(xpointmax)+makeAbsolute(xpointmin);i++){
    x.push_back(i+xpointmin);
  }

  //getting y values
  if (lobftype == "linear"){
    Linear_Fit LbF(originalXdouble,originalYdouble);
    for (auto e:x){
    y.push_back(LbF.x.at(0)*e+LbF.x.at(1));
  }
  }
  if (lobftype == "exponential"){
    Exponential_Fit EbF(originalXdouble,originalYdouble);
    float e = 2.71828;
    for (auto t:x){
      y.push_back((pow(e,EbF.k*t))*EbF.N);
    }
  }
  if (lobftype == "none"){
    for (auto e:x){
      y.push_back(originalY.at(0));
    }
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
  if (originalYmax > ypointmax){
    ypointmax = originalYmax;
  }

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

  //cout << ypointmax << ' ' << makeAbsolute(ypointmax) << ' ' << makeAbsolute(ypointmin)/10 << '\n';
  if (makeAbsolute(ypointmin) < makeAbsolute(ypointmax)/10){
    ypointmin = -(ypointmax/10);
  }
  if (makeAbsolute(ypointmax) < makeAbsolute(ypointmin)/10){
    ypointmax = -(ypointmin/10);
  }
  //cout << ypointmax << '\n';

  float offsety = ((makeAbsolute(ypointmax)+0.0)/((makeAbsolute(ypointmin)+makeAbsolute(ypointmax))));
  float originy = offsety*ysetmax;
  //cout << offsety << ' ' << originy << '\n';
  
  //getting x scale
  xscale = xsetmax/(makeAbsolute(xpointmax)+makeAbsolute(xpointmin));
  //getting y scale
  yscale = ysetmax/(makeAbsolute(ypointmax)+makeAbsolute(ypointmin));

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
  coord.setPosition(x.at(count)*xscale+originx-2,-(y.at(count)*yscale+originy-2));
  window.draw(coord);
  if (lobftype == "none"){
    coord.setFillColor(sf::Color::Transparent);
  }

  sf::CircleShape ogCoord;
  ogCoord.setRadius(2);
  ogCoord.setFillColor(sf::Color::Blue);
  ogCoord.setPosition(originalX.at(count)*xscale+originx-2,(originalY.at(count)*yscale+originy-2));
  window.draw(ogCoord);

  //cout << (x.at(count)*xscale)+originx << ' ' << (y.at(count)*yscale)+originy << ' ';
  //cout << (originalX.at(count)*xscale)+originx << ' ' << (originalY.at(count)*yscale)+originy << ' ';
  //cout << originalX.at(count) << ' ' << originalY.at(count) << ' ';
  //cout << x.at(count) << ' ' << y.at(count) << '\n';

  //running window
  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) window.close();
    }
    window.draw(ogCoord);
    if (count < x.size()-1){
      count++;
      coord.setPosition((x.at(count)*xscale)+originx-2,(y.at(count)*yscale)+originy-2);
      window.draw(coord);
      //cout << (x.at(count)*xscale)+originx << ' ' << (y.at(count)*yscale)+originy << ' ';
      //cout << (originalX.at(count)*xscale)+originx<< ' ' << (originalY.at(count)*yscale)+originy << ' ';
      //cout << originalX.at(count) << ' ' << originalY.at(count) << ' ';
      //cout << x.at(count) << ' ' << y.at(count) << '\n';
    }
    if (count2 < originalX.size()-1){
      count2++;
      ogCoord.setPosition((originalX.at(count)*xscale)+originx-2,(originalY.at(count)*yscale)+originy-2);
      window.draw(ogCoord);
    }
    window.display();
  }
}


