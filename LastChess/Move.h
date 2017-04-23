#ifndef MOVE_H_
#define MOVE_H_
#include"Piece.h"

class Move
{
public:
	Move(int sourceRow, int sourceColumn, int targetRow, int targetColumn);

	int sourceRow;
	int sourceColumn;
	int targetRow;
	int targetColumn;

	bool isMoveValid();

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

#endif // !MOVE_H_