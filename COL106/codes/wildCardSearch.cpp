/*
  Complexity
  Search.insert delete - O(m) -- m is the size of the key and d is the alphabet size
  BST would have been O(m log n)

 */

#include <iostream>
#include <map>
#include <vector>
#include <memory>

using namespace std;

class TrieNode
{
public:
    map<char, TrieNode *> children;
    bool isEndOfWord; // indicates terminal node
    TrieNode() : isEndOfWord(false) {}
};

// class TrieNode
// {
// public:
//     std::unordered_map<char, std::shared_ptr<TrieNode>> children;
//     bool isEndOfWord = false; // indicates terminal node
// };

class Trie
{
private:
    TrieNode *root;

public:
    Trie() : root(new TrieNode()) {}

    void insert(const std::string &word)
    {
        auto node = root;
        for (char ch : word)
        {
            if (node->children.find(ch) == node->children.end())
            {
                node->children[ch] = new TrieNode();
            }
            // change the pointer to now pointing to the ch's child node
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    // const func -- function cannot modify the object
    // on which it is called -- object's state doesn't change
    //
    bool search(const std::string &word) const
    {
        auto node = root;
        for (char ch : word)
        {
            if (node->children.find(ch) == node->children.end())
            {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }

    // Delete a word from the Trie
    void remove(const std::string &word)
    {
        deleteRecursively(root, word, 0);
    }

    bool deleteRecursively(TrieNode *node, const std::string &word, int depth)
    {
        if (!node)
            return false;

        if (depth == word.size())
        {
            if (node->isEndOfWord)
            {
                node->isEndOfWord = false;
                return node->children.empty();
            }
            return false;
        }

        char ch = word[depth];
        if (node->children.find(ch) == node->children.end())
            return false;

        bool shouldDeleteChild = deleteRecursively(node->children[ch], word, depth + 1);

        if (shouldDeleteChild)
        {
            node->children.erase(ch);

            if (node->children.empty() && !node->isEndOfWord)
            {
                delete node;
                node = nullptr;
                return true;
            }

            // return node->children.empty() && !node->isEndOfWord;
        }

        return false;
    }

    // Pretty print the Trie
    void print() const
    {
        printRecursively(root, "");
    }

    void printRecursively(const TrieNode *node, std::string currentWord) const
    {
        if (node->isEndOfWord)
        {
            std::cout << currentWord << "\n";
        }
        for (const auto &pair : node->children)
        {
            printRecursively(pair.second, currentWord + pair.first);
        }
    }

    vector<string> wildcardMatch(const string &word)
    {
        vector<string> result;
        wildcardMatchRecursively(root, word, 0, result, "");
        return result;
    }

    void wildcardMatchRecursively(TrieNode *node, const string &word, int index, vector<string> &results, string current)
    {
        if (index == word.size())
        {
            if (node->isEndOfWord)
            {
                results.push_back(current);
            }
            return;
        }

        char c = word[index];

        string curr = current;

        if (node->children.find(c) != node->children.end())
        {
            current.push_back(c);
            wildcardMatchRecursively(node->children[c], word, index + 1, results, current);
        }

        if (c == '*')
        {
            for (const auto &child : node->children)
            {
                current = curr;
                current.push_back(child.first);
                wildcardMatchRecursively(child.second, word, index+1, results, current);
            }
        }
    }

};

int main()
{
    Trie trie;
    trie.insert("abple");
    trie.insert("abcle");
    trie.insert("abele");
    trie.insert("abfle");
    trie.insert("abhle");
    trie.insert("app");
    trie.insert("ajp");
    trie.insert("atp");
    trie.insert("acp");
    trie.insert("banana");

    std::cout << "Contents of Trie:" << std::endl;
    trie.print();
    
    std::cout << std::endl;

    vector<string> results = trie.wildcardMatch("*b*le");

    cout << "Searching for *b*le \n-------------------------" << endl;
    
    for (const auto &result : results)
    {
        cout << result << endl;
    }
    cout << "No of Matches = " << results.size() << endl;

    return 0;
}
