#include <iostream>
#include<string>
using namespace std;
// TicTacToe class
class TicTacToe {
private:
	static const int size = 3;
	char board[size][size];
	char currentPlayer;

public:
	TicTacToe() {
		currentPlayer = 'X';
		for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			board[i][j] = ' ';
	}

	void display() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				cout << board[i][j];
				if (j < 2) cout << "|";
			}
			cout << endl;
			if (i < 2) cout << "-----" << endl;
		}
	}

	bool makeMove(int x, int y) {
		if (board[x][y] == ' ') {
			board[x][y] = currentPlayer;
			return true;
		}
		else{
			cout << "Invalid Move..Try again\n";
			return false;
		}
	}

	bool checkWin() {
		for (int i = 0; i < size; ++i)
		if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
			return true;

		for (int i = 0; i < size; ++i)
		if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
			return true;

		if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
			return true;

		if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
			return true;

		return false;
	}
	bool isBoardFull() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (board[i][j] == ' ') {
					return false;
				}
			}
		}

		return true;
	}


	void switchPlayer() {
		currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
	}
	bool PlayAnotherRound(){
		char response;
		cout << "press y for another round or any key to exit TicTacToe\n";
		cin >> response;
		while (response == 'y'){
			resetBoard();
			return 1;

		}
		return false;

	}
	// Function to reset the game board for a new game
	void resetBoard() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				board[i][j] = ' ';
			}
		}
		currentPlayer = 'X'; // Reset to 'X' starting player
	}
};
// code for chess begins here!!!
// Base class for all pieces
// Constants for board size
const int BOARD_SIZE = 8;

// Base class for chess pieces
class Piece {
public:
	bool isWhite;
	string name;// Returns the symbol of the piece ('P' for pawn, 'R' for rook, etc.)
	virtual bool isValidMove(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) = 0; // Validates if a move is legal
	Piece(bool isWhite) : isWhite(isWhite), name(""){}
	virtual ~Piece() {}

};

// Derived class for Pawn
class Pawn : public Piece {
public:
	Pawn(bool isWhite) : Piece(isWhite) {
		name = isWhite ? "Pawn" : "pawn";
	}

	bool isValidMove(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) override {
		// Pawns move one square forward, or two squares from the starting position.
		if (startY == endY && ((startX == 1 && endX == 3) || (startX + 1 == endX))) {
			return board[endX][endY] == nullptr; // Ensure the destination is empty
		}
		return false;
	}
};

// Derived class for Rook
class Rook : public Piece {
public:
	Rook(bool isWhite) : Piece(isWhite) {
		name = isWhite ? "Rook" : "rook";
	}


	bool isValidMove(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) override {
		if (startX != endX && startY != endY) return false; // Rooks move in straight lines only
		int dx = (endX - startX) ? (endX - startX) / abs(endX - startX) : 0;
		int dy = (endY - startY) ? (endY - startY) / abs(endY - startY) : 0;

		// Check if no pieces are in the way
		int x = startX + dx, y = startY + dy;
		while (x != endX || y != endY) {
			if (board[x][y] != nullptr) return false;
			x += dx;
			y += dy;
		}
		return true;
	}
};

// Derived class for Knight
class Knight : public Piece {
public:
	Knight(bool isWhite) : Piece(isWhite) {
		name = isWhite ? "Horse" : "horse";
	}

	bool isValidMove(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) override {
		// Knight moves in "L" shape
		if ((abs(startX - endX) == 2 && abs(startY - endY) == 1) || (abs(startX - endX) == 1 && abs(startY - endY) == 2)) {
			return true;
		}
		return false;
	}
};

// Derived class for Bishop
class Bishop : public Piece {
public:
	Bishop(bool isWhite) : Piece(isWhite) {
		name = isWhite ? "Bishop" : "bishop";
	}

	bool isValidMove(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) override {
		if (abs(startX - endX) != abs(startY - endY)) return false; // Bishops move diagonally
		int dx = (endX - startX) / abs(endX - startX);
		int dy = (endY - startY) / abs(endY - startY);

		// Check if no pieces are in the way
		int x = startX + dx, y = startY + dy;
		while (x != endX || y != endY) {
			if (board[x][y] != nullptr) return false;
			x += dx;
			y += dy;
		}
		return true;
	}
};

// Derived class for Queen
class Queen : public Piece {
public:
	Queen(bool isWhite) : Piece(isWhite) {
		name = isWhite ? "Queen" : "queen";
	}

	bool isValidMove(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) override {
		// Queen moves like both a rook and a bishop
		if (startX == endX || startY == endY) { // Rook-like movement
			return checkLine(startX, startY, endX, endY, board);
		}
		else if (abs(startX - endX) == abs(startY - endY)) { // Bishop-like movement
			return checkDiagonal(startX, startY, endX, endY, board);
		}
		return false;
	}

private:
	bool checkLine(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) {
		int dx = (endX - startX) ? (endX - startX) / abs(endX - startX) : 0;
		int dy = (endY - startY) ? (endY - startY) / abs(endY - startY) : 0;
		int x = startX + dx, y = startY + dy;
		while (x != endX || y != endY) {
			if (board[x][y] != nullptr) return false;
			x += dx;
			y += dy;
		}
		return true;
	}

