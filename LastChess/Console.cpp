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
string getNameOfPiece(Piece piece);

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
		//printCurrentGameState();
		cout << "your move (format e2-a3): ";

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

			

		}
		catch (const std::exception&)
		{
			cout << "Blad run\n";
		}

	}
}
