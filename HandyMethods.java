package board;

import java.util.ArrayList;

public class HandyMethods {
	public static ArrayList<Integer> surroundings(int spot, int size){
		ArrayList<Integer> surrounding = new ArrayList<Integer>();
		if(spot>=size*size){return null;}
		if(spot/size>0) {surrounding.add(spot-size);
			if(spot%size>0) {
				surrounding.add(spot-size-1);
				surrounding.add(spot-1);
			}
			if(spot%size<size-1) {
				surrounding.add(spot-size+1);
				surrounding.add(spot+1);
			}
		}
		if(spot/size<size-1) {surrounding.add(spot+size);
			if(spot%size>0) {
			surrounding.add(spot+size-1);
			}
			if(spot%size<size-1) {
				surrounding.add(spot+size+1);
			}
		}
		return surrounding;
	}

	public static void Flag(Board B, int spot) {
		B.tiles[spot].isFlag = true;
	}
}
