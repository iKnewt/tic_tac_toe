#include "tool.h"

namespace game
{
	using namespace std;

	struct Player
	{
		string name;
		string character;
		int wins;
	};

	void game(Player* player1, Player* player2);
	string playerCharacter(string playerName, string playerCharacter);
	string playerName(int playerNumber);
}

