#include <bits/stdc++.h>
#include <chrono>
#include "search_KMP.cpp"
// #include "search_rk.cpp"
#include "Node.cpp"
using namespace std;

// #define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"
#define FILENAME "text_combined.txt"

int main() 
{
    int countin = 0;
    std::ifstream inputFile(FILENAME);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return 1;
    }
    std::ofstream outfile("Occurrences.txt");

    std::string tuple;
    std::string sentence;

    auto start = chrono::high_resolution_clock::now();
    SearchEngine d;

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        std::vector<int> metadata;    
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata.push_back(num);
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata.push_back(num);
            }
        }

        // Now we have the string in sentence
        // And the other info in metadata
        // Add to the dictionary

        // Insert in the dictionary
        d.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        countin++;
    }

    inputFile.close();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);

    cout << endl;
    cout << "Insert Time (milli-seconds) : " << duration.count() << endl;
    

    int count = 0;
    string search_pattern;
    cout << "Enter search string : ";
    cin >> search_pattern;
    start = chrono::high_resolution_clock::now();
    Node* search_results = d.search(search_pattern, count);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop-start);

    cout << "Search Time (milli-seconds) : " << duration.count() << endl;

    cout << "No of occurences of " << search_pattern << " is : " << count << endl;

    Node* traversal = search_results;
    while (traversal != nullptr)
    {
        outfile << "In book "<< traversal->book_code << ", In page " << traversal->page << ", In paragraph "<< traversal->paragraph << ", In sentence " << traversal->sentence_no << " at " << traversal->offset << endl;
        traversal = traversal->right;
    }

    cout << "Success!" <<endl;
}