
#include <iostream>
#include <string>
#include <vector>

const int prime = 101; // A prime number used for hashing

// Function to calculate the hash value of a substring
int calculateHash(const std::string& str, int start, int end) {
    int hash = 0;
    for (int i = start; i < end; ++i) {
        hash = (hash * prime + str[i]) % prime;
    }
    return hash;
}

// Function to search for a phrase in a sentence using Rabin-Karp
std::vector<int> searchRabinKarp(const std::string& sentence, const std::string& phrase) {
    int sentenceLength = sentence.length();
    int phraseLength = phrase.length();
    int phraseHash = calculateHash(phrase, 0, phraseLength);
    std::vector<int> occurrences;

    for (int i = 0; i <= sentenceLength - phraseLength; ++i) {
        int currentHash = calculateHash(sentence, i, i + phraseLength);

        if (currentHash == phraseHash) {
            // If the hash values match, compare the substrings
            if (sentence.substr(i, phraseLength) == phrase) {
                occurrences.push_back(i);
            }
        }
    }

    return occurrences;
}

int main() {
    std::string sentence = "The quick brown fox jumps over the lazy dog, the quick brown fox jumps over a lazy dog. He owns a Mercedes S-class.";
    std::string phrase = "hell";

    std::vector<int> positions = searchRabinKarp(sentence, phrase);

    if (positions.empty()) {
        std::cout << "Phrase not found in the sentence." << std::endl;
    } else {
        std::cout << "Phrase found at positions: ";
        for (int pos : positions) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
