class Tile
{
	public:
		// use default constructor/destructor
		// all members are static & have default values
		int Open();
		bool FlipFlag();
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
};

// open a tile
// return -1 if it is a bomb (game should end in a loss)
// return 0 otherwise (game should continue)
void Open()
{
	// return -1 if it's a bomb
	if(m_bomb)
		return -1;

	// don't do anything if it's already open
	if(m_open) 
		return 0;

	// in any other case, first set its status to open
	m_open = true;

	// if it's a blank square, open all of its neighbors (none of them will be bombs)
	if(m_neighborBombs == 0)
	{
		for(int i = 0; i < 8; i++)
		{
			if (m_neighbors[i] != nullptr)
				m_neighbors[i]->Open();
		}
	}
	return 0;
}

// flip flag status of a tile
// return final flag status of the tile
bool Tile::FlipFlag()
{
	m_flag = !m_flag;
	return m_flag;
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
