package board;

import java.util.Scanner;

public class Runner {
	public static void main(String[]args) {
		Board B = new Board(10);
		System.out.println(B);
		int spot;
		Scanner s = new Scanner(System.in);
		while(!B.gameIsOver){
			System.out.println("Enter an integer from 1 to 100 to open a spot, and open a negative integer from -100 to -1 to flag that spot");
			spot = s.nextInt();
			if(spot>0) {
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
