#include <iostream>
#include <string>
#include <map>

class Trie;

class TrieNode {
  friend class Trie;

  private:
    std::map<char, TrieNode> children;
    bool end = false;
    std::string word;
};

class Trie {
  private:
    TrieNode root;
  public:
    Trie &insert(const std::string &word);
    std::string searchFirst(const std::string &word);
    std::string searchLast(const std::string &word);
};

Trie &Trie::insert(const std::string &word) {
  TrieNode *currentNode = &root;
  for (char ch : word) {
    currentNode = &currentNode->children[ch];
  }
  currentNode->end = true;
  currentNode->word = word;
  return *this;
}

std::string Trie::searchFirst(const std::string &word) {
  TrieNode *currentNode = &root;

  int prev = -1;
  int ch = 0;
  while (ch <= word.length() - 1) {
    if (currentNode->children.count(word[ch]) == 0) {
      if (prev != -1) {
        ch = prev;
        prev = -1;
      }
      currentNode = &root;
      if (currentNode->children.count(word[ch]) != 0) {
        currentNode = &currentNode->children[word[ch]];
        if (currentNode->end) {
          return currentNode->word;
        }
      }
      ++ch;
      continue;
    } else {
      prev = ch;
      currentNode = &currentNode->children[word[ch]];
      if (currentNode->end) {
        return currentNode->word;
      }
    }
    ++ch;
  } 
  return currentNode->word;
}

std::string Trie::searchLast(const std::string &word) {
  TrieNode *currentNode = &root;

  int prev = -1;
  int ch = word.length() - 1;
  while (ch >= 0) {
    if (currentNode->children.count(word[ch]) == 0) {
      if (prev != -1) {
        ch = prev;
        prev = -1;
      }
      currentNode = &root;
      if (currentNode->children.count(word[ch]) != 0) {
        currentNode = &currentNode->children[word[ch]];
        if (currentNode->end) {
          return currentNode->word;
        }
      }
      --ch;
      continue;
    } else {
      prev = ch;
      currentNode = &currentNode->children[word[ch]];
      if (currentNode->end) {
        return currentNode->word;
      }
    }
    --ch;
  }
  return currentNode->word;
}
