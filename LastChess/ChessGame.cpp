#include"ChessGame.h"
#include<iostream>
using namespace std;

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

bool ChessGame::isNonCapturedPieceAtLocation(int row, int column)
{
	for each (Piece var in pieces)
	{
		if (var.getRow() == row && var.getColumn() == column && var.getIsCaptured() == false)
		{
			return true;
		}
	}
	return false;
}

int ChessGame::getGameState()
{
	return this->gameState;
}

void ChessGame::changeGameState()
{
	if (this->isGameEndConditionReached())
	{
		if (this->gameState == ChessGame::GAME_STATE_BLACK)
		{
			cout << "Koniec gry, wygrali czarni!" << endl;
		}
		else
		{
			cout << "Koniec gry, wygrali biali!" << endl;
		}
		this->gameState = ChessGame::GAME_STATE_END;
		return;
	}
	switch (this->gameState) {
	case GAME_STATE_BLACK:
		this->gameState = GAME_STATE_WHITE;
		break;
	case GAME_STATE_WHITE:
		this->gameState = GAME_STATE_BLACK;
		break;
	case GAME_STATE_END:
		// don't change anymore
		break;
	default:
		break;
	}
}

void ChessGame::createAndAddPiece(int color, int type, int row, int column)
{
	Piece piece(color, type, row, column);
	this->pieces.push_back(piece);
}

bool ChessGame::isGameEndConditionReached()
{
	for each (Piece var in pieces)
	{
		if (var.getType() == Piece::TYPE_KING && var.getIsCaptured())
		{
			return true;
		}
		else
		{

		}
	}
	return false;
}

bool ChessGame::isNonCapturedPieceAtLocation(int color, int row, int column)
{
	for each (Piece var in pieces)
	{
		if (var.getRow() == row && var.getColumn() == column && var.getIsCaptured() == false && var.getColor() == color)
		{
			return true;
		}
	}
	return false;
}

ChessGame::Move::Move(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	this->sourceRow = sourceRow;
	this->sourceColumn = sourceColumn;
	this->targetColumn = targetColumn;
	this->targetRow = targetRow;
}


bool ChessGame::movePiece(ChessGame::Move move)
{
	if (!move.isMoveValid())
	{
		cout << "Ruch jest niepoprawny!" << endl;
		return false;
	}

	Piece *piece = getNonCapturedPieceAtLocation(move.sourceRow, move.sourceColumn);
	int opponentColor;
	if (piece->getColor() == Piece::COLOR_BLACK)
	{
		opponentColor = Piece::COLOR_BLACK;
	}
	else
	{
		opponentColor = Piece::COLOR_WHITE;
	}

	if (isNonCapturedPieceAtLocation(opponentColor, move.targetRow, move.targetColumn))
	{
		Piece *opponentPiece = getNonCapturedPieceAtLocation(move.targetRow, move.targetColumn);
		opponentPiece->setIsCaptured(true);
	}
	piece->setRow(move.targetRow);
	piece->setColumn(move.targetColumn);

	if (isGameEndConditionReached())
	{
		this->gameState = GAME_STATE_END;
	}
	else
	{
		this->changeGameState();
	}
	return true;
}

bool ChessGame::Move::isMoveValid()
{
	int sR = this->sourceRow;
	int sC = this->sourceColumn;
	int tR = this->targetRow;
	int tC = this->targetColumn;

	sourcePiece = game.getNonCapturedPieceAtLocation(sR, sC);
	targetPiece = game.getNonCapturedPieceAtLocation(tR, tC);

	if (sourcePiece == nullptr)
	{
		cout << "Brak figury na tym polu\n";
		return false;
	}

	if (sourcePiece->getColor() == Piece::COLOR_WHITE && game.getGameState() == ChessGame::GAME_STATE_WHITE)
	{
	}
	else if(sourcePiece->getColor() == Piece::COLOR_BLACK && game.getGameState() == ChessGame::GAME_STATE_BLACK)
	{
	}
	else
	{
		cout << "Nie twoja tura!" << endl;
		return false;
	}

	if (tR <Piece::ROW_1 || tR >Piece::ROW_8 || tC <Piece::COLUMN_A || tC > Piece::COLUMN_H)
	{
		cout << "Cel jest poza zakresem" << endl;
		return false;
	}

	bool validPieceMove = false;
	switch (sourcePiece->getType())
	{
	case Piece::TYPE_BISHOP:
		validPieceMove = isValidBishopMove(sourceRow, sourceColumn, targetRow, targetColumn);
		break;
	case Piece::TYPE_KING:
		validPieceMove = isValidKingMove(sourceRow, sourceColumn, targetRow, targetColumn);
		break;
	case Piece::TYPE_KNIGHT:
		validPieceMove = isValidKnightMove(sourceRow, sourceColumn, targetRow, targetColumn);
		break;
	case Piece::TYPE_PAWN:
		validPieceMove = isValidPawnMove(sourceRow, sourceColumn, targetRow, targetColumn);
		break;
	case Piece::TYPE_QUEEN:
		validPieceMove = isValidQueenMove(sourceRow, sourceColumn, targetRow, targetColumn);
		break;
	case Piece::TYPE_ROOK:
		validPieceMove = isValidRookMove(sourceRow, sourceColumn, targetRow, targetColumn);
		break;
	default: break;
	}
	if (!validPieceMove)
	{
		return false;
	}
	else
	{
		// ok
	}
	//tutaj ma byc szach i szachmat
	return true;
}

