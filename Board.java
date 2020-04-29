package board;
import java.util.Random;
public class Board {
	public int[]bombs;
	public Tile[] tiles;
	public int size;
	public int bombCount;
	public boolean gameIsOver = false;
	
	public Board(int size) {
		
		this.size = size;
		
		tiles = new Tile[size*size];
		
		for(int i=0;i<size*size;i++) {
			tiles[i]=new Tile(i, this);
		}
		
		bombCount = (int)(size*1.2);
		
		bombs = new Random().ints(0,size*size).distinct().limit(bombCount).toArray();
		
		for (int i: bombs) {
			tiles[i].placeMine();
		}
		
		for(int i = 0; i<size*size; i++) {
				if(!tiles[i].isBomb) {
					for(int j : tiles[i].neighbors) {
					if(tiles[j].print==-1) {tiles[i].print++;}
					}
				}
		}
	}

	
	public static Board createNew(int n) {
		Board B = new Board(n);
		return B;
	}
	public void checkGame() {
		for(int i =0;i<size*size;i++) {
			if(tiles[i].isBomb ^ (tiles[i].isFlag && !tiles[i].isOpen)) {return;}
			}
		gameIsOver = true;
		System.out.println("YOU WIN!");
	}
	
	@Override
	public String toString() {
		String printer = new String();
		for(int i = 0; i<size; i++) {
			for(int j= 0;j<size;j++) {
				printer+= tiles[size*i+j].toString();
			}
			printer+="\n";
		}
		return printer;
	}
}
