#ifndef PIECE_H_
#define PIECE_H_
#include<string>

/// <summary>
/// Klasa reprezentuj¹ca figurê na szachownicy
/// </summary>
class Piece
{
public:
	//pobierz cechy pionka
	int getRow();
	int getColumn();
	int getColor();
	int getType();
	bool getIsCaptured();

	//konwertery intów na okreœlenie znaku na planszy w string
	static std::string getRowString(int row);
	static std::string getColumnString(int column);

	//ustaw cechy pionka
	void setRow(int row);
	void setColumn(int column);
	void setType(int type);
	void setIsCaptured(bool isCaptured);
	
	/// <summary>
	/// Konstruktor figury. Przy tworzeniu nowej figury okresla siê ja paramterami
	/// </summary>
	/// <param name="color">kolor figury</param>
	/// <param name="type">rodzaj figury</param>
	/// <param name="row">rz¹d na ktorym jest pionek</param>
	/// <param name="column">kolumna w ktorej jest pionek</param>
	Piece(int color, int type, int row, int column);

	//kolory pionkow w grze
	static const int COLOR_WHITE = 0;
	static const int COLOR_BLACK = 1;

	//Rodzaje figur
	static const int TYPE_ROOK = 1;
	static const int TYPE_KNIGHT = 2;
	static const int TYPE_BISHOP = 3;
	static const int TYPE_QUEEN = 4;
	static const int TYPE_KING = 5;
	static const int TYPE_PAWN = 6;

	//Okreœlenie 8 rzedow planszy
	static const int ROW_1 = 0;
	static const int ROW_2 = 1;
	static const int ROW_3 = 2;
	static const int ROW_4 = 3;
	static const int ROW_5 = 4;
	static const int ROW_6 = 5;
	static const int ROW_7 = 6;
	static const int ROW_8 = 7;

	//Okreslenie 8 kolumn planszy
	static const int COLUMN_A = 0;
	static const int COLUMN_B = 1;
	static const int COLUMN_C = 2;
	static const int COLUMN_D = 3;
	static const int COLUMN_E = 4;
	static const int COLUMN_F = 5;
	static const int COLUMN_G = 6;
	static const int COLUMN_H = 7;

private:
	/// <summary>
	/// kolor figury (COLOR_BLACK || COLOR_WHITE)
	/// </summary>
	int color;

	/// <summary>
	/// rodzaj figury (TYPE_PAWN || TYPE_QUEEN ...)
	/// </summary>
	int type;

	/// <summary>
	/// kolumna w której jest pionek (COLUMN_ ...)
	/// </summary>
	int column;

	/// <summary>
	/// rz¹d w którym znajduje siê pionek na planszy (ROW_ ...)
	/// </summary>
	int row;

	/// <summary>
	/// Okreœla czy dana figura jest zbita czy nie (true-zbita, false - na planszy)
	/// </summary>
	bool isCaptured = false;
};

#endif // !PIECE_H_
