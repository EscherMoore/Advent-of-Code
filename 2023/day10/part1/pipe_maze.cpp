#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*

--- Day 10: Pipe Maze ---

You use the hang glider to ride the hot air from Desert Island all the way up
to the floating metal island. This island is surprisingly cold and there
definitely aren't any thermals to glide on, so you leave your hang glider
behind.

You wander around for a while, but you don't find any people or animals.
However, you do occasionally find signposts labeled "Hot Springs" pointing in a
seemingly consistent direction; maybe you can find someone at the hot springs
and ask them where the desert-machine parts are made.

The landscape here is alien; even the flowers and trees are made of metal. As
you stop to admire some metal grass, you notice something metallic scurry away
in your peripheral vision and jump into a big pipe! It didn't look like any
animal you've ever seen; if you want a better look, you'll need to get ahead of
it.

Scanning the area, you discover that the entire field you're standing on is
densely packed with pipes; it was hard to tell at first because they're the
same metallic silver color as the "ground". You make a quick sketch of all of
the surface pipes you can see (your puzzle input).

The pipes are arranged in a two-dimensional grid of tiles:

  | is a vertical pipe connecting north and south.

  - is a horizontal pipe connecting east and west.

  L is a 90-degree bend connecting north and east.

  J is a 90-degree bend connecting north and west.

  7 is a 90-degree bend connecting south and west.

  F is a 90-degree bend connecting south and east.

  . is ground; there is no pipe in this tile.

  S is the starting position of the animal; there
  is a pipe on this tile, but your sketch doesn't
  show what shape the pipe has.

Based on the acoustics of the animal's scurrying, you're confident the pipe
that contains the animal is one large, continuous loop.

For example, here is a square loop of pipe:

.....
.F-7.
.|.|.
.L-J.
.....

If the animal had entered this loop in the northwest corner, the sketch would
instead look like this:

.....
.S-7.
.|.|.
.L-J.
.....

In the above diagram, the S tile is still a 90-degree F bend: you can tell
because of how the adjacent pipes connect to it.

Unfortunately, there are also many pipes that aren't connected to the loop!
This sketch shows the same loop as above:

-L|F7
7S-7|
L|7||
-L-J|
L|-JF

In the above diagram, you can still figure out which pipes form the main loop:
they're the ones connected to S, pipes those pipes connect to, pipes those
pipes connect to, and so on. Every pipe in the main loop connects to its two
neighbors (including S, which will have exactly two pipes connecting to it, and
which is assumed to connect back to those two pipes).

Here is a sketch that contains a slightly more complex main loop:

..F7.
.FJ|.
SJ.L7
|F--J
LJ...

Here's the same example sketch with the extra, non-main-loop pipe tiles also
shown:

7-F7-
.FJ|7
SJLL7
|F--J
LJ.LJ

If you want to get out ahead of the animal, you should find the tile in the
loop that is farthest from the starting position. Because the animal is in the
pipe, it doesn't make sense to measure this by direct distance. Instead, you
need to find the tile that would take the longest number of steps along the
loop to reach from the starting point - regardless of which way around the loop
the animal went.

In the first example with the square loop:

.....
.S-7.
.|.|.
.L-J.
.....

You can count the distance each tile in the loop is from the starting point
like this:

.....
.012.
.1.3.
.234.
.....

In this example, the farthest point from the start is 4 steps away.

Here's the more complex loop again:

..F7.
.FJ|.
SJ.L7
|F--J
LJ...

Here are the distances for each tile on that loop:

..45.
.236.
01.78
14567
23...

Find the single giant loop starting at S. How many steps along the loop does it
take to get from the starting position to the point farthest from the starting
position?

*/

void moveToNextTile(int &row, int &col);
bool left(const int row, const int col, const int prevRow, const int prevCol);
bool right(const int row, const int col, const int prevRow, const int prevCol);
bool up(const int row, const int col, const int prevRow, const int prevCol);
bool down(const int row, const int col, const int prevRow, const int prevCol);

std::vector<std::vector<char>> maze;

int main(int argc, char *argv[]) {
  std::ifstream input(argv[1]);

  if (!input) {
    std::cout << "Failed to open the input file!" << std::endl;
    return 1;
  }

  std::string line;
  int row = 0, col = 0;
  int currentRow = 0, currentCol = 0;
  while (input >> line) {
    std::vector<char> mazeRow;
    for (char tile : line) {
      if (tile == 'S') {
        row = currentRow, col = currentCol;
      }
      mazeRow.push_back(tile);
      ++currentCol;
    }
    ++currentRow, currentCol = 0;
    maze.push_back(mazeRow);
  }
  
  moveToNextTile(row, col);
  int steps = 1;
  while (maze[row][col] != 'S') {
    moveToNextTile(row, col);
    ++steps;
  }

  int farthestSteps = steps / 2;
  std::cout << "Answer: " << farthestSteps << std::endl;
}

void moveToNextTile(int &row, int &col) {
  static int prevRow = -1, prevCol = -1;

  if (left(row, col, prevRow, prevCol)) {
    prevRow = row, prevCol = col;
    --col;
  } else if (right(row, col, prevRow, prevCol)) {
    prevRow = row, prevCol = col;
    ++col;
  } else if (up(row, col, prevRow, prevCol)) {
    prevRow = row, prevCol = col;
    --row;
  } else if (down(row, col, prevRow, prevCol)) {
    prevRow = row, prevCol = col;
    ++row;
  }
}

bool left(const int row, const int col, const int prevRow, const int prevCol) {
  char leftTile = maze[row][col - 1];
  if (
    leftTile == '.' || 
    col - 1 < 0 ||
    col - 1 == prevCol && row == prevRow
  ) {
    return false;
  }

  char currentTile = maze[row][col];
  switch(currentTile) {
    case 'S':
    case '-':
    case '7':
    case 'J':
      return true;
  }
  return false;
}

bool right(const int row, const int col, const int prevRow, const int prevCol) {
  char rightTile = maze[row][col + 1];
  if (
    col + 1 > maze[0].size() - 1 ||
    rightTile == '.' ||
    col + 1 == prevCol && row == prevRow
  ) {
    return false;
  }

  char currentTile = maze[row][col];
  switch(currentTile) {
    case 'S':
    case '-':
    case 'L':
    case 'F':
      return true;
  }
  return false;
}

bool up(const int row, const int col, const int prevRow, const int prevCol) {
  char tileAbove = maze[row - 1][col];
  if (
    row - 1 < 0 ||
    tileAbove == '.' ||
    col == prevCol && row - 1 == prevRow
  ) {
    return false;
  }

  char currentTile = maze[row][col];
  switch(currentTile) {
    case 'S':
    case '|':
    case 'L':
    case 'J':    
      return true;
  }
  return false;
}

bool down(const int row, const int col, const int prevRow, const int prevCol) {
  char tileBelow = maze[row + 1][col];
  if (
    row + 1 > maze.size() - 1 ||
    tileBelow == '.' ||
    col == prevCol && row + 1 == prevRow
  ) {
    return false;
  }

  char currentTile = maze[row][col];
  switch(currentTile) {
    case 'S':
    case '|':
    case '7':
    case 'F':
      return true;
  }
  return false;
}
