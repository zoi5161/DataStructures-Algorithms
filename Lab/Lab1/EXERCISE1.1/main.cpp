#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

int countDistinctWords(string sentence) 
{
    set<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) 
    {
        if((word[word.length()-1] >= 'a' && word[word.length()-1] <= 'z') || (word[word.length()-1] >= 'A' && word[word.length()-1] <= 'Z'))
            words.insert(word);
    }
    return words.size();
}

int countSentences(string sentence)
{
    string s = sentence;
    int cnt = 0;
    for(int i = 0; i < sentence.length(); i++)
        if((i == s.length() - 1) || (s[i] == '.' && (s[i-1] == ' ' || s[i+1] == ' ')) || (s[i] == '!' && (s[i-1] == ' ' || s[i+1] == ' ')) || (s[i] == '?' && (s[i-1] == ' ' || s[i+1] == ' ')))
            cnt++;
    return cnt;
}

int main()
{
    string s = "";
    int k = 0;
    ifstream fin("input1.1.txt");

    if(fin.is_open())
    {
        char ch;
        while(fin.get(ch))
        {
            if(ch == '\n')
            {
                ch = ' ';
                k++;
            }
            s += ch;
        }
        cout << "Number of words: " << countDistinctWords(s) + k << endl;
        cout << "Number of sentences: " << countSentences(s);
        fin.close();
    }
    else
        cout << "Can't open file";
    return 0;
}