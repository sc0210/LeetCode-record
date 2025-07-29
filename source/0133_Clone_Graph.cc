/* 133. Clone Graph */

#include <map>
#include <vector>

using std::map;
using std::vector;

// Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        map<Node *, Node *> hp;
        return dfs(node, hp);
    }
    Node *dfs(Node *node, map<Node *, Node *> &hp)
    {
        // NULL
        if (node == nullptr)
            return nullptr;
        // already visited
        if (hp.count(node))
            return hp[node];

        // not visited, create an new node
        Node *copy = new Node(node->val);
        hp[node] = copy;
        for (auto nei : node->neighbors) {
            copy->neighbors.push_back(dfs(nei, hp));
        }
        return copy;
    }
};