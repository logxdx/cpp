// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SearchEngine {
private:
    // You can add attributes/helper functions here

    class Sentence_Node {
        public: 
            Sentence_Node* left;
            Sentence_Node* right;

            int book_code;
            int page;
            int paragraph;
            int sentence_no;
            string sentence;

            Sentence_Node();
            Sentence_Node(int b_code, int pg, int para, int s_no, string sent);
    };
    
    vector <SearchEngine::Sentence_Node> kiku;


public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};