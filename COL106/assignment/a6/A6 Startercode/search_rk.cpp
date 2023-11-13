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

SearchEngine::~SearchEngine()
{
    for (int i = 0; i < kiku.size(); i++)
    {
        delete(kiku[i]);
        kiku[i] = nullptr;
    }
    
    
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence) {
    
    Sentence_Node* nenode = new Sentence_Node(book_code,page,paragraph,sentence_no,sentence);
    kiku.push_back(nenode);

}



class polyhash
{
    public:
    int mod = 10000079;
    static vector <int> pow1;
    static vector <ull> pow2;
    int base = 57;

    int diff(int a, int b)
    {
        a = a%mod;
        b = b%mod;

        return (a>b)?(a-b):(b-a);
    }

    vector<int> pref1;
    vector<ull> pref2;

    polyhash(const string& s) : pref1(s.length()+1) , pref2(s.length()+1)
    {
        int n = s.size();
        while ((int)pow1.size() <= n)
        {
            pow1.push_back(1LL*pow1.back()*base%mod);
            pow2.push_back(pow2.back()*base);
        }
        for (size_t i = 0; i < n; ++i)
        {
            pref1[i+1] = (pref1[i] + 1LL * s[i] * pow1[i]) % mod;
            pref2[i+1] = pref2[i] + s[i] * pow2[i];
        }
        
    }

    ~polyhash()
    {
        //cout << "polyhash del";
    }

    pair<int,ull> operator()(const int pos, const int len,const int mxpow = 0)const
    {
        int hash1 = pref1[pos+len] - pref1[pos];
        ull hash2 = pref2[pos+len] - pref2[pos];
        if (hash1 < 0) hash1 += mod;
        if (mxpow != 0) {
            hash1 = 1LL * hash1 * pow1[mxpow-(pos+len-1)] % mod;
            hash2 *= pow2[mxpow-(pos+len-1)];
        }
        return std::make_pair(hash1, hash2);
    }

};

vector<int> polyhash::pow1{1};
vector<ull> polyhash::pow2{1};

vector<int> offs;



void rka(string sent, string pat)
{
    const int mxpow = max(sent.size(),pat.size());
    polyhash hasha(sent), hashb(pat);

    std::pair<int,ull> nudes = hashb(0,pat.size(),mxpow);

    for (int i = 0; i  <= (int)sent.size() - (int)pat.size(); ++i)
    {
        if (hasha(i, pat.size(), mxpow) == nudes) {
            bool issame = true;
            for (int j = 0; j < pat.size(); j++)
            {
                if (pat[j] != sent[i+j])
                {
                    issame = false;
                    break;
                }
                
            }

            if (issame == true)
            {
                offs.push_back(i);
            }
            
        }
    }
}

Node* SearchEngine::search(string pattern, int& n_matches)
{
    vector<Node*> ll;
    vector<Sentence_Node*> s;
    string patn = to_lower(pattern);

    for (int i = 0; i < kiku.size(); i++)
    {
        rka(kiku[i]->sentence, patn);

        for (int j = 0; j < offs.size(); j++)
        {
            Node* newnode = new Node(kiku[i]->book_code,kiku[i]->page,kiku[i]->paragraph,kiku[i]->sentence_no,offs[j]);
            ll.push_back(newnode);
        }

        offs.clear();
        
    }
    

    n_matches += ll.size();


    if (ll.size() != 0)
    {
        for (int i = 0; i < ll.size()-1; i++)
        {
            ll[i]->right = ll[i+1];

        }
        return ll[0];
    }

    return nullptr;
    
    
}
