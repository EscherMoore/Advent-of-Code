#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <limits>

/*

--- Day 5: If You Give A Seed A Fertilizer ---

You take the boat and find the gardener right where you were told he would be:
managing a giant "garden" that looks more to you like a farm.

"A water source? Island Island is the water source!" You point out that Snow
Island isn't receiving any water.

"Oh, we had to stop the water because we ran out of sand to filter it with!
Can't make snow with dirty water. Don't worry, I'm sure we'll get more sand
soon; we only turned off the water a few days... weeks... oh no." His face
sinks into a look of horrified realization.

"I've been so busy making sure everyone here has food that I completely forgot
to check why we stopped getting more sand! There's a ferry leaving soon that is
headed over in that direction - it's much faster than your boat. Could you
please go check it out?"

You barely have time to agree to this request when he brings up another. "While
you wait for the ferry, maybe you can help us with our food production problem.
The latest Island Island Almanac just arrived and we're having trouble making
sense of it."

The almanac (your puzzle input) lists all of the seeds that need to be planted.
It also lists what type of soil to use with each kind of seed, what type of
fertilizer to use with each kind of soil, what type of water to use with each
kind of fertilizer, and so on. Every type of seed, soil, fertilizer and so on
is identified with a number, but numbers are reused by each category - that is,
soil 123 and fertilizer 123 aren't necessarily related to each other.

For example:

seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4

The almanac starts by listing which seeds need to be planted: seeds 79, 14, 55,
and 13.

The rest of the almanac contains a list of maps which describe how to convert
numbers from a source category into numbers in a destination category. That is, 
the section that starts with seed-to-soil map: describes how to convert a seed
number (the source) to a soil number (the destination). This lets the gardener
and his team know which soil to use with which seeds, which water to use with
which fertilizer, and so on.

Rather than list every source number and its corresponding destination number
one by one, the maps describe entire ranges of numbers that can be converted.
Each line within a map contains three numbers: the destination range start, the
source range start, and the range length.

Consider again the example seed-to-soil map:

50 98 2
52 50 48

The first line has a destination range start of 50, a source range start of 98,
and a range length of 2. This line means that the source range starts at 98 and
contains two values: 98 and 99. The destination range is the same length, but
it starts at 50, so its two values are 50 and 51. With this information, you
know that seed number 98 corresponds to soil number 50 and that seed number 99
corresponds to soil number 51.

The second line means that the source range starts at 50 and contains 48
values: 50, 51, ..., 96, 97. This corresponds to a destination range starting
at 52 and also containing 48 values: 52, 53, ..., 98, 99. So, seed number 53
corresponds to soil number 55.

Any source numbers that aren't mapped correspond to the same destination
number. So, seed number 10 corresponds to soil number 10.

So, the entire list of seed numbers and their corresponding soil numbers looks
like this:

seed  soil
0     0
1     1
...   ...
48    48
49    49
50    52
51    53
...   ...
96    98
97    99
98    50
99    51

With this map, you can look up the soil number required for each initial seed
number:

  Seed number 79 corresponds to soil number 81.
  Seed number 14 corresponds to soil number 14.
  Seed number 55 corresponds to soil number 57.
  Seed number 13 corresponds to soil number 13.

The gardener and his team want to get started as soon as possible, so they'd
like to know the closest location that needs a seed. Using these maps, find the
lowest location number that corresponds to any of the initial seeds. To do
this, you'll need to convert each seed number through other categories until
you can find its corresponding location number. In this example, the
corresponding types are:

  Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, 
  humidity 78, location 82.

  Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42,
  humidity 43, location 43.

  Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82,
  humidity 82, location 86.

  Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34,
  humidity 35, location 35.

So, the lowest location number in this example is 35.

What is the lowest location number that corresponds to any of the initial seed 
numbers?

Your puzzle answer was 309796150.

--- Part Two ---

Everyone will starve if you only plant such a small number of seeds. Re-reading
the almanac, it looks like the seeds: line actually describes ranges of seed
numbers.

The values on the initial seeds: line come in pairs. Within each pair, the
first value is the start of the range and the second value is the length of the
range. So, in the first line of the example above:

seeds: 79 14 55 13

This line describes two ranges of seed numbers to be planted in the garden. The
first range starts with seed number 79 and contains 14 values: 79, 80, ..., 91,
92. The second range starts with seed number 55 and contains 13 values: 55, 56,
..., 66, 67.

Now, rather than considering four seed numbers, you need to consider a total of
27 seed numbers.

In the above example, the lowest location number can be obtained from seed
number 82, which corresponds to soil 84, fertilizer 84, water 84, light 77,
temperature 45, humidity 46, and location 46. So, the lowest location number is
46.

Consider all of the initial seed numbers listed in the ranges on the first line
of the almanac. What is the lowest location number that corresponds to any of
the initial seed numbers?

*/

