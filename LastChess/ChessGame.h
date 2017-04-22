#ifndef CHESSGAME_H_
#define CHESSGAME_H_
#include<vector>
#include"Piece.h"

class ChessGame
{
public:
	ChessGame();
	std::vector<Piece> pieces;
	std::vector<Piece> getPieces();
	static const int GAME_STATE_WHITE = 0;
	static const int GAME_STATE_BLACK = 1;
	static const int GAME_STATE_END = 2;
	Piece *getNonCapturedPieceAtLocation(int row, int column);
	bool isNonCapturedPieceAtLocation(int row, int column);
	int getGameState();
	void changeGameState();

	class Move
	{
	public:
		Move(int sourceRow, int sourceColumn, int targetRow, int targetColumn);

		int sourceRow;
		int sourceColumn;
		int targetRow;
		int targetColumn;
	};

	class MoveValidator
	{
	public:
		MoveValidator();
		bool isMoveValid(Move move);

	private:
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

private:
	int gameState = GAME_STATE_WHITE;
	void createAndAddPiece(int color, int type, int row, int column);
	bool movePiece(Move move);
	bool isGameEndConditionReached();
	bool isNonCapturedPieceAtLocation(int color, int row, int column);


	MoveValidator moveValid;

};

#endif // !CHESSGAME_H_
