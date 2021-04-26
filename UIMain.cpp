#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "pemdas.cpp"
#include <iostream>
using std::cout;

bool inRange(const sf::Vector2f& loc, sf::Event::MouseButtonEvent mouse){
	return ((mouse.x-(loc.x+200))*(mouse.x-(loc.x)) <= 0 && (mouse.y-(loc.y+100))*(mouse.y-(loc.y)) <=0);
}

bool inRange(const sf::Vector2f& loc, sf::Event::MouseMoveEvent mouse){
	return ((mouse.x-(loc.x+200))*(mouse.x-(loc.x)) <= 0 && (mouse.y-(loc.y+100))*(mouse.y-(loc.y)) <=0);
}

int main(){

	sf::RenderWindow App(sf::VideoMode(1080, 1920, 24), "Calculator App");
	sf::RectangleShape Pemdas(sf::Vector2f(200, 100));
	sf::RectangleShape Graph(sf::Vector2f(200, 100));
	sf::RectangleShape Matrix(sf::Vector2f(200, 100));
	sf::RectangleShape Back(sf::Vector2f(200, 100));
	sf::Font font;
	font.loadFromFile("/System/Library/Fonts/Optima.ttc");
	sf::Text title;
	title.setString("Calculator App 1.0-beta1.1");
	title.setCharacterSize(69);
	title.setFillColor(sf::Color(0,0,0));
	title.setPosition(130, 240);
	title.setFont(font);
	sf::Text pdtext;
	pdtext.setString("Pemdas");
	pdtext.setCharacterSize(30);
	pdtext.setFillColor(sf::Color(0,0,0));
	pdtext.setPosition(100, 990);
	pdtext.setFont(font);
	sf::Text gftext;
	gftext.setString("Graph");
	gftext.setCharacterSize(30);
	gftext.setFillColor(sf::Color(0,0,0));
	gftext.setPosition(460, 990);
	gftext.setFont(font);
	sf::Text mxtext;
	mxtext.setString("Matrix");
	mxtext.setCharacterSize(30);
	mxtext.setFillColor(sf::Color(255,255,255));
	mxtext.setPosition(820, 990);
	mxtext.setFont(font);
	Pemdas.setPosition(60, 960);
	Pemdas.setFillColor(sf::Color(0,205,100));
	Graph.setPosition(420, 960);
	Graph.setFillColor(sf::Color(205,100,0));
	Matrix.setPosition(780, 960);
	Matrix.setFillColor(sf::Color(0,100,205));
	Back.setPosition(50,50);
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
	pdtitle.setFillColor(sf::Color(0,0,0));
	pdtitle.setPosition(130, 240);
	pdtitle.setFont(font);


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
  	userInputDisplay.setPosition(350,1000);
  	//creating text display
	sf::Text enterHere("Enter Here:", font);
  	enterHere.setCharacterSize(30);
	enterHere.setFillColor(sf::Color::Black);
    enterHere.setPosition(350, 1000);

	//line used to indicate you clicked on the text box
	sf::RectangleShape line;
	line.setSize(sf::Vector2f(350, 1));
	line.setFillColor(sf::Color::Black/*Transparent*/);
	//position for x is same as user input display, position for y
	//is yinit + character size + 3;
	line.setPosition(350, 1033);

	sf::Text answertxt("Answer will appear here:", font);
  	answertxt.setCharacterSize(30);
	answertxt.setFillColor(sf::Color::Black);
    answertxt.setPosition(350, 800);

	while (App.isOpen()) {
		App.clear(sf::Color::White);

		sf::Event event;
    	while (App.pollEvent(event)) {

      		if (event.type == sf::Event::Closed) App.close();

      		if (mode == 0 && event.type == sf::Event::MouseButtonPressed){
      			auto ploc = Pemdas.getPosition();
      			auto gloc = Graph.getPosition();
      			auto mloc = Matrix.getPosition();
      			if (inRange(ploc, event.mouseButton)){
      				cout << "Pemdas\n";
      				mode = 1;
      				userInput = "";
      				userInputDisplay.setString(userInput);
      				enterHere.setFillColor(sf::Color::Black);
      				answertxt.setString("Answer will appear here:");
      			}
      			if (inRange(gloc, event.mouseButton)){
      				cout << "Graph\n";
      				// mode = 2;
      			}
      			if (inRange(mloc, event.mouseButton)){
      				cout << "Matrix\n";
      				// mode = 3;
      			}
      		}

      		if (mode == 0 && event.type == sf::Event::MouseMoved){
      			auto ploc = Pemdas.getPosition();
      			auto gloc = Graph.getPosition();
      			auto mloc = Matrix.getPosition();
      			sf::Cursor hand;
      			hand.loadFromSystem(sf::Cursor::Hand);
      			sf::Cursor arrow;
      			arrow.loadFromSystem(sf::Cursor::Arrow);

      			if (inRange(ploc, event.mouseMove) || inRange(gloc, event.mouseMove) || inRange(mloc, event.mouseMove)){
      				App.setMouseCursor(hand);
      			} else {
      				App.setMouseCursor(arrow);
      			}

      			if (inRange(ploc, event.mouseMove)){
      				Pemdas.setFillColor(sf::Color((0+255)%256,(205+255)%256,(100+255)%256));
      			} else if(!inRange(ploc, event.mouseMove)) {
      				Pemdas.setFillColor(sf::Color(0,205,100));
				}
      			if (inRange(gloc, event.mouseMove)){ 
      				Graph.setFillColor(sf::Color((205+255)%256,(100+255)%256,(0+255)%256));
      			} else if (!inRange(gloc, event.mouseMove)){
      				Graph.setFillColor(sf::Color(205,100,0));
      			}
      			if (inRange(mloc, event.mouseMove)){
      				Matrix.setFillColor(sf::Color((0+255)%256,(100+255)%256,(205+255)%256));
      			} else if (!inRange(mloc, event.mouseMove)){
      				Matrix.setFillColor(sf::Color(0,100,205));
      			}

      		}

      		if (mode != 0 && event.type == sf::Event::MouseButtonPressed){
      			auto bloc = Back.getPosition();
      			if (inRange(bloc, event.mouseButton)){
      				cout << "Back\nMain Menu\n";
      				mode = 0;
      			}
      		}

      		if (mode != 0 && event.type == sf::Event::TextEntered){
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

      		if (mode != 0 && event.type == sf::Event::MouseMoved){
      			auto bloc = Back.getPosition();

      			sf::Cursor hand;
      			hand.loadFromSystem(sf::Cursor::Hand);
      			sf::Cursor arrow;
      			arrow.loadFromSystem(sf::Cursor::Arrow);

      			if (inRange(bloc, event.mouseMove)){
      				App.setMouseCursor(hand);
      				Back.setFillColor(sf::Color(225,225,225));
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


    	App.display();
	}

	return 0;
}
