# Minesweeper
This is a pretty elementary version of the Minesweeper game, complete with no GUI or output-window clearing functionality. 
I plan to come back to this sometime in the future to make it a little bit easier to play;
but at the end of the day, it's still Minesweeper, and it's still a lot of fun!
## Table of Contents

## Usage
The program runs out of the `Runner` file, which you can modify to change the size of the board. The number of bombs scales automatically with the board.

Run the runner file (with all the other files in the same folder) however you like to run java files. Personally, I always ran my java programs directly out of the Eclipse IDE.

As you play, the current board will be printed out. As I mentioned above, there's not a whole lot of optimization at the moment to make this incredibly comfortable to play,
but if you have the patience, here's how it works. When it starts, you'll see something like this (say you've chosen a 5x5 board by writing `Board.Run(5);` in the Runner's main method. When the game starts, you'll see something like this:
```
  1  2  3  4  5
0 ?  ?  ?  ?  ?
1 ?  ?  ?  ?  ?
2 ?  ?  ?  ?  ?
3 ?  ?  ?  ?  ?
4 ?  ?  ?  ?  ?
```
