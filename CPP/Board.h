#include <cstdlib>
#include <ctime>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
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
		int checkGame(int gameState);
		void print(int gameState);
		/*int hint();*/
		void play();
	private:
		int m_size;
		std::vector<std::vector<Tile*>> m_tiles;
		int m_unopened;
		int m_bombs;
		int m_flags;
		/*int m_hints;*/

		void openAll();
		bool validate(int row, int col, std::string action);
};

Board::Board(int size)
{
	// set size as given
	m_size = size;
	m_unopened = size*size;
	// initialize board of nullptrs
	std::vector<std::vector<Tile*>> tiles(size, std::vector<Tile*> (size, 0));
	
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

	std::srand(std::time(nullptr));
	// place bombCount distinct bombs
	while(bombCount > 0)
	{
		// pick random spot on board
		int nextBomb = std::rand() % (size*size);
		// try to set as bomb
		// if already a bomb, ignore
		if(!tiles[nextBomb/size][nextBomb%size]->setBomb())
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
	if(m_unopened == m_bombs) 
		return GAME_OVER_WIN;
	else
		return GAME_CONTINUE;
}

void Board::print(int gameState)
{
	std::cout<<"Board Size: "<<m_size<<" x "<<m_size<<"\t";
	std::cout<<"Total Bombs: "<<m_bombs<<"\t";
	std::cout<<"Remaining Flags: "<<m_flags<<std::endl;

	std::cout<<"+\t";
	for(int c = 0; c < m_size; c++)
	{
		std::cout << c << "\t";
	}
	std::cout << std::endl;
	for(int r = 0; r < m_size; r++)
	{
		std::cout << r << "\t";
		for(int c = 0; c < m_size; c++)
		{
			std::cout << m_tiles[r][c]->value() << "\t";
		}
		std::cout << std::endl;
	}
	if(gameState == GAME_CONTINUE)
	{
		std::cout << "\n" << std::endl;
		std::cout << "Enter a row number (vertical along left), column number (horizontal across top), and action (open/flag/hint/soln); separated by spaces:" << std::endl;
	}
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
			m_tiles[r][c]->open();
		}
	}
	return;
}

bool Board::validate(int row, int col, std::string action)
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
	std::string action;
	do
	{
		this->print(gameState);
		std::cin >> row >> col >> action;
		// std::cerr<<"input received"<<std::endl;
		// std::cin.ignore(std::numeric_limits<std::streamsize>::max());	
		while(!validate(row, col, action))
		{
			std::cout << "Invalid Input! Please enter a valid row number (0-" << m_size-1 << "), column number (0-" << m_size-1 << "), and action (open, flag, hint, soln)" << std::endl;
			std::cin >> row >> col >> action;
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max());
		}
		// std::cerr<<"input valid"<<std::endl;
		
		if(action=="open")
		{
			int opened = m_tiles[row][col]->open();
			if(opened < 0)
				gameState = GAME_OVER_LOSS;
			else
				m_unopened -= opened;
		}
		else if(action=="flag")
		{
			m_flags -= m_tiles[row][col]->flipFlag();
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
	this->print(gameState);
	
	if(gameState == GAME_OVER_LOSS)
		std::cout<<"YOU LOSE"<<std::endl;
	else
		std::cout<<"YOU WIN!"<<std::endl;
	return;
}
