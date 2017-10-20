// ConnectFourGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ConnectFourGame.h"

int main()
{
	bool playAgain = true;
	ConnectFourGame game = ConnectFourGame(7, 6);

	std::string input;
	while (playAgain) {
		while (!game.IsWon() && game.HasValidMoves())
		{
			std::cout << game.RenderBoardToString() << "\n";
			std::cout << "Player " << game.GetCurrentPlayer() << " enter a move: ";

			getline(std::cin, input);
			int column = stoi(input);

			std::cout << "\n";

			bool isMoveValid = game.CheckMoveIsValid(column);
			if (!isMoveValid)
			{
				std::cerr << "Move is invalid!\n" << std::endl;
				continue;
			}

			game.MakeMove(column);
		}

		if (game.IsWon())
		{
			std::cout << "Player " << game.GetCurrentPlayer() << " won the game!\n" << std::endl;
		}
		else
		{
			std::cout << "Sorry, nobody won this time...\n" << std::endl;
		}

		std::cout << game.RenderBoardToString() << std::endl;

		std::cout << "Play again? (y/n) ";
		getline(std::cin, input);
		if (tolower(input[0]) == 'y')
		{
			game.Reset();
		}
		else
		{
			playAgain = false;
		}
	}

	std::cout << "Thanks for playing!" << std::endl;

    return 0;
}

