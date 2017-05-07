#include"ChessGame.h"
#include<iostream>
using namespace std;

/// <summary>
/// Inicjalizacja gry
/// </summary>
ChessGame::ChessGame()
{
	//postawienie figur na planszy w odpowiednich miejscach i ustawienie gry na zaczecie jej przez bialych
	this->gameState = GAME_STATE_WHITE;

	//biale
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_ROOK, Piece::ROW_1, Piece::COLUMN_A);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_KNIGHT, Piece::ROW_1, Piece::COLUMN_B);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_BISHOP, Piece::ROW_1, Piece::COLUMN_C);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_QUEEN, Piece::ROW_1, Piece::COLUMN_D);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_KING, Piece::ROW_1, Piece::COLUMN_E);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_BISHOP, Piece::ROW_1, Piece::COLUMN_F);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_KNIGHT, Piece::ROW_1, Piece::COLUMN_G);
	createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_ROOK, Piece::ROW_1, Piece::COLUMN_H);

	//czarne
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_ROOK, Piece::ROW_8, Piece::COLUMN_A);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_KNIGHT, Piece::ROW_8, Piece::COLUMN_B);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_BISHOP, Piece::ROW_8, Piece::COLUMN_C);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_QUEEN, Piece::ROW_8, Piece::COLUMN_D);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_KING, Piece::ROW_8, Piece::COLUMN_E);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_BISHOP, Piece::ROW_8, Piece::COLUMN_F);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_KNIGHT, Piece::ROW_8, Piece::COLUMN_G);
	createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_ROOK, Piece::ROW_8, Piece::COLUMN_H);

	//Pionki
	int currentColumn = Piece::COLUMN_A;
	for (int i = 0; i < 8; i++)
	{
		createAndAddPiece(Piece::COLOR_WHITE, Piece::TYPE_PAWN, Piece::ROW_2, currentColumn);
		createAndAddPiece(Piece::COLOR_BLACK, Piece::TYPE_PAWN, Piece::ROW_7, currentColumn);
		currentColumn++;
	}
}

/// <summary>
/// Przeszukuje liste wszystkich pionkow (pude³ko) i zwraca ten ktory jest na okreslonej pozycji i jest niezbity
/// </summary>
/// <param name="row">rzad na ktorym znajduje sie pionek</param>
/// <param name="column">kolumna w krórej znajduej sie pionek</param>
/// <returns>wskaznik do pionka, ktory jest na danym polu i jest niezbity</returns>
Piece* ChessGame::getNonCapturedPieceAtLocation(int row, int column)
{
	//przeszukaj cala liste i zwroc wskaznik do danego pionka
	for (int i = 0; i < pieces.size(); i++)
	{
		//jezeli spelnia te warunki
		if (pieces[i].getRow() == row && pieces[i].getColumn() == column && pieces[i].getIsCaptured() == false)
		{
			return &pieces[i];
		}
	}
	//zwroc nic jak nie ma
	return nullptr;
}

/// <summary>
/// Sprawdza czy jest niezbity pionek na zadanym polu
/// </summary>
/// <param name="row">rzad na ktorym znajduje sie pionek</param>
/// <param name="column">kolumna w krórej znajduej sie pionek</param>
/// <returns>true, jesli na polu jest taki pionek</returns>
bool ChessGame::isNonCapturedPieceAtLocation(int row, int column)
{
	for each (Piece var in pieces)
	{
		//jest pionek
		if (var.getRow() == row && var.getColumn() == column && var.getIsCaptured() == false)
		{
			return true;
		}
	}
	//nie ma niezbitego pionka na polu
	return false;
}

