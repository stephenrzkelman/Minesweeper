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
		void checkGame();
		string print();
		string hint();
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