bool ChessGame::Move::isTargetLocationCaptureable()
{
	if (targetPiece == nullptr)
	{
		return false;
	}
	else if(targetPiece->getColor() != sourcePiece->getColor())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ChessGame::Move::isTargetLocationFree()
{
	return targetPiece == nullptr;
}

bool ChessGame::Move::isValidBishopMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	if (isTargetLocationFree() || isTargetLocationCaptureable())
	{
		//ok
	}
	else
	{
		cout << "Pole jest zajête lub pole jest niedostêpne";
		return false;
	}
	bool isValid = false;

	int diffRow = targetRow - sourceRow;
	int diffColumn = targetColumn - sourceColumn;

	if (diffRow == diffColumn && diffColumn > 0)
	{
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, +1, +1);
	}
	else if (diffRow == -diffColumn && diffColumn > 0) {
		// moving diagnoally down-right
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, -1, +1);

	}
	else if (diffRow == diffColumn && diffColumn < 0) {
		// moving diagnoally down-left
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, -1, -1);

	}
	else if (diffRow == -diffColumn && diffColumn < 0) {
		// moving diagnoally up-left
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, +1, -1);

	}
	else {
		// not moving diagonally
		cout<<diffRow<<endl;
		cout<<diffColumn<<endl;
		cout << "not moving diagonally\n";
		isValid = false;
	}
	return isValid;
}

bool ChessGame::Move::isValidQueenMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	bool result = isValidBishopMove(sourceRow, sourceColumn, targetRow, targetColumn);
	result |= isValidRookMove(sourceRow, sourceColumn, targetRow, targetColumn);
	return result;
}

bool ChessGame::Move::isValidPawnMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	bool isValid = false;
	// The pawn may move forward to the unoccupied square immediately in front
	// of it on the same file, or on its first move it may advance two squares
	// along the same file provided both squares are unoccupied
	if (isTargetLocationFree()) {
		if (sourceColumn == targetColumn) {
			// same column
			if (sourcePiece->getColor() == Piece::COLOR_WHITE) {
				// white
				if (sourceRow + 1 == targetRow) {
					// move one up
					isValid = true;
				}
				else {
					cout<<"not moving one up"<<endl;
					isValid = false;
				}
			}
			else {
				// black
				if (sourceRow - 1 == targetRow) {
					// move one down
					isValid = true;
				}
				else {
					cout << "not moving one down" << endl;
					isValid = false;
				}
			}
		}
		else {
			// not the same column
			cout<<"not staying in same column\n";
			isValid = false;
		}

		// or it may move
		// to a square occupied by an opponent’s piece, which is diagonally in front
		// of it on an adjacent file, capturing that piece. 
	}
	else if (isTargetLocationCaptureable()) {

		if (sourceColumn + 1 == targetColumn || sourceColumn - 1 == targetColumn) {
			// one column to the right or left
			if (sourcePiece->getColor() == Piece::COLOR_WHITE) {
				// white
				if (sourceRow + 1 == targetRow) {
					// move one up
					isValid = true;
				}
				else {
					cout<<"not moving one up"<<endl;
					isValid = false;
				}
			}
			else {
				// black
				if (sourceRow - 1 == targetRow) {
					// move one down
					isValid = true;
				}
				else {
					cout<<"not moving one down";
					isValid = false;
				}
			}
		}
		else {
			// note one column to the left or right
			cout<<"not moving one column to left or right";
			isValid = false;
		}
	}

	// on its first move it may advance two squares
	// ..

	// The pawn has two special
	// moves, the en passant capture, and pawn promotion.

	// en passant
	// ..
	return isValid;
}