/// <summary>
/// Sprawdza czy jest niezbity pionek na zadanym polu o okreslonym kolorze
/// </summary>
/// <param name="color">kolor pionka</param>
/// <param name="row">rzad na ktorym znajduje sie pionek</param>
/// <param name="column">kolumna w krórej znajduej sie pionek</param>
/// <returns>true, jesli na polu jest taki pionek</returns>
bool ChessGame::isNonCapturedPieceAtLocation(int color, int row, int column)
{
	for each (Piece var in pieces)
	{
		//jest pionek?
		if (var.getRow() == row && var.getColumn() == column && var.getIsCaptured() == false && var.getColor() == color)
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// Zwraca informacje czyja jest teraz tura
/// </summary>
/// <returns>czyja teraz kolej: GAME_STATE_...</returns>
int ChessGame::getGameState()
{
	return this->gameState;
}

/// <summary>
/// Zmienia tury w grze w zaleznosci od tego co jest na planszy
/// </summary>
void ChessGame::changeGameState()
{
	//skonczyli gre?
	if (this->isGameEndConditionReached())
	{
		//wyswietl komunikat czyj koniec
		if (this->gameState == ChessGame::GAME_STATE_BLACK)
		{
			cout << "Koniec gry, wygrali czarni!" << endl;
		}
		else
		{
			cout << "Koniec gry, wygrali biali!" << endl;
		}
		//ustaw koniec gry i zakoncz
		this->gameState = ChessGame::GAME_STATE_END;
		return;
	}

	//albo biali, albo czarni, albo koniec
	switch (this->gameState) {
	case GAME_STATE_BLACK:
		this->gameState = GAME_STATE_WHITE;
		break;
	case GAME_STATE_WHITE:
		this->gameState = GAME_STATE_BLACK;
		break;
	case GAME_STATE_END:
		// juz nie przelaczaj tur
		break;
	default:
		break;
	}
}

/// <summary>
/// Stwarza pionek o zadanych parametrach i dodaje go do listy pionkow (pudelko)
/// </summary>
/// <param name="color">Kolor figury (COLOR_WHITE || COLOR_BLACK)</param>
/// <param name="type">Rodzaj figury (TYPE_...)</param>
/// <param name="row">Rz¹d na którym stoi pocz¹tkowo figura (ROW_...)</param>
/// <param name="column">Rz¹d na którym stoi pocz¹tkowo figura (COLUMN_...)</param>
void ChessGame::createAndAddPiece(int color, int type, int row, int column)
{
	//stworz pionek
	Piece piece(color, type, row, column);
	//dodaj go do listy na koniec
	this->pieces.push_back(piece);
}

/// <summary>
/// Warunek konca gry: jeden gracz musi mieæ zbitego króla
/// </summary>
/// <returns>true jezeli krol jest zbity</returns>
bool ChessGame::isGameEndConditionReached()
{
	//przeszukaj liste z pionkami
	for each (Piece var in pieces)
	{
		//jak krol jest zbity to zakoncz
		if (var.getType() == Piece::TYPE_KING && var.getIsCaptured()==true)
		{
			return true;
		}
		else
		{
			//kontynuuj przeszukiwanie
		}
	}
	return false;
}

/// <summary>
/// Przemieszcza figure z jednego pola na drugie i sprawdza wszelkie niezbêdne warunki.
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <returns>true, jezeli udalo sie przemiescic figure</returns>
bool ChessGame::movePiece(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	//czy ruch mozna wykonac
	if (!isMoveValid(sourceRow, sourceColumn, targetRow, targetColumn))
	{
		//jezeli sie nie da to zakoncz funkcje
		cout << "Ruch jest niepoprawny!" << endl;
		return false;
	}

	//chwyc pionek
	Piece *piece = getNonCapturedPieceAtLocation(sourceRow, sourceColumn);

	//ustawiony kolor przeciwnika na odwrotny niz swoj
	int opponentColor= (piece->getColor() == Piece::COLOR_BLACK ? Piece::COLOR_WHITE : Piece::COLOR_BLACK);

	//jezeli na docelowym polu jest figura przeciwnika to ustaw jej stan na zbity
	if (isNonCapturedPieceAtLocation(opponentColor, targetRow, targetColumn))
	{
		//zbicie
		Piece *opponentPiece = getNonCapturedPieceAtLocation(targetRow, targetColumn);
		opponentPiece->setIsCaptured(true);
	}

	//ustaw pionek na docelowym polu
	piece->setRow(targetRow);
	piece->setColumn(targetColumn);

	//czy byl to ruch koncowy
	if (isGameEndConditionReached())
	{
		//tak - zakoncz gre
		this->gameState = GAME_STATE_END;
	}
	else
	{
		//nie - zmien kolejke
		this->changeGameState();
	}

	//jezeli bialy pionek dotarl do ostatniego rzedu, to nalezy mu sie awans
	if (piece->getType() == Piece::TYPE_PAWN && piece->getRow() == Piece::ROW_8 && piece->getColor() == Piece::COLOR_WHITE)
	{
		piece->setType(Piece::TYPE_BISHOP);
	}

	//jezeli czarny pionek dotarl do pierwszego rzedu, to nalezy mu sie awans
	if (piece->getType() == Piece::TYPE_PAWN && piece->getRow() == Piece::ROW_1 && piece->getColor() == Piece::COLOR_BLACK)
	{
		piece->setType(Piece::TYPE_BISHOP);
	}

	//ruch zostal wykonany poprawnie
	return true;
}

/// <summary>
/// Sprawdza czy ruch jest zgodny z zasadami gry
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <returns>true, jesli ruch jest zgodny z zasadami</returns>
bool ChessGame::isMoveValid(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	int sR = sourceRow;
	int sC = sourceColumn;
	int tR = targetRow;
	int tC = targetColumn;

	sourcePiece = getNonCapturedPieceAtLocation(sR, sC);
	targetPiece = getNonCapturedPieceAtLocation(tR, tC);

	//jesli na zrodlowym polu nic nie ma 
	if (sourcePiece == nullptr)
	{
		//to przerwij i pokaz komunikat
		cout << "Brak figury na tym polu\n";
		return false;
	}

	//jezeli jest odpowiednia tura i jezeli jest proba przestawienia odpowiednego pionka to
	if (sourcePiece->getColor() == Piece::COLOR_WHITE && getGameState() == ChessGame::GAME_STATE_WHITE)
	{
		//ok
	}
	else if(sourcePiece->getColor() == Piece::COLOR_BLACK && getGameState() == ChessGame::GAME_STATE_BLACK)
	{
		//ok
	}
	else
	{
		//ruch jest bledny
		cout << "Nie twoja tura!" << endl;
		return false;
	}

	//czy ruch docelowy jest w ogole na planszy
	if (tR <Piece::ROW_1 || tR >Piece::ROW_8 || tC <Piece::COLUMN_A || tC > Piece::COLUMN_H)
	{
		//ruch jest bledny
		cout << "Cel jest poza zakresem" << endl;
		return false;
	}

	//w zaleznosci od typu figury zweryfikuj ruch
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

	//ruch niezgodny z mozliwosciami pionka
	if (!validPieceMove)
	{
		return false;
	}
	else
	{
		// ok
	}

	//==================
	//tutaj ma byc szach, szachmat, impas
	//==================

	//ruch jest ok
	return true;
}

/// <summary>
/// Sprawdza czy pole jest zajete przez wroga albo przez nasza inna figure
/// </summary>
/// <returns>true jesli da sie zbic</returns>
bool ChessGame::isTargetLocationCaptureable()
{
	//Nie ma czego zbijac
	if (targetPiece == nullptr)
	{
		return false;
	}
	//Czy pole jest zajête przez figure o innym kolorze
	else if(targetPiece->getColor() != sourcePiece->getColor())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Czy pole jest puste?
/// </summary>
/// <returns>true jesli pole nie jest zajete</returns>
bool ChessGame::isTargetLocationFree()
{
	return targetPiece == nullptr;
}

/// <summary>
/// Ruch gonca - po skosie, o dowolna ilosc, ale nie moze przeskakiwac nad innymi figurami
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <returns>true, jesli ruch jest zgodny z ruchem laufra</returns>
bool ChessGame::isValidBishopMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	//czy pole nie jest zajete przez "naszego" i czy pole jest wolne
	if (isTargetLocationFree() || isTargetLocationCaptureable())
	{
		//ruch ok
	}
	else
	{
		//ruch nie jest ok, zakoncz
		cout << "Pole jest zajête lub pole jest niedostêpne";
		return false;
	}
	//zakladamy ze jest bledny ruch
	bool isValid = false;

	//czy ruch jest po skosie?
	int diffRow = targetRow - sourceRow;
	int diffColumn = targetColumn - sourceColumn;

	if (diffRow == diffColumn && diffColumn > 0)
	{
		//skos gora-prawo
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, +1, +1);
	}
	else if (diffRow == -diffColumn && diffColumn > 0)
	{
		//skos dol-prawo
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, -1, +1);
	}
	else if (diffRow == diffColumn && diffColumn < 0)
	{
		//skos dol-lewo
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, -1, -1);
	}
	else if (diffRow == -diffColumn && diffColumn < 0)
	{
		// skos gora-lewo
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, +1, -1);
	}
	else
	{
		//ruch nie jest po skosie
		cout<<diffRow<<endl;
		cout<<diffColumn<<endl;
		cout << "ruch nie jest po skosie\n";
		isValid = false;
	}
	return isValid;
}

