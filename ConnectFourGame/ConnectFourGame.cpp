#include "stdafx.h"
#include "ConnectFourGame.h"

ConnectFourGame::ConnectFourGame(int columns, int rows)
{
	this->columns = columns;
	this->rows = rows;
	InitGameBoard();
	Reset();
}

ConnectFourGame::~ConnectFourGame()
{
}

void ConnectFourGame::Reset()
{
	this->currentPlayer = PLAYER_1;
	this->isWon = false;
	this->hasValidMoves = true;
	ZeroFillGameBoard();
}

void ConnectFourGame::InitGameBoard()
{
	this->gameBoard = new int*[columns];
	for (int i = 0; i < columns; i++)
	{
		this->gameBoard[i] = new int[rows];
	}
}

void ConnectFourGame::ZeroFillGameBoard() const
{
	for (int i = 0; i < columns; i++)
	{
		memset(this->gameBoard[i], EMPTY_SPACE, rows * sizeof(int));
	}
}


bool ConnectFourGame::IsWon() const
{
	return this->isWon;
}

bool ConnectFourGame::HasValidMoves() const
{
	return this->hasValidMoves;
}


int ConnectFourGame::GetCurrentPlayer() const
{
	return this->currentPlayer;
}

bool ConnectFourGame::CheckMoveIsValid(int column) const
{
	if (column >= columns || column < 0)
	{
		return false;
	}
	if (this->gameBoard[column][rows-1] != EMPTY_SPACE)
	{
		return false;
	}
	return true;
}

void ConnectFourGame::MakeMove(int column)
{
	int x = column;
	int y;
	for (int i = 0; i < rows; i++)
	{
		if (this->gameBoard[column][i] == EMPTY_SPACE)
		{
			y = i;
			break;
		}
	}

	this->gameBoard[x][y] = GetCurrentPlayer();

	CheckGameWon(x, y);

	if (!IsWon())
	{
		CheckHasValidMoves();
		this->currentPlayer = currentPlayer == PLAYER_1 ? PLAYER_2 : PLAYER_1;
	}
}

void ConnectFourGame::CheckGameWon(int x, int y)
{
	int y1 = std::max(y - 3, 0);
	int y2 = std::min(y + 3, rows - 1);

	int x1 = std::max(x - 3, 0);
	int x2 = std::min(x + 3, columns - 1);

	// Check vertically
	if (CheckVertically(x, y1, y2))
	{
		this->isWon = true;
		return;
	}

	// Check horizontally
	if (CheckHorizontally(y, x1, x2))
	{
		this->isWon = true;
		return;
	}

	// Check diagonally
	if (CheckDiagonally(x1, x2, y1, y2))
	{
		this->isWon = true;
	}
}

bool ConnectFourGame::CheckVertically(int x, int y1, int y2) const
{
	int matches = 0;
	for (int y = y1; y <= y2; y++)
	{
		if (CountMatchAndCheckWinCondition(x, y, matches))
		{
			return true;
		}
	}

	return false;
}

bool ConnectFourGame::CheckHorizontally(int y, int x1, int x2) const
{
	int matches = 0;
	for (int x = x1; x <= x2; x++)
	{
		if (CountMatchAndCheckWinCondition(x, y, matches))
		{
			return true;
		}
	}
	return false;
}

bool ConnectFourGame::CheckDiagonally(int x1, int x2, int y1, int y2) const
{
	int matches = 0;

	int x = x1;
	int y = y1;
	while (x <= x2 && y <= y2)
	{
		if (CountMatchAndCheckWinCondition(x, y, matches))
		{
			return true;
		}
		x++; y++;
	}

	matches = 0;
	while (x <= x2 && y >= y1)
	{
		if (CountMatchAndCheckWinCondition(x, y, matches))
		{
			return true;
		}
		x++; y--;
	}
	return false;
}

bool ConnectFourGame::CountMatchAndCheckWinCondition(int x, int y, int &counter) const
{
	if (this->gameBoard[x][y] == GetCurrentPlayer())
	{
		counter++;
	}
	else
	{
		counter = 0;
	}
	return counter == WIN_CONDITION;
}


void ConnectFourGame::CheckHasValidMoves()
{
	int y = rows - 1;
	for (int x = 0; x < columns; x++)
	{
		if (this->gameBoard[x][y] == EMPTY_SPACE)
		{
			this->hasValidMoves = true;
			return;
		}
	}
	this->hasValidMoves = false;
}


std::string ConnectFourGame::RenderBoardToString() const
{
	std::stringstream board;
	for (int y = rows - 1; y >= 0; y--)
	{
		for (int x = 0; x < columns; x++)
		{
			board << this->gameBoard[x][y] << " ";
		}
		board << "\n";
	}
	return board.str();
}