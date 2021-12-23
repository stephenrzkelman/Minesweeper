class Tile
{
	public:
		// use default constructor/destructor
		// all members are static & have default values
		int open();
		int flipFlag();
		bool setBomb();
		// NOTE: don't think I will be needing these next 3
		bool isBomb();
		bool isOpen();
		bool isFlag();

		void assignNeighbor(int col, int row, Tile* neighbor);
		void assignBombCount();
		char value();
	private:
		bool m_bomb = false;
		bool m_open = false;
		bool m_flag = false;
		Tile* m_neighbors[8] = {0};
		int m_neighborBombs = 0;

		bool setFlag();
		bool unSetFlag();
};

// open a tile
// return -1 if it is a bomb (game should end in a loss)
// return 0 if not a bomb but already open
// return n, the number of total tiles opened, otherwise
void open()
{
	// return -1 if it's a bomb
	if(m_bomb)
		return -1;

	// don't do anything if it's already open or if it's flagged
	if(m_open || m_flag) 
		return 0;

	// in any other case, first set its status to open
	m_open = true;
	int opened = 1;

	// if it's a blank square, open all of its neighbors (none of them will be bombs)
	if(m_neighborBombs == 0)
	{
		for(int i = 0; i < 8; i++)
		{
			if (m_neighbors[i] != nullptr)
				opened += m_neighbors[i]->open();
		}
	}
	return opened;
}

// don't flag an open spot (return false)
// otherwise, flag it and return true
bool Flag::setFlag()
{
	if(m_open)
		return false;
	else
	{
		m_flag = true;
		return true;
	}
}

// don't unflag a non-flagged spot (return false)
// otherwise, remove the flag and return true
bool Flag::unSetFlag()
{
	if(!m_flag)
		return false;
	else
	{
		m_flag = false;
		return true;
	}
}

// do the proper flag/unflag action
// return number of additional flags being used after flip
int Tile::flipFlag()
{
	if(m_flag) return unSetFlag() ? -1 : 0;
	else return setFlag() ? 1 : 0;
}

// set a tile to be a bomb
// increment neighboring squares bomb counts
// return false if it is already a bomb, true otherwise
bool Tile::setBomb()
{
	if(m_bomb)
		return false;
	else
	{
		m_bomb = true;
		for(int i = 0; i<8; i++)
		{
			if(m_neighbors[i] != nullptr)
				m_neighbors[i]->m_neighborBombs++;
		}
		return true;
	}
}

// return whether tile is bomb
bool Tile::isBomb()
{
	return m_bomb;
}

// return whether tile is open
bool Tile::isOpen()
{
	return m_open;
}

// return whether tile is flagged
bool Tile::isFlag()
{
	return m_flag;
}

// assign a neighbor to a tile
// col and row are ints -1 to 1 indicating where the neighbor is relative to the tile
int assignNeighbor(int row, int col, Tile* neighbor)
{
	// if not valid coords, return -1
	if(col<-1 || col>1 || row<-1 || row>1 || (row==0 && col==0))
	{
		return -1;
	}
	// otherwise, add to neighbor set
	// and return true
	else
	{
		int index = 4 + row*3+col;
		index -= index/5;
		m_neighbors[index] = neighbor;
		return 0;
	}
}

// return value to be printed out
char Tile::value()
{
	if(m_flag)
		return 'F';
	else if(!m_open)
		return '.';
	else if(!m_bomb)
	{
		if(m_neighborBombs == 0)
			return '_';
		else
			return '0'+m_neighborBombs;
	}
	else
		return 'B';
}
