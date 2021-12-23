#include "Board.h"

using namespace std;

int main()
{
	int size;
	cout << "Enter size for board:" << endl;
	cin >> size;
	Board* Game = new Board(size);
	Game->play();
	delete Game;
	return 0;
}
