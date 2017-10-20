#pragma once
#include <string>
#include <sstream>

class ConnectFourGame
{
public:
	ConnectFourGame(int columns, int rows);
	~ConnectFourGame();
	bool CheckMoveIsValid(int column) const;
	void MakeMove(int column);
	bool IsWon() const;
	bool HasValidMoves() const;
	int GetCurrentPlayer() const;
	void Reset();
	std::string RenderBoardToString() const;
private:
	constexpr static unsigned short EMPTY_SPACE = 0;
	constexpr static unsigned short PLAYER_1 = 1;
	constexpr static unsigned short PLAYER_2 = 2;

	int columns;
	int rows;
	int **gameBoard;
	unsigned short currentPlayer;
	bool isWon;
	bool hasValidMoves;

	void InitGameBoard();
	void ZeroFillGameBoard();
	void CheckGameWon(int x, int y);
	void CheckHasValidMoves();

	bool CheckVertically(int x, int y1, int y2);
	bool CheckHorizontally(int y, int x1, int x2);
	bool CheckDiagonally(int x1, int x2, int y1, int y2);
	void CountMatch(int x, int y, int &counter);
};