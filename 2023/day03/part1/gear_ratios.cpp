#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*

--- Day 3: Gear Ratios ---

You and the Elf eventually reach a gondola lift station; he says the gondola
lift will take you up to the water source, but this is as far as he can bring
you. You go inside.

It doesn't take long to find the gondolas, but there seems to be a problem:
they're not moving.

"Aaah!"

You turn around to see a slightly-greasy Elf with a wrench and a look of
surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working
right now; it'll still be a while before I can fix it." You offer to help.

The engineer explains that an engine part seems to be missing from the engine,
but nobody can figure out which one. If you can add up all the part numbers in
the engine schematic, it should be easy to work out which part is missing.

The engine schematic (your puzzle input) consists of a visual representation
of the engine. There are lots of numbers and symbols you don't really
understand, but apparently any number adjacent to a symbol, even diagonally, is
a "part number" and should be included in your sum. (Periods (.) do not count
as a symbol.)

Here is an example engine schematic:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, two numbers are not part numbers because they are not
adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number
is adjacent to a symbol and so is a part number; their sum is 4361.

Of course, the actual engine schematic is much larger. What is the sum of all
of the part numbers in the engine schematic?

*/

bool adjacentToSymbol(const int row, const int col, const int len);
bool isSymbol(const int row, const int col);
bool isValidCell(const int row, const int col);

std::vector<std::vector<char>> matrix;

int main(int argc, char *argv[]) {
  std::ifstream engineSchematic(argv[1]);

  if (!engineSchematic) {
    std::cout << "Failed to open engineSchematic." << std::endl;
    return -1;
  }

  std::string line;
  while (engineSchematic >> line) {
    std::vector<char> row;
    for (auto ch = line.begin(); ch != line.end(); ++ch) {
      row.push_back(*ch);
    }
    matrix.push_back(row);
  }

  std::string digit = "";
  int sum = 0;

  for (int currentRow = 0; currentRow <= matrix.size() - 1; ++currentRow) {
    for (int currentCol = 0; 
        currentCol <= matrix[currentRow].size() - 1; ++currentCol) 
    {
      char ch = matrix[currentRow][currentCol];
      if (isdigit(ch)) {
        digit += ch;
      } else if (digit != "") {
        int number = stoi(digit), len = digit.length();
        if (adjacentToSymbol(currentRow, currentCol - len, len)) {
          sum += number;
        }
        digit = "";
      }
    }
    if (digit != "") {
      int number = stoi(digit), len = digit.length();
      if (adjacentToSymbol(currentRow, (matrix[currentRow].size() - 1) - len, len)) {
        sum += number;
      }
      digit = "";
    }
  }
  std::cout << "Answer: " << sum << std::endl;
}

bool adjacentToSymbol(const int row, const int col, const int len) {
  for (int currentCol = col; currentCol < col + len; ++currentCol) {
    if (
      isSymbol(row, currentCol - 1) || // left
      isSymbol(row, currentCol + 1) || // right
      isSymbol(row - 1, currentCol) || // top
      isSymbol(row - 1, currentCol - 1) || // top left
      isSymbol(row - 1, currentCol + 1) || // top right
      isSymbol(row + 1, currentCol) || // bottom
      isSymbol(row + 1, currentCol - 1) || // bottom left
      isSymbol(row + 1, currentCol + 1) // bottom right
    ) {
      return true;
    }
  }
  return false;
}

bool isSymbol(const int row, const int col) {
    if (!isValidCell(row, col)) {
      return false;
    }
    char ch = matrix[row][col];
    return ch != '.' && ch != '\n' && !isdigit(ch);
}

bool isValidCell(const int row, const int col) {
    return row >= 0 && row < matrix.size() && col >= 0 && col < matrix[0].size();
}
