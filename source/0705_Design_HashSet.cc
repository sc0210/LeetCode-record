/* 705. Design HashSet */

class Node
{
public:
    int val;
    Node *next;
    Node() : val(-1), next(nullptr) {}
    Node(int x) : val(x), next(nullptr) {}
};

class MyHashSet
{
public:
    Node head;  // dummy head node

    MyHashSet() { head.next = nullptr; }

    void add(int key)
    {
        if (contains(key))
            return;

        Node *newNode = new Node(key);
        newNode->next = head.next;
        head.next = newNode;
    }

    void remove(int key)
    {
        Node *cur = &head;
        while (cur->next) {
            if (cur->next->val == key) {
                Node *toDelete = cur->next;
                cur->next = cur->next->next;
                delete toDelete;
                return;
            } else {
                cur = cur->next;
            }
        }
    }

    bool contains(int key)
    {
        Node *cur = head.next;
        while (cur) {
            if (cur->val == key)
                return true;
            else
                cur = cur->next;
        }
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */