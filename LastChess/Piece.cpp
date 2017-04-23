#include "Piece.h"

Piece::Piece(int color, int type, int row, int column)
{
	this->color = color;
	this->type = type;
	this->row = row;
	this->column = column;
}

int Piece::getRow()
{
	return this->row;
}

int Piece::getColumn()
{
	return this->column;
}

void Piece::setRow(int row)
{
	this->row = row;
}

void Piece::setColumn(int column)
{
	this->column = column;
}

void Piece::setType(int type)
{
	this->type = type;
}

int Piece::getColor()
{
	return this->color;
}

int Piece::getType()
{
	return this->type;
}

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

void Piece::setIsCaptured(bool isCaptured)
{
	this->isCaptured = isCaptured;
}

bool Piece::getIsCaptured()
{
	return this->isCaptured;
}
