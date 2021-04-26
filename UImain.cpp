#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "pemdas.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include "Best_Fit.h"
using std::cout;
using std::vector;
using std::pow;
using std::to_string;
using std::string;
using std::fstream;
using std::getline;

bool inRange(const sf::Vector2f& loc, sf::Event::MouseButtonEvent mouse) {
  return ((mouse.x - (loc.x + 200)) * (mouse.x - (loc.x)) <= 0 && (mouse.y - (loc.y + 100)) * (mouse.y - (loc.y)) <= 0);
}

bool inRange(const sf::Vector2f& loc, sf::Event::MouseMoveEvent mouse) {
  return ((mouse.x - (loc.x + 200)) * (mouse.x - (loc.x)) <= 0 && (mouse.y - (loc.y + 100)) * (mouse.y - (loc.y)) <= 0);
}

bool fileExist(string filename) {
  if (FILE *file = fopen(filename.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

float makeAbsolute(float num){
  if (num < 0){
    return num*-1;
  } else {
    return num*1;
  }
}

void plot(float xpointmin, float xpointmax, string filename, string lobftype){

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

int main() {
  sf::RenderWindow App(sf::VideoMode(1080, 900, 24), "Calculator App");
  sf::RectangleShape Pemdas(sf::Vector2f(200, 100));
  sf::RectangleShape Graph(sf::Vector2f(200, 100));
  sf::RectangleShape Matrix(sf::Vector2f(200, 100));
  sf::RectangleShape Back(sf::Vector2f(200, 100));
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  sf::Text title;
  title.setString("Calculator App 1.0-beta1.1");
  title.setCharacterSize(69);
  title.setFillColor(sf::Color(0, 0, 0));
  title.setPosition(130, 240);
  title.setFont(font);
  sf::Text pdtext;
  pdtext.setString("Pemdas");
  pdtext.setCharacterSize(30);
  pdtext.setFillColor(sf::Color(0, 0, 0));
  pdtext.setPosition(100, 690);
  pdtext.setFont(font);
  sf::Text gftext;
  gftext.setString("Graph");
  gftext.setCharacterSize(30);
  gftext.setFillColor(sf::Color(0, 0, 0));
  gftext.setPosition(460, 690);
  gftext.setFont(font);
  sf::Text mxtext;
  mxtext.setString("Matrix");
  mxtext.setCharacterSize(30);
  mxtext.setFillColor(sf::Color(255, 255, 255));
  mxtext.setPosition(820, 690);
  mxtext.setFont(font);
  Pemdas.setPosition(60, 660);
  Pemdas.setFillColor(sf::Color(0, 205, 100));
  Graph.setPosition(420, 660);
  Graph.setFillColor(sf::Color(205, 100, 0));
  Matrix.setPosition(780, 660);
  Matrix.setFillColor(sf::Color(0, 100, 205));
  Back.setPosition(50, 50);
  Back.setFillColor(sf::Color::Black);
  sf::Text backtext;
  backtext.setString("<-- Back");
  backtext.setCharacterSize(30);
  backtext.setFillColor(sf::Color::White);
  backtext.setPosition(80, 80);
  backtext.setFont(font);
  sf::Text pdtitle;
  pdtitle.setString("Pemdas Mode");
  pdtitle.setCharacterSize(69);
  pdtitle.setFillColor(sf::Color(0, 0, 0));
  pdtitle.setPosition(130, 240);
  pdtitle.setFont(font);

  //graphing
  bool mintextinputallow = false;
  bool maxtextinputallow = false;
  bool filetextinputallow = false;
  bool choiceinputallow = false;
  bool queryFilled = true;

  string terminaltext = " ";
  sf::Text terminal(terminaltext, font);
  terminal.setCharacterSize(20);
  terminal.setStyle(sf::Text::Bold);
  terminal.setFillColor(sf::Color::Red);
  terminal.setPosition(250 - terminaltext.size() * 5, 490);

  //creating text display
  sf::Text userTextxpointmin(" ", font);
  string userInputxpointmin = "-10";
  userTextxpointmin.setCharacterSize(20);
  userTextxpointmin.setFillColor(sf::Color::Black);
  userTextxpointmin.setPosition(135, 170);

  sf::Text userTextxpointmax(" ", font);
  string userInputxpointmax = "10";
  userTextxpointmax.setCharacterSize(20);
  userTextxpointmax.setFillColor(sf::Color::Black);
  userTextxpointmax.setPosition(140, 250);

  sf::Text userTextfile(" ", font);
  string userInputfile = "data.csv";
  userTextfile.setCharacterSize(20);
  userTextfile.setFillColor(sf::Color::Black);
  userTextfile.setPosition(130, 330);

  sf::Text userTextchoice(" ", font);
  string userInputchoice = "none";
  userTextchoice.setCharacterSize(20);
  userTextchoice.setFillColor(sf::Color::Black);
  userTextchoice.setPosition(225, 410); //COME BACK HERE

  //Text
  sf::Text xpointmintext("X-PointMin:", font);
  xpointmintext.setCharacterSize(20);
  xpointmintext.setFillColor(sf::Color::Black);
  xpointmintext.setPosition(20, 170);

  sf::Text xpointmaxtext("X-PointMax:", font);
  xpointmaxtext.setCharacterSize(20);
  xpointmaxtext.setFillColor(sf::Color::Black);
  xpointmaxtext.setPosition(20, 250);

  sf::Text filetext("File Name:", font);
  filetext.setCharacterSize(20);
  filetext.setFillColor(sf::Color::Black);
  filetext.setPosition(20, 330);

  sf::Text choicetext("Line of Best Fit Type:", font);
  choicetext.setCharacterSize(20);
  choicetext.setFillColor(sf::Color::Black);
  choicetext.setPosition(20, 410); //COME BACK HERE

  //submit buttom
  sf::RectangleShape button;
  button.setSize(sf::Vector2f(100, 40));
  button.setFillColor(sf::Color::Transparent);
  button.setOutlineColor(sf::Color::Black);
  button.setOutlineThickness(1);
  button.setPosition(200, 580);
  sf::Text submit("Submit", font);
  submit.setCharacterSize(20);
  submit.setFillColor(sf::Color::Black);
  submit.setStyle(sf::Text::Bold);
  submit.setPosition(214, 588);

  //lines
  sf::RectangleShape xpointminline;
  xpointminline.setSize(sf::Vector2f(300, 1));
  xpointminline.setFillColor(sf::Color::Transparent);
  xpointminline.setPosition(135, 191);

  sf::RectangleShape xpointmaxline;
  xpointmaxline.setSize(sf::Vector2f(300, 1));
  xpointmaxline.setFillColor(sf::Color::Transparent);
  xpointmaxline.setPosition(140, 271);

  sf::RectangleShape filenameline;
  filenameline.setSize(sf::Vector2f(300, 1));
  filenameline.setFillColor(sf::Color::Transparent);
  filenameline.setPosition(130, 351);

  sf::RectangleShape choiceline;
  choiceline.setSize(sf::Vector2f(300, 1));
  choiceline.setFillColor(sf::Color::Transparent);
  choiceline.setPosition(225, 431); //COME BACK HERE


  int mode = 0; // 0 = Menu, 1 = Pemdas, 2 = Graph, 3 = Calculator

  cout << "Current Directory: Main Menu\n";

  //allocate string
  string userInput = "";
  //user input display
  sf::Text userInputDisplay(" ", font);
  userInputDisplay.setCharacterSize(30);
  userInputDisplay.setFillColor(sf::Color::Black);
  //push the input display a bit past the text display, each letter
  // is about 10 pixels
  userInputDisplay.setPosition(350, 500);
  //creating text display
  sf::Text enterHere("Enter Here:", font);
  enterHere.setCharacterSize(30);
  enterHere.setFillColor(sf::Color::Black);
  enterHere.setPosition(350, 500);

  //line used to indicate you clicked on the text box
  sf::RectangleShape line;
  line.setSize(sf::Vector2f(350, 1));
  line.setFillColor(sf::Color::Black/*Transparent*/);
  //position for x is same as user input display, position for y
  //is yinit + character size + 3;
  line.setPosition(350, 533);

  sf::Text answertxt("Answer will appear here:", font);
  answertxt.setCharacterSize(30);
  answertxt.setFillColor(sf::Color::Black);
  answertxt.setPosition(350, 800);

  while (App.isOpen()) {
    App.clear(sf::Color::White);

    sf::Event event;
    while (App.pollEvent(event)) {
      if (mode == 2){
        if (event.type == sf::Event::MouseButtonPressed) {
        if ((event.mouseButton.x > 200 && event.mouseButton.x < 300) && queryFilled) {
          if (event.mouseButton.y < 620 && event.mouseButton.y > 580) {
            if (fileExist(userInputfile)) {
              if (stof(userInputxpointmin) < stof(userInputxpointmax)) {
                plot(stof(userInputxpointmin), stof(userInputxpointmax), userInputfile, userInputchoice);
                terminaltext = " ";
              } else {
                terminaltext = "X-min should be smaller than X-max";
              }
            }
          }
        }
        if (event.mouseButton.y > 170 && event.mouseButton.y < 190) {
          mintextinputallow = true;
        } else {
          mintextinputallow = false;
        }
        if (event.mouseButton.y > 250 && event.mouseButton.y < 270) {
          maxtextinputallow = true;
        } else {
          maxtextinputallow = false;
        }
        if (event.mouseButton.y > 330 && event.mouseButton.y < 350) {
          filetextinputallow = true;
        } else {
          filetextinputallow = false;
        }
        if (event.mouseButton.y > 410 && event.mouseButton.y < 430) {
          choiceinputallow = true;
        } else {
          choiceinputallow = false;
        }
      }
      if (mintextinputallow) {
        xpointminline.setFillColor(sf::Color::Black);
      } else {
        xpointminline.setFillColor(sf::Color::Transparent);
      }
      if (maxtextinputallow) {
        xpointmaxline.setFillColor(sf::Color::Black);
      } else {
        xpointmaxline.setFillColor(sf::Color::Transparent);
      }
      if (filetextinputallow) {
        filenameline.setFillColor(sf::Color::Black);
      } else {
        filenameline.setFillColor(sf::Color::Transparent);
      }
      if (choiceinputallow) {
        choiceline.setFillColor(sf::Color::Black);
      } else {
        choiceline.setFillColor(sf::Color::Transparent);
      }
      if (event.type == sf::Event::TextEntered && mintextinputallow) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
          if (userInputxpointmin.length() > 0) userInputxpointmin.pop_back();
        } else {
          if ((event.text.unicode < 58 && event.text.unicode > 47) || (event.text.unicode == 45)) {
            userInputxpointmin += (char)event.text.unicode;
          }
        }
        if (userInputxpointmin.length() == 0) {
          queryFilled = false;
          terminaltext = "Query should not be empty";
        } else {
          terminaltext = " ";
          queryFilled = true;
        }
        if (userInputxpointmin.length()>6){
          queryFilled = false;
          terminaltext = "Query length should not exceed 6 including '-'";
        }
      }
      if (event.type == sf::Event::TextEntered && maxtextinputallow) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
          if (userInputxpointmax.length() > 0) userInputxpointmax.pop_back();
        } else {
          if ((event.text.unicode < 58 && event.text.unicode > 47) || (event.text.unicode == 45)) {
            userInputxpointmax += (char)event.text.unicode;
          }
        }
        if (userInputxpointmax.length() == 0) {
          queryFilled = false;
          terminaltext = "Query should not be empty";
        } else {
          terminaltext = " ";
          queryFilled = true;
        }
        if (userInputxpointmax.length()>6){
          queryFilled = false;
          terminaltext = "Query length should not exceed 6 including '-'";
        }
      }
      if (event.type == sf::Event::TextEntered && filetextinputallow) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
          if (userInputfile.length() > 0) userInputfile.pop_back();
        } else {
          if (event.text.unicode < 128) {
            userInputfile += (char)event.text.unicode;
          }
        }
        if (userInputfile.length() == 0) {
          queryFilled = false;
          terminaltext = "Query should not be empty";
        } else {
          terminaltext = " ";
          queryFilled = true;
        }
      }
      if (event.type == sf::Event::TextEntered && choiceinputallow) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
          if (userInputchoice.length() > 0) userInputchoice.pop_back();
        } else {
          if (event.text.unicode < 128) {
            userInputchoice += (char)event.text.unicode;
          }
        }
        if (userInputchoice.length() == 0) {
          queryFilled = false;
          terminaltext = "Query should not be empty";
        } else {
          terminaltext = " ";
          queryFilled = true;
        }
      }
      std::transform(userInputchoice.begin(), userInputchoice.end(), userInputchoice.begin(),
        [](unsigned char c){ return tolower(c); });
      if (userInputchoice != "linear"){
        if (userInputchoice != "exponential"){
          if (userInputchoice != "none"){
            terminaltext = "LoBF must be linear, exponential, or none";
            queryFilled = false;
          }
        }
      }
    }
    if (fileExist(userInputfile) == false) {
      terminaltext = "File does not exist";
      }

      if (event.type == sf::Event::Closed) App.close();

      if (mode == 0 && event.type == sf::Event::MouseButtonPressed) {
        auto ploc = Pemdas.getPosition();
        auto gloc = Graph.getPosition();
        auto mloc = Matrix.getPosition();
        if (inRange(ploc, event.mouseButton)) {
          cout << "Pemdas\n";
          mode = 1;
          userInput = "";
          userInputDisplay.setString(userInput);
          enterHere.setFillColor(sf::Color::Black);
          answertxt.setString("Answer will appear here:");
        }
        if (inRange(gloc, event.mouseButton)) {
          cout << "Graph\n";
          mode = 2;
        }
        if (inRange(mloc, event.mouseButton)) {
          cout << "Matrix\n";
          // mode = 3;
        }
      }

      if (mode == 0 && event.type == sf::Event::MouseMoved) {
        auto ploc = Pemdas.getPosition();
        auto gloc = Graph.getPosition();
        auto mloc = Matrix.getPosition();
        sf::Cursor hand;
        hand.loadFromSystem(sf::Cursor::Hand);
        sf::Cursor arrow;
        arrow.loadFromSystem(sf::Cursor::Arrow);

        if (inRange(ploc, event.mouseMove) || inRange(gloc, event.mouseMove) || inRange(mloc, event.mouseMove)) {
          App.setMouseCursor(hand);
        } else {
          App.setMouseCursor(arrow);
        }

        if (inRange(ploc, event.mouseMove)) {
          Pemdas.setFillColor(sf::Color((0 + 255) % 256, (205 + 255) % 256, (100 + 255) % 256));
        } else if(!inRange(ploc, event.mouseMove)) {
          Pemdas.setFillColor(sf::Color(0, 205, 100));
        }
        if (inRange(gloc, event.mouseMove)) {
          Graph.setFillColor(sf::Color((205 + 255) % 256, (100 + 255) % 256, (0 + 255) % 256));
        } else if (!inRange(gloc, event.mouseMove)) {
          Graph.setFillColor(sf::Color(205, 100, 0));
        }
        if (inRange(mloc, event.mouseMove)) {
          Matrix.setFillColor(sf::Color((0 + 255) % 256, (100 + 255) % 256, (205 + 255) % 256));
        } else if (!inRange(mloc, event.mouseMove)) {
          Matrix.setFillColor(sf::Color(0, 100, 205));
        }

      }

      if (mode != 0 && event.type == sf::Event::MouseButtonPressed) {
        auto bloc = Back.getPosition();
        if (inRange(bloc, event.mouseButton)) {
          cout << "Back\nMain Menu\n";
          mode = 0;
        }
      }

      if (mode != 0 && event.type == sf::Event::TextEntered) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
          if (userInput.length() > 0) {
            userInput.pop_back();
            userInputDisplay.setString(userInput);
            cout << userInput << "\n";
            enterHere.setFillColor(sf::Color::Transparent);
          } else {
            enterHere.setFillColor(sf::Color::Black);
            userInputDisplay.setString(" ");
          }
        } else {
          //the number here is based off ascii code
          char in = (char)event.text.unicode;
          // cout << in << "\n";
          if (event.text.unicode < 128 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) userInput.push_back(in);
          cout << userInput << "\n";
          userInputDisplay.setString(userInput);
        }

        if (userInput.length() > 0) {
          enterHere.setFillColor(sf::Color::Transparent);
        } else {
          enterHere.setFillColor(sf::Color::Black);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
          string answer = eval(userInput);
          cout << answer << "\n";
          userInput = "";
          userInputDisplay.setString(userInput);
          answertxt.setString(answer);
        }

      }

      if (mode != 0 && event.type == sf::Event::MouseMoved) {
        auto bloc = Back.getPosition();

        sf::Cursor hand;
        hand.loadFromSystem(sf::Cursor::Hand);
        sf::Cursor arrow;
        arrow.loadFromSystem(sf::Cursor::Arrow);

        if (inRange(bloc, event.mouseMove)) {
          App.setMouseCursor(hand);
          Back.setFillColor(sf::Color(225, 225, 225));
          backtext.setFillColor(sf::Color::Black);
        } else {
          App.setMouseCursor(arrow);
          Back.setFillColor(sf::Color::Black);
          backtext.setFillColor(sf::Color::White);
        }
      }
    }

      // cout << eval("44*44/44") << "\n";

      if (mode == 0) {
        App.draw(Pemdas);
        App.draw(Graph);
        App.draw(Matrix);
        App.draw(title);
        App.draw(pdtext);
        App.draw(gftext);
        App.draw(mxtext);
      }
      if (mode == 1) {
        App.draw(Back);
        App.draw(backtext);
        App.draw(pdtitle);
        App.draw(userInputDisplay);
        App.draw(enterHere);
        App.draw(answertxt);
        App.draw(line);
      }
      if (mode == 2) {
        terminal.setPosition(250 - terminaltext.size() * 5, 490);
        terminal.setString(terminaltext);
        userTextxpointmin.setString(userInputxpointmin);
        userTextxpointmax.setString(userInputxpointmax);
        userTextchoice.setString(userInputchoice);
        userTextfile.setString(userInputfile);
        App.clear(sf::Color::White);
        App.draw(choiceline);
        App.draw(choicetext);
        App.draw(userTextchoice);
        App.draw(Back);
        App.draw(backtext);
        App.draw(terminal);
        App.draw(xpointmintext);
        App.draw(xpointmaxtext);
        App.draw(submit);
        App.draw(userTextfile);
        App.draw(filetext);
        App.draw(userTextxpointmin);
        App.draw(userTextxpointmax);
        App.draw(xpointminline);
        App.draw(xpointmaxline);
        App.draw(filenameline);
        App.draw(button);
      }
      App.display();
    }
  return 0;
}