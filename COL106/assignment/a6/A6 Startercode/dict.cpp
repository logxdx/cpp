
// Do NOT add any other includes
#include "dict.h"

// ------------------------------------------------- //
// Start TreeNode Class

Dict::TreeNode::TreeNode() {

    key = "";
    height = 1;

}

Dict::TreeNode::TreeNode(string k){

    key = k;
    height = 1;

}

Dict::TreeNode* Dict::TreeNode::LeftLeftRotation(){

    TreeNode* newRoot = right;

    right = newRoot->left;
    newRoot->left = this;

    height = max((left ? left->height : 0), (right ? right->height : 0)) + 1;
    newRoot->height = max((newRoot->left ? newRoot->left->height : 0), (newRoot->right ? newRoot->right->height : 0)) + 1;

    return newRoot;

}

Dict::TreeNode* Dict::TreeNode::RightRightRotation(){

    TreeNode* newRoot = left;
    
    left = newRoot->right;
    newRoot->right = this;

    height = max((left ? left->height : 0), (right ? right->height : 0)) + 1;
    newRoot->height = max((newRoot->left ? newRoot->left->height : 0), (newRoot->right ? newRoot->right->height : 0)) + 1;

    return newRoot;
    
}

Dict::TreeNode::~TreeNode() {}

// End TreeNode class
// ------------------------------------------------- //


// ------------------------------------------------- //
// Start AVL_TREE class

Dict::AVL_TREE::AVL_TREE() {}

int Dict::AVL_TREE::getHeight(TreeNode* node) {
    
    if (node == NULL) {
        return 0;
    }
    return node->height;

}

int Dict::AVL_TREE::getBalance(TreeNode* node) {
        
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);

}

Dict::TreeNode* Dict::AVL_TREE::balancer(TreeNode* node) {
    
    if (node == nullptr)
        return node;

    int balanceFactor = getBalance(node);

    // Left heavy
    if (balanceFactor > 1) {
        if (getBalance(node->left) < 0) {
            node->left = node->left->LeftLeftRotation();
        }
        return node->RightRightRotation();
    }
    
    // Right heavy
    if (balanceFactor < -1) {
        if (getBalance(node->right) > 0) {
            node->right = node->right->RightRightRotation();
        }
        return node->LeftLeftRotation();
    }
    
    return node;

}

Dict::TreeNode* Dict::AVL_TREE::findMin(TreeNode* node) {

    while (node->left != nullptr) {
        node = node->left;
    }
    
    return node;

}

Dict::TreeNode* Dict::AVL_TREE::insert_recursive(string k, TreeNode* node) {
    
    if (node == NULL) {
        node = new TreeNode(k);
        node->count++;
        size++;
        return node;
    }

    if (k < node->key) {
        node->left = insert_recursive(k, node->left);
    }
    else if (k > node->key) {
        node->right = insert_recursive(k, node->right);
    }
    else {
        node->count++;
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    return balancer(node);

}

void Dict::AVL_TREE::insert(string k){

    root = insert_recursive(k, root);

}

int Dict::AVL_TREE::search(string k){

    TreeNode* current = root;

    while (current != NULL) {
        if (k == current->key) {
            return current->count;
        }
        else if (k < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return -1;

}

Dict::TreeNode* Dict::AVL_TREE::get_root(){

    return root;

}

void Dict::AVL_TREE::print_AVL_Tree(TreeNode* root, int depth) {
    
        if (root == NULL) {
            return;
        }
    
        print_AVL_Tree(root->right, depth + 1);

        for (int i = 0; i < 2*depth; i++) {
            cout << "   ";
        }
        cout << root->key << endl << endl << endl;
        
        print_AVL_Tree(root->left, depth + 1);

}
//int countings = 0;

void Dict::AVL_TREE::write_AVL_Tree(TreeNode* root, vector<string> &words) {
    
        if (root == NULL) {
            return;
        }
    
        write_AVL_Tree(root->left, words);

        string s;
        // s += root->key + ", " + to_string(search(root->key));
        s += root->key + ", " + to_string(root->count);
        words.push_back(s);
        //countings += root->count;


        write_AVL_Tree(root->right, words);

}

void Dict::AVL_TREE::delete_tree(TreeNode* node) {

    if (node != NULL) {       
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
    return;

}

Dict::AVL_TREE::~AVL_TREE() {

    if (root != NULL) {
        delete_tree(root);
    }
    root = NULL;

}

// End AVL_TREE class
// ------------------------------------------------- //


// ------------------------------------------------- //
//  Helper Functions to process statements

vector<string> remove_punctuations(string sentence) {

    // Replace punctuations with space
    for (int i = 0; i < sentence.length(); i++) {

        
        string s(1, sentence[i]);

        if (
            s == "." || s == "," || s == "-" || s == ":" || s == "!" || s == "\"" ||
            s == "\'" || s == "(" || s == ")" || s == "?" || s == "[" || s == "]" || 
            s == ";" || s == "@"
            )
        {
            sentence[i] = ' ';
        }
        else {
            sentence[i] = tolower(sentence[i]);
        }
    }

    vector<string> words;
 
    int start, end;
    start = end = 0;
 
    string delimiter = " ";
 
    while ((start = sentence.find_first_not_of(delimiter, end)) != string::npos) {
        end = sentence.find(delimiter, start);
        words.push_back(sentence.substr(start, end - start));
    }
 
    return words;
}

// ------------------------------------------------- //


// ------------------------------------------------- //
// Start Dictionary class

Dict::Dict(){ 
    tree = new AVL_TREE();
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    
    vector<string> words = remove_punctuations(sentence);

    for (int i = 0; i < words.size(); i++) {
        tree->insert(words[i]);
    }

    return;

}

int Dict::get_word_count(string word){
    
    return tree->search(word);

}

void Dict::dump_dictionary(string filename){
    
    ofstream file;
    file.open(filename);

    vector<string> words;
    tree->write_AVL_Tree(tree->get_root(), words);
    for (int i = 0; i < words.size(); i++) {
        file << words[i] << endl;
    }

    file.close();
    return;
}

Dict::~Dict(){
    // Implement your function here
    tree->~AVL_TREE();
}

//  End Dictionay class
// ------------------------------------------------- //
