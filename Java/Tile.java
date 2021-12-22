package board;

import java.util.ArrayList;

public class Tile {
	public int print=0;
	public ArrayList<Integer> neighbors;
	public boolean isBomb = false;
	public boolean isOpen = false;
	public boolean isFlag = false;
	int spot;
	
	public Tile(int spot, Board B) {
		
		this.spot=spot;
		int size = B.size;
		neighbors = new ArrayList<Integer>();
		//if(spot>=size*size){do nothing;}
		if(spot/size!=0) {neighbors.add(spot-size);}
		if(spot/size!=size-1) {neighbors.add(spot+size);}
		if(spot%size!=0) {neighbors.add(spot-1);}
		if(spot%size!=size-1) {neighbors.add(spot+1);}
		if(spot/size!=0&&spot%size!=0) {neighbors.add(spot-size-1);}
		if(spot/size!=size-1&&spot%size!=size-1) {neighbors.add(spot+size+1);}
		if(spot/size!=0&&spot%size!=size-1) {neighbors.add(spot-size+1);}
		if(spot/size!=size-1&&spot%size!=0) {neighbors.add(spot+size-1);}
		}
	
	public void Open(Board B) {
		if(isOpen||isFlag) {return;}
		if(isBomb) {
			for(int j : B.bombs) {
				B.tiles[j].isOpen=true;
			}
			B.gameIsOver = true;
			System.out.println("YOU LOSE.");
		}
		else if(print==0) {
			isOpen = true;
			for(int j : neighbors) {
				B.tiles[j].Open(B);
			}
		}
		else {
			isOpen=true;
		}
	}
	
	public void Flag() {
		isFlag=true;
	}
	public void unFlag() {
		isFlag=false;
	}
	public void flipFlag() {
		isFlag = !isFlag;
	}
	public void placeMine() {
		isBomb = true;
		print = -1;
	}
	
	@Override
	public String toString() {
		if(isFlag) {return "F\t";}
		if(!isOpen) {return "?\t";}
		else {
			return print+"\t";
		}
	}
	
}
