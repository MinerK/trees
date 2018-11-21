#pragma once
#include <iostream>

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
    
    void _traverse(Node*,void(*f)(K k, T d));
    void _traverse(Node*, void(*f)(Node*));
    void traverse(void(*f)(Node *));
    
    void inline LL(Node*&,Node*&);
    void inline RR(Node*&,Node*&);
    
    void BalanceL(Node*&, bool&);
    void BalanceR(Node*&, bool&);
    
    void del(Node*&, bool&, Node*&);
    void _delete(K, Node*&,bool&);
    
    bool eq(K, K);
    void insert(K, T, Node*&, bool&);
    Node* locate(K, Node*);
	unsigned int height(Node*);
    
public:
    tree();
    tree(bool(*f)(K, K));
    tree(bool(*f)(K, K), K k, T d);
    ~tree();
    
    void Add(K, T);
    T Find(K);
    void Traverse(void(*f)(K k, T d));
    void Remove(K);
	void Change(K, T);
    void Print();
};
