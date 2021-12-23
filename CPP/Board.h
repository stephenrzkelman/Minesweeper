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
		/*int hint();*/
		void Play();
	private:
		int m_size;
		vector<vector<Tile*>> m_tiles;
		int m_unopened;
		int m_bombs;
		int m_flags;
		/*int m_hints;*/

		void openAll();
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
	m_flags = m_bombs;

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

int Board::checkGame(int gameState)
{
	if(gameState == GAME_OVER_LOSS) 
		return GAME_OVER_LOSS;
	if(m_unopened = m_bombs) 
		return GAME_OVER_WIN;
	else
		return GAME_CONTINUE;
}

void Board::print()
{
	cout<<"Board Size: "<<m_size<<" x "<<m_size<<"\t";
	cout<<"Total Bombs: "<<m_bombs<<"\t";
	cout<<"Remaining Flags: "<<m_flags<<endl;

	cout<<"+\t";
	for(int c = 0; c < m_size; c++)
	{
		cout << c << "\t";
	}
	cout << endl;
	for(int r = 0; r < m_size; r++)
	{
		cout << r << "\t";
		for(int c = 0; c < m_size; c++)
		{
			cout << m_tiles[r][c].value() << "\t";
		}
		cout << endl;
	}
	cout << "\n" <<endl;
	cout << "Enter a row number (vertical along left), column number (horizontal across top), and action (open/flag/hint/soln); separated by spaces:" << endl;
	return;
}

/*
int Board::hint()
{
	// TODO: print out state of random (incomplete) tile
	// TODO: use cout directly
	// TODO: wait for confirmation from user before returning [use getch() from conio.h]
	return GAME_CONTINUE;
}
*/

void Board::openAll()
{
	for(int r = 0; r < m_size; r++)
	{
		for(int c = 0; c < m_size; c++)
		{
			m_tiles[r][c].open();
		}
	}
	return;
}

void Board::validate(row, col, action)
{
	if(row >= 0 && row < m_size &&
			col >= 0 && col < m_size &&
			(action=="open" || action=="flag" || action=="hint" || action=="soln"))
		return true;
	else 
		return false;
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
		cin.ignore(std::numeric_limits<std::streamsize>::max());
		
		while(!validate(row, col, action))
		{
			cout << "Invalid Input! Please enter a valid row number (1-" << m_size << "), column number (1-" << m_size << "), and action (open, flag, hint, soln)" << endl;
			cin >> row >> col >> action;
			cin.ignore(std::numeric_limits<std::streamsize>::max());
		}
		
		if(action=="open")
		{
			int opened = m_tiles[row][col].open()<0;
			if(opened < 0)
				gameState = GAME_OVER_LOSS;
			else
				m_unopened -= opened;
		}
		else if(action=="flag")
		{
			m_flags -= m_tiles[row][col].flipFlag();
		}
		else if(action=="hint")
		{
			/* this->hint(); */
		}
		else if(action=="soln")
		{
			this->openAll();
			gameState = GAME_OVER_LOSS;
		}
		// TODO: flush stdout
		gameState = checkGame(gameState);
	}
	while(gameState == GAME_CONTINUE);
	
	this->openAll();
	this->print();
	
	if(gameState == GAME_OVER_LOSS)
		cout<<"YOU LOSE"<<endl;
	else
		cout<<"YOU WIN!"<<endl;
	return;
}