bool ChessGame::Move::isValidKnightMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	// The knight moves to any of the closest squares which are not on the same rank,
	// file or diagonal, thus the move forms an "L"-shape two squares long and one
	// square wide. The knight is the only piece which can leap over other pieces.

	// target location possible?
	if (isTargetLocationFree() || isTargetLocationCaptureable()) {
		//ok
	}
	else {
		cout<<"target location not free and not captureable";
		return false;
	}

	if (sourceRow + 2 == targetRow && sourceColumn + 1 == targetColumn) {
		// move up up right
		return true;
	}
	else if (sourceRow + 1 == targetRow && sourceColumn + 2 == targetColumn) {
		// move up right right
		return true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn + 2 == targetColumn) {
		// move down right right
		return true;
	}
	else if (sourceRow - 2 == targetRow && sourceColumn + 1 == targetColumn) {
		// move down down right
		return true;
	}
	else if (sourceRow - 2 == targetRow && sourceColumn - 1 == targetColumn) {
		// move down down left
		return true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn - 2 == targetColumn) {
		// move down left left
		return true;
	}
	else if (sourceRow + 1 == targetRow && sourceColumn - 2 == targetColumn) {
		// move up left left
		return true;
	}
	else if (sourceRow + 2 == targetRow && sourceColumn - 1 == targetColumn) {
		// move up up left
		return true;
	}
	else {
		return false;
	}
}

bool ChessGame::Move::isValidKingMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	// target location possible?
	if (isTargetLocationFree() || isTargetLocationCaptureable()) {
		//ok
	}
	else {
		cout<<"target location not free and not captureable\n";
		return false;
	}

	// The king moves one square in any direction, the king has also a special move which is
	// called castling and also involves a rook.
	bool isValid = true;
	if (sourceRow + 1 == targetRow && sourceColumn == targetColumn) {
		//up
		isValid = true;
	}
	else if (sourceRow + 1 == targetRow && sourceColumn + 1 == targetColumn) {
		//up right
		isValid = true;
	}
	else if (sourceRow == targetRow && sourceColumn + 1 == targetColumn) {
		//right
		isValid = true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn + 1 == targetColumn) {
		//down right
		isValid = true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn == targetColumn) {
		//down
		isValid = true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn - 1 == targetColumn) {
		//down left
		isValid = true;
	}
	else if (sourceRow == targetRow && sourceColumn - 1 == targetColumn) {
		//left
		isValid = true;
	}
	else if (sourceRow + 1 == targetRow && sourceColumn - 1 == targetColumn) {
		//up left
		isValid = true;
	}
	else {
		cout<<"moving too far\n";
		isValid = false;
	}

	// castling
	// ..

	return isValid;
}

bool ChessGame::Move::isValidRookMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	// The rook can move any number of squares along any rank or file, but
	// may not leap over other pieces. Along with the king, the rook is also
	// involved during the king's castling move.
	if (isTargetLocationFree() || isTargetLocationCaptureable()) {
		//ok
	}
	else {
		cout<<"target location not free and not captureable"<<endl;
		return false;
	}

	bool isValid = false;

	// first lets check if the path to the target is straight at all
	int diffRow = targetRow - sourceRow;
	int diffColumn = targetColumn - sourceColumn;

	if (diffRow == 0 && diffColumn > 0) {
		// right
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, 0, +1);

	}
	else if (diffRow == 0 && diffColumn < 0) {
		// left
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, 0, -1);

	}
	else if (diffRow > 0 && diffColumn == 0) {
		// up
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, +1, 0);

	}
	else if (diffRow < 0 && diffColumn == 0) {
		// down
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, -1, 0);

	}
	else {
		// not moving diagonally
		cout << "not moving straight\n";
		isValid = false;
	}

	return isValid;
}

bool ChessGame::Move::arePiecesBetweenSourceAndTarget(int sourceRow, int sourceColumn, int targetRow, int targetColumn, int rowIncrementPerStep, int columnIncrementPerStep)
{
	int currentRow = sourceRow + rowIncrementPerStep;
	int currentColumn = sourceColumn + columnIncrementPerStep;
	while (true)
	{
		if (currentRow == targetRow && currentColumn == targetColumn) {
			break;
		}
		if (currentRow < Piece::ROW_1 || currentRow > Piece::ROW_8 || currentColumn < Piece::COLUMN_A || currentColumn > Piece::COLUMN_H) {
			break;
		}

		if (game.isNonCapturedPieceAtLocation(currentRow, currentColumn)) {
			cout<<"pieces in between source and target"<<endl;
			return true;
		}

		currentRow += rowIncrementPerStep;
		currentColumn += columnIncrementPerStep;
	}
	return false;
}
