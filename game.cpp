#include "game.h"


using namespace std;

namespace game
{
	enum class Result
	{
		GameTie,
		GameHasWinner,
		GameInProgress,
	};

	void printBoard(char tile[]);
	Result testGameStatus(char tile[]);
	bool testIfValidMove(char tile);
	Result playerRound(char tile[], Player* player);

	// lets the player input a nickname, uses an int as parameter to indicate which player it's refering to
	// returns the string the player chose as a nickname
	string playerName(int playerNumber)
	{
		cout << "\nPlayer " << playerNumber << ", type a nickname: ";
		return tool::readLine();
	}

	// lets the first player chose a character x or o and deals with wrong user input by looping
	// automatically choses the opposite character for the second player
	char playerCharacter(string playerName, char playerCharacter)
	{
		if(playerCharacter == 'x')
			return 'o';
		else if(playerCharacter == 'o')
			return 'x';
		do
		{
			cout << "\n" << playerName << ", which character would you like to be [x or o]: ";
			string character = tool::toLower(tool::readLine());
			//since a string is sort of an array of chars, the line under uses the first char in the string
			playerCharacter = character[0];

			if(playerCharacter != 'x' && playerCharacter != 'o')
				cout << "\nInvalid input" << endl;

		} while(playerCharacter != 'x' && playerCharacter != 'o');

		return playerCharacter;
	}

	// the main game, the array tile represents the tiles on the board and is declared here so that
	// the array is "remade" the next time this function is entered (a new game round), since it only exists within this function.
	// this function takes Player-pointer parameters because we want to keep that data across all rounds, but we also want to overwrite the data.
	void game(Player* player1, Player* player2)
	{
		char tile[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

		while (true)
		{
			if (playerRound(tile, player1) != Result::GameInProgress)
				break;
			if (playerRound(tile, player2) != Result::GameInProgress)
				break;
		}

	}

	// contains all statements I want to do every turn
	Result playerRound(char tile[], Player* player)
	{
		while (true)
		{
			cout << endl;
			printBoard(tile);

			cout << player->name << " - Write a number from 1 to 9: ";
			string userInput = tool::readLine();
			int playerInput = 0;
			// first ckecks if the user is an int, then if it's within the range we want, and if the tile is already taken by another player.
			// we need playerInput -1 because f.ex. the user input '3' corresponds to tile[2] in our tile array.
			if(tool::tryParseInt(userInput, &playerInput) &&
					playerInput > 0 &&
					playerInput < 10 &&
					testIfValidMove(tile[playerInput - 1]))
			{
				tile[playerInput - 1] = player->character;
				break;
			}
			else
			{
				cout << "That's an invalid move." << endl;
			}
		}

		Result gameStatus = testGameStatus(tile);

		switch (gameStatus) {
			case Result::GameHasWinner:
				cout << endl;
				printBoard(tile);
				cout << "Congratulations! " << player->name << " wins!!" << endl << endl;
				player->winCount++;
				break;

			case Result::GameTie:
				cout << endl;
				printBoard(tile);
				cout << "It's a tie! You're both winners..." << endl << endl;
				break;

			case Result::GameInProgress:
				break;
		}
		return gameStatus;
	}

	// a simple test to see if the char input is either 'x' or 'o', which would indicate an already used tile
	// eg. if user input is '2', testIfValidMove returns true, because it is a valid move
	bool testIfValidMove(char tile)
	{
		return !(tile == 'x' || tile == 'o');
	}

	// simply prints the game board to screen using whatever data is in the original array tile declared eariler
	// prints one and one tile until the tile reaches a number in the 3-table when starting at 2 (2, 5, 8, etc) then adds a new line and continues
	void printBoard(char tile[])
	{
		for(int i = 0; i < 9; ++i)
		{
			cout << " | " << tile[i];
			if(i % 3== 2)
				cout << " |" << endl;
		}
		cout << endl;
	}

	// tests if the game has a winner by comparing the tiles on the board to each other
	// in all different combinations that would mean a win if they are the same (eg. xxx or ooo)
	// uses two for-loops for the horizontal and vertical possible cominations
	// the diagonal possible combinations are checked manually by again comparing the tiles to each other
	Result testGameStatus(char tile[])
	{
		for(int i = 0; i <= 6; i += 3)
			if(tile[i] == tile[i + 1] && tile[i + 1] == tile[i + 2])
				return Result::GameHasWinner;

		for(int i = 0; i <= 2; i++)
			if(tile[i] == tile[i + 3] && tile[i + 3] == tile[i + 6])
				return Result::GameHasWinner;

		if((tile[0] == tile[4] && tile[4] == tile[8]) ||
				(tile[6] == tile[4] && tile[4] == tile[2]))
			return Result::GameHasWinner;
		else if(
				tile[0] != '1' && tile[1] != '2' && tile[2] != '3' &&
				tile[3] != '4' && tile[4] != '5' && tile[5] != '6' &&
				tile[6] != '7' && tile[7] != '8' && tile[8] != '9')
			return Result::GameTie;
		else
			return Result::GameInProgress;
	}



}
