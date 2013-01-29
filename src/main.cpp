#include "InitialState.h"

#include <Scene/Game.hpp>

int main(int argc, char** argv) {
//	HWND hWnd = GetConsoleWindow();
//    ShowWindow(hWnd, SW_HIDE);

	dt::Game game;

	game.run(new InitialState(), argc, argv);

    return 0;
}