/// <summary>
/// Ruch krolowej to polaczenie wiezy i goñca, ale nie moze przeskakiwac nad innymi figurami
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <returns>true, jesli ruch jest zgodny z ruchem krolowej</returns>
bool ChessGame::isValidQueenMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	bool result = isValidBishopMove(sourceRow, sourceColumn, targetRow, targetColumn);
	//bitwise OR - wystarczy zeby ktorykolwiek z tych ruchow byl wykonany poprawnie
	result |= isValidRookMove(sourceRow, sourceColumn, targetRow, targetColumn);
	return result;
}

/// <summary>
/// Pion moze sie ruszac wzdluz kolumny dopoki nie zostanie zablokowany lub o 2 w pierwszym ruchu
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <returns>true, jesli ruch jest zgodny z ruchem pionka</returns>
bool ChessGame::isValidPawnMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	bool isValid = false;
	if (isTargetLocationFree())
	{
		//czy ta sama kolumna?
		if (sourceColumn == targetColumn)
		{
			if (sourcePiece->getColor() == Piece::COLOR_WHITE)
			{
				// dla bialych figur
				if (sourceRow + 1 == targetRow)
				{
					// przesun o jedna w gore
					isValid = true;
				}
				else if (sourceRow + 2 == targetRow)
				{
					if (sourcePiece->getRow() == Piece::ROW_2 && sourcePiece->getColor() == Piece::COLOR_WHITE)
					{
						isValid = true;
					}
					else
					{
						cout << "probujesz przesunac pionek o za duzo pol" << endl;
						isValid = false;
					}
				}
				else
				{
					cout<<"probujesz przesunac pionek o za duzo pol"<<endl;
					isValid = false;
				}
			}
			else
			{
				// dla czarnych figur
				if (sourceRow - 1 == targetRow)
				{
					// przesun o jedna w dol
					isValid = true;
				}
				else if (sourceRow - 2 == targetRow)
				{
					if (sourcePiece->getRow() == Piece::ROW_7 && sourcePiece->getColor() == Piece::COLOR_BLACK)
					{
						isValid = true;
					}
					else
					{
						cout << "probujesz przesunac pionek o za duzo pol" << endl;
						isValid = false;
					}
				}
				else
				{
					cout<<"probujesz przesunac pionek o za duzo pol"<<endl;
					isValid = false;
				}
			}
		}
		else
		{
			// zla kolumna docelowa
			cout<<"ruch nie w tej samej kolumnie\n";
			isValid = false;
		}
	}
	//moze sie ruszac po skosie jezeli w kolumnie obok jest mozliwosc zbicia przeciwnika
	else if (isTargetLocationCaptureable())
	{
		if (sourceColumn + 1 == targetColumn || sourceColumn - 1 == targetColumn)
		{
			// kolumna na prawo lub lewo
			if (sourcePiece->getColor() == Piece::COLOR_WHITE) {
				// dla bialych
				if (sourceRow + 1 == targetRow)
				{
					// przesun o jedno w gore
					isValid = true;
				}
				else
				{
					cout<<"probujesz przesunac pionek o za duzo pol w gore"<<endl;
					isValid = false;
				}
			}
			else
			{
				// dla czarnych
				if (sourceRow - 1 == targetRow)
				{
					// przesun o jedno w dol
					isValid = true;
				}
				else
				{
					cout<<"probujesz przesunac pionek o za duzo pol w dol";
					isValid = false;
				}
			}
		}
		else
		{
			cout<<"Za duzo kolumn w prawo lub w lewo";
			isValid = false;
		}
	}

	//=======================
	// do zrobienia en passant (bicie w przelocie)
	//=======================

	return isValid;
}

