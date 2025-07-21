/* 211 211. Design Add and Search Words Data Structure */

#include <string>
#include <vector>
using std::string;
using std::vector;

class TrieNode
{
public:
    vector<TrieNode *> child;
    bool endOfWord;

    TrieNode() : child(26, nullptr), endOfWord(false) {}
};

class WordDictionary
{
public:
    TrieNode *root;

    WordDictionary() { root = new TrieNode(); }

    void addWord(string word)
    {
        TrieNode *cur = root;
        for (char c : word) {
            // not existed, create one
            if (cur->child[c - 'a'] == nullptr) {
                cur->child[c - 'a'] = new TrieNode();
            }
            // existed, iterate next
            cur = cur->child[c - 'a'];
        }
        // Add the end sign
        cur->endOfWord = true;
    }

    bool search(string word) { return dfs(word, 0, root); }

private:
    bool dfs(string word, int st, TrieNode *root)
    {
        TrieNode *cur = root;

        for (int i = st; i < word.size(); i++) {
            char c = word[i];
            // handle '.' in the word
            if (c == '.') {
                for (TrieNode *ptr : cur->child) {
                    // when at least one solution get, return ture
                    if (ptr != nullptr && dfs(word, i + 1, ptr)) {
                        return true;
                    }
                }
                // when there are no compatitable solution
                return false;
            }
            // else, normal case
            else {
                if (cur->child[c - 'a'] == nullptr) {
                    // not existed, return false
                    return false;
                }
                // shift to next
                cur = cur->child[c - 'a'];
            }
        }
        // wether match to the endOfWord
        return cur->endOfWord;
    }
};