	bool checkDiagonal(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) {
		int dx = (endX - startX) / abs(endX - startX);
		int dy = (endY - startY) / abs(endY - startY);
		int x = startX + dx, y = startY + dy;
		while (x != endX || y != endY) {
			if (board[x][y] != nullptr) return false;
			x += dx;
			y += dy;
		}
		return true;
	}
};

// Derived class for King
class King : public Piece {
public:
	King(bool isWhite) : Piece(isWhite) {
		name = isWhite ? "King" : "king";
	}

	bool isValidMove(int startX, int startY, int endX, int endY, Piece* board[BOARD_SIZE][BOARD_SIZE]) override {
		// King moves one square in any direction
		return (abs(startX - endX) <= 1 && abs(startY - endY) <= 1);
	}
};

// Class to represent the Chessboard
class Board {
private:
	Piece* board[BOARD_SIZE][BOARD_SIZE];  // 8x8 chessboard, each element is a pointer to a piece

public:
	Board() {
		// Initialize all spaces to nullptr (empty)
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				board[i][j] = nullptr;
			}
		}
	}

	~Board() {
		// Clean up dynamically allocated memory
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				delete board[i][j];
			}
		}
	}

	void setup() {
		// Setup pawns
		for (int i = 0; i < BOARD_SIZE; i++) {
			board[1][i] = new Pawn(true);
			board[6][i] = new Pawn(false);
		}

		// Setup rooks
		board[0][0] = board[0][7] = new Rook(true);
		board[7][0] = board[7][7] = new Rook(false);

		// Setup knights
		board[0][1] = board[0][6] = new Knight(true);
		board[7][1] = board[7][6] = new Knight(false);

		// Setup bishops
		board[0][2] = board[0][5] = new Bishop(true);
		board[7][2] = board[7][5] = new Bishop(false);

		// Setup queens
		board[0][3] = new Queen(true);
		board[7][3] = new Queen(false);

		// Setup kings
		board[0][4] = new King(true);
		board[7][4] = new King(false);
	}

	void printBoard() {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (board[i][j] == nullptr) {
					cout << ". ";
				}
				else {
					cout << board[i][j]->name[0] << " ";
				}
			}
			cout << endl;
		}
	}

	bool movePiece(int startX, int startY, int endX, int endY) {
		if (startX < 0 || startX >= BOARD_SIZE || startY < 0 || startY >= BOARD_SIZE || endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) {
			cout << "Invalid move! Out of bounds." << endl;
			return false;
		}

		Piece* movingPiece = board[startX][startY];
		if (movingPiece == nullptr) {
			cout << "No piece at the start position." << endl;
			return false;
		}

		if (!movingPiece->isValidMove(startX, startY, endX, endY, board)) {
			cout << "Invalid move for " << movingPiece->name[0] << endl;
			return false;
		}

		// Move the piece
		delete board[endX][endY]; // Remove the piece at the destination
		board[endX][endY] = movingPiece;
		board[startX][startY] = nullptr;

		return true;
	}
};
class GameMenu {
public:
	void showMenu() {
		cout << "WELCOME TO KASHIF & HASNAIN's GAME!!!\n";
		int choice;
		do {
			cout << "Select a game to play:\n";
			cout << "1. Tic Tac Toe\n";
			cout << "2. Chess\n";
			cout << "3. Exit\n";
			cout << "Enter your choice: ";
			cin >> choice;
			switch (choice) {
			case 1:
				playTicTacToe();
				break;
			case 2:
				playChess();
				break;
			case 3:
				cout << "Exiting the game." << endl;
				break;
			default:
				cout << "Invalid choice, try again." << endl;
			}
		} while (choice != 3);
	}

private:


	void playTicTacToe() {

		TicTacToe game;
		do{

			bool gameover = false;
			while (!gameover){
				int row, col;




				for (int i = 0; i < 9; ++i) {
					game.display();
					cout << "Player " << (i % 2 == 0 ? 'X' : 'O') << ", enter your move (row and column): ";
					cin >> row >> col;

					if (game.makeMove(row, col)) {
						if (game.checkWin()) {
							game.display();
							cout << "Player " << (i % 2 == 0 ? 'X' : 'O') << " wins!" << endl;
							gameover = 1;
							game.PlayAnotherRound();
							return;
						}
						else if (game.isBoardFull()){
							game.display();
							cout << "It is a Draw!!!\n";
							gameover = true;
						}
						else
						{
							game.switchPlayer();
						}

					}
				}
			}
		} while (game.PlayAnotherRound());
		cout << "thanks for playing\n";
		return;

	}
	void playChess(){
		Board board;
		board.setup();
		int startX, startY, endX, endY;
		bool whiteTurn = true;

		while (true) {
			board.printBoard();
			cout << (whiteTurn ? "White's turn" : "Black's turn") << endl;
			cout << "Enter move (startX startY endX endY): ";
			cin >> startX >> startY >> endX >> endY;

			if (board.movePiece(startX, startY, endX, endY)) {
				cout << "Move successful!" << endl;
				whiteTurn = !whiteTurn;
			}
		}
	}
};

// Main function

int main()
{
	GameMenu menu;
	menu.showMenu();
	return 0;
}