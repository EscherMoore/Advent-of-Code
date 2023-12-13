#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "trie.hpp"

/*

--- Day 1: Trebuchet?! ---

Something is wrong with global snow production, and you've been selected to
take a look. The Elves have even given you a map; on it, they've used stars to
mark the top fifty locations that are likely to be having problems.

You've been doing this long enough to know that to restore snow operations, you
need to check all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each
day in the Advent calendar; the second puzzle is unlocked when you complete the
first. Each puzzle grants one star. Good luck!

You try to ask why they can't just use a weather machine ("not powerful
enough") and where they're even sending you ("the sky") and why your map looks
mostly blank ("you sure ask a lot of questions") and hang on did you just say
the sky ("of course, where do you think snow comes from") when you realize that
the Elves are already loading you into a trebuchet ("please hold still, we need
to strap you in").

As they're making the final adjustments, they discover that their calibration
document (your puzzle input) has been amended by a very young Elf who was
apparently just excited to show off her art skills. Consequently, the Elves are
having trouble reading the values on the document.

The newly-improved calibration document consists of lines of text; each line
originally contained a specific calibration value that the Elves now need to
recover. On each line, the calibration value can be found by combining the
first digit and the last digit (in that order) to form a single two-digit
number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet

In this example, the calibration values of these four lines are 12, 38, 15, and
77. Adding these together produces 142.

Consider your entire calibration document. What is the sum of all of the
calibration values?

Your puzzle answer was 55123.

The first half of this puzzle is complete! It provides one gold star: *

--- Part Two ---

Your calculation isn't quite right. It looks like some of the digits are 
actually spelled out with letters: one, two, three, four, five, six, seven, 
eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and
last digit on each line. For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen

In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. 
Adding these together produces 281.

What is the sum of all of the calibration values?

*/

int main(int argc, char *argv[]) {
  std::ifstream calibrationDocument(argv[1]);

  std::map<std::string, char> lookupTable = {
    {"one", '1'}, {"eno", '1'}, {"1", '1'},
    {"two", '2'}, {"owt", '2'}, {"2", '2'},
    {"three", '3'}, {"eerht", '3'}, {"3", '3'},
    {"four", '4'}, {"ruof", '4'}, {"4", '4'},
    {"five", '5'}, {"evif", '5'}, {"5", '5'},
    {"six", '6'}, {"xis", '6'}, {"6", '6'},
    {"seven", '7'}, {"neves", '7'}, {"7", '7'},
    {"eight", '8'}, {"thgie", '8'}, {"8", '8'},
    {"nine", '9'}, {"enin", '9'}, {"9", '9'}
  };

  Trie digits;
  digits.insert("one").insert("eno").insert("1");
  digits.insert("two").insert("owt").insert("2");
  digits.insert("three").insert("eerht").insert("3");
  digits.insert("four").insert("ruof").insert("4");
  digits.insert("five").insert("evif").insert("5");
  digits.insert("six").insert("xis").insert("6");
  digits.insert("seven").insert("neves").insert("7");
  digits.insert("eight").insert("thgie").insert("8");
  digits.insert("nine").insert("enin").insert("9");

  int sum = 0;
  if (calibrationDocument) {
    std::string calibrationValue;

    while (calibrationDocument >> calibrationValue) {
      char first = lookupTable[digits.searchFirst(calibrationValue)];
      char last = lookupTable[digits.searchLast(calibrationValue)];

      std::string joinedInts(1, first);
      joinedInts.push_back(last);
      int joined = std::stoi(joinedInts);
      sum += joined;
    }
  } else {
    std::cout << "Failed to open the calibration document." << std::endl;
    return -1;
  }
  calibrationDocument.close();
  std::cout << "Answer: " << sum << std::endl;
}
