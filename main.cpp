#include "game.h"

using namespace std;
using namespace game;

int main()
{
	cout << endl << "******** Welcome to Tic Tac Toe! ********" << endl;

	// this creates two instances of the struct Player, that stores information about each player
	// it lets the players chose a nickname and char to play as (x or o), as well as stores the amount of wins that player has
	Player player1;
	player1.name = playerName(1);
	player1.character = playerCharacter(player1.name, 'n');
	player1.winCount = 0;

	Player player2;
	player2.name = playerName(2);
	player2.character = playerCharacter("none", player1.character);
	player2.winCount = 0;

	string yesNo = "y";
	int gameCount = 0;

	// just a simple while-loop that exits the console if the player chooses to (by typing "n")
	while(yesNo != "n")
	{
		// if the player wants to play again, this adds one to the gamecount and makes sure that it swaps between which player
		// gets the first turn next round by checking if the gameCount is an even number.
		// It also prints the scoreboard.
		if(yesNo == "y")
		{
			if(gameCount % 2 == 0 )
				game::game(&player1, &player2);
			else
				game::game(&player2, &player1);

			gameCount++;

			int totalTies = gameCount - player1.winCount - player2.winCount;
			cout << " | " << player1.name << ": " << player1.winCount << " | " << player2.name << ": " << player2.winCount << " | " << "Ties: " << totalTies << " | " << endl;
		}

		cout << "\nWould you like to play again? [y/n]:\t" << endl;
		yesNo = tool::readLine();
		yesNo = tool::toLower(yesNo);
	}

	return 0;
}
