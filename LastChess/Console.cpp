#include<iostream>
#include"Piece.h"
#include"ChessGame.h"
using namespace std;

ChessGame game;

void handleMove(string input);
int convertColumnStrToColumnInt(string strColumn);
int convertRowStrToRowInt(string strRow);
void printCurrentGameState();
string getNameOfPiece(Piece *piece);

//=====================================================
int main()
{
	string input = "";

	while (true)
	{
		printCurrentGameState();
		cout << ".\nWpisz ruch (format e2-a3): ";

		try
		{
			cin >> input;
			if (input == "exit")
			{
				return 0;
			}
			else
			{
				handleMove(input);
			}

			if (game.getGameState() == ChessGame::GAME_STATE_END)
			{
				printCurrentGameState();
				cout << "KONIEC GRY!" << endl;
				return 0;
			}

		}
		catch (const std::exception&)
		{
			cout << "Blad run\n";
		}
	}
	cout << endl;
	system("pause");
	return 0;
}

void handleMove(string input)
{
	string strSourceColumn = input.substr(0, 1);
	string strSourceRow = input.substr(1, 1);
	string strTargetColumn = input.substr(3, 1);
	string strTargetRow = input.substr(4, 1);

	int sourceColumn = 0, sourceRow = 0;
	int targetColumn = 0, targetRow = 0;

	sourceColumn = convertColumnStrToColumnInt(strSourceColumn);
	sourceRow = convertRowStrToRowInt(strSourceRow);

	targetColumn = convertColumnStrToColumnInt(strTargetColumn);
	targetRow = convertRowStrToRowInt(strTargetRow);

	game.movePiece(sourceRow, sourceColumn, targetRow, targetColumn);
	
}

int convertColumnStrToColumnInt(string strColumn)
{
	if (strColumn == "a")
		return Piece::COLUMN_A;
	else if (strColumn == "b")
		return Piece::COLUMN_B;
	else if (strColumn == "c")
		return Piece::COLUMN_C;
	else if (strColumn == "d")
		return Piece::COLUMN_D;
	else if (strColumn == "e")
		return Piece::COLUMN_E;
	else if (strColumn == "f")
		return Piece::COLUMN_F;
	else if (strColumn == "g")
		return Piece::COLUMN_G;
	else if (strColumn == "h")
		return Piece::COLUMN_H;
	else {
	}
}

int convertRowStrToRowInt(string strRow)
{
	if (strRow == "1")
		return Piece::ROW_1;
	else if (strRow == "2")
		return Piece::ROW_2;
	else if (strRow == "3")
		return Piece::ROW_3;
	else if (strRow == "4")
		return Piece::ROW_4;
	else if (strRow == "5")
		return Piece::ROW_5;
	else if (strRow == "6")
		return Piece::ROW_6;
	else if (strRow == "7")
		return Piece::ROW_7;
	else if (strRow == "8")
		return Piece::ROW_8;
	else throw new exception();
}

void printCurrentGameState()
{
	cout << "  a  b  c  d  e  f  g  h  " << endl;
	for (int row = Piece::ROW_8; row >= Piece::ROW_1; row--)
	{
		cout << " +--+--+--+--+--+--+--+--+" << endl;
		string strRow = to_string(row + 1) + "|";
		for (int col = Piece::COLUMN_A; col <= Piece::COLUMN_H; col++)
		{
			Piece *piece = game.getNonCapturedPieceAtLocation(row, col);
			string pieceStr = getNameOfPiece(piece);
			strRow += pieceStr + "|";
		}
		cout << strRow + to_string(row + 1) << endl;
	}
	cout << " +--+--+--+--+--+--+--+--+" << endl;
	cout << "  a  b  c  d  e  f  g  h  " << endl;

	string gameStateStr = "unknw";
	switch (game.getGameState())
	{
	case ChessGame::GAME_STATE_BLACK:
		gameStateStr = "czarni";
		break;
	case ChessGame::GAME_STATE_WHITE:
		gameStateStr = "biali";
		break;
	case ChessGame::GAME_STATE_END:
		gameStateStr = "end";
		break;
	default:
		gameStateStr = "unknw";
		break;
	}
	cout << "teraz " + gameStateStr;
}

string getNameOfPiece(Piece* piece)
{
	if (piece == nullptr)
		return "  ";

	string strColor = "";

	switch (piece->getColor())
	{
	case Piece::COLOR_BLACK:
		strColor = "B";
		break;
	case Piece::COLOR_WHITE:
		strColor = "W";
		break;
	default:
		strColor = "?";
	}

	string strType = "";
	switch (piece->getType())
	{
	case Piece::TYPE_BISHOP:
		strType = "B";
		break;
	case Piece::TYPE_KING:
		strType = "K";
		break;
	case Piece::TYPE_KNIGHT:
		strType = "N";
		break;
	case Piece::TYPE_PAWN:
		strType = "P";
		break;
	case Piece::TYPE_QUEEN:
		strType = "Q";
		break;
	case Piece::TYPE_ROOK:
		strType = "R";
		break;
	default:
		strType = "?";
		break;
	}

	return strColor + strType;
}
