#include <string>
#include "treenode.h"

using namespace std;

// Encodes a tree to a single string.
std::string serialize(TreeNode *root)
{
    vector<string> res;
    dfsSerialize(root, res);
    return join(res, ",");
}

// Decodes your encoded data to tree.
TreeNode *deserialize(string data)
{
    vector<string> val = split(data, ',');
    int i = 0;
    return dfsDeserialize(val, i);
}

void dfsSerialize(TreeNode *node, vector<string> &res)
{
    if (node == nullptr) {
        res.push_back("N");
        return;
    }
    res.push_back(to_string(node->val));
    dfsSerialize(node->left, res);
    dfsSerialize(node->right, res);
}

TreeNode *dfsDeserialize(vector<string> &val, int &i)
{
    if (val[i] == "N") {
        i++;
        return NULL;
    }
    TreeNode *node = new TreeNode(stoi(val[i]));
    i++;
    node->left = dfsDeserialize(val, i);
    node->right = dfsDeserialize(val, i);
    return node;
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

string join(const vector<string> &v, const string &delim)
{
    ostringstream s;
    for (const auto &i : v) {
        if (&i != &v[0])
            s << delim;
        s << i;
    }
    return s.str();
}

int main(void)
{
    return 0;
}