// WordCount.cpp

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	// STUB - your solution from Lab06 goes here
	int total = 0;
    for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto& entry : table[i]) {
            total += entry.second;
        }
    }
    return total;


}

int WordCount::getNumUniqueWords() const {
	// STUB - your solution from Lab06 goes here
	//return -1;
	int count = 0;
    for (size_t i = 0; i < CAPACITY; ++i) {
        count += table[i].size();
    }
    return count;
}

int WordCount::getWordCount(std::string word) const {
	// STUB - your solution from Lab06 goes here
	    word = makeValidWord(word);
    if (word.empty()) return 0;

    size_t index = hash(word);
    const auto& bucket = table[index];
    for (const auto& entry : bucket) {
        if (entry.first == word) {
            return entry.second;
        }
    }
    return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	// STUB - your solution from Lab06 goes here
	    word = makeValidWord(word);
    if (word.empty()) return 0;

    size_t index = hash(word);
    auto& bucket = table[index];
    for (auto& entry : bucket) {
        if (entry.first == word) {
            ++entry.second;
            return entry.second;
        }
    }

    bucket.push_back(make_pair(word, 1));
    return 1;
}

int WordCount::decrWordCount(std::string word) {
	// STUB - your solution from Lab06 goes here
	    word = makeValidWord(word);
    if (word.empty()) return -1;

    size_t index = hash(word);
    auto& bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == word) {
            if (it->second > 1) {
                --(it->second);
                return it->second;
            } else {
                bucket.erase(it);
                return 0;
            }
        }
    }
    return -1;
}


bool WordCount::isWordChar(char c) {
	// STUB - your solution from Lab06 goes here
	return isalpha(static_cast<unsigned char>(c));
}

std::string WordCount::makeValidWord(std::string word) {
	// STUB - your solution from Lab06 goes here
	    string result;
    for (char c : word) {
        if (isalpha(static_cast<unsigned char>(c)) || c == '-' || c == '\'') {
            result += tolower(static_cast<unsigned char>(c));
        }
    }

    
    while (!result.empty() && !isalpha(result.front()))
        result.erase(result.begin());
    while (!result.empty() && !isalpha(result.back()))
        result.pop_back();

    return result;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	// STUB
	//d::vector<std::pair<std::string, int>> allWords;
	    std::vector<std::pair<std::string, int>> allWords;

    for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto& entry : table[i]) {
            allWords.push_back(entry);
        }
    }

    std::sort(allWords.begin(), allWords.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.first > b.first;  // descending order
    });

    for (const auto& entry : allWords) {
        out << entry.first << "," << entry.second << "\n";
    }
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	// STUB
    std::vector<std::pair<std::string, int>> allWords;

    for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto& entry : table[i]) {
            allWords.push_back(entry);
        }
    }

    std::sort(allWords.begin(), allWords.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    for (const auto& entry : allWords) {
        out << entry.first << "," << entry.second << "\n";
    }
}

void WordCount::addAllWords(std::string text) {
	// STUB
	    std::string word;
    for (size_t i = 0; i <= text.size(); ++i) {
        char c = (i < text.size()) ? text[i] : ' ';
        if (isalnum(c) || c == '-' || c == '\'') {
            word += c;
        } else if (!word.empty()) {
            word = makeValidWord(word);
            if (!word.empty()) {
                incrWordCount(word);
            }
            word.clear();
        }
  }
}
