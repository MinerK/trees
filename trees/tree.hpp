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
		short balance;
        Node()
        {
            left = nullptr;
            right = nullptr;
			balance = 0;
        }
        Node(K k, T d) : Node()
        {
            key = k;
            data = d;
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
	void insert(K, T, Node*&, bool&);
	Node* locate(K, Node*);
    bool eq(K, K);
    T search(K);
	void traverse(void(*f)(K k, T d));
	void traverse(void(*f)(Node *));
	void _traverse(Node*,void(*f)(K k, T d));
	void _traverse(Node*, void(*f)(Node*));

	unsigned int height(Node*);
	void printinfo();
	void _Balance(Node* );
	void Balance();

};
