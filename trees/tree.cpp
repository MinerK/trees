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

template<class K, class T>
typename tree<K, T>::Node * tree<K, T>::locate(K k, Node* t)
{
    while (t != nullptr && !eq(k, t->key))
        if (rule(t->key, k))
            t = t->right;
        else
            t = t->left;
    return t;
}




template <class K, class T>
void tree<K, T>::insert(K k, T d)
{
    bool h = root == nullptr;
    insert(k, d, root, h);
}

template<class K, class T>
void tree<K, T>::insert(K k, T d, Node *& p, bool & h)
{
    if (p == nullptr)
    {
        p = new Node(k, d);
        h = true;
    }
    else
    {
        if (rule(k, p->key))
        {
            insert(k, d, p->left, h);
            if (h)
            {
                switch (p->balance)
                {
                    case 1:
                        p->balance = 0;
                        h = false;
                        break;
                    case 0:
                        p->balance = -1;
                        break;
                    case -1:
                        Node* p1 = p->left;
                        if (p1->balance == -1)
                        {
                            p->balance = 0;
                            LL(p, p1);
                            p=p1;
                        }
                        else
                        {
                            Node* p2 = p1->right;
                            RR(p2, p1);
                            LL(p,p1);
                            p=p2;
                        }
                        p->balance = 0;
                        h = false;
                        break;
                }
            }
        }
        else
        {
            if (rule(p->key,k))
            {
                insert(k, d, p->right, h);
                if (h)
                {
                    switch (p->balance)
                    {
                        case -1:
                            p->balance = 0;
                            h = false;
                            break;
                        case 0:
                            p->balance = 1;
                            break;
                        case 1:
                            Node* p1 = p->right;
                            if (p1->balance==1)
                            {
                                p->balance = 0;
                                RR(p, p1);
                                p=p1;
                            }
                            else
                            {
                                Node* p2 = p1->left;
                                LL(p2,p1);
                                RR(p, p1);
                                if (p2->balance == 1)
                                    p->balance = -1;
                                else
                                    p->balance = 0;
                                if (p2->balance == -1)
                                    p1->balance = 1;
                                else
                                    p1->balance = 0;
                                p = p2;
                            }
                            p->balance = 0;
                            h = false;
                            break;
                    }
                }
            }
        }
    }
}

template<class K, class T>
T tree<K,T>::search(K k)
{
    Node* node = locate(k, root);
    if (node != nullptr)
        return node;
    else
        throw "not found";
    
}

template<class K, class T>
void tree<K, T>::traverse(void(*f)(K k, T d))
{
    _traverse(root, f);
}

template<class K, class T>
void tree<K, T>::traverse(void(*f)(Node *))
{
    _traverse(root, f);
}

template<class K, class T>
void tree<K, T>::_traverse(Node *p, void(*f)(K k, T d))
{
    if (p==nullptr)
    {
        return;
    }
    _traverse(p->left, f);
    f(p->key, p->data);
    _traverse(p->right, f);
}

template<class K, class T>
void tree<K, T>::_traverse(Node* node, void(*f)(Node *))
{
    if (node==nullptr)
        return;
    _traverse(node->left, f);
    f(node);
    _traverse(node->right, f);
}


template<class K, class T>
unsigned int tree<K, T>::height(Node *target)
{
    if (target==nullptr)
    {
        return 0;
    }
    unsigned int l = 0;
    unsigned int r = 0;
    
    if (target->left != nullptr)
        l = height(target->left);
    
    if (target->right != nullptr)
        r = height(target->right);
    
    if (l < r)
        return r+1;
    else
        return l+1;
}

template<class K, class T>
void tree<K, T>::printinfo()
{
    traverse([](Node* s) {std::cout << s->key << " : " << s->data << "; " << s->balance << std::endl; });
}

template <class K, class T>
void tree<K, T>::LL(Node*& p, Node *& p1)
{
    p->left = p1->right;
    p1->right = p;
}

template <class K, class T>
void tree<K, T>::RR(Node*& p, Node *& p1)
{
    p->right = p1->left;
    p1->left = p;
}

template <class K, class T>
void tree<K, T>::BalanceL(Node*& p, bool& h)
{
    switch(p->balance)
    {
        case -1:
            p->balance = 0;
            break;
        case 0:
            p->balance=1;
            h=false;
            break;
        case 1:
            Node* p1 = p->right;
            short int b1 = p1->balance;
            if (b1 >= 0)
            {
                RR(p, p1);
                if (b1==0)
                {
                    p->balance=1;
                    p1->balance=-1;
                    h=false;
                }
                else
                {
                    p->balance = 0;
                    p1->balance = 0;
                }
                p = p1;
            }
            else
            {
                Node* p2 = p1->left;
                short b2 = p2->balance;
                LL(p1,p2);
                RR(p, p2);
                if (b2 == 1)
                    p->balance = -1;
                else
                    p->balance = 0;
                if (b2 == -1)
                    p1->balance = 1;
                else
                    p1->balance = 0;
                p=p2;
                p2->balance = 0;
            }
            break;
    }
}

template <class K, class T>
void tree<K, T>::BalanceR(Node*& p, bool& h)
{
    switch(p->balance)
    {
        case 1:
            p->balance = 0;
            break;
        case 0:
            p->balance=-1;
            h=false;
            break;
        case -1:
            Node* p1 = p->left;
            short int b1 = p1->balance;
            if (b1 >= 0)
            {
                LL(p, p1);
                if (b1==0)
                {
                    p->balance=-1;
                    p1->balance=1;
                    h=false;
                }
                else
                {
                    p->balance = 0;
                    p1->balance = 0;
                }
                p = p1;
            }
            else
            {
                Node* p2 = p1->right;
                short b2 = p2->balance;
                RR(p1,p2);
                LL(p, p2);
                if (b2 == -1)
                    p->balance = 1;
                else
                    p->balance = 0;
                if (b2 == 1)
                    p1->balance = -1;
                else
                    p1->balance = 0;
                p=p2;
                p2->balance = 0;
            }
            break;
    }
}

template<class K, class T>
void tree<K,T>::del(<#tree::Node *&#> r, <#bool &#> h)
{
    if (r->right)
    {
        del(r->right, h);
        if (h)
            balanceR(r,h);
    }
    else

}

template<class K, class T>
void tree<K,T>::Remove(K k)
{
    bool h=false;
    _delete(k, root, h);
}

