#ifndef PIECE_H_
#define PIECE_H_
#include<string>

class Piece
{
public:
	inline int getRow();
	inline int getColumn();
	inline void setRow(int row);
	inline void setColumn(int column);
	inline int getColor();
	inline int getType();
	inline static std::string getRowString(int row);
	inline static std::string getColumnString(int column);
	inline void setIsCaptured(bool isCaptured);
	bool getIsCaptured();

	Piece(int color, int type, int row, int column);

	static const int COLOR_WHITE = 0;
	static const int COLOR_BLACK = 1;

	static const int TYPE_ROOK = 1;
	static const int TYPE_KNIGHT = 2;
	static const int TYPE_BISHOP = 3;
	static const int TYPE_QUEEN = 4;
	static const int TYPE_KING = 5;
	static const int TYPE_PAWN = 6;

	static const int ROW_1 = 0;
	static const int ROW_2 = 1;
	static const int ROW_3 = 2;
	static const int ROW_4 = 3;
	static const int ROW_5 = 4;
	static const int ROW_6 = 5;
	static const int ROW_7 = 6;
	static const int ROW_8 = 7;

	static const int COLUMN_A = 0;
	static const int COLUMN_B = 1;
	static const int COLUMN_C = 2;
	static const int COLUMN_D = 3;
	static const int COLUMN_E = 4;
	static const int COLUMN_F = 5;
	static const int COLUMN_G = 6;
	static const int COLUMN_H = 7;

private:
	int color;
	int type;
	int column;
	int row;
	bool isCaptured = false;

};

#endif // !PIECE_H_
