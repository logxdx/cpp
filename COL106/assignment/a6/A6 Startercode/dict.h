// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict {
private:
    // You can add attributes/helper functions here
    
    class TreeNode {
        
        public:
        
            string key;
            int height;
            int count=0;
            
            TreeNode* left = NULL;
            TreeNode* right = NULL;

            TreeNode();
            TreeNode(string k);

            TreeNode* LeftLeftRotation(); // case 1
            TreeNode* RightRightRotation(); // case 2

            ~TreeNode();
            
        };

    class AVL_TREE {

        public:

            int size = 0;
            TreeNode* root = NULL;

            AVL_TREE();

            // Insert a key in the symbol table, there is no value now
            Dict::TreeNode* insert_recursive(string k, Dict::TreeNode* node);
            void insert(string k);

            // Find the memory address corresponding to the variable in the symbol table
            int search(string k);

            // Pretty print Tree
            void print_AVL_Tree(TreeNode* node, int depth = 0);
            void write_AVL_Tree(TreeNode* node, vector<string> &words);

            // Get height
            int getHeight(Dict::TreeNode* node);

            // Height(left tree) - Height(right tree)
            int getBalance(Dict::TreeNode* node);

            // Balances the tree
            Dict::TreeNode* balancer(Dict::TreeNode* node); 

            // Get the minimum element
            Dict::TreeNode* findMin(Dict::TreeNode* node);

            // Get root 
            TreeNode* get_root();

            // Helper function to delete tree
            void delete_tree(TreeNode* node);

            ~AVL_TREE();
            
    };    

    AVL_TREE* tree;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};