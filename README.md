# Minesweeper
This is a pretty elementary version of the Minesweeper game, complete with no GUI or output-window clearing functionality. 
I plan to come back to this sometime in the future to make it a little bit easier to play;
but at the end of the day, it's still Minesweeper, and it's still a lot of fun!
## Table of Contents
- [Usage](#usage)
  - [The Board](#the-board)
  - [Taking Your Turn](#taking-your-turn)
  - [Taking Your Turn (Example)](#taking-your-turn-example)
  - [Finishing the Game](#finishing-the-game)
- [Implementation Notes](#implementation-notes)
  - [Graph Functionality](#graph-functionality)
  - [Modes](#modes)
- [Improvements](#improvements)
  - [Ease of Use](#ease-of-use)
  - [Input Filtering](#input-filtering)
  - [Hints and Help](#hints-and-help)
  - [OOP Best Practices](#oop-best-practices)
## Usage
The program runs out of the `Runner` file, which you can modify to change the size of the board. The number of bombs scales automatically with the board.

Run the runner file (with all the other files in the same folder) however you like to run java files. Personally, I always ran my java programs directly out of the Eclipse IDE, back in high school.

As you play, the current board will be printed out. As I mentioned above, there's not a whole lot of optimization at the moment to make this incredibly comfortable to play,
but if you have the patience, here's how it works. 

### The Board
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

### Taking Your Turn
To do something to the spot at row n, column m, on a board with size SxS, you will have to calculate the number `S*n+m`.

Then, if you want to open the spot, type in this value and hit enter. If you want to flag (or unflag) that spot, type in the value, but negative, and hit enter.

(The input number 0 is reserved for revealing the answer to the game, in case you get to a point where you have to guess and don't really feel like playing anymore. Note that this will print out the board with every spot revealed, but it won't end the game. So you can technically use this to cheat, but you won't get the normal satisfaction of actually solving the minesweeper game.)

### Taking Your Turn (Example)
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

### Finishing the Game
You can continue like this, step by step, until the game is over. As you may well know, the game either ends by you opening a spot that is a bomb (in which case you lose), or by you opening every spot that is not a bomb, and flagging every spot that is a bomb (in which case, you win).

If you lose, the board will print out with all bombs revealed, including the one you just opened, and you will get a message that says "YOU LOSE!"

If you win, the board will print out with all spots now opened or flagged, and then you will get a messsage that says "YOU WIN!"

## Implementation Notes
I made this in high school when my friends were building games in their AP Comp Sci class, and as you look through it, you may be able to tell that it was written by a high schooler. I'm planning to improve this sometime soon, but at the moment, I have a lot of classes and more interesting projects going on, so I will get back to it as I have time. This section is for some notes on my implementation, since I was very bad about commenting my code, and there are some pretty easy-to-spot issues, and some things that might not make a lot of sense.

### Graph Functionality
The implementation of the board sort of indirectly involves graphs and trees. This is how I got the "chunk-opening" functionality common to minesweeper games to work. Basically, when you call `Open()` on one of the game tiles, it marks itself as "opened" and recursively calls `Open()` on neighboring non-bomb tiles that have not yet been opened. I was pretty proud of this, since it was one of the things I spent the most time getting to work when I was originally putting the game together. And, my friends who were implementing minesweeper weren't able to get this functionality working in their own games.

### Modes
If you poke around in the Board.java file, you might notice that there's a comment (Wow! quite rare!) in the checkGame() method. It says something about digger mode vs. flagger mode. You might also have noticed in the usage instructions above that you can't win just by opening every non-bomb spot, you also have to flag every bomb spot. This is what flagger mode is. "Digger mode" is the normal version of the game that you might find on the app store/google play, where you win as soon as you have dug up every non-bomb spot, without having to use any flags. When testing the game, I found that the boards were often small enough that I could win before I expected by opening all non-bomb spots, and then I would get the "YOU WIN!" message and I would be super unsatisfied. So, I have the game currently set to flagger mode, but if you run this game locally and would prefer digger mode, you can change the commenting so that it checks the condition next to "digger mode" rather than the flagger mode condition.

## Improvements
This is sort of an extension on implementation notes, but this focuses on issues or inconveniences that I know exist in the program, and my plans to fix them in the future.

### Ease of Use
I think anyone who uses this probably feels that the input/output procedure at the moment is incredibly clunky. Lots of calculation on the user's part, and a lot of output. 

I wasn't aware that stdout could be flushed until one of my profs did it in the skeleton of one of the projects I had in my first quarter college CS class, but this is one thing I am planning to add to the program. I also am planning to make it so that users don't have to do calculation. Without a GUI, I still can't have any clicking going on, but I could at least separate the single input number with several layers of encoding into several numbers. I plan to change it to a three-part input that includes `<row> <column> <action>`.

### Input Filtering
As you might have noticed, there's no input filtering. If you type a number that is too small or too large, you'll just get an array out-of-bounds error. I'm going to fix this as well, and with the changes noted in ease-of-use above, there'll also be filtering on the available actions.

### Hints and Help
As it stands, the "help" system (this is what happens when you hit '0') is sort of weird. I think a couple better options might be to:

(1) just end the game once the solution is revealed, or

(2) give the location of an unopened, non-flagged, non-bomb spot, sort of as a hint to keep the player going

Personally, I lean towards option (2). This will be a little more work and may require me to add a little more info to the classes as they stand, but I feel it shouldn't be unmanageable and will be worth it

### OOP Best Practices
You might also notice that this doesn't really follow any OOP best practices. All member variables are public and are accessed and modified directly by other classes. Honestly, I think I would just fix this by going back through and rewriting the whole thing (all 2 classes) in C/C++, since I barely use Java anymore anyways. This is the overall plan for the program; one of these days, when I have time, I'm going to go back through and rewrite the whole thing in a different language and make all the improvements I have listed above.

