#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "Tile.h"

#define GAME_CONTINUE   0
#define GAME_OVER_WIN   1
#define GAME_OVER_LOSS -1

class Board
{
	public:
		Board(int size);
		~Board();
		int checkGame();
		void print();
		int hint();
		int soln();
		void Play();
	private:
		int m_size;
		vector<vector<Tile*>> m_tiles;
		int m_unopened;
		int m_bombs;
		// TODO: keep track of number of hints issued
}

Board::Board(int size)
{
	// set size as given
	m_size = size;
	m_unopened = size*size;
	// initialize board of nullptrs
	vector<vector<int>> tiles(size, vector<int> (size, 0));
	
	// create tiles, add neighbors
	for(int r = 0; r < size; r++)
	{
		for(int c = 0; c < size; c++)
		{
			Tile* tmp = new Tile();
			if(r>0)
			{
				tmp->assignNeighbor(-1,0,tiles[r-1][c]);
				tiles[r-1][c]->assignNeighbor(1,0,tmp);
				if(c>0)
				{
					tmp->assignNeighbor(-1,-1,tiles[r-1][c-1]);
					tiles[r-1][c-1]->assignNeighbor(1,1,tmp);
				}
				if(c<size-1)
				{
					tmp->assignNeighbor(-1,1,tiles[r-1][c+1]);
					tiles[r-1][c+1]->assignNeighbor(1,-1,tmp);
				}
			}
			if(c>0)
			{
				tmp->assignNeighbor(0,-1,tiles[r][c-1]);
				tiles[r][c-1]->assignNeighbor(0,1,tmp);
			}
			tiles[r][c] = tmp;
		}
	}

	// prepare to place bombs
	int bombCount = size*6/5;
	m_bombs = bombCount;

	// place bombCount distinct bombs
	while(bombCount > 0)
	{
		// pick random spot on board
		int nextBomb = rand() % (size*size);
		// try to set as bomb
		// if already a bomb, ignore
		if(!tiles[nextBomb/size][nextBomb%size].setBomb())
			continue;
		// otherwise, decrement bombCount
		else
		{
			bombCount--;
		}
	}

	m_tiles = tiles;
}

Board::~Board()
{
	for(int r = 0; r < m_size; r++)
	{
		for(int c = 0; c < m_size; c++)
		{
			delete m_tiles[r][c];
		}
	}
}

// TODO: add some member variable(s) to make this constant time
// TODO: note! we win the game if and only if the only unopened squares are bombs
// and, if we have opened a bomb before, then the game will have already ended
// so while the game has not ended, if the number of unopened squares is the number of bombs,
// then we have won
int Board::checkGame(int gameState)
{
	if(gameState == GAME_OVER_LOSS) 
		return GAME_OVER_LOSS;
	if(/* number of unopened tiles == number of bombs */) 
		return GAME_OVER_WIN;
	else
		return GAME_CONTINUE;
}

void Board::print()
{
	// TODO: print out board directly using cout;
}

int Board::hint()
{
	// TODO: print out state of random (incomplete) tile
	// TODO: use cout directly
	// TODO: wait for confirmation from user before returning [use getch() from conio.h]
	return GAME_CONTINUE;
}

int Board::soln()
{
	// TODO: open all unopened spots on the board
	return GAME_OVER_LOSS;
}

void Board::play()
{
	int gameState = 0;
	int row, col;
	string action;
	do
	{
		this->print();
		cin >> row >> col >> action;
		// TODO: flush stdin
		// TODO: validate() helper function
		while(!validate(row, col, action))
		{
			cout << "Invalid Input! Please enter a valid row number (1-" << m_size << "), column number (1-" << m_size << "), and action (open, flag, hint, soln)" << endl;
			cin >> row >> col >> action;
			// TODO: flush stdin
		}
		// TODO: handle action flag
		// TODO: handle action hint
		// TODO: handle action soln
		// TODO: flush stdout
		// TODO: update gameState by checking game
	}
	while(gameState == GAME_CONTINUE);
	// TODO: open all unopened tiles
	// TODO: print out board one last time
	if(gameState == GAME_OVER_LOSS)
		cout<<"YOU LOSE"<<endl;
	else
		cout<<"YOU WIN!"<<endl;
	return;
}
