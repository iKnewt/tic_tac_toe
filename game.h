#include "tool.h"

namespace game
{
	using namespace std;

	struct Player
	{
		string name;
		char character;
		int winCount;
	};

	void game(Player* player1, Player* player2);
	char playerCharacter(string playerName, char playerCharacter);
	string playerName(int playerNumber);
}

