#include<iostream>
#include"Piece.h"
#include"ChessGame.h"
using namespace std;

ChessGame game;

void run();
void handleMove(string input);
int convertColumnStrToColumnInt(string strColumn);
int convertRowStrToRowInt(string strRow);
void printCurrentGameState();
string getNameOfPiece(Piece *piece);

//=====================================================
int main()
{
	run();
	cout << endl;
	system("pause");
	return 0;
}

void run()
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
				return;
			}
			else
			{
				//handleMove(input);
			}

			if (game.getGameState() == ChessGame::GAME_STATE_END)
			{
				printCurrentGameState();
				cout << "KONIEC GRY!" << endl;
				return;
			}

		}
		catch (const std::exception&)
		{
			cout << "Blad run\n";
		}
	}
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