/// <summary>
/// Kon porusza sie po literze L i moze skakac nad pionkami.
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <returns>true, jesli ruch jest zgodny z ruchem konia</returns>
bool ChessGame::isValidKnightMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	// Czy pole docelowe jest wolne i nie zajete przez "naszego"
	if (isTargetLocationFree() || isTargetLocationCaptureable()) {
		//tak
	}
	else
	{
		cout<<"Pole jest niedostepne";
		return false;
	}

	if (sourceRow + 2 == targetRow && sourceColumn + 1 == targetColumn) {
		// 2 gora w prawo
		return true;
	}
	else if (sourceRow + 1 == targetRow && sourceColumn + 2 == targetColumn) {
		// gora 2 w prawo
		return true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn + 2 == targetColumn) {
		// dol 2 w prawo
		return true;
	}
	else if (sourceRow - 2 == targetRow && sourceColumn + 1 == targetColumn) {
		// 2 dol prawo
		return true;
	}
	else if (sourceRow - 2 == targetRow && sourceColumn - 1 == targetColumn) {
		// 2 dol w lewo
		return true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn - 2 == targetColumn) {
		// dol 2 w lewo
		return true;
	}
	else if (sourceRow + 1 == targetRow && sourceColumn - 2 == targetColumn) {
		// gora 2 w lewo
		return true;
	}
	else if (sourceRow + 2 == targetRow && sourceColumn - 1 == targetColumn) {
		// 2 gora w lewo
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Król porusza sie o jedno pole w ka¿dym kierunku
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <returns>true, jesli ruch jest zgodny z ruchem krola</returns>
bool ChessGame::isValidKingMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	// Czy pole ktore ma sie ruszyc krol jest wolne?
	if (isTargetLocationFree() || isTargetLocationCaptureable()) {
		//tak
	}
	else
	{
		cout<<"Pole jest niedostepne\n";
		return false;
	}
	bool isValid = true;
	if (sourceRow + 1 == targetRow && sourceColumn == targetColumn)
	{
		//gora
		isValid = true;
	}
	else if (sourceRow + 1 == targetRow && sourceColumn + 1 == targetColumn)
	{
		//gora prawo
		isValid = true;
	}
	else if (sourceRow == targetRow && sourceColumn + 1 == targetColumn)
	{
		//prawo
		isValid = true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn + 1 == targetColumn)
	{
		//dol prawo
		isValid = true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn == targetColumn)
	{
		//dol
		isValid = true;
	}
	else if (sourceRow - 1 == targetRow && sourceColumn - 1 == targetColumn)
	{
		//dol lewo
		isValid = true;
	}
	else if (sourceRow == targetRow && sourceColumn - 1 == targetColumn)
	{
		//lewo
		isValid = true;
	}
	else if (sourceRow + 1 == targetRow && sourceColumn - 1 == targetColumn)
	{
		//gora lewo
		isValid = true;
	}
	else
	{
		cout<<"Probujesz przesunac figure o za duzo pol\n";
		isValid = false;
	}

	//========================
	// Do zrobienia: Castling (rozszada z wieza)
	//========================

	return isValid;
}

