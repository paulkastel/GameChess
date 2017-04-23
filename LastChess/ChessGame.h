#ifndef CHESSGAME_H_
#define CHESSGAME_H_
#include<vector>
#include"Piece.h"

class ChessGame
{
public:
	static const int GAME_STATE_WHITE = 0;
	static const int GAME_STATE_BLACK = 1;
	static const int GAME_STATE_END = 2;

	ChessGame();

	bool isMoveValid(int sourceRow, int sourceColumn, int targetRow, int targetColumn);


	bool movePiece(int sourceRow, int sourceColumn, int targetRow, int targetColumn);
	//std::vector<Piece> getPieces();
	Piece *getNonCapturedPieceAtLocation(int row, int column);
	bool isNonCapturedPieceAtLocation(int row, int column);
	int getGameState();
	void changeGameState();

private:
	int gameState = GAME_STATE_WHITE;
	std::vector<Piece> pieces;

	void createAndAddPiece(int color, int type, int row, int column);
	bool isGameEndConditionReached();
	bool isNonCapturedPieceAtLocation(int color, int row, int column);




	Piece *sourcePiece;
	Piece *targetPiece;

	bool isTargetLocationCaptureable();
	bool isTargetLocationFree();
	bool isValidBishopMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn);
	bool isValidQueenMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn);
	bool isValidPawnMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn);
	bool isValidKnightMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn);
	bool isValidKingMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn);
	bool isValidRookMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn);
	bool arePiecesBetweenSourceAndTarget(int sourceRow, int sourceColumn, int targetRow, int targetColumn, int rowIncrementPerStep, int columnIncrementPerStep);

};

#endif // !CHESSGAME_H_
