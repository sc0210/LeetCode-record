/* 208. Implement Trie (Prefix Tree) */

#include <string>
#include <unordered_map>
using std::string;

/* Tire Node definition */
class TrieNode
{
public:
    std::unordered_map<char, TrieNode *> child;
    bool endOfTrie = false;
};

class PrefixTree
{
    TrieNode *root;

public:
    PrefixTree() { root = new TrieNode(); }

    void insert(string word)
    {
        TrieNode *cur = root;
        for (char c : word) {
            // When not existed, create new node to store
            if (cur->child.find(c) == cur->child.end()) {
                cur->child[c] = new TrieNode();
            }
            // When existed, iterate to next node
            cur = cur->child[c];
        }
        // Mark the last node as end
        cur->endOfTrie = true;
    }

    bool search(string word)
    {
        TrieNode *cur = root;
        for (char c : word) {
            // When not existed, create new node to store
            if (cur->child.find(c) == cur->child.end()) {
                return false;
            }
            // When existed, iterate to next char
            cur = cur->child[c];
        }
        // Verify if it match the end of the string store before
        return cur->endOfTrie;
    }

    bool startsWith(string prefix)
    {
        TrieNode *cur = root;
        for (char c : prefix) {
            // When not existed, create new node to store
            if (cur->child.find(c) == cur->child.end()) {
                return false;
            }
            // When existed, iterate to next char
            cur = cur->child[c];
        }
        /*
        Different to search()
        Only sheck if there existed a string that start with prefix
        Don't care the rest of the string wether is match or not
        */
        return true;
    }
};
