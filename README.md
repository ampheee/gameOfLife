## Contents.
***Graphics***.

The playing field is a rectangle of 80 by 25 squares - as a matrix of the "game" state. 
It is assumed that the field is "closed to itself", for example, in the lower right square the neighbor to the right is the lower left square, and the neighbor to the bottom is the upper right square.

## Important Notes:
* The game is written in C, is structured, and is run from the terminal; 
* No cumbersome functions are used, no more than 40 lines (not counting `main`).
> E. Dijkstra's structured programming principles were used in developing the game.

>The Game of Life, also known simply as Life, is a cellular automaton developed by British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its development is determined by its initial state, requiring no additional input. A person interacts with the Game of Life by creating an initial configuration and observing its development. It is Turing-complete and can mimic the universal constructor or any other Turing machine.
>
>The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states - alive or dead (or inhabited and uninhabited, respectively). Each cell interacts with its eight neighbors, i.e. cells located next to each other horizontally, vertically, or diagonally. At each step in time, the following transitions occur:
>
>Each living cell with less than two living neighbors dies, as if by overpopulation.
>Each living cell with two or three living neighbors passes on to the next generation.
>Each living cell with more than three living neighbors dies, as if by overpopulation.
>A dead cell with exactly three living neighbors becomes a living cell, as in reproduction.
>These rules, which compare the behavior of an automaton to real life, can be reduced to the following:
>
>Every living cell with two or three living neighbors survives.
>A dead cell with three living neighbors becomes a living cell.
>All other living cells die in the next generation. Similarly, all other dead cells remain dead.
>The initial pattern represents the seed of the system. The first generation is created by simultaneously applying the above rules to each cell in the seed; birth and death occur simultaneously, and the discrete moment when this occurs is sometimes called a tick. Each generation is a net function of the previous one.

