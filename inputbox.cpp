#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using std::string;
using std::cout;

//first code is input box that only works if u click on it
int main(){
  //load font
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  //create windows
  sf::RenderWindow window(sf::VideoMode(500, 500), "Graph");
  window.setFramerateLimit(120);

  //a bool variable
  bool allowTyping;

  //allocate string
  string userInput;
  //user input display
  sf::Text userInputDisplay(" ", font);
  userInputDisplay.setCharacterSize(20);
  userInputDisplay.setFillColor(sf::Color::White);
  //push the input display a bit past the text display, each letter
  // is about 10 pixels
  userInputDisplay.setPosition(110,0);

  //creating text display
  sf::Text enterHere("Enter Here:", font);
  enterHere.setCharacterSize(20);
  enterHere.setFillColor(sf::Color::White);
  enterHere.setPosition(0, 0);

  //line used to indicate you clicked on the text box
  sf::RectangleShape line;
  line.setSize(sf::Vector2f(300, 1));
  line.setFillColor(sf::Color::Transparent);
  //position for x is same as user input display, position for y
  //is character size + 1;
  line.setPosition(110, 21);


  while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      //checking if the click was on the text area
      if (event.type == sf::Event::MouseButtonPressed){
        cout << event.mouseButton.y << ' ';
        //makes it so u can only type after u click on the area
        if (event.mouseButton.y > 0 && event.mouseButton.y < 20) {
          allowTyping = true;
        } else {
          allowTyping = false;
        }

      }
      //windows close clause
      if (event.type == sf::Event::Closed) window.close();
      //actual input including backspace
      if ((event.type == sf::Event::TextEntered) && allowTyping) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
          if (userInput.length() > 0) userInput.pop_back();
        } else {
          //the number here is based off ascii code
          if (event.text.unicode < 128) {
            userInput += (char)event.text.unicode;
          }
        }
    }
  }
  if (allowTyping) {
        line.setFillColor(sf::Color::White);
      } else {
        line.setFillColor(sf::Color::Transparent);
      }
  //drawing and displaying
  userInputDisplay.setString(userInput);
  window.clear();
  window.draw(line);
  window.draw(enterHere);
  window.draw(userInputDisplay);
  window.display();
}
}

//input box that works in general
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

int main(){
  //load font
  sf::Font font;
  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
  //create windows
  sf::RenderWindow window(sf::VideoMode(500, 500), "Graph");
  window.setFramerateLimit(120);

  //allocate string
  string userInput;
  sf::Text userInputDisplay(" ", font);
  userInputDisplay.setCharacterSize(20);
  userInputDisplay.setFillColor(sf::Color::White);
  userInputDisplay.setPosition(0,0);

  while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      if (event.type == sf::Event::Closed) window.close();
      //actual input including backspace
      if (event.type == sf::Event::TextEntered) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
          if (userInput.length() > 0) userInput.pop_back();
        } else {
          //the number here is based off ascii code
          if (event.text.unicode < 128) {
            userInput += (char)event.text.unicode;
          }
        }
    }
  }
  //drawing and displaying
  userInputDisplay.setString(userInput);
  window.clear();
  window.draw(userInputDisplay);
  window.display();
}
}