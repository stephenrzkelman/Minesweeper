# Minesweeper
This is a pretty elementary version of the Minesweeper game, complete with no GUI or output-window clearing functionality. 
I plan to come back to this sometime in the future to make it a little bit easier to play;
but at the end of the day, it's still Minesweeper, and it's still a lot of fun!
## Table of Contents

## Usage
The program runs out of the `Runner` file, which you can modify to change the size of the board. The number of bombs scales automatically with the board.

Run the runner file (with all the other files in the same folder) however you like to run java files. Personally, I always ran my java programs directly out of the Eclipse IDE, back in high school.

As you play, the current board will be printed out. As I mentioned above, there's not a whole lot of optimization at the moment to make this incredibly comfortable to play,
but if you have the patience, here's how it works. 

Let's say you've chosen a 5x5 board by writing `Board.Run(5);` in the Runner's main method. When the game starts, you'll see something like this:
```
  1  2  3  4  5
0 ?  ?  ?  ?  ?
1 ?  ?  ?  ?  ?
2 ?  ?  ?  ?  ?
3 ?  ?  ?  ?  ?
4 ?  ?  ?  ?  ?
Enter an integer from 1 to 25 to open a spot, or type a negative integer from -25 to -1 to flag/unflag that spot
```
As you can see, the rows and columns are numbered, and you have to use these indirectly.

To do something to the spot at row n, column m, on a board with size SxS, you will have to calculate the number `S*n+m`.

Then, if you want to open the spot, type in this value and hit enter. If you want to flag (or unflag) that spot, type in the value, but negative, and hit enter.

For example, if I wanted to open the spot at row 2, column 5, then I would calculate `5*2+5 = 15`, type in 15, and hit enter. Let's say this spot happened to have 5 bombs neighboring it. Then, we would see the following print out:
```
  1  2  3  4  5
0 ?  ?  ?  ?  ?
1 ?  ?  ?  ?  ?
2 ?  ?  ?  ?  5
3 ?  ?  ?  ?  ?
4 ?  ?  ?  ?  ?
Enter an integer from 1 to 25 to open a spot, or type a negative integer from -25 to -1 to flag/unflag that spot
```
All the spots that have not been revealed or flagged still have question marks, but since we have revealed spot 15, and it had 5 bombs neighboring it, it now shows 5. If it had non-bomb spots neighboring it, it would've opened those automatically, just like in normal minesweeper games. 

Now, we know that all the spots neighboring spot 15 are bombs, so we should flag them. Let's start with spot 14, which is at row 2 and column 4. We'll go ahead and type in `-14` to flag it, and we should get the following output:
```
  1  2  3  4  5
0 ?  ?  ?  ?  ?
1 ?  ?  ?  ?  ?
2 ?  ?  ?  F  5
3 ?  ?  ?  ?  ?
4 ?  ?  ?  ?  ?
Enter an integer from 1 to 25 to open a spot, or type a negative integer from -25 to -1 to flag/unflag that spot
```
So, we can see that we have flagged spot 14, since it prints out an `F` in that spot.

