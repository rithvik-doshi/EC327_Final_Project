pemdas: pemdas.cpp
	g++ pemdas.cpp -o pemdas -g
uimain: UIMain.cpp
	g++ UIMain.cpp -o uimain -lsfml-graphics -lsfml-window -lsfml-system