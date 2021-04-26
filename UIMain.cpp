#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "pemdas.cpp"
#include <iostream>
using std::cout;

bool inRange(const sf::Vector2f& loc, sf::Event::MouseButtonEvent mouse){
	return ((mouse.x-(loc.x+200))*(mouse.x-(loc.x)) <= 0 && (mouse.y-(loc.y+100))*(mouse.y-(loc.y)) <=0);
}

int main(){

	sf::RenderWindow App(sf::VideoMode(1080, 1920, 24), "Calculator App");
	sf::RectangleShape Pemdas(sf::Vector2f(200, 100));
	sf::RectangleShape Graph(sf::Vector2f(200, 100));
	sf::RectangleShape Matrix(sf::Vector2f(200, 100));
	sf::Text title;
	sf::Font font;
	font.loadFromFile("/System/Library/Fonts/Optima.ttc");
	title.setString("Calculator App 1.0-beta1.1");
	title.setCharacterSize(69);
	title.setFillColor(sf::Color(0,0,0));
	title.setPosition(130, 240);
	title.setFont(font);
	Pemdas.setPosition(60, 960);
	Pemdas.setFillColor(sf::Color(0,205,100));
	Graph.setPosition(420, 960);
	Graph.setFillColor(sf::Color(205,100,0));
	Matrix.setPosition(780, 960);
	Matrix.setFillColor(sf::Color(0,100,205));

	while (App.isOpen()) {
		App.clear(sf::Color::White);

		sf::Event event;
    	while (App.pollEvent(event)) {
      		if (event.type == sf::Event::Closed) App.close();
      		if (event.type == sf::Event::MouseButtonPressed){
      			auto ploc = Pemdas.getPosition();
      			auto gloc = Graph.getPosition();
      			auto mloc = Matrix.getPosition();
      			if (inRange(ploc, event.mouseButton)) cout << "Pemdas" << "\n";
      			if (inRange(gloc, event.mouseButton)) cout << "Graph" << "\n";
      			if (inRange(mloc, event.mouseButton)) cout << "Matrix" << "\n";
      		}
    	}

		// cout << eval("44*44/44") << "\n";

    	App.draw(Pemdas);
    	App.draw(Graph);
    	App.draw(Matrix);
    	App.draw(title);
    	App.display();
	}

	return 0;
}