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