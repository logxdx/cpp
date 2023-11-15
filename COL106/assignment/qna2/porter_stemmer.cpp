#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PorterStemmer
{
public:
    template <typename InputIt, typename UnaryPredicate>
    bool my_any_of(InputIt first, InputIt last, UnaryPredicate p)
    {
        for (; first != last; ++first)
        {
            if (p(*first))
                return true;
        }
        return false;
    }

    bool isCons(char letter)
    {
        return !(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u');
    }

    bool isConsonant(const std::string &word, int i)
    {
        char letter = word[i];
        if (isCons(letter))
        {
            if (letter == 'y' && isCons(word[i - 1]))
                return false;
            else
                return true;
        }
        else
        {
            return false;
        }
    }

    bool isVowel(const std::string &word, int i)
    {
        return !isConsonant(word, i);
    }

    bool endsWith(const std::string &stem, const std::string &letter)
    {
        return std::equal(letter.rbegin(), letter.rend(), stem.rbegin());
    }

    bool containsVowel(const std::string &stem)
    {
        return my_any_of(stem.begin(), stem.end(), [this](char c)
                         { return !isCons(c); });
    }

    bool doubleCons(const std::string &stem)
    {
        if (stem.length() >= 2)
            return isConsonant(stem, stem.length() - 1) && isConsonant(stem, stem.length() - 2);
        else
            return false;
    }

    std::string getForm(const std::string &word)
    {
        std::string formStr;
        char prev = '\0';

        for (char c : word)
        {
            if (isConsonant(word, c))
            {
                if (prev != 'C')
                    formStr += 'C';
                prev = 'C';
            }
            else
            {
                if (prev != 'V')
                    formStr += 'V';
                prev = 'V';
            }
        }
        return formStr;
    }

    vector<int> makelps(std::string pat)
    {

        vector<int> lps(pat.length());

        lps[0] = 0;

        int len = 0;

        int i = 1;

        while (true)
        {

            if (i == pat.length())
            {
                break;
            }

            if (pat[len] == pat[i])
            {

                len++;

                lps[i] = len;

                i++;
            }

            else if (pat[len] != pat[i])
            {

                if (len != 0)

                {

                    len = lps[len - 1];
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

    vector<int> kmp(string txt, string pat)
    {

        int i = 0;

        int j = 0;

        int M = pat.length();

        vector<int> offs;

        vector<int> lps = makelps(pat);

        while (true)
        {
            if (i > txt.length())
            {
                break;
            }

            if (j == M)

            {

                offs.push_back(i - M);

                j = lps[j - 1];
            }

            if (txt[i] == pat[j])

            {

                i++;

                j++;
            }

            else

            {

                if (j > 0)

                {

                    j = lps[j - 1];
                }

                else

                {

                    i++;
                }
            }
        }

        return offs;
    }

    auto getM(const std::string &word)
    {
        std::string form = getForm(word);
        // auto a = std::count(form.begin(), form.end(), 'd');
        int a = kmp(form, "VC").size();
        return a;
    }

    bool cvc(const std::string &word)
    {
        if (word.length() >= 3)
        {
            char third = word[word.length() - 1];
            if (isConsonant(word, word.length() - 3) && isVowel(word, word.length() - 2) && isConsonant(word, word.length() - 1))
            {
                if (third != 'w' && third != 'x' && third != 'y')
                    return true;
            }
        }
        return false;
    }

    std::string replace(const std::string &orig, const std::string &rem, const std::string &rep)
    {
        size_t result = orig.rfind(rem);
        std::string base = orig.substr(0, result);
        return base + rep;
    }

    std::string replaceM0(const std::string &orig, const std::string &rem, const std::string &rep)
    {
        size_t result = orig.rfind(rem);
        std::string base = orig.substr(0, result);
        if (getM(base) > 0)
            return base + rep;
        else
            return orig;
    }

    std::string replaceM1(const std::string &orig, const std::string &rem, const std::string &rep)
    {
        size_t result = orig.rfind(rem);
        std::string base = orig.substr(0, result);
        if (getM(base) > 1)
            return base + rep;
        else
            return orig;
    }

    std::string step1a(std::string word)
    {
        if (endsWith(word, "sses"))
            word = replace(word, "sses", "ss");
        else if (endsWith(word, "ies"))
            word = replace(word, "ies", "i");
        else if (endsWith(word, "ss") || endsWith(word, "s"))
            word = replace(word, "s", "");
        return word;
    }

    std::string step1b(std::string word)
    {
        bool flag = false;
        if (endsWith(word, "eed"))
        {
            std::string base = word.substr(0, word.length() - 3);
            if (getM(base) > 0)
                word = base + "ee";
        }
        else if (endsWith(word, "ed"))
        {
            std::string base = word.substr(0, word.length() - 2);
            if (containsVowel(base))
            {
                word = base;
                flag = true;
            }
        }
        else if (endsWith(word, "ing"))
        {
            std::string base = word.substr(0, word.length() - 3);
            if (containsVowel(base))
            {
                word = base;
                flag = true;
            }
        }

        if (flag)
        {
            if (endsWith(word, "at") || endsWith(word, "bl") || endsWith(word, "iz"))
                word += "e";
            else if (doubleCons(word) && !endsWith(word, "l") && !endsWith(word, "s") && !endsWith(word, "z"))
                word = word.substr(0, word.length() - 1);
            else if (getM(word) == 1 && cvc(word))
                word += "e";
        }
        return word;
    }

    std::string step1c(std::string word)
    {
        if (endsWith(word, "y"))
        {
            std::string base = word.substr(0, word.length() - 1);
            if (containsVowel(base))
                word = base + "i";
        }
        return word;
    }

    std::string step2(std::string word)
    {
        if (endsWith(word, "ational"))
            word = replaceM0(word, "ational", "ate");
        else if (endsWith(word, "tional"))
            word = replaceM0(word, "tional", "tion");
        else if (endsWith(word, "enci"))
            word = replaceM0(word, "enci", "ence");
        else if (endsWith(word, "anci"))
            word = replaceM0(word, "anci", "ance");
        else if (endsWith(word, "izer"))
            word = replaceM0(word, "izer", "ize");
        else if (endsWith(word, "abli"))
            word = replaceM0(word, "abli", "able");
        else if (endsWith(word, "alli"))
            word = replaceM0(word, "alli", "al");
        else if (endsWith(word, "entli"))
            word = replaceM0(word, "entli", "ent");
        else if (endsWith(word, "eli"))
            word = replaceM0(word, "eli", "e");
        else if (endsWith(word, "ousli"))
            word = replaceM0(word, "ousli", "ous");
        else if (endsWith(word, "ization"))
            word = replaceM0(word, "ization", "ize");
        else if (endsWith(word, "ation"))
            word = replaceM0(word, "ation", "ate");
        else if (endsWith(word, "ator"))
            word = replaceM0(word, "ator", "ate");
        else if (endsWith(word, "alism"))
            word = replaceM0(word, "alism", "al");
        else if (endsWith(word, "iveness"))
            word = replaceM0(word, "iveness", "ive");
        else if (endsWith(word, "fulness"))
            word = replaceM0(word, "fulness", "ful");
        else if (endsWith(word, "ousness"))
            word = replaceM0(word, "ousness", "ous");
        else if (endsWith(word, "aliti"))
            word = replaceM0(word, "aliti", "al");
        else if (endsWith(word, "iviti"))
            word = replaceM0(word, "iviti", "ive");
        else if (endsWith(word, "biliti"))
            word = replaceM0(word, "biliti", "ble");
        return word;
    }

    std::string step3(std::string word)
    {
        if (endsWith(word, "icate"))
            word = replaceM0(word, "icate", "ic");
        else if (endsWith(word, "ative"))
            word = replaceM0(word, "ative", "");
        else if (endsWith(word, "alize"))
            word = replaceM0(word, "alize", "al");
        else if (endsWith(word, "iciti"))
            word = replaceM0(word, "iciti", "ic");
        else if (endsWith(word, "ful"))
            word = replaceM0(word, "ful", "");
        else if (endsWith(word, "ness"))
            word = replaceM0(word, "ness", "");
        return word;
    }

    std::string step4(std::string word)
    {
        if (endsWith(word, "al"))
            word = replaceM1(word, "al", "");
        else if (endsWith(word, "ance"))
            word = replaceM1(word, "ance", "");
        else if (endsWith(word, "ence"))
            word = replaceM1(word, "ence", "");
        else if (endsWith(word, "er"))
            word = replaceM1(word, "er", "");
        else if (endsWith(word, "ic"))
            word = replaceM1(word, "ic", "");
        else if (endsWith(word, "able"))
            word = replaceM1(word, "able", "");
        else if (endsWith(word, "ible"))
            word = replaceM1(word, "ible", "");
        else if (endsWith(word, "ant"))
            word = replaceM1(word, "ant", "");
        else if (endsWith(word, "ement"))
            word = replaceM1(word, "ement", "");
        else if (endsWith(word, "ment"))
            word = replaceM1(word, "ment", "");
        else if (endsWith(word, "ent"))
            word = replaceM1(word, "ent", "");
        else if (endsWith(word, "ou"))
            word = replaceM1(word, "ou", "");
        else if (endsWith(word, "ism"))
            word = replaceM1(word, "ism", "");
        else if (endsWith(word, "ate"))
            word = replaceM1(word, "ate", "");
        else if (endsWith(word, "iti"))
            word = replaceM1(word, "iti", "");
        else if (endsWith(word, "ous"))
            word = replaceM1(word, "ous", "");
        else if (endsWith(word, "ive"))
            word = replaceM1(word, "ive", "");
        else if (endsWith(word, "ize"))
            word = replaceM1(word, "ize", "");
        else if (endsWith(word, "ion"))
        {
            size_t result = word.rfind("ion");
            std::string base = word.substr(0, result);
            if (getM(base) > 1 && (endsWith(base, "s") || endsWith(base, "t")))
                word = base;
            word = replaceM1(word, "", "");
        }
        return word;
    }

    std::string step5a(std::string word)
    {
        if (endsWith(word, "e"))
        {
            std::string base = word.substr(0, word.length() - 1);
            if (getM(base) > 1 || (getM(base) == 1 && !cvc(base)))
                word = base;
        }
        return word;
    }

    std::string step5b(std::string word)
    {
        if (getM(word) > 1 && doubleCons(word) && endsWith(word, "l"))
            word = word.substr(0, word.length() - 1);
        return word;
    }

    std::string stem(std::string word)
    {
        word = step1a(word);
        word = step1b(word);
        word = step1c(word);
        word = step2(word);
        word = step3(word);
        word = step4(word);
        word = step5a(word);
        word = step5b(word);
        return word;
    }
};

// int main()
// {
//     PorterStemmer porter;
//     std::string inputWord;

//     // while (inputWord != "q")
//     // {
//     //     std::cout << "Original Word: " << inputWord << std::endl;
//     //     std::string stemmedWord = porter.stem(inputWord);
//     //     std::cout << "Stemmed Word: " << stemmedWord << std::endl;
//     // }

//     cin >> inputWord;
//     cout << porter.stem(inputWord);
//     return 0;
// }
