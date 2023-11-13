// Do NOT add any other includes
#include "search.h"
#define ull unsigned long long

string to_lower(string sentence) {
    
    for (int i = 0; i < sentence.length(); i++) {
        sentence[i] = tolower(sentence[i]);
    }
    return sentence;
}


SearchEngine::Sentence_Node::Sentence_Node() {
    left = nullptr;
    right = nullptr;
    book_code = 0;
    page = 0;
    paragraph = 0;
    sentence_no = 0;
    sentence = "";
}

SearchEngine::Sentence_Node::Sentence_Node(int b_code, int pg, int para, int s_no, string sent) {
    left = nullptr;
    right = nullptr;
    book_code = b_code;
    page = pg;
    paragraph = para;
    sentence_no = s_no;
    sentence = to_lower(sent);
}


SearchEngine::SearchEngine() {

}


SearchEngine::~SearchEngine() {

}


void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence) {
    Sentence_Node nenode = Sentence_Node(book_code,page,paragraph,sentence_no,sentence);
    kiku.push_back(nenode);
}

vector<int> makelps(std::string pat) {

    vector<int> lps(pat.length());
    lps[0] = 0;
    int len = 0;
    int i =1;

    while (true) {

        if(i == pat.length()) {break;}

        if(pat[len] == pat[i]) {

            len++;
            lps[i] = len;
            i++;
        }

        else if (pat[len] != pat[i]) {

            if(len != 0)
            {
                len = lps[len-1];
            }

            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

vector<int> kmp (string txt, string pat) {

    int i = 0;
    int j = 0;
    int M = pat.length();
    vector<int> offs;
    vector<int> lps = makelps(pat);

    while (true) { if(i > txt.length()) {break;}
    
        if(j == M)
        {
            offs.push_back(i - M);
            j = lps[j-1];
        }
        if(txt[i] == pat[j])
        {  
            i++;
            j++;
        }

        else
        {
            if(j>0)
            {
                j = lps[j-1];
            }

            else
            {
                i++;
            }
        }
    }

    return offs;
    
}


Node* SearchEngine::search(string pattern, int& n_matches)
{
    vector<Node*> ll;
    vector<Sentence_Node*> s;
    string patn = to_lower(pattern);

    for (int i = 0; i < kiku.size(); i++) {

        vector<int> offsets = kmp(kiku[i].sentence,patn);
        for (int j = 0; j < offsets.size(); j++) {
            Node* newnode = new Node(kiku[i].book_code,kiku[i].page,kiku[i].paragraph,kiku[i].sentence_no,offsets[j]);
            ll.push_back(newnode);
        }

    }
    
    n_matches += ll.size();
   
    if (ll.size() != 0) {
        for (int i = 0; i < ll.size()-1; i++)
        {
            ll[i]->right = ll[i+1];

        }
        return ll[0];
    }

    return nullptr;
    
    
}
