#ifndef CHESSGAME_H_
#define CHESSGAME_H_
#include<vector>
#include"Piece.h"

/// <summary>
/// Klasa odpowiedaj¹ca za ca³a logikê i zasady gry
/// </summary>
class ChessGame
{
public:
	//zmienne odpowiadaj¹ce za okreslenie stanu gry - czyj teraz ruch

	static const int GAME_STATE_WHITE = 0;
	static const int GAME_STATE_BLACK = 1;
	static const int GAME_STATE_END = 2;

	/// <summary>
	/// Konstruktor inicjalizuje ca³¹ grê
	/// </summary>
	ChessGame();

	/// <summary>
	/// PUDE£KO Z PIONKAMI
	/// </summary>
	std::vector<Piece> pieces;

	// Weryfikuje czy ruch jest poprawny
	bool isMoveValid(int sourceRow, int sourceColumn, int targetRow, int targetColumn);

	//wykonanie ruchu
	bool movePiece(int sourceRow, int sourceColumn, int targetRow, int targetColumn);

	Piece *getNonCapturedPieceAtLocation(int row, int column);
	bool isNonCapturedPieceAtLocation(int row, int column);

	//czyja teraz kolej
	int getGameState();

	//zmien turê gracza
	void changeGameState();

private:
	//zacznaj¹ biali
	int gameState = GAME_STATE_WHITE;

	//dodawanie pionkow do gry
	void createAndAddPiece(int color, int type, int row, int column);

	//sprawdza czy jest juz koniec gry
	bool isGameEndConditionReached();

	bool isNonCapturedPieceAtLocation(int color, int row, int column);

	//=======================zasady gry=======================

	/// <summary>
	/// WskaŸnik do figury pocz¹tkowej
	/// </summary>
	Piece *sourcePiece;

	/// <summary>
	/// WskaŸnik do figury koncowej
	/// </summary>
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
	//========================================================
};

#endif // !CHESSGAME_H_
