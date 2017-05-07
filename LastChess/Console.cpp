#include<iostream>
#include"Piece.h"
#include"ChessGame.h"
using namespace std;

/// <summary>
/// Zainicjonowanie gry
/// </summary>
ChessGame game;

void handleMove(string input);
int convertColumnStrToColumnInt(string strColumn);
int convertRowStrToRowInt(string strRow);
void printCurrentGameState();
string getNameOfPiece(Piece* piece);

//==========================================================
/// <summary>
/// Funkcja g³ówna programu. 
/// </summary>
/// <returns>0</returns>
int main()
{
	//Zmienna do której bêdzie wpisywana komenda sk¹d dok¹d ma iœæ pionek np a1-d4
	string input = "";

	while (true)
	{
		//wypisz stan na planszy
		printCurrentGameState();
		cout << ".\nWpisz ruch (format e2-a3): ";

		try
		{
			cin >> input;

			//Jezeli user wpisze exit to koniec programu
			if (input == "exit")
			{
				return 0;
			}
			//wpp spróbuj przetworzyæ polecenie
			else
			{
				handleMove(input);
			}

			//jezeli król zosta³ zbity to koniec gry
			if (game.getGameState() == ChessGame::GAME_STATE_END)
			{
				printCurrentGameState();
				cout << "KONIEC GRY!" << endl;
				break;
			}
		}
		catch (const std::exception&)
		{
		}
	}

	cout << endl;
	system("pause");
	return 0;
}
//==========================================================

/// <summary>
/// Funkcja obs³uguj¹ca polecenia ruchu podana przez uzytkownika
/// </summary>
/// <param name="input">Polecenie wprowadzone w formie np: d2-g5</param>
void handleMove(string input)
{
	//substr(index ³añcucha i ile kolejnych znaków)
	//Rozbija polecenie na czêœci pierwsze - pobiera kolumne startowa (d) i wiersz startowy (2)
	string strSourceColumn = input.substr(0, 1);
	string strSourceRow = input.substr(1, 1);

	//kolumna celu (g) i rz¹d celu (5)
	string strTargetColumn = input.substr(3, 1);
	string strTargetRow = input.substr(4, 1);

	int sourceColumn = 0, sourceRow = 0;
	int targetColumn = 0, targetRow = 0;

	//Za pomoc¹ odpowiednych funkcji zdekoduj stringa startowego na int
	sourceColumn = convertColumnStrToColumnInt(strSourceColumn);
	sourceRow = convertRowStrToRowInt(strSourceRow);

	//Za pomoc¹ odpowiednych funkcji zdekoduj stringa koncowego na int
	targetColumn = convertColumnStrToColumnInt(strTargetColumn);
	targetRow = convertRowStrToRowInt(strTargetRow);

	//wykonaj ruch w grze
	game.movePiece(sourceRow, sourceColumn, targetRow, targetColumn);
}

/// <summary>
/// Przetwarza nazwê kolumny na jej identyfikacjê w postaci liczby
/// </summary>
/// <param name="strColumn">nazwa kolumny</param>
/// <returns>numer kolumny</returns>
int convertColumnStrToColumnInt(string strColumn)
{
	//gdyby u¿ytkownik wpisa³ jak¹œ g³upotê to nie przetworzy
	try
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
	}
	catch (const std::exception&)
	{
		cout << "Zla komenda!";
	}
}

/// <summary>
/// Przetwarza nazwê rzêdu na jego identyfikacjê w postaci liczby
/// </summary>
/// <param name="strRow">numer rzêdu jako string</param>
/// <returns>numer rzêdu jako liczba</returns>
int convertRowStrToRowInt(string strRow)
{
	try
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
	}
	catch (const std::exception&)
	{
		cout << "Zla forma komendy!";
	}
}

/// <summary>
/// Wyœwietla na konsoli planszê z aktualn¹ sytuacj¹
/// </summary>
void printCurrentGameState()
{
	cout << "  a  b  c  d  e  f  g  h  " << endl;
	for (int row = Piece::ROW_8; row >= Piece::ROW_1; row--)
	{
		cout << " +--+--+--+--+--+--+--+--+" << endl;
		string strRow = to_string(row + 1) + "|";
		for (int col = Piece::COLUMN_A; col <= Piece::COLUMN_H; col++)
		{
			//sprawdza po kolei wszystkie pola i wypisuje je do rz¹du. Jak puste to "  ", a jak figura to inicjaly
			Piece *piece = game.getNonCapturedPieceAtLocation(row, col);
			string pieceStr = getNameOfPiece(piece);
			strRow += pieceStr + "|";
		}
		cout << strRow + to_string(row + 1) << endl; //nr rzedu
	}
	cout << " +--+--+--+--+--+--+--+--+" << endl;
	cout << "  a  b  c  d  e  f  g  h  " << endl;

	//informacja dla u¿ytkownika czyj teraz jest ruch
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
		gameStateStr = "KONIEC\n";
		break;
	default:
		gameStateStr = "unknw";
		break;
	}
	cout << "teraz " + gameStateStr;
}

/// <summary>
/// Funkcja przetwarza obiekt Piece i zwraca nazwê i kolor tej figury
/// </summary>
/// <param name="piece">Wskaznik do figury</param>
/// <returns>nazwa figury (inicja³y) wyœwietlana na planszy w konsoli np: WQ - White Queen</returns>
string getNameOfPiece(Piece* piece)
{
	//Jezeli figura nie istnieje zwróæ po postu "  " i zakoñcz
	if (piece == nullptr)
		return "  ";

	string strColor = "";

	//Jezeli kolor czarny to B, je¿eli bia³y to W
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

	//Na podstawie rodzaju figury weŸ inicja³
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

	//zwróæ inicja³
	return strColor + strType;
}