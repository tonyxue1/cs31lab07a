#include "WordCount.h"
#include "tddFuncs.h"
#include <iostream>
#include <sstream>

int main() {
    WordCount wc;
    wc.addAllWords("Sentence is a sentence");

    ASSERT_EQUALS(2, wc.getWordCount("sentence"));
    ASSERT_EQUALS(1, wc.getWordCount("is"));
    ASSERT_EQUALS(1, wc.getWordCount("a"));
    ASSERT_EQUALS(4, wc.getTotalWords());
    ASSERT_EQUALS(3, wc.getNumUniqueWords());

    std::ostringstream ossWord;
    wc.dumpWordsSortedByWord(ossWord);
    std::string expectedWord =
        "sentence,2\n"
        "is,1\n"
        "a,1\n";
    ASSERT_EQUALS(expectedWord, ossWord.str());

    std::ostringstream ossOcc;
    wc.dumpWordsSortedByOccurence(ossOcc);
    std::string expectedOcc =
        "a,1\n"
        "is,1\n"
        "sentence,2\n";
    ASSERT_EQUALS(expectedOcc, ossOcc.str());

    wc.addAllWords("SENTENCE sentence");
    ASSERT_EQUALS(4, wc.getWordCount("sentence"));

    std::ostringstream ossOcc2;
    wc.dumpWordsSortedByOccurence(ossOcc2);
    std::string expectedOcc2 =
        "a,1\n"
        "is,1\n"
        "sentence,4\n";
    ASSERT_EQUALS(expectedOcc2, ossOcc2.str());

    std::cout << "All Lab07a tests passed!" << std::endl;
    return 0;
}

