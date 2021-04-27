pemdas: pemdas.cpp
	g++ pemdas.cpp -o pemdas -g
uimain1: UIMain_v1.cpp
	g++ UIMain_v1.cpp -o uimain1 -lsfml-graphics -lsfml-window -lsfml-system
uimain: UImain.cpp
	g++ UImain.cpp -o uimain -lsfml-graphics -lsfml-window -lsfml-system