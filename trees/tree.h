#pragma once
template <class K, class T>
class tree
{
private:
    struct Node
    {
        K key;
        T data;
        Node* left;
        Node* right;
        Node()
        {
            left = nullptr;
            right = nullptr;
        }
        Node(K k, T d) : Node()
        {
            key = k;
            data = d;
        }
        Node(const Node& c) : Node(c.key, c.data)
        {
            left = c.left;
            right = c.right;
        }
    };
    Node* root;
    bool(*rule)(K, K);
    
public:
    tree();
    tree(bool(*f)(K, K));
    tree(bool(*f)(K, K), K k, T d);
    ~tree();
    
    void insert(K, T);
    void deletenode(K);
    bool intree(K);
    bool eq(K, K);
    T search(K);
    
    
    
};
