#include "Piece.h"

/// <summary>
/// Konstruktor figury. Przy tworzeniu nowej figury okresla siê ja paramterami
/// </summary>
/// <param name="color">kolor figury</param>
/// <param name="type">rodzaj figury</param>
/// <param name="row">rz¹d na ktorym jest pionek</param>
/// <param name="column">kolumna w ktorej jest pionek</param>
Piece::Piece(int color, int type, int row, int column)
{
	this->color = color;
	this->type = type;
	this->row = row;
	this->column = column;
}

/// <summary>
/// Pobiera rz¹d w którym jest pionek
/// </summary>
/// <returns>numer rzêdu</returns>
int Piece::getRow()
{
	return this->row;
}

/// <summary>
/// Pobiera kolumnê w której znajduje siê pionek
/// </summary>
/// <returns>numer kolumny w której znajduej sie dany pionek</returns>
int Piece::getColumn()
{
	return this->column;
}

/// <summary>
/// Ustawia rz¹d w którym ma siê znaleŸæ pionek
/// </summary>
/// <param name="row">numer docelowego rzêdu (ROW_</param>
void Piece::setRow(int row)
{
	this->row = row;
}

/// <summary>
/// Ustawia kolumnê w której ma siê znaleŸæ dany pionek
/// </summary>
/// <param name="column">numer docelowej kolumny (COLUMN_)</param>
void Piece::setColumn(int column)
{
	this->column = column;
}

/// <summary>
/// Ustawia jakiego typu ma byæ pionek
/// </summary>
/// <param name="type">numer rodzaju pionka (TYPE_ ...)</param>
void Piece::setType(int type)
{
	this->type = type;
}

/// <summary>
/// Pobiera kolor figury
/// </summary>
/// <returns>numer koloru</returns>
int Piece::getColor()
{
	return this->color;
}

/// <summary>
/// Pobiera typ danej figury
/// </summary>
/// <returns>numer danej figury</returns>
int Piece::getType()
{
	return this->type;
}

/// <summary>
/// Konwetruje numer rzêdu na jego postaæ w stringu
/// </summary>
/// <param name="row">numer rzêdu do konwersji (ROW_)</param>
/// <returns>numer rzêdu w stringu</returns>
std::string Piece::getRowString(int row)
{
	std::string strRow = "unknown";
	switch (row) {
	case ROW_1: strRow = "1";
		break;
	case ROW_2: strRow = "2";
		break;
	case ROW_3: strRow = "3";
		break;
	case ROW_4: strRow = "4";
		break;
	case ROW_5: strRow = "5";
		break;
	case ROW_6: strRow = "6";
		break;
	case ROW_7: strRow = "7";
		break;
	case ROW_8: strRow = "8";
		break;
	}
	return strRow;
}

/// <summary>
/// Konwertuje numer kolumny na jej alfabetyczny odpowiednik 
/// </summary>
/// <param name="column">numer kolumny (COLUMN_)</param>
/// <returns>alfa odpowiednik 1 = A</returns>
std::string Piece::getColumnString(int column)
{
	std::string strColumn = "unknown";
	switch (column) {
	case COLUMN_A: strColumn = "A";
		break;
	case COLUMN_B: strColumn = "B";
		break;
	case COLUMN_C: strColumn = "C";
		break;
	case COLUMN_D: strColumn = "D";
		break;
	case COLUMN_E: strColumn = "E";
		break;
	case COLUMN_F: strColumn = "F";
		break;
	case COLUMN_G: strColumn = "G";
		break;
	case COLUMN_H: strColumn = "H";
		break;
	}
	return strColumn;
}

/// <summary>
/// Ustawia zbicie figury
/// </summary>
/// <param name="isCaptured">true = zbity pionek</param>
void Piece::setIsCaptured(bool isCaptured)
{
	this->isCaptured = isCaptured;
}

/// <summary>
/// Zwraca stan zbicia figury
/// </summary>
/// <returns>stan false - nie zbity</returns>
bool Piece::getIsCaptured()
{
	return this->isCaptured;
}
