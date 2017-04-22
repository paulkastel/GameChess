#include "ChessGame.h"

ChessGame::ChessGame()
{
	this->gameState = GAME_STATE_WHITE;
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_ROOK, Piece::ROW_1, Piece::COLUMN_A);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_KNIGHT, Piece::ROW_1, Piece::COLUMN_B);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_BISHOP, Piece::ROW_1, Piece::COLUMN_C);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_QUEEN, Piece::ROW_1, Piece::COLUMN_D);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_KING, Piece::ROW_1, Piece::COLUMN_E);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_BISHOP, Piece::ROW_1, Piece::COLUMN_F);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_KNIGHT, Piece::ROW_1, Piece::COLUMN_G);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_ROOK, Piece::ROW_1, Piece::COLUMN_H);

	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_ROOK, Piece::ROW_8, Piece::COLUMN_A);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_KNIGHT, Piece::ROW_8, Piece::COLUMN_B);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_BISHOP, Piece::ROW_8, Piece::COLUMN_C);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_QUEEN, Piece::ROW_8, Piece::COLUMN_D);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_KING, Piece::ROW_8, Piece::COLUMN_E);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_BISHOP, Piece::ROW_8, Piece::COLUMN_F);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_KNIGHT, Piece::ROW_8, Piece::COLUMN_G);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_ROOK, Piece::ROW_8, Piece::COLUMN_H);

	int currentColumn = Piece::COLUMN_A;
	for (int i = 0; i < 8; i++)
	{
		createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_PAWN, Piece::ROW_2, currentColumn);
		createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_PAWN, Piece::ROW_7, currentColumn);
		currentColumn++;
	}
}

Piece* ChessGame::getNonCapturedPieceAtLocation(int row, int column)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i].getRow() == row && pieces[i].getColumn() == column && pieces[i].getIsCaptured() == false)
		{
			return &pieces[i];
		}
	}
	return nullptr;
}

int ChessGame::getGameState()
{
	return this->gameState;
}

ChessGame::MoveValidator::MoveValidator()
{
}

ChessGame::Move::Move(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	this->sourceRow = sourceRow;
	this->sourceColumn = sourceColumn;
	this->targetRow = targetRow;
	this->targetColumn = targetColumn;
}

void ChessGame::createAndAddPiece(int color, int type, int row, int column)
{
	Piece piece(color, type, row, column);
	this->pieces.push_back(piece);
}
