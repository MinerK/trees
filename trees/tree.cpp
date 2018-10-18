#include "tree.hpp"

template <class K, class T>
tree<K, T>::tree()
{
    root = nullptr;
    rule = nullptr;
}

template<class K,class T>
tree<K,T>::tree(bool(*f)(K, K))
{
    root = nullptr;
    rule = f;
}


template<class K, class T>
tree<K,T>::tree(bool(*f)(K, K), K k, T d) : tree(f)
{
    root = new Node(k, d);
}

template <class K, class T>
tree<K, T>::~tree()
{
    
}

template<class K, class T>
bool tree<K, T>::eq(K k1, K k2)
{
    return (!(rule(k1, k2) || rule(k2, k1)));
}

template <class K, class T>
bool tree<K,T>::intree(K k)
{
    Node* cursor = root;
    bool stop = false;
    while (!stop && cursor!=nullptr)
    {
        if(eq(k, cursor->key))
        {
            return true;
        }
        if (rule(k, cursor->key))
            if (cursor->left != nullptr)
                cursor = cursor->left;
            else
            {
                stop = true;
            }
            else
                if (cursor->right != nullptr)
                    cursor = cursor->right;
                else
                {
                    stop = true;
                }
    }
    return false;
}

template <class K, class T>
void tree<K, T>::insert(K k, T d)
{
    Node* cursor = root;
    if (intree(k))
    {
        return;
    }
    bool stop = false;
    while (!stop)
    {
        if (rule(k, cursor->key))
            if (cursor->left != nullptr)
                cursor = cursor->left;
            else
            {
                cursor->left = new Node(k, d);
                stop = true;
            }
            else
                if (cursor->right != nullptr)
                    cursor = cursor->right;
                else
                {
                    cursor->right = new Node(k, d);
                    stop = true;
                }
    }
}

template<class K, class T>
T tree<K,T>::search(K k)
{
    if(intree(k))
    {
        Node* cursor = root;
        bool stop = false;
        while (!stop && cursor!=nullptr)
        {
            if(eq(k, cursor->key))
            {
                return cursor->data;
            }
            if (rule(k, cursor->key))
                if (cursor->left != nullptr)
                    cursor = cursor->left;
                else
                {
                    stop = true;
                }
                else
                    if (cursor->right != nullptr)
                        cursor = cursor->right;
                    else
                    {
                        stop = true;
                    }
        }
    }
    else
        
}
