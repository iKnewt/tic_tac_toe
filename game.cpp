#include "tool.h"
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

	void printBoard(string tile[]);
	Result testGameStatus(string tile[]);
	bool testIfValidMove(string tile);
	Result playerRound(string tile[], Player* player);

	// lets the player input a nickname, uses an int as parameter to indicate which player it's refering to
	// returns the string the player chose as a nickname
	string playerName(int playerNumber)
	{
		cout << "\nPlayer " << playerNumber << ", type a nickname:\t";
		return tool::readLine();
	}

	// lets the first player chose a character x or o and deals with wrong user input by looping
	// automatically choses the opposite character for the second player

	string playerCharacter(string playerName, string playerCharacter)
	{
		if(playerCharacter == "x")
			return "o";
		else if(playerCharacter == "o")
			return "x";
		do
		{
			cout << "\n" << playerName << ", which character would you like to be [x or o]:\t";
			playerCharacter = tool::readLine();
			playerCharacter = tool::toLower(playerCharacter);

			if(playerCharacter != "x" && playerCharacter != "o")
				cout << "\nInvalid input" << endl;

		} while(playerCharacter != "x" && playerCharacter != "o");

		return playerCharacter;
	}

	// the main game, the array tile represents the tiles on the board and is declared here so that if the result is no longer "GameInProgress"
	// the array is "remade" the next time this function is entered, since it only exists within this function.
	// this function takes these parameters because we want to keep that data across all rounds, so they are declared in main.
	// the Player info is just used for printing, but we need an int-pointer for the wincount since we wish to overwrite their data
	void game(Player* player1, Player* player2)
	{
		string tile [9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

		while (true)
		{
			if (playerRound(tile, player1) != Result::GameInProgress)
				break;
			if (playerRound(tile, player2) != Result::GameInProgress)
				break;
		}

	}

	Result playerRound(string tile[], Player* player)
	{
		while (true)
		{
			cout << endl;
			printBoard(tile);

			cout << player->name << " - Write a number from 1 to 9:\t";

			string userInput = tool::readLine();

			int playerInput = 0;
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
				player->wins++;
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

	bool testIfValidMove(string tile)
	{
		return !(tile == "x" || tile == "o");
	}

	// simply prints the game board to screen using whatever data is in the original array tile declared eariler
	void printBoard(string tile[])
	{
		for(int i = 0; i < 9; ++i)
		{
			cout << " | " << tile[i];
			if(i % 3== 2)
				cout << " |" << endl;
		}
		cout << endl;
	}

	// test if the game has a winner by comparing the tiles on the board to each other
	// in all different combinations that would mean a win if they are the same
	Result testGameStatus(string tile[])
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
				tile[0] != "1" && tile[1] != "2" && tile[2] != "3" &&
				tile[3] != "4" && tile[4] != "5" && tile[5] != "6" &&
				tile[6] != "7" && tile[7] != "8" && tile[8] != "9")
			return Result::GameTie;
		else
			return Result::GameInProgress;
	}



}
