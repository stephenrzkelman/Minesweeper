#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "Tile.h"

class Board
{
	public:
		Board(int size);
		~Board();
		int checkGame();
		string print();
		string hint();
		string soln();
		void Play();
	private:
		int m_size;
		vector<vector<Tile*>> m_tiles;
}

Board::Board(int size)
{
	// set size as given
	m_size = size;
	
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
// TODO: honestly, with the whole gameState handling, I don't think we need this.
int Board::checkGame()
{
	for(int r = 0; r < m_size; r++)
	{
		for(int c = 0; c < m_size; c++)
		{
			// TODO: for readability, add unfinished() member function to Tile to use for this check
			if(!(m_tiles[r][c].isBomb() ^ m_tiles[r][c].isOpen()))
			{
				return 0;
				// indicates that the game should continue
			}
		}
	}
	return 1;
	// indicates that the game has been won and is over
}

string Board::print()
{
	string board = "";
	// TODO: use string to make board printout work
	// likely just converting this to directly using cout
	return board;
}

string Board::hint()
{
	// TODO: print out state of random (incomplete) tile
	// use unfinished() member function to implement
	// likely just converting this to directly using cout
}

string Board::soln()
{
	// TODO: print out solution (full board revealed)
	// note: game must end anytime this is called
	// likely just converting this to directly using cout
	// in particular, it will allow this one to return -1 and forcibly end the game with a loss
}

void Board::play()
{
	int gameState = 0;
	int row, col;
	string action;
	do
	{
		this->print();
		cin>>row>>col>>action;
		// TODO: validate() helper function
		while(!validate(row, col, action))
		{
			cout<<"Invalid Input! Please enter a valid row number (1-"<<m_size<<"), column number (1-"<<m_size<<"), and action (open, flag, hint, soln)"<<endl;
		}
		// handle action open
		// handle action flag
		// handle action hint
		// handle action soln
		// flush stdout
	}
	while(gameState == 0);
	
	// print out board one last time
	// print out relevant end-of-game message
	return;
}