std::vector<std::vector<std::array<long long, 3>>> maps;
std::vector<long long> seedRanges;
void parseAlmanac(std::ifstream &almanac);
void initalizeSeeds(const std::string &firstLine);

long long sourceToDestination(
  const long long &value,
  const std::array<long long, 3> &mapValues
);
bool isMapped(
  const long long &value,
  const std::array<long long, 3> &mapValues
);
long long lookUp(const long long &value, const int &mapIdx);

int main(int argc, char *argv[]) {
  std::ifstream almanac(argv[1]);

  if (!almanac) {
    std::cout << "Failed to open the almanac!" << std::endl;
    return 1;
  }
  parseAlmanac(almanac);

  std::cout << "Searching seed ranges. This will take a long time..."
            << std::endl;

  long long minLocationNumber = std::numeric_limits<long long>::max(); 
  for (auto seedRange = seedRanges.begin();
      seedRange != seedRanges.end();
      seedRange+=2
  ) {
    long long seedRangeStart = *seedRange;
    long long seedRangeEnd = seedRangeStart + *(seedRange + 1);
    for (long long seed = seedRangeStart; seed <= seedRangeEnd; ++seed) {
      long long locationNumber = lookUp(seed, 0);
      if (locationNumber < minLocationNumber) {
        minLocationNumber = locationNumber;
      }
    }
  }
  std::cout << "Answer: " << minLocationNumber << std::endl; 
}

void parseAlmanac(std::ifstream &almanac) {
  std::string firstLine;
  std::getline(almanac, firstLine);
  initalizeSeeds(firstLine);

  std::string line;
  while (getline(almanac, line)) {
    if (line.empty()) {
      continue;
    }

    long long mapDeclaration = line.find("map:");
    if (mapDeclaration != std::string::npos) {
      maps.push_back(std::vector<std::array<long long, 3>>());
      continue;
    }

    std::string num;
    std::stringstream ss(line);
    std::array<long long, 3> mapLine;
    int mapIdx = 0;
    while (ss >> num) {
      mapLine[mapIdx] = stoll(num);
      mapIdx++;
    }

    if (!maps.empty()) {
      maps.back().push_back(mapLine);
    }
  }
}

void initalizeSeeds(const std::string &firstLine) {
  long long seedsStartIdx = firstLine.find(":") + 2;
  std::string seedNumbers = firstLine.substr(seedsStartIdx, firstLine.length());

  std::stringstream ss(seedNumbers);
  std::string seedNumber;
  while (ss >> seedNumber) {
    seedRanges.push_back(stoll(seedNumber));
  }
}

long long lookUp(const long long &value, const int &mapIdx) {
  bool mapped = false;
  long long mappedValue;

  for (std::array<long long, 3> mapValues : maps[mapIdx]) {
    if (isMapped(value, mapValues)) {
      mapped = true;
      mappedValue = sourceToDestination(value, mapValues);
    }
  }
  if (!mapped) {
    mappedValue = value;
  }
  if (mapIdx == maps.size() - 1) { 
    return mappedValue; 
  } else {
    return lookUp(mappedValue, mapIdx + 1);
  }
}

long long sourceToDestination(
    const long long &value, 
    const std::array<long long, 3> &mapValues
  ) {

  long long destinationRangeStart = mapValues[0];
  long long sourceRangeStart = mapValues[1];
  long long rangeLength = mapValues[2];
 
  long long offset = value - sourceRangeStart;
  long long destinationValue = destinationRangeStart + offset; 
  return destinationValue;
}

bool isMapped(
    const long long &value,
    const std::array<long long, 3> &mapValues
  ) {

  long long sourceRangeStart = mapValues[1];
  long long rangeLength = mapValues[2];

  long long sourceRangeEnd = (sourceRangeStart + rangeLength) - 1;

  if (value >= sourceRangeStart && value <= sourceRangeEnd) {
    return true;
  } else {
    return false;
  }
}
