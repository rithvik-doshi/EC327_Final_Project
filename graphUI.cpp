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

bool fileExist(string filename) {
  if (FILE *file = fopen(filename.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

void plot(float xpointmin, float xpointmax, string filename) {

  //values that are interchangable
  float ysetmax = 500, xsetmax = 500;
  float ypointmin, ypointmax;

  //reading a file
  fstream myfile;
  vector <string> filereader;
  string s;

  //values that are not interchangable
  vector <int> x, y;
  vector <float> originalX, originalY;
  float yscale, xscale, originalYmax, originalYmin;
  int i, j, placeholder, deviation, count = 0, count2 = 0;
  int xpointmaxgraph = xpointmax, xpointmingraph = xpointmin;
  float offsetx = ((abs(xpointmin) + 0.0) / (abs(xpointmin) + abs(xpointmax)));
  float originx = offsetx * xsetmax;

  myfile.open(filename);
  while (getline(myfile, s)) {
    filereader.push_back(s);
  }
  for (auto e : filereader) {
    for (i = 0; i < e.length(); i++) {
      if (e.at(i) == ',') {
        s.clear();
        for (j = 0; j < i; j++) {
          s.push_back(e.at(j));
        }
        originalX.push_back(stoi(s));
        s.clear();
        for (j = i + 1; j < e.length(); j++) {
          s.push_back(e.at(j));
        }
        originalY.push_back(stof(s));
      }
    }
  }

  //getting x-negative values
  for (i = 0; i <= xpointmax - xpointmin; i++) {
    x.push_back(i + xpointmin);
  }

  //getting y values

  for (auto e : x) {
    y.push_back(pow(e, 2));
  }


  //getting max y
  ypointmax = y.at(0);
  for (auto e : y) {
    if (e > ypointmax) {
      ypointmax = e;
    }
  }
  originalYmax = originalY.at(0);
  for (auto e : originalY) {
    if (e > originalYmax) {
      originalYmax = e;
    }
  }
  /*if (originalYmax > ypointmax){
    ypointmax = originalYmax;
  }*/

  //getting min y

  ypointmin = y.at(0);
  for (auto e : y) {
    if (e < ypointmin) {
      ypointmin = e;
    }
  }
  originalYmin = originalY.at(0);
  for (auto e : originalY) {
    if (e < originalYmin) {
      originalYmin = e;
    }
  }


  /*if (originalYmin < ypointmin){
    ypointmin = originalYmin;
  }*/

  if (ypointmin == 0) {
    ypointmin = -(ypointmax / 10);
  }
  if (ypointmax == 0) {
    ypointmax = -(ypointmin / 10);
  }

  int ypointmingraph = ypointmin, ypointmaxgraph = ypointmax;
  float offsety = ((abs(ypointmax) + 0.0) / ((abs(ypointmin) + abs(ypointmax))));
  float originy = offsety * ysetmax;
  //cout << offsety << ' ' << originy << '\n';

  //getting x scale
  xscale = xsetmax / (abs(xpointmax) + abs(xpointmin));
  //getting y scale
  yscale = ysetmax / (abs(ypointmax) + abs(ypointmin));


  sf::RenderWindow window(sf::VideoMode(xsetmax, ysetmax), "Graph");
  window.setFramerateLimit(120);

  //creating axis
  sf::RectangleShape xaxis;
  xaxis.setSize(sf::Vector2f(xsetmax, 1));
  xaxis.setOutlineColor(sf::Color::White);
  xaxis.setPosition(0, originy);
  window.draw(xaxis);

  sf::RectangleShape yaxis;
  yaxis.setSize(sf::Vector2f(1, ysetmax));
  yaxis.setOutlineColor(sf::Color::White);
  yaxis.setPosition(originx, 0);
  window.draw(yaxis);

  //creating font
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");

  //cout << originx << ' ' << originy << '\n';

  //creating text
  sf::Text ymaxtext(to_string(ypointmaxgraph), font);
  ymaxtext.setCharacterSize(10);
  ymaxtext.setFillColor(sf::Color::White);
  ymaxtext.setPosition(originx, 0);
  window.draw(ymaxtext);

  sf::Text ymintext(to_string(ypointmingraph), font);
  ymintext.setCharacterSize(10);
  ymintext.setFillColor(sf::Color::White);
  ymintext.setPosition(originx, ysetmax - 10);
  window.draw(ymintext);

  string xpointmax_s = to_string(xpointmaxgraph);
  deviation = xpointmax_s.length() * 6;
  sf::Text xmaxtext(to_string(xpointmaxgraph), font);
  xmaxtext.setCharacterSize(10);
  xmaxtext.setFillColor(sf::Color::White);
  xmaxtext.setPosition(xsetmax - deviation, originy);
  window.draw(xmaxtext);

  sf::Text xmintext(to_string(xpointmingraph), font);
  xmintext.setCharacterSize(10);
  xmintext.setFillColor(sf::Color::White);
  xmintext.setPosition(0, originy);
  window.draw(xmintext);

  for (i = 0; i < y.size(); i++) {
    y.at(i) = y.at(i) * -1;
  }
  for (i = 0; i < originalY.size(); i++) {
    originalY.at(i) = originalY.at(i) * -1;
  }

  //creating shape
  sf::CircleShape coord;
  coord.setRadius(2);
  coord.setFillColor(sf::Color::White);
  coord.setPosition(x.at(count)*xscale + originx, -(y.at(count)*yscale + originy));
  window.draw(coord);

  sf::CircleShape ogCoord;
  ogCoord.setRadius(2);
  ogCoord.setFillColor(sf::Color::Blue);
  ogCoord.setPosition(originalX.at(count)*xscale + originx, (originalY.at(count)*yscale + originy));
  window.draw(ogCoord);

  /*cout << (x.at(count)*xscale)+originx << ' ' << (y.at(count)*yscale)+originy << ' ';
  cout << (originalX.at(count)*xscale)+originx << ' ' << (originalY.at(count)*yscale)+originy << ' ';
  cout << originalX.at(count) << ' ' << originalY.at(count) << ' ';
  cout << x.at(count) << ' ' << y.at(count) << '\n';*/

  //running window
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.draw(ogCoord);
    if (count < x.size() - 1) {
      count++;
      coord.setPosition((x.at(count)*xscale) + originx, (y.at(count)*yscale) + originy);
      window.draw(coord);
      /*cout << (x.at(count)*xscale)+originx << ' ' << (y.at(count)*yscale)+originy << ' ';
      cout << (originalX.at(count)*xscale)+originx<< ' ' << (originalY.at(count)*yscale)+originy << ' ';
      cout << originalX.at(count) << ' ' << originalY.at(count) << ' ';
      cout << x.at(count) << ' ' << y.at(count) << '\n';*/
    }
    if (count2 < originalX.size() - 1) {
      count2++;
      ogCoord.setPosition((originalX.at(count)*xscale) + originx, (originalY.at(count)*yscale) + originy);
      window.draw(ogCoord);
    }
    window.display();
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(500, 500), "Graph");
  window.setFramerateLimit(120);

  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  bool mintextinputallow = false;
  bool maxtextinputallow = false;
  bool filetextinputallow = false;
  bool queryFilled = true;

  string terminaltext = " ";
  sf::Text terminal(terminaltext, font);
  terminal.setCharacterSize(20);
  terminal.setStyle(sf::Text::Bold);
  terminal.setFillColor(sf::Color::Red);
  terminal.setPosition(250 - terminaltext.size() * 5, 310);

  //creating text display
  sf::Text userTextxpointmin(" ", font);
  string userInputxpointmin = "-10";
  userTextxpointmin.setCharacterSize(20);
  userTextxpointmin.setFillColor(sf::Color::Black);
  userTextxpointmin.setPosition(135, 70);

  sf::Text userTextxpointmax(" ", font);
  string userInputxpointmax = "10";
  userTextxpointmax.setCharacterSize(20);
  userTextxpointmax.setFillColor(sf::Color::Black);
  userTextxpointmax.setPosition(140, 150);

  sf::Text userTextfile(" ", font);
  string userInputfile = "data.csv";
  userTextfile.setCharacterSize(20);
  userTextfile.setFillColor(sf::Color::Black);
  userTextfile.setPosition(125, 230);

  //Text
  sf::Text xpointmintext("X-PointMin:", font);
  xpointmintext.setCharacterSize(20);
  xpointmintext.setFillColor(sf::Color::Black);
  xpointmintext.setPosition(20, 70);

  sf::Text xpointmaxtext("X-PointMax:", font);
  xpointmaxtext.setCharacterSize(20);
  xpointmaxtext.setFillColor(sf::Color::Black);
  xpointmaxtext.setPosition(20, 150);

  sf::Text filetext("File Name:", font);
  filetext.setCharacterSize(20);
  filetext.setFillColor(sf::Color::Black);
  filetext.setPosition(20, 230);

  //submit buttom
  sf::RectangleShape button;
  button.setSize(sf::Vector2f(100, 40));
  button.setFillColor(sf::Color::Transparent);
  button.setOutlineColor(sf::Color::Black);
  button.setOutlineThickness(1);
  button.setPosition(200, 400);
  sf::Text submit("Submit", font);
  submit.setCharacterSize(20);
  submit.setFillColor(sf::Color::Black);
  submit.setStyle(sf::Text::Bold);
  submit.setPosition(214, 408);

  //lines
  sf::RectangleShape xpointminline;
  xpointminline.setSize(sf::Vector2f(300, 1));
  xpointminline.setFillColor(sf::Color::Transparent);
  xpointminline.setPosition(135, 91);

  sf::RectangleShape xpointmaxline;
  xpointmaxline.setSize(sf::Vector2f(300, 1));
  xpointmaxline.setFillColor(sf::Color::Transparent);
  xpointmaxline.setPosition(140, 171);

  sf::RectangleShape filenameline;
  filenameline.setSize(sf::Vector2f(300, 1));
  filenameline.setFillColor(sf::Color::Transparent);
  filenameline.setPosition(125, 251);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::MouseButtonPressed) {
        if ((event.mouseButton.x > 200 && event.mouseButton.x < 300) && queryFilled) {
          if (event.mouseButton.y < 440 && event.mouseButton.y > 400) {
            if (fileExist(userInputfile)) {
              if (stof(userInputxpointmin) < stof(userInputxpointmax)) {
                plot(stof(userInputxpointmin), stof(userInputxpointmax), userInputfile);
                terminaltext = " ";
              } else {
                terminaltext = "X-min should be smaller than X-max";
              }
            }
          }
        }
        if (event.mouseButton.y > 70 && event.mouseButton.y < 90) {
          mintextinputallow = true;
        } else {
          mintextinputallow = false;
        }
        if (event.mouseButton.y > 150 && event.mouseButton.y < 170) {
          maxtextinputallow = true;
        } else {
          maxtextinputallow = false;
        }
        if (event.mouseButton.y > 230 && event.mouseButton.y < 250) {
          filetextinputallow = true;
        } else {
          filetextinputallow = false;
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
      if (event.type == sf::Event::Closed) window.close();
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
    }
    if (fileExist(userInputfile) == false) {
      terminaltext = "File does not exist";
    }
    terminal.setPosition(250 - terminaltext.size() * 5, 310);
    terminal.setString(terminaltext);
    userTextxpointmin.setString(userInputxpointmin);
    userTextxpointmax.setString(userInputxpointmax);
    userTextfile.setString(userInputfile);
    window.clear(sf::Color::White);
    window.draw(terminal);
    window.draw(xpointmintext);
    window.draw(xpointmaxtext);
    window.draw(submit);
    window.draw(userTextfile);
    window.draw(filetext);
    window.draw(userTextxpointmin);
    window.draw(userTextxpointmax);
    window.draw(xpointminline);
    window.draw(xpointmaxline);
    window.draw(filenameline);
    window.draw(button);
    window.display();
  }
}

