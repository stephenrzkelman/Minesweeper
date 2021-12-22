package board;
import java.util.Random;
import java.util.Scanner;
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
			if(/*digger mode:*/!(tiles[i].isBomb ^ tiles[i].isOpen)) 
			///*flagger mode:*/ tiles[i].isBomb ^ (tiles[i].isFlag && !tiles[i].isOpen))
			{return;}
			}
		gameIsOver = true;
		System.out.println("YOU WIN!");
	}
	
	@Override
	public String toString() {
		String printer = new String();
		printer += "Game\t";
		for(int i = 0;i<size;i++) {printer+=((i+1)+"\t");}
		printer+="\n";
		for(int i = 0; i<size; i++) {
			printer+=(i*size+"\t");
			for(int j= 0;j<size;j++) {
				printer+= tiles[size*i+j].toString();
			}
			printer+="\n";
		}
		return printer;
	}
	public String help() {
		String printer = new String();
		printer += "Answer\t";
		for(int i =0; i<size;i++) {printer+=((i+1)+"\t");}
		printer += "\n";
		for(int i = 0; i<size; i++) {
			printer+=(i*size+"\t");
			for(int j= 0;j<size;j++) {
				printer+= tiles[size*i+j].print+"\t";
			}
			printer+="\n";
		}
		return printer;
	}
	
	public static void Run(int boardSize) {
		Board B = new Board(boardSize);
		System.out.println(B);
		int spot;
		Scanner s = new Scanner(System.in);
		while(!B.gameIsOver){
			System.out.println("Enter an integer from 1 to "+ boardSize*boardSize+" to open a spot, or type a negative integer from -"+boardSize*boardSize+" to -1 to flag/unflag that spot");
			spot = s.nextInt();
			if(spot ==0) {
				System.out.println(B.help());
			}
			else if(spot>0) {
				B.tiles[spot-1].Open(B);
			}
			else {
				B.tiles[-1-spot].flipFlag();
			}
			System.out.println(B);
			B.checkGame();
		}
		s.close();
	}
}