/// <summary>
/// Wieza moze sie poruszac w pionie lub poziomie
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <returns>true, jesli ruch jest zgodny z ruchem krola</returns>
bool ChessGame::isValidRookMove(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
	//czy pole jest docelowe jest nie zajête?
	if (isTargetLocationFree() || isTargetLocationCaptureable()) {
		//tak
	}
	else 
	{
		cout<<"pole jest niedostêpne"<<endl;
		return false;
	}

	bool isValid = false;

	// Czy ruch jest w pionie lub poziomie?
	int diffRow = targetRow - sourceRow;
	int diffColumn = targetColumn - sourceColumn;

	if (diffRow == 0 && diffColumn > 0)
	{
		// prawo
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, 0, +1);
	}
	else if (diffRow == 0 && diffColumn < 0)
	{
		// lewo
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, 0, -1);
	}
	else if (diffRow > 0 && diffColumn == 0)
	{
		// gora
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, +1, 0);
	}
	else if (diffRow < 0 && diffColumn == 0)
	{
		// down
		isValid = !arePiecesBetweenSourceAndTarget(sourceRow, sourceColumn, targetRow, targetColumn, -1, 0);
	}
	else
	{
		cout << "ruch nie jest w linii prostej\n";
		isValid = false;
	}
	return isValid;
}

/// <summary>
/// Sprawdza czy podczas wykonywania ruchu na trasie figury sa inne figury
/// </summary>
/// <param name="sourceRow">zrodlowy rzad</param>
/// <param name="sourceColumn">zrodlowa kolumna</param>
/// <param name="targetRow">docelowy rzad</param>
/// <param name="targetColumn">docelowa kolumna</param>
/// <param name="rowIncrementPerStep">inkrementacja rzedow</param>
/// <param name="columnIncrementPerStep">inkrementacja kolumn</param>
/// <returns>true, jezeli na drodze figury sa przeszkody</returns>
bool ChessGame::arePiecesBetweenSourceAndTarget(int sourceRow, int sourceColumn, int targetRow, int targetColumn, int rowIncrementPerStep, int columnIncrementPerStep)
{
	int currentRow = sourceRow + rowIncrementPerStep;
	int currentColumn = sourceColumn + columnIncrementPerStep;

	//przemieszczaj figure dopoki
	while (true)
	{
		if (currentRow == targetRow && currentColumn == targetColumn)
		{
			//osiagniesz cel
			break;
		}
		if (currentRow < Piece::ROW_1 || currentRow > Piece::ROW_8 || currentColumn < Piece::COLUMN_A || currentColumn > Piece::COLUMN_H)
		{
			//przekroczy zakres planszy
			break;
		}

		//jezeli natrafisz na figure, przerwij
		if (isNonCapturedPieceAtLocation(currentRow, currentColumn)) {
			cout<<"Na drodze znajduja sie figury!"<<endl;
			return true;
		}

		//przesuwaj figure o inkrementacje zgodna z ruchem
		currentRow += rowIncrementPerStep;
		currentColumn += columnIncrementPerStep;
	}
	return false;
}
